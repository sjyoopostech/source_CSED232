using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MainInventory : MonoBehaviour
{

    // 전체 클래스에 정의된 teamID와 studentID를 가져온다.
    public int team_ID;
    public int student_ID;

    // 게임오브젝트 UNITY와 연동
    public GameObject ItemPanel; // 전제 아이템 탭과 입력 창에 해당하는 패널
    public GameObject QuizPanel; // 전체 퀴즈 탭과 입력 창에 해당하는 패널
    public GameObject inventorySlot; // 정의된 아이템 슬롯 프리팹
    public GameObject quizinventorySlot; // 정의된 퀴즈 슬롯 프리팹
    public GameObject inventoryItem; // 정의된 아이템 슬롯-아이템 프리팹
    public GameObject quizinventoryItem; // 정의된 퀴즈 슬롯-아이템 프리팹
    public GameObject panel; // Quiz의 정답 입력 패널
    public GameObject AnswerPanel; // 정답 여부와 아이템 사용 여부를 출력해 주는 패널
    public Text quizanswer; // 퀴즈 inputfield에서 받아오는 입력창
    public Button quizsubmit; // 퀴즈 inputfield 값을 제출하는 버튼
    public Button itemsubmit; // 아이템을 제출하는 버튼
    public Button gethint; // 힌트를 받아오는 버튼
    public Text ItemComment; // 아이템의 설명을 출력해주는 패널
    public Text QuizComment; // 퀴즈 내용과 힌트를 출력해주는 패널
    public Button QuizTab; // 퀴즈 패널로 전환하는 탭 버튼
    public Button ItemTab; // 아이템 패널로 전환하는 탭 버튼

    // 하위 게임오브젝트를 받기 위한 보조적인 오브젝트
    GameObject inventoryPanel;
    GameObject QuizinventoryPanel;
    GameObject slotPanel;
    GameObject QuizslotPanel;

    // 데이터베이스 구축 관련 변수
    int slotAmount;
    int quizslotAmount;
    ItemDatabase database;
    QuizDatabase quizdatabase;
    public List<Items> itemlists = new List<Items>();
    public List<Quizes> quizlists = new List<Quizes>();
    // 프리팹을 복사하여 저장하는 리스트
    public List<GameObject> slots = new List<GameObject>();
    public List<GameObject> quizslots = new List<GameObject>();
    // 기타 사용할 전역 변수들
    int[] iID_array;
    int[] item_ID_array;
    int[] qID_array;
    int[] quiz_ID_array;
    int[] hint_array;
    public string ID;
    public string item_ID;
    public string quiz_ID;
    public string hint;
    int studentitem_num;
    int teamitem_num;
    int teamquiz_num;
    string[] studentitem;
    string[] teamitem;
    string[] teamquiz;

    IEnumerator receive()  // 처음에 가지고 있는 팀별 퀴즈, 아이템, 학생별 아이템 정보를 불러오는 함수
    {
        // 해당 url에 studentID와 teamID 제출하고 정보 불러오기
        string url1 = "http://141.223.163.207:3001/inventory-studentitem?ID=" + student_ID.ToString();
        string url2 = "http://141.223.163.207:3001/inventory-teamitem?ID=" + team_ID.ToString();
        string url3 = "http://141.223.163.207:3001/inventory-teamquiz?ID=" + team_ID.ToString();
        WWW studentitem_www = new WWW(url1);
        WWW teamitem_www = new WWW(url2);
        WWW teamquiz_www = new WWW(url3);

        // 모든 링크에서 받아올 때까지 기다리기
        while (true)
        {
            yield return new WaitForSeconds(.1f);
            if (studentitem_www.isDone && teamitem_www.isDone && teamquiz_www.isDone) break;
        }

        // html를 string type으로 추출
        string studentitem_text = studentitem_www.text;
        string teamitem_text = teamitem_www.text;
        string teamquiz_text = teamquiz_www.text;

        // 전체 string을 한 아이템/퀴즈 단위로 끊어서 string[]에 저장
        string[] separatingChars1 = { "[{", "},{", "}]" };
        string ss1 = studentitem_www.text;
        studentitem = ss1.Split(separatingChars1, System.StringSplitOptions.RemoveEmptyEntries);
        string[] separatingChars2 = { "[{", "},{", "}]" };
        string ss2 = teamitem_www.text;
        teamitem = ss2.Split(separatingChars2, System.StringSplitOptions.RemoveEmptyEntries);
        string[] separatingChars3 = { "[{", "},{", "}]" };
        string ss3 = teamquiz_www.text;
        teamquiz = ss3.Split(separatingChars3, System.StringSplitOptions.RemoveEmptyEntries);

        // 각 변수 초기화 후 각 string 배열의 원소의 개수로 체크
        studentitem_num = 0;
        teamitem_num = 0;
        teamquiz_num = 0;
        foreach (string s in studentitem) studentitem_num++;
        foreach (string s in teamitem) teamitem_num++;
        foreach (string s in teamquiz) teamquiz_num++;

        // 원소의 개수가 0인 경우 에러 처리
        if (ss1 != "[]") readitem(0, studentitem_num, studentitem);
        else studentitem_num = 0;
        if (ss2 != "[]") readitem(studentitem_num, studentitem_num + teamitem_num, teamitem);
        else teamitem_num = 0;
        if (ss3 != "[]") readquiz(0, teamquiz_num, teamquiz);
        else teamquiz_num = 0;

        /* AddItem/ AddQuiz 함수 호출하여 전역변수 배열의 아이디 값을 넣어 아이템/퀴즈 리스트에 로드하기
         * 아이템/퀴즈 프리팹을 복사하여 slots/quizslots 오브젝트들에 하위 오브젝트로 추가
         * 전역변수의 변경은 AddItem/AddQuiz 함수 안에 포함되어 있음
         */
        for (int i = 0; i < studentitem_num + teamitem_num; i++) AddItem(item_ID_array[i]);
        for (int i = 0; i < teamquiz_num; i++) AddQuiz(quiz_ID_array[i]);
    }

    public void RemoveItem() // 초기화 시 기존에 생성된 Item 프리팹과 Slot 프리팹들을 삭제하여 주는 함수
    {
        int k = studentitem_num + teamitem_num;
        for (int j = 0; j < k; j++)
        {
            Destroy(slots[j].transform.Find("Item(Clone)").gameObject);
        }
        for (int j = 0; j < slotAmount; j++)
        {
            Destroy(slots[j]);
        }
    }

    public void RemoveQuiz() // 초기화 시 기존에 생성된 quizItem 프리팹과 quizSlot 프리팹들을 삭제하여 주는 함수
    {
        int k = teamquiz_num;
        for (int j = 0; j < k; j++)
        {
            Destroy(quizslots[j].transform.Find("quizItem(Clone)").gameObject);
        }
        for (int j = 0; j < quizslotAmount; j++)
        {
            Destroy(quizslots[j]);
        }
    }

    IEnumerator isJuhang() // 저항이가 활성 상태인지를 체크하여 주는 함수
    {
        string url1 = "http://141.223.163.207:3001/inventory-juhang?team_ID=" + team_ID.ToString();
        WWW juhang_www = new WWW(url1);
        while (true)
        {
            yield return new WaitForSeconds(.1f);
            if (juhang_www.isDone) break;
        }

        string checkuse = juhang_www.text;
        Debug.Log(checkuse);
        if (checkuse == "juhang") panel.SetActive(false); // 저항이가 활성화 상태일 경우 quizsubmit 버튼을 비활성화
        else if (checkuse == "free") panel.SetActive(true); // 저항이가 비활성화 상태일 경우 quizsubmit 버튼을 활성화
        yield return new WaitForSeconds(2); //2초 마다 정보 업데이트
        StartCoroutine(isJuhang());
    }

    IEnumerator CheckUse(int i, int ishint) // 사용하고 싶은 아이템을 서버에 제출하고 아이템 목록을 업데이트하여 주는 함수
    {
        string url1 = "http://141.223.163.207:3001/inventory-useitem?ID=" + iID_array[i].ToString() + "&item_ID=" + item_ID_array[i].ToString() + "&team_ID=" + team_ID.ToString() + "&student_ID=" + student_ID.ToString();
        WWW checkuse_www = new WWW(url1);

        while (true)
        {
            yield return new WaitForSeconds(.1f);
            if (checkuse_www.isDone) break;
        }

        string checkuse = checkuse_www.text;

        if (checkuse == "fail") // 아이템을 사용할 수 없는 경우 해당 메세지를 2초간 띄우고 종료
        {
            AnswerPanel.SetActive(true);
            AnswerPanel.GetComponentInChildren<Text>().text = "사용할 수 없는 아이템입니다.";
            while (true)
            {
                yield return new WaitForSeconds(2);
                break;
            }
            AnswerPanel.SetActive(false);
        }
        else if (checkuse == "success" && ishint == 0) // 아이템을 사용할 수 있는 경우 해당 메세지를 띄우고 reload
        {
            AnswerPanel.SetActive(true);
            AnswerPanel.GetComponentInChildren<Text>().text = "아이템을 사용하였습니다.";
            while (true)
            {
                yield return new WaitForSeconds(2);
                break;
            }
            AnswerPanel.SetActive(false);

            slot_remake(1);
        }
        else if (checkuse == "success" && ishint == 1)
        {
            AnswerPanel.SetActive(true);
            AnswerPanel.GetComponentInChildren<Text>().text = "힌트를 사용하였습니다.";
            while (true)
            {
                yield return new WaitForSeconds(2);
                break;
            }
            AnswerPanel.SetActive(false);

            slot_remake(1);
        }
    }

    IEnumerator CheckAnswer(int i) // 퀴즈의 답을 서버에 제출하고 퀴즈 목록을 업데이트하여 주는 함수
    {
        string url1 = "http://141.223.163.207:3001/inventory-usequiz?ID=" + qID_array[i].ToString() + "&quiz_ID=" + quiz_ID_array[i].ToString() + "&team_ID=" + team_ID.ToString() + "&answer=%27" + quizanswer.GetComponent<Text>().text + "%27";
        WWW checkanswer_www = new WWW(url1);
        while (true)
        {
            yield return new WaitForSeconds(.1f);
            if (checkanswer_www.isDone) break;
        }
        string checkanswer = checkanswer_www.text;

        if (checkanswer == "error 0 : incorrect") // 정답이 아닌 경우 해당 메세지를 2초간 띄우고 종료
        {
            AnswerPanel.SetActive(true);
            AnswerPanel.GetComponentInChildren<Text>().text = "정답이 아닙니다!";
            while (true)
            {
                yield return new WaitForSeconds(2);
                break;
            }
            quizanswer.text = "";
            AnswerPanel.SetActive(false);
        }
        else if (checkanswer == "success") // 정답인 경우 해당 메세지를 2초간 띄운 후 slot_remake 함수를 호출하여 슬롯 업데이트
        {
            AnswerPanel.SetActive(true);
            AnswerPanel.GetComponentInChildren<Text>().text = "정답입니다!";
            while (true)
            {
                yield return new WaitForSeconds(2);
                break;
            }
            quizanswer.text = "";
            AnswerPanel.SetActive(false);
            slot_remake(1);
        }
    }

    IEnumerator usehint(int i) // 힌트 vaild 값을 변경하도록 서버에 요청하는 함수
    {
        string url1 = "http://141.223.163.207:3001/inventory-usehint?ID=" + qID_array[i].ToString();
        WWW checkhint_www = new WWW(url1);
        while (true)
        {
            yield return new WaitForSeconds(.1f);
            if (checkhint_www.isDone) break;
        }
    }

    public void readitem(int start, int end, string[] s) // 스트링 단위 input을 입력 받을 수 있는 값으로 끊어서 초기화한 변수에 넣어 주는 함수
    {
        for (int i = start; i < end; i++)
        {
            ID = null;
            item_ID = null;
            int jID = s[i - start].IndexOf("\"ID\"");
            int jitem_ID = s[i - start].IndexOf("\"item_ID\"");
            if (jitem_ID > 0)
            {
                ID = s[i - start].Substring(jID + 5, jitem_ID - jID - 6);
                item_ID = s[i - start].Substring(jitem_ID + 10, s[i - start].Length - jitem_ID - 10);
            }
            // 전역변수에 고유 ID 및 itemID 저장
            iID_array[i] = Int32.Parse(ID);
            item_ID_array[i] = Int32.Parse(item_ID);
        }
    }

    public void readquiz(int start, int end, string[] s) // 스트링 단위 input을 입력 받을 수 있는 값으로 끊어서 초기화한 변수에 넣어 주는 함수
    {
        for (int i = start; i < end; i++)
        {
            ID = null;
            quiz_ID = null;
            hint = null;
            int jID = s[i - start].IndexOf("\"ID\"");
            int jquiz_ID = s[i - start].IndexOf("\"quiz_ID\"");
            int jhint = s[i - start].IndexOf("\"hint\"");
            if (jquiz_ID > 0)
            {
                ID = s[i - start].Substring(jID + 5, jquiz_ID - jID - 6);
                quiz_ID = s[i - start].Substring(jquiz_ID + 10, jhint - jquiz_ID - 11);
                hint = s[i - start].Substring(jhint + 7, s[i - start].Length - jhint - 7);
            }
            // 전역변수에 고유 id, quiz_ID, 힌트 vaild 저장
            qID_array[i] = Int32.Parse(ID);
            quiz_ID_array[i] = Int32.Parse(quiz_ID);
            hint_array[i] = Int32.Parse(hint); // 0 or 1
        }
    }

    void AddonClickItem(int i) // Listener를 통해 slots 버튼 클릭을 입력 받는 함수
    {
        slots[i].GetComponentInChildren<Button>().onClick.RemoveAllListeners();
        slots[i].GetComponentInChildren<Button>().onClick.AddListener(() => LoadItemComment(i));
    }

    void AddonClickQuiz(int i) // Listener를 통해 quizslots 버튼 클릭을 입력 받는 함수
    {
        quizslots[i].GetComponentInChildren<Button>().onClick.RemoveAllListeners();
        quizslots[i].GetComponentInChildren<Button>().onClick.AddListener(() => LoadQuizComment(i));
    }

    void LoadItemComment(int i) // 아이템의 설명을 화면에 출력해 주는 함수
    {
        if (itemlists[i].Title == "None") ItemComment.text = "";
        else ItemComment.text = itemlists[i].Title + "\n" + itemlists[i].Comment;
        itemsubmit.onClick.RemoveAllListeners();
        itemsubmit.onClick.AddListener(() => StartCoroutine(CheckUse(i, 0))); // 아이템 사용을 체크하기 위해 CheckUse 함수를 호출

    }

    void LoadQuizComment(int i) // 퀴즈 내용과 힌트를 화면에 출력해 주는 함수
    {
        // 힌트 사용 가능 여부를 받아서 화면에 힌트를 함께 출력할지 아닐지를 결정
        if (quizlists[i].Name == "None") QuizComment.text = "";
        else QuizComment.text = quizlists[i].Name + "(분야:" + quizlists[i].Field + ")\n " + quizlists[i].Question;
        if (hint_array[i] == 1) QuizComment.text = QuizComment.text + "\n힌트 : " + quizlists[i].Hint;
        gethint.onClick.RemoveAllListeners();
        gethint.onClick.AddListener(() => hintbutton(i)); // 힌트 버튼 클릭 시에 hintbutton 함수를 호출
        quizsubmit.onClick.RemoveAllListeners();
        quizsubmit.onClick.AddListener(() => StartCoroutine(CheckAnswer(i))); // 퀴즈 답을 체크하기 위해 CheckAnswer 함수를 호출
    }

    public void hintbutton(int i) // 힌트 버튼 클릭 시에 사용하는 함수
    {
        int hintitem = -1; // 사용할 수 없는 값으로 초기화
        // 퀴즈 아이디에 따라 가능한 힌트 아이템을 매칭(비커, 빵판, 공학용 계산기, 연필)
        if (quizlists[i].Field == "화학" || quizlists[i].Field == "화공" || quizlists[i].Field == "생명") hintitem = 4;
        else if (quizlists[i].Field == "전자" || quizlists[i].Field == "컴공") hintitem = 5;
        else if (quizlists[i].Field == "물리" || quizlists[i].Field == "기계" || quizlists[i].Field == "소재") hintitem = 9;
        else if (quizlists[i].Field == "수학" || quizlists[i].Field == "산경") hintitem = 11;
        // 위의 경우에 대해서 힌트 버튼 인풋을 체크
        for (int j = 0; j < studentitem_num + teamitem_num; j++)
        {
            if (item_ID_array[j] == hintitem)
            {
                StartCoroutine(CheckUse(j, 1));
                StartCoroutine(usehint(i));
                return;
            }
        }
        int check = -1;
        for (int j = 0; j < studentitem_num + teamitem_num; j++)
        {
            if (item_ID_array[j] == 1) // 현재 가지고 있는 아이템에 데자와가 있는지 체크
            {
                if (check == -1) check = j; // 데자와가 하나도 없을 때
                else // 데자와가 하나 있는 경우
                {
                    StartCoroutine(CheckUse(check, 2)); // 기존의 하나를 사용
                    StartCoroutine(CheckUse(j, 1)); // 새로 먹은 하나를 사용
                    StartCoroutine(usehint(i)); // 힌트를 사용
                    return;
                }
            }
        }
    }

    public void AddItem(int ID_info)    // 아이템의 고유 식별 아이디 값(item_ID)을 넣어 아이템 리스트에 로드하고 아이템 프리팹을 복사하여 하위 오브젝트로 생성하는 함수
    {
        Items itemtoAdd = database.FetchItemByID(ID_info); // 데이터베이스에서 ID로 아이템을 불러오기
        for (int i = 0; i < slotAmount; i++)
        {
            if (itemlists[i].Title == "None") // 아이템 리스트 중 빈 오브젝트가 들어 있는 리스트 자리에 새로운 아이템을 추가
            {
                itemlists[i] = itemtoAdd;
                itemlists[i].Id = iID_array[i];
                GameObject itemObj = Instantiate(inventoryItem); // 인벤토리 아이템 프리팹을 복사하여 새로운 아이템 오브젝트에 넣기
                itemObj.transform.SetParent(slots[i].transform); // 새로 생성한 오브젝트의 부모 오브젝트를 slots[i]로 설정
                itemObj.transform.position = slots[i].transform.position; // 부모 오브젝트와 자식 오브젝트의 위치 설정을 동기화
                itemObj.GetComponent<Image>().sprite = itemtoAdd.Sprite; // 새로 생성한 오브젝트 안의 이미지를 아이템에서 로드한 이미지로 설정
                break;
            }
        }
    }

    public void AddQuiz(int ID_info) // 퀴즈의 고유 식별 아이디 값(quiz_ID)을 넣어 퀴즈 리스트에 로드하고 퀴즈 프리팹을 복사하여 하위 오브젝트로 생성하는 함수
    {
        Quizes quiztoAdd = quizdatabase.FetchQuizByID(ID_info); // 퀴즈데이터베이스에서 ID로 퀴즈을 불러오기
        for (int i = 0; i < quizslotAmount; i++)
        {
            if (quizlists[i].Name == "None") // 퀴즈 리스트 중 빈 오브젝트가 들어 있는 리스트 자리에 새로운 퀴즈를 추가
            {
                quizlists[i] = quiztoAdd;
                quizlists[i].Id = qID_array[i];
                GameObject quizObj = Instantiate(quizinventoryItem); // 인벤토리 아이템 프리팹을 복사하여 새로운 아이템 오브젝트에 넣기
                quizObj.transform.SetParent(quizslots[i].transform); // 새로 생성한 오브젝트의 부모 오브젝트를 quizslots[i]로 설정
                quizObj.transform.position = quizslots[i].transform.position; // 부모 오브젝트와 자식 오브젝트의 위치 설정을 동기화
                quizObj.GetComponent<Image>().sprite = Resources.Load<Sprite>("퀴즈"); // 새로 생성한 오브젝트 안의 이미지를 퀴즈 이미지로 설정
                break;
            }
        }
    }

    public void slot_remake(int state) // 리스트 데이터 초기화 및 슬롯과 아이템 리스트 reload
    {
        if (state == 1) // 처음 호출한 경우가 아닌 경우 기존의 슬롯에 들어가 있는 리스트 오브젝트와 리스트와 슬롯들을 모두 초기화
        {
            RemoveItem();
            RemoveQuiz();
            itemlists.Clear();
            slots.Clear();
            quizlists.Clear();
            quizslots.Clear();
        }
        // 전역변수로 설정되어 있는 행렬들을 모두 초기화
        for (int i = 0; i < slotAmount; i++)
        {
            iID_array[i] = 0;
            item_ID_array[i] = 0;
        }
        for (int i = 0; i < quizslotAmount; i++)
        {
            qID_array[i] = 0;
            quiz_ID_array[i] = 0;
            hint_array[i] = 0;
        }
        // 새로운 슬롯을 프리팹을 복사하여 생성
        for (int i = 0; i < slotAmount; i++)
        {
            itemlists.Add(new Items());
            slots.Add(Instantiate(inventorySlot));
            slots[i].transform.SetParent(slotPanel.transform);
        }
        // 새로운 퀴즈 슬롯을 프리팹을 복사하여 생성
        for (int i = 0; i < quizslotAmount; i++)
        {
            quizlists.Add(new Quizes());
            quizslots.Add(Instantiate(quizinventorySlot));
            quizslots[i].transform.SetParent(QuizslotPanel.transform);
        }
        StartCoroutine(receive()); // receive 함수 호출
        // 슬롯의 아이템과 퀴즈 클릭 입력 받기
        for (int i = 0; i < slotAmount; i++) AddonClickItem(i);
        for (int i = 0; i < quizslotAmount; i++) AddonClickQuiz(i);
    }

    private void Start()
    {
        // 설정된 teamID와 studentID를 불러오는 함수
        team_ID = idInformation.teamID;
        student_ID = idInformation.studentID;
        // 아이템과 퀴즈를 데이터베이스로부터 로드
        database = GetComponent<ItemDatabase>();
        quizdatabase = GetComponent<QuizDatabase>();
        // 퀴즈, 아이템 슬롯 개수를 30개로 설정
        slotAmount = 30;
        quizslotAmount = 30;
        // 각 게임오브젝트들을 찾아서 매칭
        ItemPanel = GameObject.Find("Item Panel");
        QuizPanel = GameObject.Find("Quiz Panel");
        inventoryPanel = ItemPanel.transform.Find("Inventory Panel").gameObject;
        QuizinventoryPanel = QuizPanel.transform.Find("Inventory Panel").gameObject;
        slotPanel = inventoryPanel.transform.Find("Slot Panel").gameObject;
        QuizslotPanel = QuizinventoryPanel.transform.Find("Slot Panel").gameObject;
        // 전역변수로 정의되어 있는 행렬들 동적할당
        iID_array = new int[slotAmount];
        item_ID_array = new int[slotAmount];
        qID_array = new int[quizslotAmount];
        quiz_ID_array = new int[quizslotAmount];
        hint_array = new int[quizslotAmount];
        // 초기화 및 슬롯 만들기
        slot_remake(0);
        QuizPanel.SetActive(false);
        ItemPanel.SetActive(true);
        AnswerPanel.SetActive(false);
        // 패널 전환 탭 버튼 입력 받기
        QuizTab.onClick.AddListener(() => QuizTabClicked());
        ItemTab.onClick.AddListener(() => ItemTabClicked());
        StartCoroutine(isJuhang()); // 저항이의 상태를 체크
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) // 뒤로가기 버튼 함수
        {
            SceneManager.LoadScene("main");
        }
    }

    public void QuizTabClicked() // 퀴즈 패널 버튼 클릭 시 판넬 활성을 바꾸어 주는 함수
    {
        QuizPanel.SetActive(true);
        ItemPanel.SetActive(false);
    }
    public void ItemTabClicked() // 아이템 패널 버튼 클릭 시 판넬 활성을 바꾸어 주는 함수
    {
        QuizPanel.SetActive(false);
        ItemPanel.SetActive(true);
    }

}

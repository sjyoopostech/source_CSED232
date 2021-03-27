using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class findidpwScript : MonoBehaviour
{

    // ID 찾기 부분
    public string Name_input;
    // ID 찾기 시 입력받은 이름
    public string Teamname_input;
    // ID 찾기 시 입력받은 팀 이름

    // PW 찾기 부분
    public string ID_input;
    // PW 찾기 시 입력받은 ID
    public string HintPW_Question_input;
    // PW 찾기 시 입력받은 비밀번호 찾기 질문
    public string HintPW_Answer_input;
    // PW 찾기 시 입력받은 비밀번호 찾기 답

    private string returned1;
    // 서버로 부터 받은 ID 찾기의 결과 정보
    private string returned2;
    // 서버로 부터 받은 PW 찾기의 결과 정보

    private string ID_found;
    // 위의 returned1 정보 중 ID에 해당하는 string(ID를 찾은 경우)
    private string PW_found;
    // 위의 returned2 정보 중 PW에 해당하는 string(PW를 찾은 경우)

    public Text ID_show;
    // 찾은 ID를 팝업창에 띄우기 위해 필요한 Text 형 변수
    public Text PW_show;
    // 찾은 PW를 팝업창에 띄우기 위해 필요한 Text 형 변수

    public GameObject Panel_TeamName;
    // ID 찾기 시 팀이름이 존재하지 않는 경우를 알려주는 팝업창
    public GameObject Panel_Name;
    // ID 찾기 시 이름이 존재하니 않는 경우를 알려주는 팝업창
    public GameObject Panel_ID_Found;
    // ID 찾기 성공을 알려주는 팝업창

    public GameObject Panel_PWerror;
    // PW 찾기 시 입력이 잘못됨을 알려주는 팝업창
    public GameObject Panel_PW_Found;
    // PW 찾기 성공을 알려주는 팝업창


    void Start()
    {
        Panel_TeamName.SetActive(false);
        Panel_Name.SetActive(false);
        Panel_ID_Found.SetActive(false);
        // 화면 시작과 동시에 모든 ID 팝업창들을 Off

        Panel_PWerror.SetActive(false);
        Panel_PW_Found.SetActive(false);
        // 화면 시작과 동시에 모은 PW 팝업창들을 Off

        ID_show.text = "";
        PW_show.text = "";
        // text들을 초기화
    }


    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Escape)) // Android 환경에서 뒤로 가기 버튼을 누른 경우
        {
            SceneManager.LoadScene("login");
        }
    }

    public void get_signupName(string Name_guess) // ID 찾기에서 이름 inputfield 의 정보를 읽는 함수
    {
        Name_input = Name_guess;
    }
    public void get_signupTeamname(string Teamname_guess) // ID 찾기에서 팀 이름 inputfield의 정보를 읽는 함수
    {
        Teamname_input = Teamname_guess;
    }

    public void get_signupID(string ID_guess) // PW 찾기에서 ID inputfield 의 정보를 읽는 함수
    {
        ID_input = ID_guess;
    }
    public void get_signupQuestionForHint(string Question_guess) // PW 찾기에서 비밀번호 찾기 질문 inputfield 의 정보를 읽는 함수
    {
        HintPW_Question_input = Question_guess;
    }
    public void get_signupAnswerForHint(string Answer_guess) // PW 찾기에서 비밀번호 찾기 답 inputfield의 정보를 읽는 함수
    {
        HintPW_Answer_input = Answer_guess;
    }

    public void click_button_findID() // ID 찾기 버튼
    {
        string url1 = "http://141.223.163.207:3001/findidpw-id?team_name='" + Teamname_input + "'&name='" + Name_input + "'";
        // 서버로 입력 정보들을 전송
        WWW www1 = new WWW(url1);
        StartCoroutine(WaitForRequest1(www1));
    }
    IEnumerator WaitForRequest1(WWW www)
    {
        yield return www;
        //서버로부터 ID 찾기 결과를 한번 읽음(yield return)
        returned1 = www.text;
        // 위 정보의 text 부분만 string 으로 저장

        if (returned1 == "error 0: no such team name")
        // 팀 이름이 없는 경우
        {
            Panel_TeamName.SetActive(true);
            //해당 팝업창을 active
            Debug.Log("There is no such team name");
        }
        else if (returned1 == "[]")
        // 이름이 없는 경우
        {
            Panel_Name.SetActive(true);
            //해당 팝업창을 active
            Debug.Log("There is no such student name");
        }
        else
        // ID 찾기에 성공한 경우
        {
            ID_found = returned1.Substring(returned1.IndexOf(':') + 2, returned1.IndexOf('}') - returned1.IndexOf(':') - 3);
            // returned1에 저장된 정보를 잘라서 ID 부분만 저장함

            ID_show.text = "Your ID is " + ID_found;
            // 출력할 형식에 맞게 text를 저장함
            Panel_ID_Found.SetActive(true);
            // 해당 팝업창을 active

            Debug.Log("Your ID is " + ID_found);
        }
    }

    public void click_button_findPW() //PW 찾기 버튼
    {
        string url2 = "http://141.223.163.207:3001/findidpw-pw?ID='" + ID_input + "'&pw_find_question='" + HintPW_Question_input + "'&pw_find_answer='" + HintPW_Answer_input + "'";
        // 서버로 필요한 정보들을 전송
        WWW www2 = new WWW(url2);
        StartCoroutine(WaitForRequest2(www2));
    }
    IEnumerator WaitForRequest2(WWW www)
    {
        yield return www;
        // 서버로부터 PW 찾기 결과를 한번 읽어들임(yield return)
        returned2 = www.text;
        // 읽은 정보의 text 부분만 string으로 저장함

        if (returned2 == "[]")
        // 입력이 잘못된 경우
        {
            Panel_PWerror.SetActive(true);
            // 해당 팝업창을 active
            Debug.Log("Incorrect Input");
        }
        else
        // PW 찾기에 성공한 경우
        {
            PW_found = returned2.Substring(returned2.IndexOf(':') + 2, returned2.IndexOf('}') - returned2.IndexOf(':') - 3);
            // returned2에 저장된 가공되지 않는 text 중에서 PW에 해당하는 부분만 골라 저장
            PW_show.text = "Your Password is " + PW_found;
            // 출력할 형식에 맞게 text 저장
            Panel_PW_Found.SetActive(true);
            // 해당 팝업창을 active

            Debug.Log("Your Password is " + PW_found);
        }



        //Debug.Log(www.text);
    }
    public void click_button_login() // login 화면으로 넘어가는 버튼
    {
        SceneManager.LoadScene("login");
    }

    public void click_button_back_TeamName() // 팀이름이 없는 경우의 팝업창의 뒤로가기 버튼
    {
        Panel_TeamName.SetActive(false);
    }
    public void click_button_back_Name() // 이름이 없는 경우의 팝업창의 뒤로가기 버튼
    {
        Panel_Name.SetActive(false);
    }
    public void click_button_back_ID_Found() // ID 찾기 성공시의 팝업창의 뒤로가기 버튼
    {
        Panel_ID_Found.SetActive(false);
    }
    public void click_button_back_PW_error() // PW 찾기 실패시 팝업창의 뒤로가기 버튼
    {
        Panel_PWerror.SetActive(false);
    }
    public void click_button_back_PW_Found() // PW 찾기 성공시의 팝업창의 뒤로가기 버튼
    {
        Panel_PW_Found.SetActive(false);
    }
}


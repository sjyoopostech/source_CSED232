using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//유저의 이미지를 Resources 폴더에서 찾아서 출력하는 스크립트
//유저의 이미지는 기본 이미지가 user_ponix.png 로 저장되어 있다
//착용 중인 아이템이 없을 때는 이 기본 이미지가 출력됨
//아이템을 착용하면, 해당 아이템을 착용한 user_ponix_(아이템 이름).png 로 저장된 이미지가 출력된다

public class userImg : MonoBehaviour
{

    public Image image;
    int student_ID = idInformation.studentID;
    string imgName = "user_ponix"; //기본 이미지 파일 이름
    public StudentList students = new StudentList();
    // Use this for initialization

    //학생의 정보가 저장된 서버에서 학생의 정보를 받아와서
    //학생의 아이템 착용 여부에 따라 이미지의 이름을 수정해서
    //해당 이미지를 표시해주는 함수
    IEnumerator Get_img()
    {
        string studentID = student_ID.ToString();
        string url = "http://141.223.163.207:3001/user-student?ID=" + studentID; //유저의 정보가 저장된 서버 주소
        string json;
        WWW www = new WWW(url);
        while (true)
        {
            WaitForSeconds wfs = new WaitForSeconds(1);
            if (www.isDone) break; //서버에서 정보를 다 받을 때까지 진행
        }
        yield return new WaitForSeconds(1);

        json = www.text; //서버의 텍스트 정보를 저장
        string json2parse = "{\"students\":" + json + "}"; //json 파싱을 하기 위해 저장 형태를 수정
        students = JsonUtility.FromJson<StudentList>(json2parse); //파싱된 정보를 나눠서 리스트에 담기

        imgName = "user_ponix"; //이미지 이름 초기화
        if (students.students[0].glasses == 1) //안경 아이팀을 착용했다면
            imgName = imgName + "_glasses"; //불러올 파일 이름에 "_glasses" 추가
        image.sprite = Resources.Load<Sprite>(imgName); //해당 이미지 출력

        yield return new WaitForSeconds(5); //5초 마다 정보 업데이트
        StartCoroutine(Get_img());
    }

    void Start()
    {
        image = GetComponent<Image>();
        StartCoroutine(Get_img());
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Escape)) //핸드폰의 뒤로가기 버튼을 누르면 메인 화면 출력
        {
            SceneManager.LoadScene("main");
        }

    }
}

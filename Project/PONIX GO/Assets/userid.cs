using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//유저의 아이디를 표시하는 스크립트

[System.Serializable]
public class Student //서버에 저장된 학생의 정보 클래스
{
    public string student_ID;
    public int glasses;
}

[System.Serializable]
public class StudentList //학생들 리스트
{
    public List<Student> students;
}


public class userid : MonoBehaviour
{

    // Use this for initialization
    public Text user_id;
    public StudentList students = new StudentList();
    int student_ID = idInformation.studentID;

    //학생의 정보가 저장된 서버에서 데이터를 받아서 학생의 ID를 출력해주는 함수
    IEnumerator Get_id()
    {
        string studentID = student_ID.ToString();
        string url = "http://141.223.163.207:3001/user-student?ID=" + studentID; //학생 정보가 저장된 서버 주소
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

        user_id.text = students.students[0].student_ID; //해당 유저의 아이디를 리스트에서 찾아서 출력

        yield return new WaitForSeconds(5); //5초 마다 정보 업데이트

        StartCoroutine(Get_id());
    }

    void Start()
    {

        user_id = GetComponent<Text>();
        StartCoroutine(Get_id());

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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class loginScript : MonoBehaviour
{

    private string ID_input;
    //login시 입력받은 ID string

    private string PW_input;
    //login시 입력받은 PW string

    private string returned;
    //서버로 부터 받은 login 결과 string

    private string[] returned_splitted;
    // 위의 returned string을 ':' 라는 문자로 잘라낸 string array

    private string student_ID;
    //returned_splitted 안에 있는 student ID  정보

    private string team_ID;
    //returend_splitted 안에 있는 team ID 정보

    public static int studentID;
    // student ID를 int형으로 변환한 것(다른 스크립트와의 호환을 위해)

    public static int teamID;
    // team ID를 int형으로 변환한 것(다른 스크립트와의 호환을 위해)

    public GameObject panel;
    // login 결과를 출력하는 팝업창에 해당하는 panel


    void Start()
    {
        panel.SetActive(false); //시작할 때 팝업창은 Off
    }

    void awake()
    {
        Screen.sleepTimeout = SleepTimeout.NeverSleep;
        Screen.SetResolution(720, 1080, true);
        DontDestroyOnLoad(this);
    }

    void Update()
    {

    }

    public void click_button_back() //panel 안에 있는 뒤로가기 버튼. panel을 inactive 시킴.
    {
        panel.SetActive(false);
    }

    public void get_ID(string ID_guess) // login 화면에서 ID inputfield의 정보를 get 하는 함수
    {
        ID_input = ID_guess;
    }
    public void get_PW(string PW_guess) // login 화면에서 PW inputfield의 정보를 get 하는 함수
    {
        PW_input = PW_guess;
    }
    public void click_button_main() // login 버튼
    {
        string url = "http://141.223.163.207:3001/login?ID='" + ID_input + "'&pw='" + PW_input + "'"; // 서버에 ID와 PW 정보를 전송함
        WWW www = new WWW(url);
        StartCoroutine(WaitForRequest(www));
    }
    IEnumerator WaitForRequest(WWW www)
    {
        yield return www;
        //서버로 부터 정보를 한번 읽어 옴(yield return)
        returned = www.text;
        //읽은 정보의 text 부분(string)

        if (returned == "[]")
        //ID나 PW의 입력이 잘못 된 경우
        {
            Debug.Log("Incorrect ID or PW");
            panel.SetActive(true);
        }
        else
        //ID와 PW가 정상적으로 입력되었을 경우
        {
            returned_splitted = returned.Split(',');
            //읽은 정보를 ',' 기준으로 잘라서 저장함
            student_ID = returned_splitted[0].Substring(returned_splitted[0].IndexOf(":") + 1);
            //그 중 첫 번째는 student ID
            idInformation.studentID = int.Parse(student_ID);
            // int 형으로 student ID를 변환

            team_ID = returned_splitted[1].Substring(returned_splitted[1].IndexOf(":") + 1, returned_splitted[1].IndexOf("}") - returned_splitted[1].IndexOf(":") - 1);
            //그 중 두 번째는 team ID
            idInformation.teamID = int.Parse(team_ID);
            // int형으로 team ID를 변환

            SceneManager.LoadScene("main");
            //login 성공시 main으로 넘어감
        }
    }
    public void click_button_findidpw() // login 화면에서 ID/PW 찾기 화면으로 넘어가는 버튼
    {
        SceneManager.LoadScene("findidpw");
    }
    public void click_button_signup() // login 화면에서 회원가입 화면으로 넘어가는 부분
    {
        SceneManager.LoadScene("signup");
    }
    public string get_studentID() // class 외부에서도 student ID를 가져오는 함수(다른 스크립트와의 호환성)
    {
        return student_ID;
    }
    public string get_teamID() // class 외부에서도 team ID를 가져오는 함수
    {
        return team_ID;
    }
}

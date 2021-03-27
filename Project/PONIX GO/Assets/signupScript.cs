using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class signupScript : MonoBehaviour
{

    public string ID_input;
    // 회원가입 화면에서 받아온 ID
    public string PW_input;
    // 회원가입 화면에서 받아온 PW
    public string Name_input;
    // 회원가입 화면에서 받아온 이름
    public string Teamname_input;
    // 회원가입 화면에서 받아온 팀 이름
    public string HintPW_Question_input;
    // 회원가입 화면에서 받아온 비밀번호 찾기 질문
    public string HintPW_Answer_input;
    // 회원가입 화면에서 받아온 비밀번호 찾기 답

    private string returned;
    // 서버로 부터 받은 회원가입 결과 string

    public GameObject signup_panel_ID;
    // 입력한 ID가 중복되었다는 것을 알려주는 팝업창
    public GameObject signup_panel_Teamname;
    // 입력한 Teamname이 이미 존재한다는 것을 알려주는 팝업창  
    public GameObject signup_panel_success;
    // 회원가입이 성공한 경우의 팝업창

    void Start() // 화면이 시작될 때 모든 팝업창을 Off
    {
        signup_panel_ID.SetActive(false);
        signup_panel_Teamname.SetActive(false);
        signup_panel_success.SetActive(false);
    }

    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Escape)) // Android 환경에서 뒤로 가기 버튼을 누른 경우
        {
            SceneManager.LoadScene("login");
        }

    }

    public void get_signupID(string ID_guess) // 화면에서 ID inputfield의 정보를 읽는 함수
    {
        ID_input = ID_guess;
    }
    public void get_signupPW(string PW_guess) // 화면에서 PW inputfield의 정보를 읽는 함수
    {
        PW_input = PW_guess;
    }
    public void get_signupName(string Name_guess) // 화면에서 Name inputfield의 정보를 읽는 함수
    {
        Name_input = Name_guess;
    }
    public void get_signupTeamname(string Teamname_guess) // 화면에서 TeamName inputfield의 정보를 읽는 함수
    {
        Teamname_input = Teamname_guess;
    }
    public void get_signupQuestionForHint(string Question_guess) // 화면에서 비밀번호 찾기 질문 inputfield의 정보를 읽는 함수
    {
        HintPW_Question_input = Question_guess;
    }
    public void get_signupAnswerForHint(string Answer_guess) // 화면에서 비밀번호 찾기 답 inputfield의 정보를 읽는 함수
    {
        HintPW_Answer_input = Answer_guess;
    }

    public void click_button_signup() // 회원가입 버튼
    {
        string url = "http://141.223.163.207:3001/signup-newuser?ID='" + ID_input + "'&pw='" + PW_input + "'&name='" + Name_input + "'&team_name='" + Teamname_input + "'&pw_find_question='" + HintPW_Question_input + "'&pw_find_answer='" + HintPW_Answer_input + "'";  //서버에게 정보 전송
        WWW www = new WWW(url);
        StartCoroutine(WaitForRequest(www));
    }

    IEnumerator WaitForRequest(WWW www)
    {
        yield return www;
        //서버로 부터 정보를 한 번 읽어 옴(yield return)
        returned = www.text;
        //읽은 정보의 text(string) 정보

        if (returned == "error 0 : no such team name")
        // 팀 이름이 존재하지 않는 경우
        {
            Debug.Log("There is no such team");
            signup_panel_Teamname.SetActive(true); // 해당하는 팝업창을 active
        }
        else if (returned == "error 1 : already same ID")
        // 입력한 ID와 동일한 ID가 이미 있는 경우
        {
            Debug.Log("There is already same ID");
            signup_panel_ID.SetActive(true); // 해당하는 팝업창을 active
        }
        else
        // 회원 가입에 성공한 경우
        {
            Debug.Log(returned);
            signup_panel_success.SetActive(true); // 해당하는 팝업창을 active
        }
    }
    /*
    public void click_button_login()
    {
        SceneManager.LoadScene("login");
    }
     */

    public void click_button_back_ID() // ID 중복 팝업창의 뒤로가기 버튼
    {
        signup_panel_ID.SetActive(false); // 해당 팝업창을 inactive
    }
    public void click_button_back_Teamname() // 팀 이름 없는 경우 팝업창의 뒤로가기 버튼
    {
        signup_panel_Teamname.SetActive(false); // 해당 팝업창을 inactive
    }
    public void click_button_back_success() // login 성공한 경우 팝업창의 뒤로가기 버튼
    {
        signup_panel_success.SetActive(false); // 해당 팝업창을 inactive
    }
}

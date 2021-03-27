using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//현재 학기에 수강 중인 학점을 표시하는 스크립트

public class currentCredit : MonoBehaviour
{

    // Use this for initialization
    Text ccredit;
    public TeamList teams = new TeamList();
    int team_ID = idInformation.teamID;

    //서버에서 해당 팀의 정보를 받아와서
    //그 중에 현재 수강 중인 학점을 나타내주는 함수
    IEnumerator Get_credit()
    {
        string teamID = team_ID.ToString();
        string url = "http://141.223.163.207:3001/user-team?team_ID=" + teamID; //팀의 정보가 저장된 서버의 주소
        string json;
        WWW www = new WWW(url);
        while (true)
        {
            WaitForSeconds wfs = new WaitForSeconds(1);
            if (www.isDone) break; //서버에서 정보를 다 받을 때까지 진행
        }

        json = www.text; //서버의 텍스트 정보를 저장
        string json2parse = "{\"teams\":" + json + "}"; //json 파싱을 하기 위해 저장 형태를 수정
        teams = JsonUtility.FromJson<TeamList>(json2parse); //파싱된 정보를 나눠서 리스트에 담기

        ccredit.text = teams.teams[0].credit.ToString() + " / 17"; //해당 팀의 수강 학점을 출력

        yield return new WaitForSeconds(5); //5초 마다 정보 업데이트

        StartCoroutine(Get_credit());

    }


    void Start()
    {
        ccredit = GetComponent<Text>();
        StartCoroutine(Get_credit());
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

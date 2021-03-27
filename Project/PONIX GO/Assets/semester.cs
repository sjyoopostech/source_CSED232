using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//현재의 학기를 표시해주는 스크립트

public class semester : MonoBehaviour
{

    // Use this for initialization
    Text csemester;
    public Text smt;
    public TeamList teams = new TeamList();
    int team_ID = idInformation.teamID;

    //해당 팀의 정보를 서버에서 받아와서
    //그 중에 현재 학기에 대한 정보를 출력해주는 함수
    IEnumerator Get_smt()
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
        //yield return new WaitForSeconds(1);

        json = www.text; //서버의 텍스트 정보를 저장
        string json2parse = "{\"teams\":" + json + "}"; //json 파싱을 하기 위해 저장 형태를 수정
        teams = JsonUtility.FromJson<TeamList>(json2parse); //파싱된 정보를 나눠서 리스트에 담기

        csemester.text = teams.teams[0].semester.ToString() + " 학기"; //해당 팀의 학기 정보를 출력

        yield return new WaitForSeconds(5); //5초마다 정보 업데이트

        StartCoroutine(Get_smt());

    }


    void Start()
    {

        csemester = GetComponent<Text>();
        StartCoroutine(Get_smt());

    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene("main");
        }

    }
}
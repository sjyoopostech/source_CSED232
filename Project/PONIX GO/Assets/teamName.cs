using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//팀의 이름을 표시해주는 스크립트

[System.Serializable]
public class Team //서버의 저장된 팀의 정보 형태를 가진 클래스
{
    public int ID;
    public string team_name;
    public int credit;
    public int semester;
}

[System.Serializable]
public class TeamList //팀들의 리스트
{
    public List<Team> teams;
}

public class teamName : MonoBehaviour
{

    // Use this for initialization
    public Text team_name;
    public TeamList teams = new TeamList();
    int team_ID = idInformation.teamID;

    //서버에서 팀의 정보를 받아와서 그 중에 팀의 이름을 출력해주는 함수
    IEnumerator Get_team_name()
    {
        string teamID = team_ID.ToString();
        string url = "http://141.223.163.207:3001/user-team?team_ID=" + teamID; //팀의 정보가 저장된 서버의 주소
        string json;
        WWW www = new WWW(url);
        while (true)
        {
            WaitForSeconds wfs = new WaitForSeconds(.1f);
            if (www.isDone) break; //서버에서 정보를 다 받을 때까지 진행
        }

        json = www.text; //서버의 텍스트 정보를 저장
        string json2parse = "{\"teams\":" + json + "}"; //json 파싱을 하기 위해 저장 형태를 수정
        teams = JsonUtility.FromJson<TeamList>(json2parse); //파싱된 정보를 나눠서 리스트에 담기

        team_name.text = teams.teams[0].team_name; //팀의 이름을 출력


        yield return new WaitForSeconds(5);//5초 마다 정보 업데이트

        StartCoroutine(Get_team_name());

    }

    void Start()
    {

        team_name = GetComponent<Text>();

        StartCoroutine(Get_team_name());
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

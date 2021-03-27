using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//현재 학기에 수강한 학점을 그래프로 나타내주는 스크립트
//그래프를 사진 파일의 형태로 Resources 폴더에 저장하고 파일 이름을 학점으로 저장해서 학점에 따라 파일을 불러와서 표시

public class credit_bar : MonoBehaviour
{

    public TeamList teams = new TeamList();
    public Image image;
    string imgName; //불러올 이미지의 이름
    int team_ID = idInformation.teamID;

    //서버에서 학점 정보를 받아와서 학점 정보를 이미지 이름에 추가해서
    //Resources 폴더에 있는 해당 이미지를 보여주는 함수
    IEnumerator Get_credit()
    {
        string teamID = team_ID.ToString();
        string url = "http://141.223.163.207:3001/user-team?team_ID=" + teamID; //서버의 주소
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

        imgName = teams.teams[0].credit.ToString() + "credit"; //해당 팀의 수강 학점을 불러올 이미지 이름에 저장
        image.sprite = Resources.Load<Sprite>(imgName); //해당 이미지를 Resources 폴더에서 불러옴

        yield return new WaitForSeconds(5); //5초 마다 정보 업데이트

        StartCoroutine(Get_credit());

    }


    void Start()
    {
        image = GetComponent<Image>();
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
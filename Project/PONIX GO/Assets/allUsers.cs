using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//팀의 전체 유저의 접속 상태를 보여주는 스크립트

[System.Serializable]
public class User //서버에 저장된 각 유저 정보를 담을 클래스
{
    public string name;
    public int connection;
}

[System.Serializable]
public class UserList //User 클래스의 리스트
{
    public List<User> users;
}

public class allUsers : MonoBehaviour
{

    // Use this for initialization
    Text user_list;
    int team_ID = idInformation.teamID;
    public UserList users = new UserList();
    public string online; //접속 중인 유저들
    public string offline; //비접속 중인 유저들

    //서버에 있는 해당 팀의 모든 유저의 접속상태를 받아와서
    //접속한 유저와 비접속 중인 유저로 나눠 표시해주는 함수
    IEnumerator Get_connection()
    {
        string teamID = team_ID.ToString();
        string url = "http://141.223.163.207:3001/user-connection?team_ID=" + teamID; //서버의 주소
        string json;
        WWW www = new WWW(url);
        while (true)
        {
            WaitForSeconds wfs = new WaitForSeconds(1);
            if (www.isDone) break; //서버에서 정보를 다 받을 때까지 진행
        }

        json = www.text; //서버의 텍스트 정보를 저장
        string json2parse = "{\"users\":" + json + "}"; //json 파싱을 하기 위해 저장 형태를 수정
        users = JsonUtility.FromJson<UserList>(json2parse); //파싱된 정보를 나눠서 리스트에 담기

        online = null;
        offline = null;
        user_list.text = null; //함수 재시작시 접속, 비접속 유저 정보 초기화

        int k = 0;
        for (int i = 0; i < users.users.Count; i++)
        {
            if (users.users[i].connection == 1)
            { //유저가 접속 중이면, online에 유저 이름을 추가
                if (k % 3 == 0)
                {
                    online = online + "\n" + users.users[i].name;
                }
                else
                {
                    online = online + "\t" + users.users[i].name;
                }
                k++;
            }
        }

        int l = 0;
        for (int j = 0; j < users.users.Count; j++)
        {
            if (users.users[j].connection == 0)
            {//유저가 비접속 중이면, offline에 유저 이름을 추가
                if (l % 3 == 0)
                {
                    offline = offline + "\n" + users.users[j].name;
                }
                else
                {
                    offline = offline + "\t" + users.users[j].name;
                }
                l++;
            }
        }

        //온라인과 오프라인 유저를 합침
        user_list.text = "Online" + online + "\nOffline" + offline;

        yield return new WaitForSeconds(5); //5초 마다 정보 업데이트

        StartCoroutine(Get_connection());

    }


    void Start()
    {
        user_list = GetComponent<Text>();
        StartCoroutine(Get_connection());
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

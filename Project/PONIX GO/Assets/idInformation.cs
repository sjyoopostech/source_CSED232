using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class idInformation : MonoBehaviour
{
	// 여러 scene을 아울러 저장되는 변수
    public static int studentID;
    public static int teamID;

	// connection을 보내는 Enumerator
    IEnumerator send_connection()
    {
		// url 제작 과정
        string student_ID = studentID.ToString();
        string url = "http://141.223.163.207:3001/connection?ID=" + studentID;
        string ret;

		// www class를 통한 get 통신 연결
        WWW www = new WWW(url);
        while (true)
        {
            WaitForSeconds wfs = new WaitForSeconds(1);
            if (www.isDone) break;
        }
        ret = www.text;
		
		// 5초마다 이를 반복
        yield return new WaitForSeconds(5);
        StartCoroutine(send_connection());
    }

    // Use this for initialization
    void Start()
    {
        StartCoroutine(send_connection());
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class pop_up_resistance : MonoBehaviour {

    public Text resistance_text;
    public RawImage X;

    string x_url = "https://i.imgur.com/IwcQUmb.png";

    void Set_text()
    {
        resistance_text.text = "저항이에게 홀렸습니다!\n일정 시간 동안 문제를 풀 수 없습니다.";
    }

    IEnumerator Set_X()
    {
        WWW x_www = new WWW(x_url);

        while (true) // downloading ...
        {
            yield return new WaitForSeconds(.1f);
            if (x_www.isDone) break;
        }

        X.texture = x_www.texture;

        yield return new WaitForSeconds(1);

        StartCoroutine(Set_X());

        yield break;
    }

    // Use this for initialization
    void Start () {
        Set_text();
        StartCoroutine(Set_X());
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}

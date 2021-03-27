using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class pop_up_alcohol : MonoBehaviour {

    public Text alcohol_text;
    public RawImage X;

    string x_url = "https://i.imgur.com/IwcQUmb.png";

    void Set_text()
    {
        alcohol_text.text = "술에 취해서 아이템들이 제대로 보이지 않습니다.";
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PONIX : MonoBehaviour {

    public RawImage ponix;

    string ponix_url;

    IEnumerator Ponix()
    {
        ponix_url = "https://i.imgur.com/21guqIi.png";

        yield return new WaitForSeconds(.5f);

        ponix_url = "https://i.imgur.com/Rv8Talo.png";

        yield return new WaitForSeconds(1);

        StartCoroutine(Ponix());

        yield break;
    }

    IEnumerator Set()
    {
        WWW ponix_www = new WWW(ponix_url);

        while (true) // downloading ...
        {
            yield return new WaitForSeconds(.1f);
            if (ponix_www.isDone) break;
        }

        ponix.texture = ponix_www.texture;

        yield return new WaitForSeconds(1);

        StartCoroutine(Set());

        yield break;
    }

    public void click_PONIX()
    {
        SceneManager.LoadScene("user");
    }

    // Use this for initialization
    void Start () {
        StartCoroutine(Ponix());

        StartCoroutine(Set());
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}

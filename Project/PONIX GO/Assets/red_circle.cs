using System;
using System.Linq; // function - Convert.Todouble
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class red_circle : MonoBehaviour {

    public RawImage circle;

    public string red_circle_url;

    float meter_to_pixel = 6.67747483322F;
    
    string search_scale_url = "http://141.223.163.207:3001/main-searchscale?ID=1";

    double search_scale = 10;

    void Set_search_scale_url()
    {
        search_scale_url = "http://141.223.163.207:3001/main-searchscale?ID=1";
    }

    IEnumerator Search_scale()
    {
        WWW search_scale_www = new WWW(search_scale_url);
        while (true) // downloading ...
        {
            if (search_scale_www.isDone) break;
        }

        string search_scale_string = search_scale_www.text;

        search_scale = double.Parse(search_scale_string, System.Globalization.NumberStyles.AllowDecimalPoint);

        yield return new WaitForSeconds(1);

        StartCoroutine(Search_scale());

        yield break;
    }

    IEnumerator Set()
    {
        red_circle_url = "https://i.imgur.com/VBoizAG.png";

        WWW red_circle_www = new WWW(red_circle_url);

        while (true) // downloading ...
        {
            yield return new WaitForSeconds(.1f);
            if (red_circle_www.isDone) break;
        }

        circle.texture = red_circle_www.texture;

        yield break;
    }

    IEnumerator Set_size()
    {
        circle.rectTransform.sizeDelta = new Vector2((float)(search_scale * meter_to_pixel), (float)(search_scale * meter_to_pixel));


        yield return new WaitForSeconds(.5f);

        StartCoroutine(Set_size());
    }

    // Use this for initialization
    void Start () {
        StartCoroutine(Search_scale());
        StartCoroutine(Set_size());
        StartCoroutine(Set());
    }

    // Update is called once per frame
    void Update () {
		
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Point{

    public int ID;
    public int Type;
    public double latitude;
    public double longitude;

    public Point(int n, int t, double lat, double lon)
    {
        ID = n;
        Type = t;
        latitude = lat;
        longitude = lon;
    }


    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

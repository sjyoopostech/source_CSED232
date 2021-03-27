using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class mainScript : MonoBehaviour {

    public GameObject pop_up_resistance;
    public GameObject pop_up_alcohol;
    
    // Use this for initialize program
    void awake()
    {
        Screen.sleepTimeout = SleepTimeout.NeverSleep;
        Screen.SetResolution(720, 1080, true);
    }

    // Use this for initialization
    void Start () {
        pop_up_resistance.SetActive(false);
        pop_up_alcohol.SetActive(false);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

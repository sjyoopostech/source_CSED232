using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JSON_item{

    public string ID;
    public string Item_ID;
    public string X;
    public string Y;
    
    public JSON_item(string s)
    {
        ID               = null;
        Item_ID          = null;
        X                = null;
        Y                = null;
        
        int json_ID               = s.IndexOf("\"ID\"");
        int json_Item_ID          = s.IndexOf("\"item_ID\"");
        int json_X                = s.IndexOf("\"x\"");
        int json_Y                = s.IndexOf("\"y\"");
        

        if (json_Item_ID > 0 && json_X > 0 && json_Y > 0)
        {
            ID               = s.Substring(json_ID + 5       , json_Item_ID - json_ID               - 6);
            Item_ID          = s.Substring(json_Item_ID + 10 , json_X       - json_Item_ID          - 11);
            X                = s.Substring(json_X + 4        , json_Y       - json_X                - 5);
            Y                = s.Substring(json_Y + 4        , s.Length     - json_Y                - 4);
        }
    }


    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

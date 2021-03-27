using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class button_inventory : MonoBehaviour {

    public RawImage inventory;

    string inventory_url;

    IEnumerator Set()
    {
        inventory_url = "https://i.imgur.com/0dvrdG9.png";

        WWW inventory_www = new WWW(inventory_url);

        while (true) // downloading ...
        {
            yield return new WaitForSeconds(.1f);
            if (inventory_www.isDone) break;
        }

        inventory.texture = inventory_www.texture;

        yield break;
    }

    // Use this for initialization
    void Start () {
        StartCoroutine(Set());
	}
	
	// Update is called once per frame
	void Update () {
        
	}

    public void click_button_inventory()
    {
        SceneManager.LoadScene("inventory");
    }

}

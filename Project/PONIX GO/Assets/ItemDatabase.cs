using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LitJson;
using System.IO;
using System;
using System.Linq;

public class ItemDatabase : MonoBehaviour {
    public List<Items> database = new List<Items>();
    private JsonData itemData;

    private void Start()
    {

        Debug.Log("Item");

        //   itemData = JsonMapper.ToObject(File.ReadAllText("jar:file://"+Application.dataPath + "!/asses/Items.json"));
        TextAsset t = (TextAsset)Resources.Load("Items", typeof(TextAsset));
        itemData = JsonMapper.ToObject(t.ToString());
        ConstructItemDatabase();
    }

    public Items FetchItemByID(int id)
    {
        
        for (int i = 0; i < database.Count; i++)
        {
            if (database[i].item_ID == id)
                return database[i];
        }
        return null;
    }

    void ConstructItemDatabase()
    {

        for (int i=0;i<itemData.Count; i++)
        {
            database.Add(new Items((int)itemData[i]["ID"], itemData[i]["name"].ToString(), itemData[i]["explanation"].ToString()) );
        }
    }

}

public class Items
{
    public int Id { get; set; }
    public int item_ID { get; set; }
    public string Title { get; set; }
    public string Comment { get; set; }
    public Sprite Sprite { get; set; }

    public Items( int item_id, string title, string comment)
    {
        this.Id = 0;
        this.item_ID = item_id;
        this.Title = title;
        this.Comment = comment;
        this.Sprite = Resources.Load<Sprite>(Title);
    }
    public Items() {
        this.Id = 0;
        this.item_ID = 0;
        this.Title = "None";
        this.Comment = "No comment";
        this.Sprite = Resources.Load<Sprite>("연필");

    }
}


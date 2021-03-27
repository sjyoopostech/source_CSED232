using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LitJson;
using System.IO;

public class QuizDatabase : MonoBehaviour {
    public List<Quizes> quizdatabase = new List<Quizes>();
    private JsonData quizData;
    
    private void Start()
    {
        Debug.Log("Data");

        // quizData = JsonMapper.ToObject(File.ReadAllText(Application.persistentDataPath+ "/Quizes.json"));
        TextAsset t = (TextAsset)Resources.Load("Quizes", typeof(TextAsset));
        quizData = JsonMapper.ToObject(t.ToString());
        ConstructQuizDatabase();
    }

    public Quizes FetchQuizByID(int id)
    {
        for (int i = 0; i < quizdatabase.Count; i++)
        {
            if (quizdatabase[i].quiz_ID == id)
            {
                return quizdatabase[i];
            }
        }
        return null;
    }

    void ConstructQuizDatabase()
    {
        for (int i=0;i<quizData.Count; i++)
        {
            quizdatabase.Add(new Quizes((int)quizData[i]["ID"],quizData[i]["name"].ToString(), quizData[i]["question"].ToString(), quizData[i]["field"].ToString(), (int)quizData[i]["credit"], quizData[i]["hint"].ToString()) );
        }
    }

}

public class Quizes
{
    public int Id { get; set; }
    public int quiz_ID { get; set; }
    public string Name { get; set; }
    public string Question { get; set; }
    public string Field { get; set; }
    public int Credit { get; set; }
    public string Hint { get; set; }

    public Quizes(int id, string name, string question, string field, int credit, string hint)
    {
        this.Id = 0;
        this.quiz_ID = id;
        this.Name = name;
        this.Question = question;
        this.Field = field;
        this.Credit = credit;
        this.Hint = hint;
    }

    public Quizes() {
        this.Id = 0;
        this.quiz_ID = 0;
        this.Name = "None";
        this.Question = "No Question";
        this.Field = "No Field";
        this.Credit = 0;
        this.Hint = "No hint";
    }
}


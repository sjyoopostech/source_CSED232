using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JSON_quiz{

        public string ID;
        public string Quiz_ID;
        public string X;
        public string Y;

        public JSON_quiz(string s)
        {
            ID = null;
            Quiz_ID = null;
            X = null;
            Y = null;

            int json_ID = s.IndexOf("\"ID\"");
            int json_Quiz_ID = s.IndexOf("\"quiz_ID\"");
            int json_X = s.IndexOf("\"x\"");
            int json_Y = s.IndexOf("\"y\"");


            if (json_Quiz_ID > 0 && json_X > 0 && json_Y > 0)
            {
                ID = s.Substring(json_ID + 5, json_Quiz_ID - json_ID - 6);
                Quiz_ID = s.Substring(json_Quiz_ID + 10, json_X - json_Quiz_ID - 11);
                X = s.Substring(json_X + 4, json_Y - json_X - 5);
                Y = s.Substring(json_Y + 4, s.Length - json_Y - 4);
            }
        }


        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }
    }


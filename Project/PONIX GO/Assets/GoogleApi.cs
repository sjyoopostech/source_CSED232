using System;
using System.Linq; // function - Convert.ToInt32(string)
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; // Rawimage

public class GoogleApi : MonoBehaviour
{
    public RawImage img; // map image

    public Camera main_camera; // main camera

    string url; // google map api url 

    public double latitude = 0;
    public double longitude = 0;
    public string lat = "0"; // latitude of user
    public string lon = "0"; // longitude of user


    // Google map - 포스텍 검색결과 (무은재, 대강당 사이)
    // public string postech_N = "36.011742";
    // public string postech_W = "129.321917";
    //



    /********************************************************************************************/
    // 맵 요소들 //
    public int zoom = 19;           // zoom
    public int mapWidth = 720;      // Width of map
    public int mapHeight = 1080;    // Height of map

    public enum mapType { roadmap, satellite, hybrid, terrain }
    public mapType mapSelected; // roadmap 에서 바꾸지 않음
    public int scale = 2; // scale of map
    /********************************************************************************************/



    string[] separatingChars = { "[{", "},{", "}]" }; // WWW 클래스의 객체에서 받아온 text를 parsing 할 때 기준이 되는 substring들



    /********************************************************************************************/
    // 아이템
    string item_url = "http://141.223.163.207:3001/main-mapitem?team_ID=1"; // server - item url
    WWW item_www;
    string item_text;
    string[] item;
    Point[] item_pos;
    int item_num;
    bool item_pos_download = false;
    /********************************************************************************************/



    /********************************************************************************************/
    // 퀴즈
    string quiz_url = "http://141.223.163.207:3001/main-mapquiz?team_ID=1"; // server - quiz url
    WWW quiz_www;
    string quiz_text;
    string[] quiz;
    Point[] quiz_pos;
    int quiz_num;
    bool quiz_pos_download = false;
    /********************************************************************************************/


    bool url_make;



    /********************************************************************************************/
    // 변환 인자
    double meter_to_degree = 0.00000898315;
    double degree_to_pixel = 743333;
    /********************************************************************************************/


    /********************************************************************************************/
    // 마커 위치 제한 (degree 기준)
    double x_pixelmax = 0.00048;
    double y_pixelmax = 0.00072;
    /********************************************************************************************/

    
    int student_ID = 1;
    int team_ID = 1;


    /********************************************************************************************/
    // 아이템, 퀴즈 획득 범위
    string search_scale_url = "http://141.223.163.207:3001/main-searchscale?ID=1";
    double search_scale = 30; // default
    /********************************************************************************************/

    /********************************************************************************************/
    // default setting
    void Set_student_ID()
    {
        return;
    }
    void Set_team_ID()
    {
        return;
    }
    void Set_item_url()
    {
        item_url = "http://141.223.163.207:3001/main-mapitem?team_ID=" + team_ID;
    }
    void Set_quiz_url()
    {
        quiz_url = "http://141.223.163.207:3001/main-mapquiz?team_ID=" + team_ID;
    }
    void Set_search_scale_url()
    {
        search_scale_url = "http://141.223.163.207:3001/main-searchscale?ID=" + student_ID;
    }
    /********************************************************************************************/


    public GameObject pop_up_resistance; // 저항이를 먹을 때 뜨는 팝업 창
    public GameObject pop_up_alcohol; // 술을 먹을 때 뜨는 팝업 창
    

    // 아이템 위치 받아오기
    IEnumerator Item()
    {
        int wait, i;

        item_www = new WWW(item_url);

        wait = 0;
        while (wait < 10) // downloading ...
        {
            wait++;
            yield return new WaitForSeconds(1);
            if (item_www.isDone) break;
        }

        if (wait < 10) // if successfully downloaded
        {
            item_text = item_www.text;

            item = item_text.Split(separatingChars, System.StringSplitOptions.RemoveEmptyEntries); // parsing

            item_num = 0;

            foreach (string s in item)
            {
                item_num++;
            }
            

            item_pos_download = false; // item position is not downloaded yet

            item_pos = new Point[item_num];

            i = 0;

            foreach (string s in item)
            {
                JSON_item json_item = new JSON_item(s);

                double x = double.Parse(json_item.X, System.Globalization.NumberStyles.AllowDecimalPoint); // string to double
                double y = double.Parse(json_item.Y, System.Globalization.NumberStyles.AllowDecimalPoint); // string to double

                item_pos[i] = new Point(Convert.ToInt32(json_item.ID), Convert.ToInt32(json_item.Item_ID), x, y);

                i++;
            }
        
            item_pos_download = true; // item position is downloaded
        }

        yield return new WaitForSeconds(.1f);

        StartCoroutine(Item());

        yield break;
    }
    
    // 퀴즈 위치 받아오기
    IEnumerator Quiz()
    {
        int wait, i;

        wait = 0;

        quiz_www = new WWW(quiz_url);
        while (wait < 10) // downloading ...
        {
            wait++;
            yield return new WaitForSeconds(1);
            if (quiz_www.isDone) break;
        }

        if (wait < 10)
        {
            quiz_text = quiz_www.text;

            string[] quiz = quiz_text.Split(separatingChars, System.StringSplitOptions.RemoveEmptyEntries);

            quiz_num = 0;

            foreach (string q in quiz)
            {
                quiz_num++;
            }
            
            quiz_pos_download = false;

            quiz_pos = new Point[quiz_num];

            i = 0;

            foreach (string s in quiz)
            {
                JSON_quiz json_quiz = new JSON_quiz(s);

                double x = double.Parse(json_quiz.X, System.Globalization.NumberStyles.AllowDecimalPoint); // string to double
                double y = double.Parse(json_quiz.Y, System.Globalization.NumberStyles.AllowDecimalPoint); // string to double

                quiz_pos[i] = new Point(Convert.ToInt32(json_quiz.ID), Convert.ToInt32(json_quiz.Quiz_ID), x, y);

                i++;
            }

            quiz_pos_download = true;
        }

        yield return new WaitForSeconds(.1f);

        StartCoroutine(Quiz());

        yield break;
    }

    // make google map api url
    IEnumerator Url()
    {
        int i;
        
        url_make = false;

        /****************************************************************/
        // start making url to download GoogleMap
        url = "https://maps.googleapis.com/maps/api/staticmap?center="
            + lat + ","                                                 // latitude
            + lon                                                       // longitude
            + "&zoom=" + zoom                                           // zoom
            + "&size=" + mapWidth + "x" + mapHeight                     // size
            + "&scale=" + 2                                             // scale
            + "&maptype=" + mapSelected;                                // mapSelected

        // if item position is clearly downloaded
        if(item_pos_download)
        {
            i = 0;
            while(i<item_num)
            {
                if (item_pos[i].latitude - latitude > y_pixelmax || item_pos[i].latitude - latitude < -y_pixelmax)
                {
                    i++;
                    continue;
                }
                if (item_pos[i].longitude - longitude > x_pixelmax || item_pos[i].longitude - longitude < -x_pixelmax)
                {
                    i++;
                    continue;
                }

                url = url
                    + "&markers=color:orange"
                    + "%7Clabel:I%7C"
                    + item_pos[i].latitude.ToString() + "," + item_pos[i].longitude.ToString();

                i++;
            }
        }

        // if quiz position is clearly downloaded
        if(quiz_pos_download)
        {
            i = 0;
            while (i < quiz_num)
            {
                if (quiz_pos[i].latitude - latitude > y_pixelmax || quiz_pos[i].latitude - latitude < -y_pixelmax)
                {
                    i++;
                    continue;
                }
                if (quiz_pos[i].longitude - longitude > x_pixelmax || quiz_pos[i].longitude - longitude < -x_pixelmax)
                {
                    i++;
                    continue;
                }

                url = url
                    + "&markers=color:blue"
                    + "%7Clabel:Q%7C"
                    + quiz_pos[i].latitude.ToString() + "," + quiz_pos[i].longitude.ToString();

                i++;
            }
        }

        url = url + "&key=AIzaSyDSbdEr7Wa99jM6jCb8nt7Dm08ODIqeQMA"; // Google map api key

        url_make = true;

        yield return new WaitForSeconds(1);

        StartCoroutine(Url());

        yield break;
    }
    
    // google map download
    IEnumerator Map()
    {
        if (url_make)
        {
            WWW www = new WWW(url);
            while (true) // downloading ...
            {
                if (www.isDone) break;
            }
            img.texture = www.texture;
            img.SetNativeSize();
        }

        yield return new WaitForSeconds(1); // per second

        StartCoroutine(Map());

        yield break;
    }

    // set search scale
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

    // Use this for initialization
    void Start()
    {
        // default setting
        Set_student_ID();
        Set_team_ID();
        Set_item_url();
        Set_quiz_url();
        Set_search_scale_url();
        //

        Input.location.Start();

        // infinite routine
        StartCoroutine(Item());
        StartCoroutine(Quiz());
        StartCoroutine(Url());
        StartCoroutine(Map());
        StartCoroutine(Search_scale());
    }

    // Update is called once per frame
    void Update()
    {
        int wait = 1000;

        while (Input.location.status == LocationServiceStatus.Initializing && wait > 0)
        {
            wait--;
        }
        if (Input.location.status == LocationServiceStatus.Failed) return;

        latitude = Input.location.lastData.latitude;
        longitude = Input.location.lastData.longitude;
        lat = latitude.ToString();
        lon = longitude.ToString();

        
        if (Input.touchCount > 0) // or Input.GetMouseButtonDown(0)
        {
            if (!item_pos_download) return;
            if (!quiz_pos_download) return;
            
            Vector2 touch_position = Input.mousePosition;
            Vector3 click = main_camera.ScreenToWorldPoint(new Vector3(touch_position.x, touch_position.y, main_camera.nearClipPlane));
            double click_x = click.x * 720;
            double click_y = click.y * 540;


            /*
            Vector2 click = Input.mousePosition;
            double click_x = click.x - 360;
            double click_y = click.y - 540;
            */

            int i;

            i = 0;
            while(i < item_num)
            {
                double item_x = item_pos[i].longitude - longitude;
                double item_y = item_pos[i].latitude - latitude;

                double item_pixel_x = item_x * degree_to_pixel;
                double item_pixel_y = item_y * degree_to_pixel;

                // 터치 반경이 40픽셀 이상이면
                if ((click_x - item_pixel_x) * (click_x - item_pixel_x) + (click_y - item_pixel_y) * (click_y - item_pixel_y) > 1600)
                {
                    i++;
                    continue;
                }

                // 아이템 위치가 획득 범위 안이면
                if (item_x * item_x + item_y * item_y < (search_scale * meter_to_degree) * (search_scale * meter_to_degree))
                {

                    string get_item = "http://141.223.163.207:3001/main-getitem?" + "ID=" + item_pos[i].ID + "&student_ID=" + student_ID + "&team_ID=" + team_ID;
                    WWW get_item_www = new WWW(get_item);
                    while (true) // loading ...
                    {
                        if (get_item_www.isDone) break;
                    }

                    // 먹은 아이템이 저항이 이면
                    if(item_pos[i].Type == 6)
                    {
                        pop_up_resistance.SetActive(true);
                    }
                    // 먹은 아이템이 술이면
                    if(item_pos[i].Type == 10)
                    {
                        pop_up_alcohol.SetActive(true);
                    }

                    return;
                }
                i++;
            }

            i = 0;
            while(i < quiz_num)
            {
                double quiz_x = quiz_pos[i].longitude - longitude;
                double quiz_y = quiz_pos[i].latitude - latitude;

                double quiz_pixel_x = quiz_x * degree_to_pixel;
                double quiz_pixel_y = quiz_y * degree_to_pixel;

                // 터치 반경이 40픽셀 이상이면
                if ((click_x - quiz_pixel_x) * (click_x - quiz_pixel_x) + (click_y - quiz_pixel_y) * (click_y - quiz_pixel_y) > 1600)
                {
                    i++;
                    continue;
                }

                // 아이템 위치가 획득 범위 안이면
                if ( quiz_x * quiz_x + quiz_y * quiz_y < (search_scale * meter_to_degree) * (search_scale * meter_to_degree))
                {
                    string get_quiz = "http://141.223.163.207:3001/main-getquiz?" + "ID=" + quiz_pos[i].ID + "&team_ID=" + team_ID;
                    WWW get_quiz_www = new WWW(get_quiz);
                    while (true) // downloading ...
                    {
                        if (get_quiz_www.isDone) break;
                    }
                    return;
                }
                i++;
            }
        }
    }
}
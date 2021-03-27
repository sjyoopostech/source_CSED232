// express (network)
var express = require('express');
var fs = require('fs');
var bodyParser = require('body-parser');
var app = express();
app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());

// server-client connection
var server = app.listen(3001, function() {
	var host = server.address().address;
	var port = server.address().port;
	console.log('Running at %s:%s', host, port);
});

// mysql (database)
var mysql = require('mysql');

// server-database connection
var database = mysql.createConnection({
  host : 'localhost',
  user : 'ponixgo',
  password : 'ponixgo',
  port : 3306,
  database : 'ponixgo'
});

// main page
app.get('/', function(req, res) {
	res.send('PONIX GO server page');
});

// 회원가입
app.get('/signup-newuser', function(req, res) {
	var string = "select ID from team where team_name = " + req.query.team_name + ";";
	database.query(string, function(err, data) {
        if (err) console.log(err);
        else {
            console.log(string);
            if (data.length == 0) res.send("error 0 : no such team name");
            else {
				var team_ID = data[0].ID;
				string = "select ID from student where student_ID = " + req.query.ID + ";";
				database.query(string, function(err, data) {
					if (err) console.log(err);
					else {
						console.log(string);
						if (data.length > 0) res.send("error 1 : already same ID");
						else {
							string = "insert into student (student_ID, pw, name, team_ID, pw_find_question, pw_find_answer) values (";
							string = string + req.query.ID + "," + req.query.pw + "," + req.query.name + "," + team_ID + "," + req.query.pw_find_question + "," + req.query.pw_find_answer + ");";
							database.query(string, function(err, data) {
								if (err) console.log(err);
								else {
									console.log(string);
									res.send("success");
								}
							});
						}
					}
				});
            }
        }
	});
});

// ID 찾기
app.get('/findidpw-id', function(req, res) {
	var string = "select ID from team where team_name = " + req.query.team_name + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data.length == 0) res.send("error 0: no such team name");
			else {
				var team_ID = data[0].ID;
				string = "select student_ID from student where team_ID = " + team_ID + " and name = " + req.query.name + ";";
				database.query(string, function(err, data) {
					if (err) console.log(err);
					else {
						console.log(string);
						res.send(data);
					}	
				});
			}
		}
	});
});

// 비밀번호 찾기
app.get('/findidpw-pw', function(req, res) {
	var string = "select pw from student where student_ID = " + req.query.ID + " and pw_find_question = " + req.query.pw_find_question + " and pw_find_answer = " + req.query.pw_find_answer + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 로그인
app.get('/login', function(req, res) {
	var string = "select ID, team_ID from student where student_ID = " + req.query.ID + " and pw = " + req.query.pw + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 지도 위에서 탐지 범위 가져오기
app.get('/main-searchscale', function(req, res) {
	var string = "select search_scale, search from student where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			console.log(data);
			var search = data[0].search;
			var scale = data[0].search_scale;
			console.log(string);
			if (search > 0) res.send((data[0].scale + 5).toString());
			else res.send(scale.toString());
		}
	});
});

// 지도 위 아이템 목록 가져오기
app.get('/main-mapitem', function(req, res) {
	var string = "select alcohol from team where ID = " + req.query.team_ID + ";";
	database.query(string, function(err, data) {
		//console.log(string);
		var alcohol = data[0].alcohol;
		if (alcohol > 0) res.send("fail");
		else {
			string = "select * from map_item;";
			database.query(string, function(err, data) {
				if (err) console.log(err);
				else {
					//console.log(string);
					res.send(data);
				}
			});	
		}
	});
});

// 지도 위 퀴즈 목록 가져오기
app.get('/main-mapquiz', function(req, res) {
	var string = "select alcohol, exp from team where ID = " + req.query.team_ID + ";";
	database.query(string, function(err, data) {
		//console.log(string);
		var exp = data[0].exp;
		var alcohol = data[0].alcohol;
		if (alcohol > 0) res.send("fail");
		else {
			if (exp == 1) string = "select * from map_quiz;";
			else string = "select * from map_quiz where quiz_ID not in (10, 11, 12, 15, 16, 18, 20, 21, 24, 26);";
			database.query(string, function(err, data) {
				if (err) console.log(err);
				else {
					//console.log(string);
					res.send(data);
				}
			});	
		}
	});
});

// 아이템 줍기
app.get('/main-getitem', function(req, res) {
	var string = "select item_ID from map_item where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data.length == 0) res.send("error 0 : item is not in map");
			else {
				var item_ID = data[0].item_ID;
				if (item_ID == '3') string = "insert into team_item (team_ID, item_ID) values (" + req.query.team_ID + "," + item_ID + ");";
				else if (item_ID == '6') string = "update team set juhang = 60 where ID = " + req.query.team_ID + ";";
				else if (item_ID == '10') string = "update team set alcohol = 60 where ID = " + req.query.team_ID + ";";
				else string = "insert into student_item (student_ID, item_ID) values (" + req.query.student_ID + "," + item_ID + ");";
				database.query(string, function(err, data) {
					if (err) console.log(err);
					else {
						console.log(string);
						string = "delete from map_item where ID = " + req.query.ID + ";";
						database.query(string, function(err, data) {
							if (err) console.log(err);
							else {
								console.log(string);
								res.send("success");
							}
						});
					}
				});
			}
		}
	});
});

// 퀴즈 줍기
app.get('/main-getquiz', function(req, res) {
	var string = "select quiz_ID from map_quiz where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data.length == 0) res.send("error 0 : quiz is not in map");
			else {
				string = "insert into team_quiz (team_ID, quiz_ID) values (" + req.query.team_ID + "," + data[0].quiz_ID + ");";
				database.query(string, function(err, data) {
					if (err) console.log(err);
					else {
						console.log(string);
						string = "delete from map_quiz where ID = " + req.query.ID + ";";
						database.query(string, function(err, data) {
							if (err) console.log(err);
							else {
								console.log(string);
								res.send(data);
							}
						});
					}
				});
			}
		}
	});
});

// 팀 정보 가져오기
app.get('/user-team', function(req, res) {
	var string = "select * from team where ID = " + req.query.team_ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 유저 ID 가져오기
app.get('/user-student', function(req, res) {
	var string = "select student_ID, glasses from student where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 팀원 접속 여부 가져오기
app.get('/user-connection', function(req, res) {
	var string = "select name, connection from student where team_ID = " + req.query.team_ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 아이템 설명 가져오기
app.get('/inventory-item', function(req, res) {
	var string = "select * from item;";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 퀴즈 설명 가져오기
app.get('/inventory-quiz', function(req, res) {
	var string = "select ID, name, question, field, credit, hint from quiz;";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 개인별 소유 아이템 가져오기
app.get('/inventory-studentitem', function(req, res) {
	var string = "select ID, item_ID from student_item where student_ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 팀별 소유 아이템 가져오기
app.get('/inventory-teamitem', function(req, res) {
	var string = "select ID, item_ID from team_item where team_ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 팀별 소유 퀴즈 가져오기
app.get('/inventory-teamquiz', function(req, res) {
	var string = "select ID, quiz_ID, hint from team_quiz where team_ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send(data);
		}
	});
});

// 소유 중인 아이템 사용하기
app.get('/inventory-useitem', function(req, res) {
	if (req.query.item_ID == 3) var string = "delete from team_item where ID = " + req.query.ID + ";";
	else var string = "delete from student_item where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data.affectedRows == 0) res.send("fail");
			else {
				if (req.query.item_ID == '2') string = "update student set search = 60 where ID = " + req.query.student_ID + ";";
				else if (req.query.item_ID == '3') string = "update team set exp = 1 where ID = " + req.query.team_ID + ";";
				else if (req.query.item_ID == '7') string = "update student set search_scale = search_scale + 3 where ID = " + req.query.student_ID + ";";
				else if (req.query.item_ID == '8') string = "update student set glasses = 1 where ID = " + req.query.student_ID + ";";
				if (req.query.item_ID == '2' || req.query.item_ID == '3' || req.query.item_ID == '7' || req.query.item_ID == '8') {
					database.query(string, function(err, data) {
						if (err) console.log(err);
						else {
							console.log(string);
							res.send("success");
						}
					});
				}
				else {
					res.send("success");
				}
			}
		}
	});
});

// 소유 중인 퀴즈 사용하기
app.get('/inventory-usequiz', function(req, res) {
	var string = "select * from quiz where ID = " + req.query.quiz_ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data.length == 0) res.send("error 1 : no such quiz in inventory");
			else if ('"' + data[0].answer + '"' == req.query.answer || "'" + data[0].answer + "'" == req.query.answer) {	
				string = "delete from team_quiz where ID = " + req.query.ID + ";";
				database.query(string, function(err, data2) {
					if (err) console.log(err);
					else if (data2.affectedRows == 0) res.send("error 1 : no such quiz in inventory");
					else {
						console.log(string);
						string = "select credit, semester from team where ID = " + req.query.team_ID + ";";
						database.query(string, function(err, data2) {
							if (err) console.log(err);
							else {
								data2[0].credit += data[0].credit;
								if (data2[0].credit >= 17) {
									data2[0].credit -= 17;
									data2[0].semester += 1;
								}
								string = "update team set credit = " + data2[0].credit + ", semester = " + data2[0].semester + " where ID = " + req.query.team_ID + ";";
								database.query(string, function(err, data) {
									if (err) console.log(err);
									else {
										console.log(string);
										res.send("success");
									}
								});
							}
						});
					}
				});
			}
			else {
				res.send("error 0 : incorrect");
			}
		}
	});
});

// 저항이에게 홀렸는지 확인하기
app.get('/inventory-juhang', function(req, res) {
	var string = "select juhang from team where ID = " + req.query.team_ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			if (data[0].juhang > 0) res.send("juhang");
			else res.send("free");
		}
	});
});

// 힌트 사용하기
app.get('/inventory-usehint', function(req, res) {
	var string = "update team_quiz set hint = 1 where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send("success");
		}
	});
});

// 접속 여부 확인하기
app.get('/connection', function(req, res) {
	var date = new Date();
	var year = date.getFullYear() % 100;
	var month = date.getMonth();
	var day = date.getDate();
	var hour = date.getHours();
	var min = date.getMinutes();
	var sec = date.getSeconds();
	var time = ((((year*12+month)*31+day)*24+hour)*60+min)*60+sec;
	var string = "update student set time = " + time + " where ID = " + req.query.ID + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
		else {
			console.log(string);
			res.send("success");
		}
	});
});

// 정보 갱신
function update_sec() {
	var date = new Date();
	var year = date.getFullYear() % 100;
	var month = date.getMonth();
	var day = date.getDate();
	var hour = date.getHours();
	var min = date.getMinutes();
	var sec = date.getSeconds();
	var time = ((((year*12+month)*31+day)*24+hour)*60+min)*60+sec;
	
	// connection
	var string = "update student set connection = 0 where time < -10 + " + time + ";";
	database.query(string, function(err, data) {
		if (err) console.log(err);
	});
	var string2 = "update student set connection = 1 where time >= -10 + " + time + ";";
	database.query(string2, function(err, data) {
		if (err) console.log(err);
	});
	
	// item 2
	var string3 = "update student set search = search - 1 where search > 0;";
	database.query(string3, function(err, data) {
		if (err) console.log(err);
	});
	
	// item 6
	var string4 = "update team set juhang = juhang - 1 where juhang > 0;";
	database.query(string4, function(err, data) {
		if (err) console.log(err);
	});
	
	// item 10
	var string5 = "update team set alcohol = alcohol - 1 where alcohol > 0;";
	database.query(string5, function(err, data) {
		if (err) console.log(err);
	});
}

// 1초마다 갱신
setInterval(update_sec, 1000);
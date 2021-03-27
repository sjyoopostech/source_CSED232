-- MySQL dump 10.13  Distrib 5.7.20, for Linux (x86_64)
--
-- Host: localhost    Database: ponixgo
-- ------------------------------------------------------
-- Server version	5.7.20-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `quiz`
--

DROP TABLE IF EXISTS `quiz`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quiz` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `question` varchar(300) DEFAULT NULL,
  `answer` varchar(100) DEFAULT NULL,
  `field` varchar(50) DEFAULT NULL,
  `credit` int(11) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `hint` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quiz`
--

LOCK TABLES `quiz` WRITE;
/*!40000 ALTER TABLE `quiz` DISABLE KEYS */;
INSERT INTO `quiz` VALUES (1,'78계단의 계단수는 78개이다. (O/X)','O','인문',10,'quiz 1.','이름은 믿어봐요!'),(2,'포항공대에는 총 11개의 학과가 있다. (O/X)','O','인문',10,'quiz 2.','입학처 홈페이지를 볼까요?'),(3,'RC 21동 기숙사는 총 13층까지 있다. (O/X)','O','인문',10,'quiz 3.','일단 소수는 맞아요'),(4,'포항공대의 주소는 \'경상북도 포항시 @@로 77\' 이다. @@에 들어갈 말로 알맞은 것은?','청암','인문',10,'quiz 4.','도서관 이름이 뭐였죠?'),(5,'포스텍에서 가장 최근에 지은 건물은?','C5','인문',10,'quiz 5.','창의IT 학생들이 자주 가요!'),(7,'탄화수소를 구성하는 2가지 원소는? ','C, H','화학',10,'quiz 6.','하나는 수소에요'),(8,'전자기 현상의 모든 면을 통일적으로 기술하는, 전자기학의 기초 방정식은?','맥스웰 방정식','전자',10,'quiz 7.','대강당 앞에 동상도 있어요!'),(9,'세포는 생명체의 구조적 기능적 기본 단위라 서술하는 \'cell doctrine\'은 몇년도에 제시되었는가?','1838','생물',10,'quiz 8.','검색할까요ㅎㅎㅎㅎ'),(10,'2016년 노벨 생리 의학상은 오토파지를 연구한 \'이 사람\'이 받았다. \'이 사람\'은 누구인가?','오스미 요시노리','생물',10,'quiz 9.','노벨상의 단독 수상은 꽤 이례적인 일이랍니다!'),(11,'자체적으로 빛을 내는 수 나노미터의 반도체 결정을 무엇이라 부르는가?','퀀텀닷','물리',10,'quiz 10.','이걸 이용한 디스플레이도 있어요!'),(12,'이것은 운영체제의 핵심 부분으로 메모리나 프로세스의 관리, 하드웨어 추상화 등을 관리한다. 마이크로소프트사가 윈도우의 이것을 공개하지 않아서 비난을 받은 이것은?','커널','컴공',10,'quiz 11.','MS가 비난받은 꽤 유명한 일이랍니다'),(13,'이것은 사용자가 작성한 소스파일을 실행 파일로 변화하는 작업이다.이 과정 도중 소스파일은 기계어로 번역되고 다른 라이브러리와 연결되는 등의 과정을 거친다. 이것은 무엇인가?','빌드','컴공',10,'quiz 12.','ctrl + shift + B'),(14,'삼각형의 세 변의 길이로 넓이를 구하는 공식의 이름은?','헤론의 공식','수학',10,'quiz 13.','헤론이 만들었어요'),(15,'소문자 \'a\'는 아스키 코드로 몇번인가?','97','컴공',10,'quiz 14.','printf %d a '),(16,'교류 전기를 개발한 사람의 이름은?','테슬라','전자',10,'quiz 15.','이 사람을 기리는 의미에서 T 라는 단위를 사용해요'),(17,'많은 전자회로 소자가 하나의 기판 위 또는 기판 자체에 분리가 불가능한 상태로 결합되어 있는 초소형 구조의 기능적인 복합적 전자소자 또는 시스템인 이것은 무엇인가?','IC','전자',10,'quiz 16.','카드에 있는 칩도 @@칩이라고 불러요!'),(18,'초전도체 속에 자기력선이 들어가지 못하는 현상을 무엇이라 하는가?','마이스너 효과','물리',10,'quiz 17.','이 현상을 이용하면 호버보드도 만들 수 있습니다'),(19,'최단강하곡선은 어떠한 형태를 보이는가?','사이클로이드','수학',10,'quiz 18.','자전거 바퀴 궤도가 뭐였죠?'),(20,'야마나카 신야가 처음 성공한 것으로, 성체 줄기 세포에 특정 전사인자를 발현시켜 배아 줄기 세포에 가깝게 만든 세포를 무엇이라 하는가?','iPS cell','생물',10,'quiz 19.','유도된 줄기세포라는 뜻이에요'),(21,'진핵세포에서 인트론이 제거되는 과정을 무엇이라 하는가?','RNA 스플라이싱','생물',10,'quiz 20.','mRNA에서 intron을 제거하고 exon만 이어붙여요'),(22,'자기디스크가 아닌 반도체 메모리에 데이터를 기록함으로써 데이터읽기나 쓰기 작업을 월등히 빠르게 할 수 있는 차세대 기억장치는?','SSD','컴공',10,'quiz 21.','HDD랑 같이 쓰는 친구 이름이 뭐죠?'),(23,'영국의 수학자이자 암호학자이며, 컴퓨터 과학의 아버지라 불리는 이 사람은?','앨런 튜링','수학',10,'quiz 22.','영화 이미테이션 게임의 주인공이 누구였죠?'),(24,'마크에 물뱀을 사용하는 프로그래밍 언어는?','파이썬','컴공',10,'quiz 23.','요새 AI 라이브러리로 유명하죠'),(25,'유전물질을 선택적으로 증폭시키는 이 방법의 이름은?','PCR','생물',10,'quiz 24.','3가지 온도를 번갈아가며 cycle을 돌아요'),(26,'수학사에서 최초로 컴퓨터를 이용해 증명한 이 문제의 이름은?','4색문제','수학',10,'quiz 25.','지도를 4가지 색으로 채울 수 있을까요?');
/*!40000 ALTER TABLE `quiz` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-12-10 10:20:18

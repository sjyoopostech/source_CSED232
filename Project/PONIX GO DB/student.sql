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
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `student` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `student_ID` varchar(20) DEFAULT NULL,
  `pw` varchar(20) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `team_ID` int(11) DEFAULT NULL,
  `connection` int(11) DEFAULT '0',
  `x` double DEFAULT NULL,
  `y` double DEFAULT NULL,
  `search_scale` int(11) DEFAULT '10',
  `pw_find_question` varchar(50) DEFAULT NULL,
  `pw_find_answer` varchar(50) DEFAULT NULL,
  `session` varchar(50) DEFAULT NULL,
  `glasses` int(11) DEFAULT '0',
  `search` int(11) DEFAULT '0',
  `time` int(11) DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES (1,'20180001','1111','고길동',1,0,1,1,18,'빙하타고','내려와','1',1,0,576743762),(2,'20180002','2222','홍길동',1,0,1,1,10,'동에 번쩍','서에 번쩍','1',0,0,576742885),(3,'20180003','3333','야스오',1,0,1,1,10,'야스오는','과학입니다','1',0,0,0),(4,'20180004','4444','가렌',1,0,1,1,10,'데마시아를','위하여','1',0,0,0),(5,'20180005','5555','리븐',1,0,1,1,10,'부러진 건','다시 붙이면 돼','1',0,0,0),(6,'20180006','6666','김수한무',1,0,1,1,10,'거북이와','두루미','1',0,0,0),(13,'20180101','password','김객체',2,0,1,1,10,'당신의 고향은?','포항','1',0,0,0),(14,'20180102','postech','어사인',2,0,1,1,10,'프로그래밍과문제해결 어싸인의 개수는?','5','1',1,0,0);
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-12-10 10:19:03

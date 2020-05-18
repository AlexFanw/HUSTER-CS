-- ----------------------------
DROP TABLE IF EXISTS `TakeTrainRecord`;
CREATE TABLE `TakeTrainRecord`(
	`RID` int PRIMARY KEY AUTO_INCREMENT,
	`PCardID` char(18) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
	`TID` int NOT NULL, 
	`SStationID` int NOT NULL, 
	`AStationID` int NOT NULL, 
	`CarrigeID` smallint, 
	`SeatRow` smallint NOT NULL,
	`SeatNo` CHAR(1),
	`SStatus` int NOT NULL,
	CHECK(`SStatus` = 0 OR `SStatus` = 1 OR `SStatus` =2),
	CHECK(`SeatNo`='A' OR `SeatNo`='B' OR `SeatNo`='C' OR `SeatNo`='E' OR `SeatNo`='F' OR `SeatNo`=NULL),
	FOREIGN KEY(PCardID) REFERENCES passenger(PCardID),
	FOREIGN KEY(TID) REFERENCES train(TID)
	);
	
	
	
	delimiter $$;
	DROP PROCEDURE IF EXISTS insertTTR;
	CREATE PROCEDURE insertTTR()
	BEGIN 
	DECLARE PCardID1 char(18);
	DECLARE TID1 int;
	DECLARE SStationID1 int; 
	DECLARE AStationID1 int;
	DECLARE CarrigeID1 SMALLINT;
	DECLARE SeatRow1 SMALLINT;
	DECLARE SeatNo1 CHAR(1);
	DECLARE SStatus1 int;
	DECLARE number INT;
	SET number = 0;
	WHILE number < 10000 DO
	SET TID1 = FLOOR(1+RAND()*40000);
	SET CarrigeID1 = ROUND(RAND()*20);
	SET SeatRow1 = ROUND(RAND()*20);
	SET SeatNo1 = CHAR(ROUND(RAND()*4+65,0));
	SET SeatNo1 = IF(SeatNo1='D','F',SeatNo1); -- 排除包含D的情况
	SET SStatus1=ROUND(RAND()*2,0);
	SELECT PCardID INTO PCardID1 FROM passenger WHERE(age=3+FLOOR(RAND()*90))ORDER BY RAND() LIMIT 1;
	SELECT SStationID,AStationID INTO SStationID1,AStationID1 FROM train WHERE(TID=TID1) LIMIT 1;
	INSERT INTO TakeTrainRecord(PCardID,TID,SStationID,AStationID,CarrigeID,SeatRow,SeatNo,SStatus)VALUES(PCardID1,TID1,SStationID1,AStationID1,CarrigeID1,SeatRow1,SeatNo1,SStatus1);
	SET number=number+1;
	END WHILE;
	END$$;
	delimiter;
	CALL insertTTR();-- 生成数据
	SELECT * FROM TakeTrainRecord; -- 去重前的表
	DROP TABLE IF EXISTS dele; -- 生成去重表dele
	CREATE TABLE dele as (SELECT TID FROM TakeTrainRecord GROUP BY TID,CarrigeID,SeatRow,SeatNo HAVING COUNT(*)>1);
	-- SELECT * FROM dele;
	DELETE FROM TakeTrainRecord
		WHERE TID IN
			(SELECT TID FROM dele);
	SELECT * FROM TakeTrainRecord; -- 去重后的表
	SELECT DISTINCT TID,CarrigeID,SeatRow,SeatNo FROM TakeTrainRecord; -- 检查是否去重结束
	DROP TABLE dele; -- 丢弃dele表
	

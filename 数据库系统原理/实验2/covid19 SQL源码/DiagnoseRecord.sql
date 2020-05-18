DROP TABLE IF EXISTS `DiagnoseRecord`;
CREATE TABLE DiagnoseRecord(
	DID int PRIMARY KEY AUTO_INCREMENT,
	PCardID char(18) NOT NULL,
	DDay date NOT NULL,
	DStatus smallint NOT NULL,
	FDay date,
	CHECK(DStatus>0 AND DStatus<4)
);

DROP PROCEDURE IF EXISTS insertDR;
CREATE PROCEDURE insertDR()
BEGIN
	DECLARE PCardID1 char(18);
	DECLARE DDay1 date;
	DECLARE DStatus1 smallint;
	DECLARE FDay1 date;
	DECLARE number int;
	SET number = 0;
	WHILE number<1000 DO
	SELECT PCardID INTO PCardID1 FROM passenger WHERE(age=3+FLOOR(RAND()*90)) ORDER BY RAND() LIMIT 1;
	SET DDAY1=date_add('2020-01-22', interval FLOOR(RAND()*90) day);
	SET DStatus1 = FLOOR(1+RAND()*3);
	SET FDay1=IF(DStatus1=3,NULL,date_add('2020-01-22', interval FLOOR(RAND()*90) day)); -- 如果排除了新冠，就没有了发病日期了。
	SET number=number+1;
	INSERT INTO DiagnoseRecord(PCardID,DDay,DStatus,Fday) VALUES(PCardID1,DDay1,DStatus1,FDay1);
	END WHILE;
END;
CALL insertDR();
-- SELECT * FROM DiagnoseRecord;
DROP TABLE IF EXISTS dele; -- 生成去重表dele
CREATE TABLE dele as (SELECT PCardID FROM DiagnoseRecord GROUP BY PCardID HAVING COUNT(*)>1);
	-- SELECT * FROM dele;
DELETE FROM DiagnoseRecord
		WHERE PCardID IN
			(SELECT PCardID FROM dele);
SELECT * FROM  DiagnoseRecord; -- 去重后的表
SELECT DISTINCT PCardID FROM DiagnoseRecord; -- 检查是否去重结束
DROP TABLE dele; -- 丢弃dele表

ALTER TABLE DiagnoseRecord DROP DID;
ALTER TABLE DiagnoseRecord ADD DID int PRIMARY KEY AUTO_INCREMENT FIRST;

SELECT * FROM DiagnoseRecord;
DROP TABLE IF EXISTS `TrainContactor`;
CREATE TABLE TrainContactor(
	CDate date NOT NULL,
	CCardID char(18) NOT NULL,
	DStatus smallint NOT NULL, 
	PCardID char(18) NOT NULL,
	CONSTRAINT allkey PRIMARY KEY (CDate,CCardID,DStatus,PCardID)
);

DROP PROCEDURE IF EXISTS insertTC;
CREATE PROCEDURE insertTC()
BEGIN
	DECLARE CDate1 date;
	DECLARE CCardID1 char(18);
	DECLARE DStatus1 smallint;
	DECLARE PCardID1 char(18);
	DECLARE number INT;
	SET number = 0;
	WHILE number<1000 DO
	SELECT PCardID INTO PCardID1 FROM DiagnoseRecord WHERE(DStatus=1) ORDER BY RAND() LIMIT 1;
	SET CDate1=date_add('2020-01-22', interval FLOOR(RAND()*90) day);
	SELECT PCardID INTO CCardID1 FROM passenger WHERE(age=3+FLOOR(RAND()*90)) ORDER BY RAND() LIMIT 1;
	SET DStatus1 = IF((SELECT DStatus FROM DiagnoseRecord WHERE DiagnoseRecord.PCardID=CCardID1),
		(SELECT DStatus FROM DiagnoseRecord WHERE DiagnoseRecord.PCardID=CCardID1),FLOOR(1+RAND()*3));
	-- 保证密切接触表中的诊断结果和 Diagnose里的结果一致。不然就尴尬了。
	SET number=number+1;
	INSERT INTO TrainContactor(CDate,CCardID,DStatus,PCardID) VALUES(CDate1,CCardID1,DStatus1,PCardID1);
	END WHILE;
END;

CALL insertTC();
SELECT * FROM TrainContactor,DiagnoseRecord WHERE TrainContactor.CCardID=DiagnoseRecord.PCardID;
DROP TABLE IF EXISTS dele; -- 生成去重表dele
CREATE TABLE dele as (SELECT CCardID FROM TrainContactor GROUP BY CCardID HAVING COUNT(*)>1);
	-- SELECT * FROM dele;
DELETE FROM TrainContactor
		WHERE CCardID IN
			(SELECT CCardID FROM dele);
SELECT * FROM TrainContactor; -- 去重后的表
SELECT DISTINCT CCardID FROM TrainContactor; -- 检查是否去重结束
DROP TABLE dele; -- 丢弃dele表

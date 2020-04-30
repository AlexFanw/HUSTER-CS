-- 1）编写一个依据乘客身份证号计算其在指定年乘列车的乘车次数的自定义函数，并利用其查询2020年至少乘车过3次的乘客。
DROP FUNCTION IF EXISTS queryTime;
CREATE FUNCTION queryTime(a char(18),b YEAR)
RETURNS INT
READS SQL DATA
DETERMINISTIC
BEGIN
	DECLARE c INT;
	SELECT count(*) INTO c FROM TakeTrainRecord,train
	WHERE TakeTrainRecord.TID = train.TID
	AND YEAR(train.SDate) = b AND TakeTrainRecord.PCardID = a
	GROUP BY (TakeTrainRecord.PCardID);
	RETURN c;
END;
SELECT passenger.* FROM passenger,TakeTrainRecord 
WHERE queryTime(TakeTrainRecord.PCardID,2020)>=3
AND passenger.PCardID = TakeTrainRecord.PCardID;

-- 2）尝试编写DBMS的存储过程，建立每趟列车的乘坐人数的统计表，并通过存储过程更新该表。

DROP TABLE IF EXISTS countTID;
CREATE TABLE countTID(
TID int PRIMARY KEY NOT NULL,
num int NOT NULL,
FOREIGN KEY(TID) REFERENCES train(TID)
);

DROP PROCEDURE IF EXISTS sumTid;
CREATE PROCEDURE sumTid()
BEGIN
	INSERT INTO countTID SELECT TID,count(*) FROM TakeTrainRecord GROUP BY TakeTrainRecord.TID;
END;

CALL sumTid();
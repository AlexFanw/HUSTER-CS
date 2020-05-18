-- 1.分别用一条sql语句完成对乘车记录表基本的增、删、改的操作
INSERT INTO TakeTrainRecord(PCardID, TID, SStationID , AStationID , CarrigeID , SeatRow,SeatNo,SStatus)VALUES('130224197009140476',40035,1599,3898,8,11,'C',1);
UPDATE TakeTrainRecord SET SStatus = 0 WHERE(PCardID = '130224197009140476' AND TID = 40035);
DELETE FROM TakeTrainRecord WHERE (PCardID = '130224197009140476' AND TID = 40035);


-- 2.批处理操作
-- 将乘车记录表中的从武汉出发的乘客的乘车记录插入到一个新表WH_TakeTrainRecord中。
DROP TABLE IF EXISTS WH_TakeTrainRecord;
CREATE TABLE WH_TakeTrainRecord AS(
		SELECT * FROM TakeTrainRecord 
		WHERE SStationID IN (
		SELECT SID FROM station WHERE CityName='武汉'));   -- 从武汉出发

SELECT * FROM WH_TakeTrainRecord;


-- 3.数据导入导出
-- 通过查阅DBMS资料学习数据导入导出功能，并将任务2.1所建表格的数据导出到操作系统文件，然后再将这些文件的数据导入到相应空表。
-- skip。实验一中已经做过啦～～～

-- 4.观察性实验
-- 建立一个关系，但是不设置主码，然后向该关系中插入重复元组，然后观察在图形化交互界面中对已有数据进行删除和修改时所发生的现象。
DROP TABLE IF EXISTS observe;
CREATE TABLE observe(
	a int,
	b int
);
INSERT INTO observe(a,b) VALUES(1,1);
INSERT INTO observe(a,b) VALUES(1,1);
INSERT INTO observe(a,b) VALUES(1,1);


-- 5.创建视图
-- 创建一个新冠确诊病人的乘火车记录视图，其中的属性包括：身份证号、姓名、年龄、乘坐列车编号、发车日期、车厢号，席位排号，席位编号。
-- 按身份证号升序排序，如果身份证号一致，按发车日期降序排序（注意，如果病人买了票但是没坐车，不计入在内）。
DROP VIEW IF EXISTS CovidPatient;
CREATE VIEW CovidPatient AS
	SELECT passenger.PCardID,Pname,Age,train.TID,SDate,CarrigeID,SeatRow,SeatNo 
	FROM passenger,DiagnoseRecord,TakeTrainRecord,train
	WHERE DiagnoseRecord.PCardID = passenger.PCardID AND DiagnoseRecord.Dstatus = 1 -- 确诊病人信息
	AND TakeTrainRecord.PCardID = DiagnoseRecord.PCardID  -- 病人坐火车信息
	AND train.TID = TakeTrainRecord.TID -- 列车发车信息
	AND SStatus = 1 -- 必须是已经乘坐了车
	ORDER BY PCardID,train.SDate DESC; -- 按照身份证号升序排序

SELECT * FROM CovidPatient WHERE PCardID IN(
	SELECT PCardID FROM CovidPatient GROUP BY PCardID HAVING COUNT(*)>1);-- 验证：身份证升序，日期降序

-- 6.触发器实验
-- 编写一个触发器，用于实现以下完整性控制规则：
-- 当新增一个确诊患者时，若该患者在发病前14天内有乘车记录，则将其同排及前后排乘客自动加入“乘客紧密接触者表”，其中：接触日期为乘车日期。
-- 当一个紧密接触者被确诊为新冠时，从“乘客紧密接触者表”中修改他的状态为“1”。

-- 因为mysql不支持两种状态，所以只能分insert 和 update 两种分开写 
-- INSERT
-- covidtrigger 第一个版本失败了。呜呜呜呜，还是必须得用游标
-- DROP TRIGGER IF EXISTS covidtriger;
-- CREATE TRIGGER covidtriger 
-- AFTER INSERT ON DiagnoseRecord
-- FOR EACH ROW
-- BEGIN
-- 	DECLARE CDate1 date;
-- 	DECLARE CCardID1 char(18);
-- 	DECLARE DStatus1 smallint;
-- 	DECLARE PCardID1 char(18);
-- 	SET DStatus1 = 2; -- 新冠疑似
-- 	SET PCardID1 = new.PCardID; -- 确诊者身份号
-- 	SELECT TakeTrainRecord.PCardID INTO CCardID1 WHERE TakeTrainRecord.TID IN(
-- 			SELECT train.TID FROM TakeTrainRecord,train
-- 			WHERE TakeTrainRecord.TID = train.TID AND new.PCardID=TakeTrainRecord.PCardID -- 确诊者坐的车次
-- 			AND new.DStatus=1 -- 确诊者被确诊了
-- 			AND train.SDate <= new.FDay AND train.SDate >= DATE_SUB(new.FDay,INTERVAL 14 DAY)); -- 14天内坐的车次
-- 	
-- 	IF CCardID1!=NULL THEN
-- 		INSERT INTO TrainContactor VALUES(CDate1,CCardID1,DStatus1,PCardID1);
-- 	END IF;
-- 	-- DiagnoseRecord诊断数据更新时，TrainContactor也会跟着更新。
-- END;

DROP TRIGGER IF EXISTS covidtrigger;
CREATE TRIGGER covidtrigger 
BEFORE INSERT ON DiagnoseRecord
FOR EACH ROW
BEGIN
		IF (new.DStatus = 1) 
		AND (EXISTS (
				SELECT * FROM TakeTrainRecord,train 
				WHERE PCardID = new.PCardID 
				AND train.TID = TakeTrainRecord.TID
				AND train.SDate > date_add(new.FDay, interval -14 day) AND train.SDate < new.FDay))  -- 14天内坐过车
		THEN
				BEGIN
						DECLARE OUTER_SDate date;
						DECLARE OUTER_PCardID CHAR(18);
						DECLARE OUTER_DStatus SMALLINT;
						DECLARE OUTER_CarriageID SMALLINT;
						DECLARE OUTER_SeatRow SMALLINT;
						DECLARE INNER_PCardID CHAR(18);
						DECLARE INNER_DStatus SMALLINT;
						DECLARE INNER_CarriageID SMALLINT;
						DECLARE INNER_SeatRow SMALLINT;
						DECLARE INNER_SStatus INT;
						DECLARE TID1 INT;
						DECLARE outer_done boolean DEFAULT 0; DECLARE inner_done boolean DEFAULT 0;
						-- 外层循环在14天范围内找到每⼀一班⻋车TID，内层循环在TID相等的基础上根据CarriageID和SeatRow 进⾏行行插⼊入
						DECLARE record_cur CURSOR FOR SELECT PCardID, TID, train.SDate, CarriageID, SeatRow 
								FROM TakeTrainRecord,train
								WHERE PCardID = new.PCardID 
								AND train.TID = TakeTrainRecord.TID
								AND train.SDate > date_add(new.FDay, interval -14 day) AND train.SDate < new.FDay;
						DECLARE passenger_cur CURSOR FOR SELECT PCardID, CarriageID, SeatRow, SStatus FROM TakeTrainRecord WHERE TID = TID1;
						DECLARE CONTINUE HANDLER FOR NOT FOUND
						
						BEGIN
								SET outer_done = 1;
								SET inner_done = 1; 
								END;
								
								OPEN record_cur;
								FETCH record_cur INTO OUTER_PCardID, TID1, OUTER_SDate, OUTER_CarriageID, OUTER_SeatRow;
								WHILE NOT outer_done DO SET inner_done = 0;
								OPEN passenger_cur;
								FETCH passenger_cur INTO INNER_PCardID, INNER_CarriageID, INNER_SeatRow, INNER_SStatus;
								
								WHILE NOT inner_done DO
								-- 先确定被接触者的确诊情况
								IF EXISTS(SELECT * FROM DiagnoseRecord WHERE PCardID = INNER_PCardID AND
								DStatus = 1)
								THEN SET INNER_DStatus = 1; -- 确诊
								ELSE SET INNER_DStatus = 2; -- 疑似 
								END IF;
								
								
								-- 查看是否满⾜足插⼊入条件
								IF INNER_PCardID <> OUTER_PCardID 
										AND INNER_CarriageID = OUTER_CarriageID
										AND ABS(INNER_SeatRow - OUTER_SeatRow) <= 1 AND INNER_SStatus = 1
								THEN INSERT INTO TrainContactor VALUES(OUTER_SDate, INNER_PCardID,INNER_DStatus, OUTER_PCardID); 
								END IF;
								
								FETCH passenger_cur INTO INNER_PCardID, INNER_CarriageID, INNER_SeatRow, INNER_SStatus;
								END WHILE;
								
								SET outer_done = 0; 
								CLOSE passenger_cur;
								
								FETCH record_cur INTO OUTER_PCardID, TID1, OUTER_SDate, OUTER_CarriageID, OUTER_SeatRow;
								END WHILE;
								CLOSE record_cur;
								UPDATE TrainContactor SET DStatus = 1 WHERE CCardID = new.PCardID; 
							END;
				END IF;
END;
-- 插入数据，测试使用
INSERT INTO Diagnoserecord(DID,PCardID,DDay,DStatus,FDay) VALUES (10000,'140212201504143135','2020-02-10',1,'2020-02-03');
DELETE FROM Diagnoserecord WHERE (PCardID = '140212201504143135');
SHOW TRIGGERS;



-- 用于判断紧密接触者是否被诊断为新冠。UPDATE
DROP TRIGGER IF EXISTS contacttrigger;
CREATE TRIGGER contacttrigger
AFTER UPDATE ON DiagnoseRecord
FOR EACH ROW
BEGIN
UPDATE TrainContactor SET DStatus = new.DStatus WHERE(TrainContactor.CCardID =new.PCardID);
	-- DiagnoseRecord诊断数据更新时，TrainContactor也会跟着更新。
END;

UPDATE DiagnoseRecord SET DStatus=1 WHERE PCardID = '341004195812141894';  -- 更新数据

SELECT * FROM DiagnoseRecord,TrainContactor 
		WHERE  DiagnoseRecord.PCardID = TrainContactor.CCardID; -- 找出同时在诊断表和密切接触表中的人
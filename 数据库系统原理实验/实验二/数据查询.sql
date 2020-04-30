-- 请分别用一条SQL语句完成下列各个小题的查询需求：
-- 1）查询确诊者“张三”的在发病前14天内的乘车记录； 
SELECT DISTINCT TakeTrainRecord.*,passenger.PName FROM TakeTrainRecord,train,DiagnoseRecord,passenger
		WHERE TakeTrainRecord.TID = train.TID -- 连接火车排布和列车乘坐表
			AND DiagnoseRecord.PCardID=TakeTrainRecord.PCardID -- 确诊人坐的车次
			AND passenger.PCardID = DiagnoseRecord.PCardID -- 用于查询确诊人的姓名
			AND passenger.PName= '范冰冰'
			AND DiagnoseRecord.DStatus=1 -- 确诊了
			AND train.SDate <= DiagnoseRecord.FDay 
			AND train.SDate >= DATE_SUB(DiagnoseRecord.FDay,INTERVAL 14 DAY); -- 14天以内
-- 2）查询所有从城市“武汉”出发的乘客乘列车所到达的城市名； 
SELECT DISTINCT station.CityName FROM station,TakeTrainRecord
	WHERE station.SID=TakeTrainRecord.AStationID AND TakeTrainRecord.SStationID IN(
	SELECT station.SID FROM station WHERE station.CityName='武汉');
-- 3）计算每位新冠患者从发病到确诊的时间间隔（天数）及患者身份信息，并将结果按照发病时间天数的降序排列；
SELECT DATEDIFF(DiagnoseRecord.FDay,DiagnoseRecord.DDay),passenger.* FROM passenger,DiagnoseRecord
	WHERE passenger.PCardID = DiagnoseRecord.PCardID
	ORDER BY (DiagnoseRecord.FDay-DiagnoseRecord.DDay) DESC;
-- 4）查询“2020-01-22”从“武汉”发出的所有列车；
SELECT train.* FROM train WHERE train.SDate='2020-01-22' 
	AND train.SStationID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉');
-- 5）查询“2020-01-22”途经“武汉”的所有列车；
SELECT train.* FROM train,trainpass WHERE train.SDate='2020-01-22' 
	AND train.TID = trainpass.TID
	AND trainpass.SID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉');
-- 6）查询“2020-01-22”从武汉离开的所有乘客的身份证号、所到达的城市、到达日期； 
SELECT passenger.PCardID,station.CityName,train.ATime FROM passenger,TakeTrainRecord,station,train
WHERE passenger.PCardID = TakeTrainRecord.PCardID AND station.SID= TakeTrainRecord.AStationID
AND train.TID = TakeTrainRecord.TID
AND TakeTrainRecord.TID IN(
SELECT DISTINCT train.TID FROM train WHERE train.SDate='2020-01-22' 
	AND train.SStationID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉'));
-- 7）统计“2020-01-22” 从武汉离开的所有乘客所到达的城市及达到各个城市的武汉人员数。
SELECT station.CityName,count(CityName) FROM passenger,TakeTrainRecord,station,train
WHERE passenger.PCardID = TakeTrainRecord.PCardID AND station.SID= TakeTrainRecord.AStationID
AND train.TID = TakeTrainRecord.TID
AND TakeTrainRecord.TID IN(
SELECT DISTINCT train.TID FROM train WHERE train.SDate='2020-01-22' 
	AND train.SStationID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉'))
GROUP BY(CityName);
-- 8）查询2020年1月到达武汉的所有人员；
SELECT DISTINCT passenger.* FROM passenger,TakeTrainRecord,station,train
	WHERE passenger.PCardID=TakeTrainRecord.PCardID
	AND TakeTrainRecord.AStationID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉')
	AND TakeTrainRecord.TID = train.TID
	AND train.ATime < '2020-01-01';
-- 9） 查询2020年1月乘车途径武汉的外地人员（身份证非“420”开头）；
SELECT DISTINCT passenger.* FROM passenger,train,trainpass,TakeTrainRecord
WHERE passenger.PCardID=TakeTrainRecord.PCardID -- 身份证
	AND LEFT(passenger.PCardID,3) != '420'
	AND trainpass.TID = train.TID -- 途径的车次
	AND trainpass.SID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉') -- 途径武汉
	AND TakeTrainRecord.TID = train.TID
	AND train.STime >='2020-01-01' AND train.STime<'2020-02-01';
-- 10）统计“2020-01-22”乘坐过‘G007’号列车的新冠患者在火车上的密切接触乘客人数（每位新冠患者的同车厢人员都算同车密切接触）。
SELECT count(*) FROM TakeTrainRecord
WHERE (TakeTrainRecord.TID,TakeTrainRecord.CarrigeID) IN(
	SELECT TakeTrainRecord.TID,TakeTrainRecord.CarrigeID
	FROM passenger,TakeTrainRecord,train,DiagnoseRecord
	WHERE TakeTrainRecord.TID = train.TID
	  -- AND train.ATime = '2020-01-22'
	  -- AND train.TName = 'G007'
		AND passenger.PCardID = TakeTrainRecord.PCardID
		AND DiagnoseRecord.PCardID = passenger.PCardID
		AND DiagnoseRecord.DStatus = 1);
-- 11）查询一趟列车的一节车厢中有3人及以上乘客被确认患上新冠的列车名、出发日期，车厢号； 
SELECT train.TName,train.SDate,TakeTrainRecord.CarrigeID FROM train,TakeTrainRecord,DiagnoseRecord
WHERE train.TID = TakeTrainRecord.TID
	AND TakeTrainRecord.PCardID = DiagnoseRecord.PCardID
	AND DiagnoseRecord.DStatus = 1
	GROUP BY TName,train.SDate,TakeTrainRecord.CarrigeID
	HAVING count(*)>=3; -- 数据量太小了。。
-- 12）查询没有感染任何周边乘客的新冠乘客的身份证号、姓名、乘车日期； 
SELECT passenger.PCardID,passenger.PName,train.SDate FROM train,TakeTrainRecord,DiagnoseRecord,passenger
WHERE train.TID = TakeTrainRecord.TID
	AND TakeTrainRecord.PCardID = DiagnoseRecord.PCardID
	AND passenger.PCardID = TakeTrainRecord.PCardID
	AND DiagnoseRecord.DStatus = 1
	AND (train.TName,train.SDate,TakeTrainRecord.CarrigeID) IN
	(SELECT train.TName,train.SDate,TakeTrainRecord.CarrigeID FROM train,TakeTrainRecord,DiagnoseRecord
	WHERE train.TID = TakeTrainRecord.TID
	AND TakeTrainRecord.PCardID = DiagnoseRecord.PCardID
	AND DiagnoseRecord.DStatus = 1
	GROUP BY TName,train.SDate,TakeTrainRecord.CarrigeID
	HAVING count(*)=1);
-- 13）查询到达 “北京”、或“上海”，或“广州”（即终点站）的列车名，要求where子句中除了连接条件只能有一个条件表达式；
SELECT DISTINCT train.TName FROM train
WHERE train.AStationID IN 
(SELECT station.SID FROM station WHERE station.CityName IN('北京','上海','广州'));
-- 14）查询“2020-01-22”从“武汉站”出发，然后当天换乘另一趟车的乘客身份证号和首乘车次号，结果按照首乘车次号降序排列，同车次则按照乘客身份证号升序排列；
SELECT train.TID,passenger.PCardID FROM train,passenger,TakeTrainRecord
WHERE passenger.PCardID = TakeTrainRecord.PCardID
	AND TakeTrainRecord.TID = train.TID
	AND train.TID IN(
		SELECT train.TID FROM train WHERE train.SDate='2020-01-22' 
			AND train.SStationID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉'))
	-- 没写搭乘另一趟车的判断
	ORDER BY train.TID DESC,PCardID;
-- 15）查询所有新冠患者的身份证号，姓名及其2020年以来所乘坐过的列车名、发车日期，要求即使该患者未乘坐过任何列车也要列出来；
SELECT passenger.PCardID,PName,Tname,SDate FROM passenger,TakeTrainRecord,train,DiagnoseRecord
WHERE passenger.PCardID = TakeTrainRecord.PCardID
	AND TakeTrainRecord.TID = train.TID
	AND DiagnoseRecord.PCardID = passenger.PCardID
	AND DiagnoseRecord.DStatus = 1
	AND Train.SDate > '2020-01-01'
	ORDER BY SDate DESC; -- 自己添加的按照日期降序来排序。
-- 16）查询所有发病日期相同而且确诊日期相同的病患统计信息，包括：发病日期、确诊日期和患者人数，结果按照发病日期降序排列的前提下再按照确诊日期降序排列。
SELECT FDay,DDay,count(*) FROM DiagnoseRecord
WHERE DStatus = 1
GROUP BY FDay,DDay
ORDER BY FDay DESC,DDay DESC;
-- ORDER BY count(*) DESC;
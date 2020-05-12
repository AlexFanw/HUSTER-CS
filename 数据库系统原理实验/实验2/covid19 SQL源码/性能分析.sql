-- 9） 查询2020年1月乘车途径武汉的外地人员（身份证非“420”开头）；
EXPLAIN 
SELECT DISTINCT passenger.* FROM passenger,train,trainpass,TakeTrainRecord
WHERE passenger.PCardID=TakeTrainRecord.PCardID -- 身份证
	AND LEFT(passenger.PCardID,3) != '420' -- 左三位不为420
	AND trainpass.TID = train.TID -- 限定途径的车次
	AND trainpass.SID IN (SELECT DISTINCT SID FROM station WHERE station.CityName= '武汉') -- 途径武汉
	AND TakeTrainRecord.TID = train.TID
	AND train.STime >='2020-01-01' AND train.STime<'2020-02-01';
SELECT DISTINCT TakeTrainRecord.*,passenger.PName FROM TakeTrainRecord,train,DiagnoseRecord,passenger
		WHERE TakeTrainRecord.TID = train.TID -- 连接火车排布和列车乘坐表
			AND DiagnoseRecord.PCardID=TakeTrainRecord.PCardID -- 确诊人坐的车次
			AND passenger.PCardID = DiagnoseRecord.PCardID -- 用于查询确诊人的姓名
			AND passenger.PName= '范冰冰'
			AND DiagnoseRecord.DStatus=1 -- 确诊了
			AND train.SDate <= DiagnoseRecord.FDay 
			AND train.SDate >= DATE_SUB(DiagnoseRecord.FDay,INTERVAL 14 DAY);
			
-- starting	0.0000840	10.332
-- checking permissions	0.0000150	1.845
-- Opening tables	0.0000140	1.722
-- init	0.0000800	9.840
-- System lock	0.0000130	1.599
-- optimizing	0.0000030	0.369
-- optimizing	0.0000020	0.246
-- statistics	0.0000080	0.984
-- preparing	0.0000100	1.230
-- statistics	0.0000100	1.230
-- preparing	0.0000200	2.460
-- executing	0.0004960	61.009
-- end	0.0000060	0.738
-- query end	0.0000050	0.615
-- removing tmp table	0.0000070	0.861
-- query end	0.0000030	0.369
-- closing tables	0.0000050	0.615
-- freeing items	0.0000210	2.583
-- cleaning up	0.0000110	1.353
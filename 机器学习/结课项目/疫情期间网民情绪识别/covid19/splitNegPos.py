# coding=utf-8
import pandas as pd

class split:
    def __init__(self):
        self.all = pd.read_csv("train&test/train.csv")
        self.pos = (self.all.loc[self.all['情感倾向']==1])['微博中文内容'].values.tolist()
        self.neg = (self.all.loc[self.all['情感倾向']==-1])['微博中文内容'].values.tolist()
        self.mid = (self.all.loc[self.all['情感倾向']==0])['微博中文内容'].values.tolist()

    def startSplit(self,posnum,negnum,midnum):
        file = open("train&test/pos.txt", 'w');
        for comment in self.pos[0:posnum]:
            file.write(comment)
            file.write('\n')
        file.close()

        file = open("train&test/neg.txt",'w');
        for comment in self.neg[0:negnum]:
            file.write(comment)
            file.write('\n')
        file.close()

        file = open("train&test/mid.txt",'w');
        for comment in self.mid[0:midnum]:
            file.write(comment)
            file.write('\n')
        file.close()


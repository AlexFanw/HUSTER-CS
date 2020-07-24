# coding=utf-8
import pandas as pd
import re
from skTrain import cut2wd

class split():
    def __init__(self):
        self.all = pd.read_csv("train&test/train.csv")
        self.pos = (self.all.loc[self.all['情感倾向'] == 1])[
            '微博中文内容'].values.tolist()
        self.neg = (self.all.loc[self.all['情感倾向'] == -1]
                    )['微博中文内容'].values.tolist()
        self.mid = (self.all.loc[self.all['情感倾向'] == 0])[
            '微博中文内容'].values.tolist()

    def cleanComment(self, comment):
        comment = re.sub('#.*#', '', comment)
        comment = re.sub('//@.*:', '', comment)
        comment = re.sub('//@.*：', '', comment)
        comment = re.sub('//.*:', '', comment)
        comment = re.sub('//.*：', '', comment)
        comment = re.sub('【.*】', '', comment)
        comment = re.sub('《.*》', '', comment)
        comment = re.sub('//.*//', '', comment)
        comment = re.sub('@.*：', '', comment)
        comment = re.sub('@.*:', '', comment)
        comment = re.sub('『.*』', '', comment)
        comment = re.sub(r'\d', '', comment)
        return comment

    def startSplit(self, posnum, negnum, midnum, testnum):
        file = open("train&test/pos.txt", 'w')
        for comment in self.pos[0:posnum]:
            comment = self.cleanComment(comment)
            if comment != '':
                file.write(comment)
                file.write('\n')
        file.close()

        file = open("train&test/neg.txt", 'w')
        for comment in self.neg[0:negnum]:
            comment = self.cleanComment(comment)
            if comment != '':
                file.write(comment)
                file.write('\n')
        file.close()

        file = open("train&test/mid.txt", 'w')
        for comment in self.mid[0:midnum]:
            comment = self.cleanComment(comment)
            if comment != '':
                file.write(comment)
                file.write('\n')
        file.close()

        data = pd.read_csv('train&test/test.csv', encoding='utf-8')
        with open('train&test/test.txt', 'w', encoding='utf-8') as f:
            for line in data.values[0:testnum]:
                testline = self.cleanComment(str(line[0]))
                f.write((testline + '\n'))

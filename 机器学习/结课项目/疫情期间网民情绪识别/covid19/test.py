import re
from skTrain import cut2wd
if __name__ == '__main__':
    rawstr = "还有孝感！！！截止1.31号孝感确诊628例，死亡12例！！物资严重不足，医疗条件也没有武汉好！！请关注??查看图片扩散下"
    rawstr = re.sub(r'\d', '', rawstr)
    rawstr = cut2wd(rawstr)
    rawstr = ''.join(rawstr)
    print(''.join(rawstr))

a = "   -alexfan -99"
class Solution:
    def myAtoi(self, str: str) -> int:
        flag = False
        num = ''
        if str == '':
            return 0
        for i in range(len(str)):
            if str[i]!=' ' and (str[i].isdigit() !=True and (str[i] != '-'and str[i] !='+')):
                return 0
            elif str[i]!=' ' and (str[i].isdigit() ==True or (str[i] == '-'or str[i] =='+')):
                break
            
        for i in range(len(str)):
            if flag == True and str[i].isdigit() == False:
                break
            if (( (str[i]=='-'or str[i]=='+')and (i<len(str)-1) ) or str[i].isdigit() == True)and flag == False:
                flag = True
                if (str[i]=='-'or str[i]=='+')and str[i+1].isdigit() == False:
                    return 0
                if str[i]=='-':
                    num+='-'
            if flag == True and str[i].isdigit() == True:
                 num = num+str[i]
        if flag == False:
            return 0
        elif int(num) >= pow(2,31)-1:
            return pow(2,31)-1
        elif int(num) <= -pow(2,31):
            return -pow(2,31)
        return int(num)

test = Solution()
test.myAtoi(a)
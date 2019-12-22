class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n = len(s)+1                                         #在字符串开头添加“@”，即s=“@”+s,"@"表示一个s和p都不存在的字符
        m = len(p)+1                                         #在模式串开头添加“@”，即p=“@”+p
        tb = [[False for j in range(n)] for i in range(m)]   #初始化dp数组
        tb[0][0] = True                                      #首行初始化，tb[0][1:]都为False。首列初始化可以放入循环中（加个条件）
        for i in range(1, m):
            for j in range(0,n):                             # 从0开始就是为了初始化首列
                if p[i-1]=="*":                              #循环中模式串当前字符为p[i-1], 字符串当前字符s[j-1]，因为开头添加了“@”，所以下标要减1
                    matched = j>0 and (p[i-2]==s[j-1] or p[i-2]=='.')   #j>0 用来首列初始化， 比较上一个模式串字符p[i-2]
                    tb[i][j] = tb[i-2][j] or (matched and tb[i][j-1])   #tb[i-2][j]：使用0个模式字符，(tb[i][j-1] and matched) ：使用1-n个模式字符
                else:
                    matched = j>0 and (p[i-1]==s[j-1] or p[i-1]=='.')   #比较当前模式串字符p[i-1]
                    tb[i][j] = matched and tb[i-1][j-1]                 #单个字符匹配
        return tb[m-1][n-1]
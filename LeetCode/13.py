class Solution:
    def romanToInt(self, s: str) -> int:
        r = {'M':1000,'CM':900,'D':500,'CD':400,'C':100,'XC':90,'L':50,'XL':40,'X':10,'IX':9,'V':5,'IV':4,'I':1}
        res = 0
        i = 0
        while i < len(s):
            if i < len(s)-1 and r[s[i]] >= r[s[i+1]]:
                res += r[s[i]]
            elif i < len(s)-1 and r[s[i]] < r[s[i+1]]:
                res += r[s[i]+s[i+1]]
                i += 1
            else:
                res += r[s[i]]
            i+=1
        return res
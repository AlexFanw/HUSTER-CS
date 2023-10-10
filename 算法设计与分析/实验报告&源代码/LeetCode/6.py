a = "LEETCODEISHIRING"
class Solution:
    def convert(self, s: str, numRows: int) -> str:
        num = numRows-1
        row = 0
        flag = -1
        r = ['']*numRows
        for i in range(len(s)):
            r[row]+=s[i]            
            if abs(row) == 0 or abs(row) == num:
                flag = -flag
            if numRows!=1:
                row += flag
        return ''.join(r)
test = Solution()
test.convert(a,3)
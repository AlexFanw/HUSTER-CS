
a = ["flower","flow","flight"]
class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        out = ''
        for i in zip(*strs):
            if len(set(i)) == 1:
                out += i[0]
            else:
                break
        return out

test = Solution()
test.longestCommonPrefix(a)
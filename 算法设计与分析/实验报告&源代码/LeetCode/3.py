class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return 0
        left = 0
        window = set()
        n = len(s)
        maxlen = 0
        nowlen = 0
        for i in range(n):
            nowlen += 1
            #滑动窗口法
            while s[i] in window:
                window.remove(s[left])
                left += 1
                nowlen -= 1
            if nowlen > maxlen:maxlen = nowlen
            window.add(s[i])
        return maxlen

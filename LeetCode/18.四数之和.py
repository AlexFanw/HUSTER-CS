#
# @lc app=leetcode.cn id=18 lang=python3
#
# [18] 四数之和
#

# @lc code=start
class Solution:
    def fourSum(self, nums, target):
        nums.sort()
        numlen = len(nums)
        for i in range(numlen-3):
            


nums = [1, 0, -1, 0, -2, 2]
test = Solution()
test.fourSum(nums,1)
# @lc code=end


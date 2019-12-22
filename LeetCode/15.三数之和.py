#
# @lc app=leetcode.cn id=15 lang=python3
#
# [15] 三数之和
#

# @lc code=start
nums = [-1, 0, 1, 2, -1, -4]

class Solution:
    def threeSum(self, nums) :
        res = []
        nums.sort()
        for i in range(len(nums)-2):
           if i > 0 and nums[i] == nums[i-1]:
               continue
           l, r = i+1, len(nums)-1
           while l < r:
               s = nums[i] + nums[l] + nums[r]
               if s < 0:
                   l +=1 
               elif s > 0:
                   r -= 1
               else:
                   res.append((nums[i], nums[l], nums[r]))
                   while l < r and nums[l] == nums[l+1]:
                       l += 1
                   while l < r and nums[r] == nums[r-1]:
                       r -= 1
                   l += 1; r -= 1
        return res      


test = Solution()
print(test.threeSum(nums))
# @lc code=end


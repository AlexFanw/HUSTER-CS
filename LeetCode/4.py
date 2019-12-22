class Solution:
    def findMedianSortedArrays(self, nums1: [int], nums2: [int]) -> float:
        if len(nums1) > len(nums2): nums1, nums2 = nums2, nums1
        l, r = 0, 2 * len(nums1)
        while l <= r:
            m1 = (l + r) // 2
            m2 = len(nums1) + len(nums2) - m1
            left1 = nums1[(m1 - 1) // 2] if m1 != 0 else float("-inf")
            right1 = nums1[m1 // 2] if m1 != 2 * len(nums1) else float("+inf")
            left2 = nums2[(m2 - 1) // 2] if m2 != 0 else float("-inf")
            right2 = nums2[m2 // 2] if m2 != 2 * len(nums2) else float("+inf")
            if left1 > right2: r = m1 - 1
            elif left2 > right1: l = m1 + 1
            else: return (max(left1, left2) + min(right1, right2)) / 2
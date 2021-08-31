class Solution:
    def maxAreaNotOpt(self, height: List[int]) -> int:
        # for each element in list, look at each other element in list
        # if that element is less than or equal current, product is that element times abs diff in indices
        # else if that element is greater, this element times absolute diff in indices
        # and check if greater than prior max, if so, store
        # return max
        # this approach is O(1) space, O(n^2) in time complexity
        max_area = 0
        tmp = 0
        for i in range(0, len(height)):
            for j in range(0, len(height)):
                if height[i] <= height[j]:
                    tmp = height[i] * abs(i - j)
                else:
                    tmp = height[j] * abs(i - j)
                if tmp > max_area:
                    max_area=tmp
        return max_area

    def maxArea(self, height: List[int]) -> int:
        # get length of array
        # set left to 0 and right to end of array index
        # set width to length of array minus 1
        # loop over width subracting one each time
        # for each possible width, check if height[l] is less than height[r]
        # if so, max area will be width * height[l], so can compare that to prior max area
        # and update l
        # else, max area will be width * height[j], so can compare that to prior max area
        # and update r
        height_size = len(height)
        area = 0
        L, R = 0, height_size - 1
        for width in range(height_size - 1, 0, -1):
            if height[L] < height[R]:
                area = max(area, height[L] * width)
                L += 1
            else:
                area = max(area, height[R] * width)
                R -= 1
        return area


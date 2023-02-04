"""
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

take number.
create tmp
while it int divided by 10 != 0
create tmp int, to 0.
take mod of num, squuare it, add it to tmp.
divide by 10, continue.

take mod of num, square, add it to tmp.

thats the new num. make a function to do this.

then set two vars, slow mover and fast mover.

we will use slow mover to do one step, and fast mover to do 2 steps each time.
while they are not equal to each other,
move them.

then return if one is == to 1.

storage complexity O(1)
time complexity O(N) where N is the number of steps to converge.

watch out for overflow

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Example 2:

Input: n = 2
Output: false

feedback from solution, didnt handle where number goes up forever.
if we look at cases:

if 13 digits, max is 9999999999999, and this next would be: 1053.
if 4 digits, max is 9999, and this next would be: 324
if 3 digits, max 999 next is 243,

so would get stuck in cycle below 243.

also time complexity wrong.

next number operation has to go through each digit, and there are logn digits.
once a number goes below 243, cant go back up.
once below 243, cant take more than 243 steps to terminate.

each number has 3 digits.

for n above 243,
cost of each num in chain above 243.
logn + loglogn + logloglogn. 
logn dominates.
O(243 * 3 + logn + loglogn + logloglogn).. = O(logn)


"""

class Solution:
    def squareSumDigits(self, n: int) -> int:
        tmp: int = 0
        while n // 10 != 0:
            digit: float = n % 10
            tmp += (digit ** 2)
            n = n // 10
        tmp += (n ** 2)
        return tmp
    def isHappy(self, n: int) -> bool:
        slow: int = self.squareSumDigits(n)
        fast: int = self.squareSumDigits(slow)
        while slow != fast:
            slow = self.squareSumDigits(slow)
            fast = self.squareSumDigits(fast)
            fast = self.squareSumDigits(fast)
        return slow == 1
        
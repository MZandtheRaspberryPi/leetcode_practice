/*

Given an array of integers, from 0 to n, with one missing, find missing number.
But, cant load integer into memory at once. also, can you do it in O(N)

n = 4

0 1 2 3

Sn = a1 + (a1 + d) + (a1 + 2d) + ... + (a1 + (n - 1)d)
Sn = an + (an - d) + (an - 2d) + ... + (an - (n - 1)d)

add two together
2Sn = n(a1 + an)
sn = n(a1 + an)/2
an = a1 + (n-1)d
sn = n(a1 + a1 + (n - 1)d) / 2
sn = n(2a1 + (n - 1)d) / 2

in our case, a1 = 0, d = 1.

so sn = n(n - 1) / 2

so if we can find n, given size of array, we can calculate the sum, and then add
stuff up and take the diff, and thats our missing number.

time complexity, O(jn) where j is size of int in bits, 32 perhaps.
but, if you look at j as sizeof(N) then it is really log2(n) so the runtime is
o(log2(n)n) which is big. space O(1)

so instead, could look at the bits and note that if n is odd we would expect
same number of 0s as 1s, or additional 0 if n is even (assuming n is inclusive).

n = 16
00000 00100 01000 01100 10000
00001 00101 01001 01101
00010 00110 01010 01110
----- 00111 01011 01111

n % 2 == 1, then count(0s) = count(1s)
n % 2 == 0, then count(0s) = count(1s) + 1

so count(1s) is always >= count(0s).

if we remove value from list, look at all bits.

if n is odd, and count(0s) = count(1s)
then when we remove a 0, count(0s) < count(1s).
then when we remove a 1, count(0s) > count(1s).

if n is even, and count(0s) = count(1s) + 1
then when we remove a 0, count(0s) = count(1s)
then when we remove a 1, count(0s) > count(1s)

so if the last digit is a 0, then count(0s) <= count(1s)
if the last digit is a 1, then count(0s) > count(1s)

so we know the last bit of missing number. can do that over next digit too.

the first time we check n numbers, and we then eliminate n / 2 options. then we
check n / 2, and eliminate n / 4. so on. so run time is O(N)

*/
#include <stdio.h>
#include <vector>

bool getBit(int num, int index) {
  int mask = 1 << index;
  return (num & mask) != 0;
}

int findMissing(const std::vector<int> &arr, int col) {

  if (col < 0) {
    return 0;
  }
  std::vector<int> oneBits;
  std::vector<int> zeroBits;

  for (int num : arr) {
    if (getBit(num, 31 - col)) {
      oneBits.push_back(num);
    } else {
      zeroBits.push_back(num);
    }
  }
  if (zeroBits.size() <= oneBits.size()) {
    int v = findMissing(zeroBits, col - 1);
    // insert a 0
    return (v << 1) | 0;
  } else {
    int v = findMissing(oneBits, col - 1);
    // insert a 1
    return (v << 1) | 1;
  }
}

int findMissing(const std::vector<int> &arr) {
  return findMissing(arr, sizeof(int) * 8 - 1);
}

int main() {
  // n = 5
  std::vector<int> arr = {0, 1, 2, 4, 5};
  printf("n=5, %d\n", findMissing(arr));

  std::vector<int> arr2 = {0, 2, 3, 4, 5};
  printf("n=5, %d\n", findMissing(arr2));

  std::vector<int> arr3 = {0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 16};
  printf("n=16, %d\n", findMissing(arr3));
}
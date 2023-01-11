/*
Write a function to determine the number of bits required to convert integer A
to integer B.

ex:
input 31, 14
output: 2

in: 0001 1111, 0000 1110
out: 0000 0010

how do we define number of bits to convert. Is this the
number of bits we have to change in integer A to arrive at integer B.

Lets assume thats the deal.

So one option is to iterate through the number of bits in an integer.
check if A bit is diff than B bit and increment counter if so, then at end
return counter.

in time complexity, we are in O(32), for an 8 byte integer. in storage we are at
O(1).

can we use bit manipulation to get to something more clever?
could we add up the number of bits in each then compare? This we would still
need to loop through?

or note that XOR will give a 1 for each bit that is diff. so could count 1s in
XOR. by shifting right till we get to zero

alternatively, can clear least sig bit in c with c = c & (c - 1) till we get to
zero and count each.
*/

#include <stdio.h>

bool getBit(int num, int index) {
  int mask = (1 << index);
  return (num & mask) != 0;
}

int getNumBitsToConvert(int num1, int num2) {
  int counter = 0;
  for (size_t i = 0; i < sizeof(num1) * 8; i++) {
    if (getBit(num1, i) != getBit(num2, i)) {
      counter++;
    }
  }
  return counter;
}

int getNumBitsToConvertOptimal1(int num1, int num2) {
  int counter = 0;
  for (int i = num1 ^ num2; i > 0; i = i >> 1) {
    counter += i & 1;
  }
  return counter;
}

int getNumBitsToConvertOptimal2(int num1, int num2) {
  int counter = 0;
  for (int i = num1 ^ num2; i > 0; i = (i & (i - 1))) {
    counter++;
  }
  return counter;
}

int main() {
  printf("%d, %d: %d\n", 31, 14, getNumBitsToConvert(31, 14));
  printf("%d, %d: %d\n", 31, 14, getNumBitsToConvertOptimal1(31, 14));
  printf("%d, %d: %d\n", 31, 14, getNumBitsToConvertOptimal2(31, 14));
}

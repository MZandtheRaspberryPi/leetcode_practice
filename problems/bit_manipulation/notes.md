# bit manipulation

bit manipulation used sometimes when explicitely asked, sometimeas to optimize code.

should be familiar w/ it by hand or with code. test thoroughly.

# 2s complement, if most sig bit is negative.
unsigned typically binary, signed typically 2s complement.
if shifting right, arithmetic right shift preserves sign, while logical right shift makes number positive.

## bit manipulation by hand
below practice, if stuck think through as a base 10 number. then apply process to binary number.

remember ^ indicates XOR operation and ~ is a not (negation) operation. assume 4 bit numbers. third col can be solved
manually or with tricks.

>> is right shift. << is left shift.

0110 + 0010 = 1000 add bits, carry over if over 1
0011 \* 0101 = 1111 do like manual mult, except carry over is 2, and watch out for overflow.
0110 + 0110 = 1100 the trick is that 0110 + 0110 is 0110 \* 2 which is equivalent to shifting 0110 left by 1.

0011 + 0010 = 0101
0011 \* 0011 = 0011 over 0110 = 1001
0100 \* 0011 = 0100 over 1000 = 1100 trick to this one is that 0100 is 4. when we multiply by 2 ^ 2, we are shifting number over by n. so shift 0011 by2. 1100.

0110 - 0011 = 0011, when need carry for subtraction, bring one from next higher digit
1101 >> 2 = shifting right, least sig bit lost and 0 added to most. so after 1, 0110, after 2 0011.
1101 ^ (~1101) = 1101 ^ (0010) = 1111 XOR, 1 if exactly 1 of inputs is 1. else 0. trick here is if you xor a bit with negated value, you will always get 1. so answer is seq of 1s.

1000 - 0110 = first step: 0200 - 0110. second step: borrow 1 from 2^2 place. 0120 - 0110 third step: do subtraction. 0010
1101 ^ 0101 = 1000
1011 & (~0 << 2) = 1011 & (1111 << 2) = 1011 & (1100) = 1000. the ~0 is a sequence of 1s. trick here is that ~0, << n, means we have 1s followed by n zeros. by doing AND with x, we clear rightmost n digits.

# Bit Facts and Tricks
Useful to think about facts. think why is true. 1s and 0s indicates sequence of 1s and seq of 0s.

x ^ 0s = x. because bitwise XOR, if zeros, will return whatever was there.
x & 0s = 0 because 0 and anything is 0.
x | 0s = x, because or will return whatever x is if 0.

x ^ 1s = ~x. because XOR inverts x if all 1s.
x & 1s = x. because & 1s will give 1 if 1 and 0 if 0.
X | 1s = 1s. because 1s will always give 1 with |.

x ^ x = 0. xor, with itslef, gives whatever it was.
x & x = x. because 0 & 0 is 0, and 1 & 1 is 1.
x | x = x. because if 1 will give back 1. if 0, 0.

# Common Bit Tasks: Get, Set, Clear, and Update Bit
Get Bit
This method shifts 1 over by i bits, 
first we shift 1 over by i bits, creating a value like. 00010000, then we do an AND with the number, clearing all bits but that one at i.
then we compare to 0. if that bit was 0, whole num is now. if that bit was 1, we will have somethign else (2^i).
```
bool getBit(int num, int i)
{
  return ((num & (1 << i)) != 0);
}
```

Set Bit
shift 1 over by i bits, so you got something like 00010000. then do an OR 
with num, only value at bit i will change. all otehr bits of mask are zero, and will not affect num.
```
int setBit(int num, int i)
{
  return num | (1 << i);
}
```

Clear Bit
create num like 11101111 by making reverse (00010000) and negating it. then, perform & with num.
will clear the ith bit, leave rest unchanged.
```
int clearBit(int num, int i)
{
  int mask = ~(1 << i);
	return num & mask;
}
```

to clear all bits from most significant bit through i (inclusive) we do. this gives us something like 11110000
```
int clearBitsInclusive(int num, int i)
{
  int mask = (1 << (i + 1)) - 1;
	return num & mask;
}
```

to clear all bits from i through 0 (inclusive)
```
int clearBitsToZero(int num, int i)
{
  int mask = ~((1 << (i + 1)) - 1);
	return num & mask;
}
```

update bit
merges approaches of set bit and clear bit.
clear the bit at position i by using mask like 11101111, then we shift the indended value b, left by i bits. makes a number with bit i equal to v and all other bits
equal to 0. then we or the numbers. updating ith bit if v is 1, and leaving it 0 if otherwise.
```
int updateBit(int num, int i, int v)
{
  int clearPositionMask = ~(1 << i);
	int new_num = num & clearPositionMask;
	int update_mask = (v << i);
	return new_num | update_mask;
	
}
```

# Hex sometimes more convenient when hardcoding masks
hex is groups of 4 bits
0-9, then A-F. A 10, F 15.

0xA = 10 = 1010
0xF = 15 = 1111

0x5 = 5 = 0101

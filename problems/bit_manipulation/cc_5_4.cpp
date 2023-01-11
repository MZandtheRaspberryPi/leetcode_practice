/*
Explain what the following code does
((n & (n-1)) == 0)

assuming n is an integer,
it will decrease n by one then do binary comparison & on the result, and we are checking that all of the checks fail when comparing to zero.

so if n decreased by one shares no binary 1s digits in common with n, we will return true.

this would likely be the case if we have a 1 followed by zeros. which in binary is a power of 2.

1000 would go to 
   1
0111

of if n is 0.



*/
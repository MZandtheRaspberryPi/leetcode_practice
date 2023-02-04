# Recursion and Dynamic Programming
Good hint, built of sub-problems. "Write code to list first n..." "implement method to compute all..."

## How to approach
By def, built off of sub-problems. Compute f(n) by adding something, removing something, or changing sol for f(n-1).

### Bottom-up recursion
Most intuitive. start knowing simple case, list with one element, figure out how to solve for 2, then 3, then so on.

Key: how can build solution for one case off the previous case.

### Top-Down recursion
More complex. How divide problem for case N into subproblems. be careful of overlap between the cases.

## Dynamic Programming
Rarely asked as too difficult for 45min interview.  if get, approach as recursion, but intermediate results
cached for future calls.

### Dyn Prog Ex
Get fibonacci.
```
int fibonacci(int i) {
  if (i == 0) return 0;
	if (i==1) return 1;
	return fibonacci(i-1) + fibonacci(i - 2);
}
```

What is runtime? nth fib, depends on previous n -1. each call does 2 recursive calls. runtime is O(2^n).
exponential increase.

can tweak to run in O(N) time. cache result of fib(i) between calls.

```
int fib[] = new int[max];
// set all to 0.
int fibonacci(int i) {
  if (i == 0) return 0;
	if (i == 1) return 1;
	if (fib[i] != 0) return fib[i]; // return cached results.
	fib[i] = fibonacci(i - 1) + fibonacci(i - 2);
	return fib[i];

}
```

Good way to approach dynamic programming is to do it recursively, then ad the caching.

## Recursive vs Iterative Solutions
Recursive can be space inefficient. Each recursive call adds new layer to stack, so if O(n) recursive calls O(n) memory.
All recursive code can be implememnted iteratively. before implementing recursively discuss tradeoffs with interviewer.
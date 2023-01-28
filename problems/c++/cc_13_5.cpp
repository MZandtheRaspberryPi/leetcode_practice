/*
What is the significance of the keyword volatile in c?

volatile indicates that the compiler shouldnt try to cache the value of the variable in between compilation.
that it could change from something that the compiler might not immediately see.

sometimes folks use that as a drop in to make a variable thread safe...but thats not quite right.

feedback from solution. 
kind of right. value of variable can change from the outside, without any update done by the code.
perhaps by thread, or os, or whatever. So compiler should reload it from memory each time.
Else it may try and optimize. For instance:

int opt = 1;
void Fn(void)
{
	start:
	  if (opt == 1) goto start;
		else break;
}

compiler may try and optimize this, as it looks like an infinite loop.
void Fn(void)
{
	start:
	  int opt = 1;
		if (true)
		goto start;
}

but what if opt is global var, could get modified by other stuff.
to prevent compiler from optimizing.

volatile int opt = 1;
void Fn(void) {
	start:
	  if (opt == 1) goto start;
		else break;
}

*/
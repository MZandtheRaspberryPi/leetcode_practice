/*
Why does a destructor in a base class need to be declared virtual?

This is to ensure the destructor gets called consistently, for example when 
something like the below happens. In this case, we would call the destructor for Base, not derived, and potentially leak memory.

virtual methods exist to ensure we call the most derived function.

feedback from solution.

*/

#include <iostream>

class Base {
	public:
	  Base() {}
		~Base() {
			std::cout << "destructor from base called.\n";
		}
};

class Derived : public Base {
	public:
	  Derived() {}
		~Derived() {
			std::cout << "destructor from deriv called.\n";
		}
};

int main() {

	Base* deriv = new Derived();
	delete deriv;
	
	Derived deriv2 = Derived();
}
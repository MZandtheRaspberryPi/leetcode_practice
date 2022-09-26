#include <math.h>

class Solution {
private:
    int getSumSquare(int n)
    {
        int result = 0;
        while (n > 0)
        {
            result += std::pow(n % 10, 2);
            n /= 10;
        }
        return result;
    }
    
    void step(int& slow, int& fast)
    {
        slow = getSumSquare(slow);
        fast = getSumSquare(fast);
        fast = getSumSquare(fast);
    }
    
public:
    bool isHappy(int n) {
        // first idea
        // set calc limit
        // while calc limit is not greater, calc value and add one to the counter
        // if value is 1, break, else continue.
        // check if exited counter
        // operate in O(n) time where this is the number of recurse limit
        // and O(1) storage
        
        // check pattern
        // 2 > 4 > 16 > 37 > 50 > 25 > 29 > 85 > 64 + 25 = 89 > 64 + 81 = 145 > 1 + 16 + 25 = 42 > 16 + 4 > 20 > 4 + 0 = 4 loop
        
        // use floyd cycle detection algorithm, fast pointer and slow pointer
        // init fast and slow to n.
        // calc slow = squaresum(n)
        // fast = squaresum(slow)
        // while slow != fast && slow != 1
        // slow next, fast double next. 
        // time complexity, depends on loop size if size of cycle is 8, then we will find at 8 / 2.
        // storage complexity, O(1)
        // ald would be use hash set to store and if already there then exit, or exit when 1
        int slow, fast;
        slow = fast = n;
        step(slow, fast);
        while (slow != fast && slow != 1)
        {
            step(slow, fast);
        }
        return slow == 1;
        
    }
};

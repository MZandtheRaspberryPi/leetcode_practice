bool isDigit(char c)
{
    int c_digit = c - '0';
    return c_digit >= 0 && c_digit <= 9;
}


bool isWspace(char c)
{
    return c == ' ';
}

class Solution {
public:
    int calculate(string s) {
        // we can scan string many times
        // first look for multiplication operator
        // when find, replace the left/right num with result of mult, replace string.

        // feedback from solution. this was too brittle. we didnt respect order of operations as we always did
        // addition before subtraction, when in reality its left to right.

        // so, use a stack.
        // if addition or mult, expression evaluated off of next expression
        // if mult or div, expression evaluated regardless of next expression

        // so, scan str left to right
        // if digit, then add to curr number, else must be operation
        // if + or -, eval based on next operation. store curr number in stack.
        // if minux, push - num into stack, and assume all stack ops are +
        // if mult or div, pop top from stack and eval expression
        // push eval result to stack
        // once str scanned pop from stack and add to result
        int len = s.size();
        if (len == 0)
        {
            return 0;
        }
        std::stack<int> num_stack;
        int currentNumber = 0;
        char operation = '+';
        for (int i = 0; i < len; i++)
        {
            char currentChar = s[i];
            if (isDigit(currentChar))
            {
                currentNumber = (currentNumber*10) + (currentChar - '0');
            }
            if ((!isDigit(currentChar)) && (!isWspace(currentChar)) || i == len - 1)
            {
                if (operation == '-')
                {
                    num_stack.push(-currentNumber);
                }
                else if (operation == '+')
                {
                    num_stack.push(currentNumber);
                }
                else if (operation == '*')
                {
                    int stackTop = num_stack.top();
                    num_stack.pop();
                    num_stack.push(stackTop * currentNumber);
                }
                else if (operation == '/')
                {
                    int stackTop = num_stack.top();
                    num_stack.pop();
                    num_stack.push(stackTop / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }
        int result = 0;
        while (num_stack.size() != 0)
        {
            result += num_stack.top();
            num_stack.pop();
        }
        return result;
    }
};

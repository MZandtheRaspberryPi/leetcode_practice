class Solution {
public:
    
    string trimLeadingZeros(string result)
    {
         // trim leading zeros
        int leading_zeros = 0;
        for (int i = 0; i < result.size(); i ++)
        {
            if (result[i] == '0')
            {
                leading_zeros++;
            }
            else
            {
                break;
            }
        }
        if (result.size() != leading_zeros)
        {
            return result.substr(leading_zeros);
        }
        else
        {
            return "0";
        }
    }
    
    
    string multiply(string num1, string num2) {
        /*
        
        allocate a result string that is the size of num1 + num2 + 1 for the carry tens digit
        
        loop over each digit of number 2
        allocate a carry to 0
        for each digit in number 1,
          find int rep by subtracing '0', multiply by int rep of digit in num 2.
          set to tmp.
          add carry to tmp.
          set result[digit_index_2 + digit_index_1] to tmp mod 10
          set carry to tmp / 10.
        
        set result[size 2 + size 1 + 1] to carry.
        
        at the end, trim leading zeros.
        
        this would for time complexity O(m * n) because for each digit in the second number
        we loop over every digit in the first number
        for space complexity, this would be O(1)
        
        
        we could check for int max and if so return an error, a error string
        
        */
        
        std::string result;
        result.resize(num1.size() + num2.size());
        std::fill_n(result.begin(), result.size(), '0');
        std::string larger_num = num2.size() > num1.size() ? num2 : num1;
        std::string smaller_num = num2.size() > num1.size() ? num1 : num2;
        int carry;
        for (int i = smaller_num.size() - 1; i >= 0; i--)
        {
            carry = 0;
            int digit2 = smaller_num[i] - '0';
            for (int j = larger_num.size() - 1; j >= 0; j--)
            {
                int digit1 = larger_num[j] - '0';
                int tmp = digit1 * digit2;               
                tmp += carry;
                int prior_result = result[i + j + 1] - '0';
                tmp += prior_result;
                result[i + j + 1] = '0' + tmp % 10;
                carry = tmp / 10;
            }
            result[i] += carry;
        }
        result[0] = '0' + carry;
        
        return trimLeadingZeros(result);
        
    }
};

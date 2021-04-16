class Solution:
    def reverse_via_str(self, x: int) -> int:
        """
        This is order n quick. uses order n storage. maybe more b/c funky characters.
        :param x:
        :return:
        """
        # if negative number grab negative sign
        str_x = str(x)
        neg_bool = False
        if str_x[0] == "-":
            str_x = str_x[1:]
            neg_bool = True

        int_len = len(str_x)
        rev_int = ""
        for i in range(int_len-1, -1, -1):
            rev_int += str_x[i]
        if neg_bool:
            rev_int = "-" + rev_int

        rev_int = int(rev_int)
        if rev_int < 2**31*(-1) or rev_int > 2**31 - 1:
            return 0
        else:
            return rev_int

    def reverse(self, x: int) -> int:
        rev = 0
        while x != 0:
            # pop operation. python does this diff than c++ or java for negative numbers
            # as it uses floors which go more negative for int division
            remainder = x % 10 if x > 0 or x % 10 == 0 else (10 - (x % 10)) * -1
            # b/c floor division, with negative numbers, rounds down to more negative,
            # use float division then go to int to drop remainder
            x = int(x / 10)
            # if we are at int max, last digit is 7 (8-1) so greater than 7 will cause overflow
            # assuming
            # Integer.MAX_VALUE = 2147483647
            # Integer.MIN_VALUE = -2147483648
            if (rev > (2**31-1) / 10) or (rev == (2**31-1) / 10 and remainder > 7):
                return 0
            elif (rev < (-1*(2**31)) / 10) or (rev == (-1*(2**31)) / 10 and remainder < -8):
                return 0
            # push operation
            temp = rev*10 + remainder
            rev = temp
        return rev


if __name__ == "__main__":
    solution = Solution()
    test_results = solution.reverse(-123)
    print(test_results)
    test_results = solution.reverse(123)
    print(test_results)
    test_results = solution.reverse(-10)
    print(test_results)
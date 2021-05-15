class Solution():
    def isPalindrome(self, number: int) -> bool:
        if number < 0:
            return False
        new_number = 0
        remainder = 0
        transformed_number = number
        while transformed_number != 0:
            new_number *= 10
            remainder = transformed_number % 10
            new_number += remainder
            transformed_number = transformed_number//10
        if new_number == number:
            return True
        else:
            return False
            
    def isPalindromeStr(self, number: int) -> bool:
        number_str = str(number)
        new_num = ""
        for i in range(0, len(number_str)):
            new_num += number_str[len(number_str) - 1 - i]
        if new_num == number_str:
            return True
        else:
            return False
            
    def isPalendromeOptimal(self, number: int) -> bool:
        # to avoid converting to str and taking non constant space
        # we will reverse second half of number and see if it matches first
        # this will also avoid integer overflow
        
        # if negative, not palindrome
        # if ends w/ a zero, then has to start with a zero to be palindrome. Only zero is that property
        if number < 0 or (number % 10 == 0 and number != 0):
            return False
        reversed_number = 0
        while reversed_number < number:
            reversed_number = reversed_number * 10 + number % 10
            number //= 10
        # for odd numbers, we have the middle digit still in reversed number. For palindrome this doesn't matter,
        # so return true if reversed number == number (even) or reversed_number//10 == number
        if reversed_number == number or reversed_number//10 == number:
            return True
        else:
            return False
        
        
            
            
        
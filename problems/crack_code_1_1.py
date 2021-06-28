# implement an algo to determine if a string has all unique characters. what if you can't use add'tl data structures?
# any constraints on size of string?

# if data structures, hash table, loop through once and add. or, set and count len.
# if no data structures, then perhaps loop through chars, check each character in string if in string from that point on
# if given a unique string with m characters, we will do m * (m-1) checks. m^2 runtime.
# could be improved to m by using datastructures like a hash table
# in terms of space complexity, O(1), because we store a bool, and a character.

def is_unique(str_to_check: str) -> bool:
    assert len(str_to_check) > 0, "Str can't be empty."
    # checking edge case here for 1
    if len(str_to_check) == 1:
        return True
    # loop through each character
    for i in range(0, len(str_to_check)):
        # check if the character is in the string at a different index
        c = str_to_check[i]
        if i == 0:
            in_str = str_to_check[1:].find(c) != -1
        elif i == len(str_to_check) - 1:
            in_str = str_to_check[0:-1].find(c) != -1
        else:
            in_str = str_to_check[0:i].find(c) != -1 or str_to_check[i+1:].find(c) != -1
        if in_str:
            return False
    # # outside of the loop, return True, as we didn't find a repeat
    return True
    
def is_unique_opt(str_to_check: str) -> bool:
    assert len(str_to_check) > 0, "Str can't be empty."
    # checking edge case here for 1
    if len(str_to_check) == 1:
        return True
    # if we have more than 256 chars, we know we have repeats, as ASCII only has 256
    if len(str_to_check) > 256:
        return False
    charset = [False] * 256
    for i in range(0, len(str_to_check)):
        # get ASCII value for char, check if we already have seen it
        val = ord(str_to_check[i])
        if charset[val]:
            return False
        charset[val] = True
    return True
    
    
print(is_unique("abb"))
# print(is_unique(""))
print(is_unique("abroc"))
print(is_unique_opt("abb"))
print(is_unique_opt("abroc"))
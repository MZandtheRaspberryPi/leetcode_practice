# given two strings write a method to decide if one is a permutation of the other

def perm_check(str1: str, str2: str) -> bool:
    """A function to check if one string is a permutation of the other string
    
    Returns True if one is a permutation of the other, False otherwise"""
    # could 2 hash tables, loop through indices and assign keys as chars and values as counts
    # then go through other and make another hash table
    # then check both hash tables are equal to each other
    # this would be order n in time complexity, and order(n+m) in space complexity
    if len(str1) != len(str2):
        return False
    
    count_dict_1 = {}
    count_dict_2 = {}

    for i in range(0, len(str1)):
        count_dict_1 = check_count(str1, count_dict_1, i)
        count_dict_2 = check_count(str2, count_dict_2, i)
    return count_dict_1 == count_dict_2
    

def check_count(str_to_check: str, dict_to_check: dict, ind: int) -> dict:
    c1 = str_to_check[ind]
    if c1 in dict_to_check.keys():
        dict_to_check[c1] += 1
    else:
        dict_to_check[c1] = 1
    return dict_to_check
    
print(perm_check("abac", "caba"))
print(perm_check("aaaa", "bbbb"))
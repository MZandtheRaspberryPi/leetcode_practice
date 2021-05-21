# implement simple compression using counts of repeated characters aaabcccaaa -> a3b1c3a3
# if string wouldn't become smaller, return original string

# use string buffer to avoid string concatenation which is O(N^2) time. dynamically sized array ok. in python, list


def compress(old_str: str) -> str:
    size = count_comp_size(old_str)
    if size >= len(old_str):
        return old_str
    new_str = []
    tmp = old_str[0]
    count = 1
    for i in range(1, len(old_str)):
        if tmp == old_str[i]:
            count += 1
        else:
            new_str.append(tmp)
            new_str.append(str(count))
            tmp = old_str[i]
            count = 1
    new_str.append(tmp)
    new_str.append(str(count))
    return "".join(new_str)
    
def count_comp_size(old_str: str) -> int:
    size = 0
    count = 1
    tmp = old_str[0]
    for i in range(1, len(old_str)):
        if old_str[i] == tmp:
            count += 1
        else:
            # letter plus length of count
            size = size + 1 + len(str(count))
            tmp = old_str[i]
            count = 1
    # adding last letter that we didn't get
    size += 1 + len(str(count))
    return size
            
if __name__ == "__main__":
    print(compress("aaabbaaaaad"))
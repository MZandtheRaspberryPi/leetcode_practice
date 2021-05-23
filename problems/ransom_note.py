class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
       
        if len(ransomNote) > len(magazine):
            return False
        
        dictMag = {}
        
        for letter in magazine:
            if letter in dictMag.keys():
                dictMag[letter] += 1
            else:
                dictMag[letter] = 1
                
        for letter in ransomNote:
            if letter not in dictMag.keys():
                return False
            else:
                dictMag[letter] -= 1
                if dictMag[letter] < 0:
                    return False

        return True
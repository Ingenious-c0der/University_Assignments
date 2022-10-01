pc1 = [57, 49, 41, 33, 25, 17, 9,
       1, 58, 50, 42, 34, 26, 18,
       10, 2, 59, 51, 43, 35, 27,
       19, 11, 3, 60, 52, 44, 36,
       63, 55, 47, 39, 31, 23, 15,
       7, 62, 54, 46, 38, 30, 22,
       14, 6, 61, 53, 45, 37, 29,
       21, 13, 5, 28, 20, 12, 4]        #Permutation Choice 1

pc2 = [14, 17, 11, 24, 1, 5, 3, 28,
       15, 6, 21, 10, 23, 19, 12, 4,
       26, 8, 16, 7, 27, 20, 13, 2,
       41, 52, 31, 37, 47, 55, 30, 40,
       51, 45, 33, 48, 44, 49, 39, 56,
       34, 53, 46, 42, 50, 36, 29, 32]          #Permutation Choice 2

ip = [58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7]            #Initial Permutation

ipInverse = [40, 8, 48, 16, 56, 24, 64, 32,
             39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30,
             37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28,
             35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26,
             33, 1, 41, 9, 49, 17, 57, 25]      #Inverse Initial Permutation

ep = [32, 1, 2, 3, 4, 5,
      4, 5, 6, 7, 8, 9,
      8, 9, 10, 11, 12, 13,
      12, 13, 14, 15, 16, 17,
      16, 17, 18, 19, 20, 21,
      20, 21, 22, 23, 24, 25,
      24, 25, 26, 27, 28, 29,
      28, 29, 30, 31, 32, 1]                #Expansion Permutation

pf = [16, 7, 20, 21, 29, 12, 28, 17,
      1, 15, 23, 26, 5, 18, 31, 10,
      2, 8, 24, 14, 32, 27, 3, 9,
      19, 13, 30, 6, 22, 11, 4, 25]         #Permutation Function

sbox1 = [[14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
         [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
         [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
         [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]]

sbox2 = [[15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
         [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
         [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
         [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]]

sbox3 = [[10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
         [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
         [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
         [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]]

sbox4 = [[7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
         [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
         [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
         [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]]

sbox5 = [[2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
         [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
         [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
         [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]]

sbox6 = [[12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
         [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
         [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
         [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]]

sbox7 = [[4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
         [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
         [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
         [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]]

sbox8 = [[13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
         [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
         [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
         [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]]

def toAscii(text):
    l = []
    for x in text:
        a = ord(x)
        l.append(a)
    return l

def XOR(a, b):
    res = ""
    for i in range(len(a)):
        if a[i] == b[i]:
            res = res + "0"
        else:
            res = res + "1"
    return res

def toBinaryLength4(n):
    res = bin(n).replace("0b","")
    while len(res) != 4:
        res = "0" + res
    return res

def toBinary(num):
    l = []
    for x in num:
        l1 = []
        s = bin(x)[2:]
        while len(s) != 8:
            s = "0" + s
        for x in s:
            l1.append(int(x))
        l.append(l1)
    return l
def toBinaryM(num):
    ctr = 0  
    l = []
    l1 = [ ]
    for x in num:
        l1.append(x)
        ctr += 1
        if ctr == 8:
            l.append(l1)
            l1 = []
            ctr = 0
    return l
        


def permutation(input_string, input_permutation):
    perm = ""
    for i in input_permutation:
        perm = perm + input_string[i-1]
    return perm

def left_shift(input, times):
    for i in range(times):
        input = input + input[0]
        input = input[1:]
    return input

def generateRoundKeys(key):
    list = []
    keySchedule = [1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1]
    left = key[0:28]
    right = key[28:56]
    for i in range(0, 16):
        left = left_shift(left, keySchedule[i])
        right = left_shift(right, keySchedule[i])
        
        combination = left + right
        combination = permutation(combination, pc2)
        list.append(combination)
    return list
    
def DESEncryption(message, key , encrypt):
    print("******************************************************")
    
    message_ascii = toAscii(message)
    print("Ascii value of message is:", message_ascii)
    if encrypt:
        message_binary = toBinary(message_ascii)
        print("Binary conversion of message is:")
    else:
        message_binary = toBinaryM(message)
        print("Binary conversion of message is:")
    for x in message_binary:
        print(x)
    message_binary = sum(message_binary, [])
    message_bin = ""
    for i in message_binary:
        message_bin = message_bin + str(i)
        
    print("******************************************************")
    message_bin = permutation(message_bin, ip)
        
    key_ascii = toAscii(key)
    print("Ascii value of key is:", key_ascii)
    key_binary = toBinary(key_ascii)
    print("Binary conversion of key is:")
    for x in key_binary:
        print(x)
    key_binary = sum(key_binary, [])
    key_bin = ""
    for i in key_binary:
        key_bin = key_bin + str(i)

    
    key_bin = permutation(key_bin, pc1)
    if(encrypt):
        roundKey = generateRoundKeys(key_bin)
    else:
        roundKey = generateRoundKeys(key_bin)[::-1]
    
    left = message_bin[0:32]
    right = message_bin[32:64]
    for i in range(0,16):
        right_exp = permutation(right, ep)
        #print("******************************************************")
        right_xor = XOR(right_exp, roundKey[i])
        #print(right)
        right1 = right_xor[0:6]
        row1 = int(right1[0::5], 2)
        col1 = int(right1[1:5], 2)
        
        right2 = right_xor[6:12]
        row2 = int(right2[0::5], 2)
        col2 = int(right2[1:5], 2)
        
        right3 = right_xor[12:18]
        row3 = int(right3[0::5], 2)
        col3 = int(right3[1:5], 2)
        
        right4 = right_xor[18:24]
        row4 = int(right4[0::5], 2)
        col4 = int(right4[1:5], 2)
        
        right5 = right_xor[24:30]
        row5 = int(right5[0::5], 2)
        col5 = int(right5[1:5], 2)
        
        right6 = right_xor[30:36]
        row6 = int(right6[0::5], 2)
        col6 = int(right6[1:5], 2)
        
        right7 = right_xor[36:42]
        row7 = int(right7[0::5], 2)
        col7 = int(right7[1:5], 2)
        
        right8 = right_xor[42:48]
        row8 = int(right8[0::5], 2)
        col8 = int(right8[1:5], 2)
        substitution = toBinaryLength4(sbox1[row1][col1])+ toBinaryLength4(sbox2[row2][col2]) + toBinaryLength4(sbox3[row3][col3]) + toBinaryLength4(sbox4[row4][col4]) + toBinaryLength4(sbox5[row5][col5]) + toBinaryLength4(sbox6[row6][col6]) + toBinaryLength4(sbox7[row7][col7]) + toBinaryLength4(sbox8[row8][col8])
        
        
        permute = permutation(substitution, pf)
      
        result = XOR(permute, left)

       
        left, right = right, result
       
        
    left, right = right, left
    cipher = left + right
    cipher = permutation(cipher, ipInverse)
    print(cipher)
    return cipher

encryptedText = DESEncryption("compitdt", "coeppune",True)
print("Binary Encrypted text: ", encryptedText)
print("Encrypted text: ", end = "")
print(chr(int(encryptedText[0:8], 2) % 127), end = "")
print(chr(int(encryptedText[8:16], 2) % 127), end = "")
print(chr(int(encryptedText[16:24], 2) % 127), end = "")
print(chr(int(encryptedText[24:32], 2) % 127), end = "")
print(chr(int(encryptedText[32:40], 2) % 127), end = "")
print(chr(int(encryptedText[40:48], 2) % 127), end = "")
print(chr(int(encryptedText[48:56], 2) % 127), end = "")
print(chr(int(encryptedText[56:64], 2) % 127), end = "")
decryptedText = DESEncryption("0011110001111110101100101011001010001001011001001010110101100100", "coeppune", False)
print("Binary Decrypted Text:", decryptedText)
decipher = chr(int(decryptedText[0:8], 2) % 127) + chr(int(decryptedText[8:16], 2) % 127) + chr(int(decryptedText[16:24], 2) % 127) + chr(int(decryptedText[24:32], 2) % 127) + chr(int(decryptedText[32:40], 2) % 127) + chr(int(decryptedText[40:48], 2) % 127) + chr(int(decryptedText[48:56], 2) % 127) + chr(int(decryptedText[56:64], 2) % 127)                                                                                                                                                                                                                                                    
print("Decrypted Text:", decipher)      

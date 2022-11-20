class pass2:
    lc = 0
    def __init__(self):
        self.symtab = []
        self.littab = []
        self.littab_file = open("littab.txt", "r")
        self.symtab_file = open("symtab.txt", "r")

    def load_data  (self):
        with open ("symtab.txt", "r") as file:
            data = file.readlines()
            for line in data:
                word = line.split()
                self.symtab.append(word[1:])
        with open ("littab.txt", "r") as file:
            data = file.readlines()
            for line in data:
                word = line.split()
                lst = []
                lst.append(word[1].split('\'')[1])
                lst.append(word[2])
                self.littab.append(lst)

    def process(self):
        self.load_data()
        flag = 0
        yy = 0
        with open("intermidiate_code.txt", "r") as file:
            data = file.readlines()
            for line in data:
                word = line.split()
                if len(word) == 0:
                    return
                if word[0] == '(AD,01)':
                    print(word)
                    lc = int(word[1].split(',')[1].split(')')[0])
                elif word[0] == '(AD,03)':
                    y = self.symtab[int(word[1][3:5]) - 1]
                    yy = int(y[1])
                    yy = yy + int(int(word[1][-1]))
                    flag = 1
                    continue
                elif word[0] == '(AD,02)':
                    continue
                elif word[0][1:3] == 'IS':
                    if flag == 1:
                        print(yy, ')', end=" ")
                        flag = 0
                        lc = lc - 1
                    else:
                        print(lc, ')', end=" ")
                    if word[0] == '(IS,00)':
                        print('00', end=" ")
                        print('0', end=" ")
                        print('000')
                    else:
                    
                        print(word[0][4:-1], end=" ")
                        print(word[1][1], end=" ")
                        if word[2][1] == 'S':
                            z = self.symtab[int(word[2][3:-1]) - 1]
                            print(z[1])
                        elif word[2][1] == 'L':
                            z = self.littab[int(word[2][3:-1]) - 1]
                            print(z[1])
                    lc = lc + 1
                elif word[0][1:3] == 'DL':
                    if word[0] == '(DL,01)':
                        if flag == 1:
                            print(yy, ')', end=" ")
                            flag = 0
                            lc = lc - 1
                        else:
                            print(lc, ')', end=" ")
                        print('00', end=" ")
                        print('0', end=" ")
                        print(word[1][3])
                    else:
                        if flag == 1:
                            print(yy, ')')
                            flag = 0
                            # lc=lc-1
                        else:
                            print(lc, ')')
                    lc = lc + 1


a = pass2()
a.process()
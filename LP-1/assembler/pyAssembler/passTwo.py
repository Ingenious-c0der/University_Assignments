import re
class Pass2: 
    def __init__(self):
        self.symtab = []
        self.littab = []
        self.machine_code = open("machinecode.txt", "w")
        self.ic = open("intermidiate_code.txt", "r")
    def load_data(self):
        with open('symtab.txt', 'r') as f:
            for line in f.readlines():
                self.symtab.append(line.split())
        with open('littab.txt', 'r') as f:
            for line in f.read().splitlines():
                self.littab.append(line.split())
    def Process(self):
        self.load_data()
        while(1):
            ipline = self.ic.readline()
            if ipline == "":
                    print("Pass Two Complete")
                    break
            parts = ipline.split()
            if( len(parts)== 0 or "AD" in parts[0] or "(DL,02)" in parts[0]):
                continue 
            elif(len(parts)== 2):
                if("(DL,01)" in parts[0]):
                    cnst = re.sub("[^0-9]", "", parts[1])
                    self.machine_code.write(f"(00 0 00{cnst})\n")
                elif("IS" in parts[0]):
                    operand = re.sub("[^0-9]", "", parts[0]) 
                    if("S" in parts[1]):
                        sym = int(re.sub("[^0-9]", "", parts[1]))
                        symbol_addr = self.symtab[sym-1][2]
                        self.machine_code.write(f"({operand} {symbol_addr})\n")
                    elif("L" in parts[1]):
                        lit = int(re.sub("[^0-9]", "", parts[1]))
                        lit_addr = self.littab[lit-1][2]
                        self.machine_code.write(f"({operand} {lit_addr})\n")
            elif(len(parts) == 3 and "IS" in parts[0]):
                opcode = int(re.sub("[^0-9]", "", parts[0]))
                regCode = int(re.sub("[^0-9]", "", parts[1]))
                if("S" in parts[2]):
                    sym = int(re.sub("[^0-9]", "", parts[2]))
                    symbol_addr = self.symtab[sym-1][2]
                    self.machine_code.write(f"({opcode} {regCode} {symbol_addr})\n")
                elif("L" in parts[2]):
                    lit = int(re.sub("[^0-9]", "", parts[2]))
                    lit_addr = self.littab[lit-1][2]
                    self.machine_code.write(f"({opcode} {regCode} {lit_addr})\n")
p  = Pass2()
p.Process()
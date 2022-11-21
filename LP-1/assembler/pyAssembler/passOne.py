
import re


class TableRow:
    def __init__(self, index, symbol, address):
        self.index = index
        self.symbol = symbol
        self.address = address

    def getIndex(self):
        return self.index

    def setIndex(self, index):
        self.index = index

    def setAddress(self, address):
        self.address = address

    def getAddress(self):
        return self.address

    def getSymbol(self):
        return self.symbol

    def __str__(self):
        return f"{self.index} {self.symbol} {self.address}"


class InstTable:
    def __init__(self):
        self.IS = {}
        self.AD = {}
        self.DL = {}
        self.CC = {}
        self.RG = {}
        self.IS.update({"STOP": 0})
        self.IS.update({"ADD": 1})
        self.IS.update({"SUB": 2})
        self.IS.update({"MULT": 3})
        self.IS.update({"MOVER": 4})
        self.IS.update({"MOVEM": 5})
        self.IS.update({"COMP": 6})
        self.IS.update({"BC": 7})
        self.IS.update({"DIV": 8})
        self.IS.update({"READ": 9})
        self.IS.update({"PRINT": 10})
        self.AD.update({"START": 1})
        self.AD.update({"END": 2})
        self.AD.update({"ORIGIN": 3})
        self.AD.update({"EQU": 4})
        self.AD.update({"LTORG": 5})
        self.DL.update({"DC": 1})
        self.DL.update({"DS": 2})
        self.RG.update({"AREG": 1})
        self.RG.update({"BREG": 2})
        self.RG.update({"CREG": 3})
        self.RG.update({"DREG": 4})
        self.CC.update({"LT": 1})
        self.CC.update({"LE": 2})
        self.CC.update({"EQ": 3})
        self.CC.update({"GT": 4})
        self.CC.update({"GE": 5})
        self.CC.update({"ANY": 6})

    def getType(self, s: str):
        s = s.upper()
        if (self.AD.__contains__(s)):
            return "AD"
        elif (self.IS.__contains__(s)):
            return "IS"
        elif (self.DL.__contains__(s)):
            return "DL"
        elif (self.CC.__contains__(s)):
            return "CC"
        elif (self.RG.__contains__(s)):
            return "RG"
        else:
            return ""

    def getCode(self, s: str):
        s = s.upper()
        if (self.AD.__contains__(s)):
            return self.AD.get(s)
        elif (self.IS.__contains__(s)):
            return self.IS.get(s)
        elif (self.DL.__contains__(s)):
            return self.DL.get(s)
        elif (self.CC.__contains__(s)):
            return self.CC.get(s)
        elif (self.RG.__contains__(s)):
            return self.RG.get(s)
        else:
            return -1


class PassOne:
    def __init__(self):
        self.symtab = {}
        self.littab = []
        self.pooltab = []
        self.lc = 0
        self.littab_file = open("littab.txt", "w")
        self.symtab_file = open("symtab.txt", "w")
        self.pooltab_file = open("pooltab.txt", "w")
        self.input = open("input.txt", "r")
        self.ic = open("intermidiate_code.txt", "w")
        self.inst_table = InstTable()

    def setLitAddrWhereIndex(self, index, addr):

        for i in range(len(self.littab)):
            if i == index:
                self.littab[i].setAddress(addr)
                return self.littab[i]

    def expr(self, expression):

        if ("+" in expression):
            parts = expression.split("+")
            return self.symtab[parts[0]].getAddress() + int(parts[1])
        elif ("-" in expression):
            parts = expression.split("-")
            return self.symtab[parts[0]].getAddress() - int(parts[1])
        else:
            if (self.symtab.__contains__(expression)):
                return self.symtab[expression].getAddress()
            else:
                return int(expression)

    def Process(self):
        symtab_index = 0
        lit_index = 0
        pool_ptr = 0
        lit_ptr = 0
        while (1):
            ipline = self.input.readline()
            if ipline == "":
                print("Pass One Complete")
                break
            parts = re.split("\\s+", ipline)

            if (parts[0] != ""):  # only possible for label declaration field
                if (self.symtab.__contains__(parts[0])):
                    self.symtab[parts[0]].setAddress(self.lc)
                else:
                    symtab_index += 1
                    self.symtab[parts[0]] = TableRow(
                        symtab_index, parts[0], self.lc)
            if (parts[1] == "START"):
                self.lc = self.expr(parts[2])
                code = f"(AD,01) (C,{self.lc})\n"
                self.ic.write(code)
            if (parts[1] == "ORIGIN"):
                self.lc = self.expr(parts[2])
                if ("+" in parts[2]):
                    elems = parts[2].split("+")
                    code = (
                        f"(AD,03) (S,0{self.symtab[elems[0]].getIndex()})+{int(elems[1])}")
                elif ("-" in parts[1]):
                    elems = parts[1].split("-")
                    code = (
                        f"(AD,03) (S,0{self.symtab[elems[0]].getIndex()})-{int(elems[1])}")
                self.ic.write(code+"\n")
            if (parts[1] == "EQU"):
                addr = self.expr(parts[2])
                if (self.symtab.__contains__(parts[0])):
                    self.symtab[parts[0]].setAddress(addr)
                else:
                    symtab_index += 1
                    self.symtab[parts[0]] = TableRow(
                        symtab_index, parts[0], addr)
                self.ic.write("\n")
            if (parts[1] == "DC"):
                self.lc += 1
                cnst = int(parts[2].replace("'", ""))
                code = f"(DL,01) (C,{cnst})"
                self.ic.write(code+"\n")
            elif (parts[1] == "DS"):
                size = int(parts[2].replace("'", ""))
                code = f"(DL,02) (C,{size})"
                self.ic.write(code+"\n")
                self.lc = self.lc+size
            if (self.inst_table.getType(parts[1]) == "IS"):
                code = f"(IS,0{self.inst_table.getCode(parts[1])}) "
                for i in range(2, len(parts)):
                    if (parts[i] == ""):
                        continue
                    if (self.inst_table.getType(parts[i]) == "RG"):
                        code += f"({self.inst_table.getCode(parts[i])}) "
                    elif (self.inst_table.getType(parts[i]) == "CC"):
                        code += f"({self.inst_table.getCode(parts[i])}) "
                    elif (parts[i].startswith("=")):
                        symbol = parts[i].replace("=", "").replace("'", "")
                        lit_index += 1
                        self.littab.append(TableRow(lit_index, symbol, -1))
                        code += f"(L,0{lit_index}) "
                        lit_ptr += 1
                    else:
                        if (self.symtab.__contains__(parts[i])):
                            code += f"(S,0{self.symtab[parts[i]].getIndex()}) "
                        else:
                            symtab_index += 1
                            self.symtab[parts[i]] = TableRow(
                                symtab_index, parts[i], -1)
                            code += f"(S,0{symtab_index}) "
                self.ic.write(code+"\n")
                self.lc += 1
            if (parts[1] == "LTORG"):
                for i in range(pool_ptr, lit_ptr):
                    tb = self.setLitAddrWhereIndex(i, self.lc)
                    code = f"(DL,01) (C,{tb.getSymbol()})\n"
                    self.ic.write(code)
                    self.lc += 1
                pool_ptr = lit_ptr
                self.pooltab.append(lit_ptr-1)
            if (parts[1] == "END"):
                if (len(parts) == 3 and parts[2] != ""):
                    self.ic.write(
                        f"(AD,02) (S,0{self.symtab[parts[2]].getIndex()})\n")
                else:
                    self.ic.write("(AD,02)\n")
                for i in range(pool_ptr, lit_ptr):
                    tb = self.setLitAddrWhereIndex(i, self.lc)
                    code = f"(DL,01) (C,{tb.getSymbol()})\n"
                    self.ic.write(code+"\n")
                    self.lc += 1
                pool_ptr += 1
                self.pooltab.append(lit_ptr)
                # write to symtab , littab and pooltab
                for key, value in self.symtab.items():
                    self.symtab_file.write(f"{str(value)}\n")
                for i in range(0, len(self.littab)):
                    self.littab_file.write(f"{str(self.littab[i])}\n")
                for i in range(0, len(self.pooltab)):
                    self.pooltab_file.write(f"#{str(self.pooltab[i])}\n")


p = PassOne()
p.Process()

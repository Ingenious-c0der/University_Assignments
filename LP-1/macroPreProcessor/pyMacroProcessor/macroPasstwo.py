import re


class MacroPassTwo:
    def __init__(self):
        self.mdt = open("LP-1\macroPreProcessor\pyMacroProcessor\mdt.txt", "r")
        self.pntab = open(
            "LP-1\macroPreProcessor\pyMacroProcessor\pntab.txt", "r")
        self.kptab = open(
            "LP-1\macroPreProcessor\pyMacroProcessor\kpdtab.txt", "r")
        self.mnt = open("LP-1\macroPreProcessor\pyMacroProcessor\mnt.txt", "r")
        self.calls = open(
            "LP-1\macroPreProcessor\pyMacroProcessor\calls.txt", "r")
        self.aptab_file = open(
            "LP-1\macroPreProcessor\pyMacroProcessor\\aptab.txt", "w")
        self.ec = open(
            "LP-1\macroPreProcessor\pyMacroProcessor\extended_code.txt", "w")
        self.mnt_dict = {}
        self.kpdtab_dict = {}
        self.pntab_list = []
        self.aptab = []

    def load_data(self):
        while (1):
            ipline = self.mnt.readline()
            if (ipline == ""):
                break
            else:
                words = ipline.split()
                self.mnt_dict[words[1]] = [
                    words[2], words[3], words[4], words[5]]
        while (1):
            ipline = self.kptab.readline()
            if (ipline == ""):
                break
            else:
                words = ipline.split()
                #kpdtab_list.append([words[0], words[1],words[2]])
                self.kpdtab_dict[words[1]] = [words[0], words[2]]
        while (1):
            ipline = self.pntab.readline()
            if (ipline == ""):
                break
            else:
                words = ipline.split()
                #kpdtab_list.append([words[0], words[1],words[2]])
                self.pntab_list.append((words[0], words[1]))
        print("Loaded data")

    def setIndexMDT(self, index):
        self.mdt.seek(0, 0)
        if (index == 0 or index == 1):
            return
        while (1):
            ipline = self.mdt.readline().rstrip("/n")
            if (ipline == "" or int(ipline.split()[0]) == index-1):
                return

    def getQ(self, param_name):
        for key in self.kpdtab_dict:
            if key == f"&{param_name}":
                return int(self.kpdtab_dict[key][0])
        return -1  # raise error

    def getDefault(self, kp_index):
        for key, value in self.kpdtab_dict.items():
            if (value[0] == f"{kp_index}"):
                return value[1]
        return -1  # raise error

    def Process(self):
        ipline = ""
        self.load_data()
        while (1):
            ipline = self.calls.readline()
            self.aptab = []
            if ipline == "":
                print("Macro Pass two complete")
                break
            else:
                elems = ipline.split()
                aptab_ctr = 0
                macroName = elems[0]
                totalPPCount = int(self.mnt_dict[macroName][0])
                totalKPCount = int(self.mnt_dict[macroName][1])
                mdt_start_point = int(self.mnt_dict[macroName][2])
                kpdtab_start = int(self.mnt_dict[macroName][3])
                for _ in range(totalKPCount + totalPPCount):
                    self.aptab.append(0)
                for element in elems[1:]:
                    if (re.match("(.+)(=)(.+)", element)):
                        params = element.split("=")
                        print(params)
                        q = self.getQ(params[0])
                        self.aptab[totalPPCount + q - kpdtab_start] = params[1]
                    else:
                        self.aptab[aptab_ctr] = element
                        aptab_ctr += 1
                for i in range(len(self.aptab)):
                    if self.aptab[i] == 0:
                        default_param = self.getDefault(
                            i+kpdtab_start - totalPPCount)
                        self.aptab[i] = default_param
                for i in range(len(self.aptab)):
                    self.aptab_file.write(f"{i+1} {self.aptab[i]}\n")
                self.setIndexMDT(mdt_start_point)
                ctr = 1
                while (1):
                    outline = ""
                    ipline = self.mdt.readline()
                    if ipline == "" or "MEND" in ipline:
                        break
                    words = ipline.split()
                    outline += f"{ctr } "
                    for element in words[1:]:
                        if (re.match("(\\()(.*)(\\))", element)):
                            num = int(element.split(",")[1].split(")")[0])
                            outline += f"{self.aptab[num-1]} "
                        else:
                            outline += f"{element} "
                    self.ec.write(f"{outline}\n")
                    ctr += 1


m = MacroPassTwo()
m.Process()

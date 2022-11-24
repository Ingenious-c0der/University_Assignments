import re  
class InputReader: 
    def __init__(self) -> None:
        self.file = open("LP-1\macroPreProcessor\pyMacroProcessor\input.txt","r")
    def readNextLine(self):
        line = self.file.readline().rstrip("\n")
        return ( line == "",line)
class MacroPassOne: 
    def __init__(self):
        self.ipReader = InputReader()
        self.mdt = open("LP-1\macroPreProcessor\pyMacroProcessor\mdt.txt","w")
        self.pntab = open("LP-1\macroPreProcessor\pyMacroProcessor\pntab.txt","w")
        self.kptab = open("LP-1\macroPreProcessor\pyMacroProcessor\kpdtab.txt","w")
        self.mnt = open("LP-1\macroPreProcessor\pyMacroProcessor\mnt.txt","w")
    
    def process(self):
        kptab_ptr = 1
        mdt_ptr = 1
        pntab_ptr = 1 
        mnt_index = 1 
        pntab_list = [ ]
        while(1):
            ipline = self.ipReader.readNextLine()
            if(ipline[0] == True):
                print("Macro Pass One Complete")
                break
            ipline = ipline[1]
            if(ipline =="MACRO"):
                kpCount = 0 
                ppCount = 0 
                macroName = "" ; 
                protosmt = self.ipReader.readNextLine()[1]
                words = protosmt.split()
                for word in words: 
                    if(re.match("(&.+)(=)(.+)",word)): #condition for keyword params with args
                        params = word.split("=")
                        self.pntab.write(f"{pntab_ptr} {params[0]}\n")
                        self.kptab.write(f"{kptab_ptr} {params[0]} {params[1]}\n")
                        kptab_ptr+=1 
                        pntab_ptr+=1
                        pntab_list.append(params[0])
                        kpCount+= 1
                    elif(re.match("(&.+)(=)",word)): #condition for keyword params without args
                        params = word.split("=")
                        self.pntab.write(f"{pntab_ptr} {params[0]}\n")
                        self.kptab.write(f"{kptab_ptr} {params[0]} ---\n")
                        kptab_ptr+=1 
                        pntab_ptr+=1 
                        kpCount+= 1 
                        pntab_list.append(params[0])
                    elif(re.match("(&.+)",word)): #condition for positional params
                        param_name = word.strip()
                        self.pntab.write(f"{pntab_ptr} {param_name}\n")
                        pntab_ptr+=1
                        ppCount += 1
                        pntab_list.append(param_name)
                    else: 
                        macroName = word#the macro name  
                self.mnt.write(f'{mnt_index} {macroName} {ppCount} {kpCount} {mdt_ptr} {kptab_ptr - kpCount}\n' )
                mnt_index+=1
            elif(ipline == "MEND"):
                self.mdt.write(f"{mdt_ptr} MEND\n" )
                pntab_ptr = 1 
                pntab_list = []
                mdt_ptr += 1
            else: 
                outline= ""
                elems = ipline.split();
                outline+= f"{mdt_ptr} {elems[0]} "
                if("&" in elems[1]) :
                    for i in range(len(pntab_list)):
                        if elems[1] == pntab_list[i]: 
                            outline+= f"(P,{i+1}) "
                else: 
                    outline+= elems[1]
                if("&" in elems[2]) :
                    for i in range(len(pntab_list)):
                        if elems[2] == pntab_list[i]: 
                            outline+= f"(P,{i+1}) "
                else: 
                    outline+= elems[2]
                self.mdt.write(outline+"\n")
                mdt_ptr+=1 
m = MacroPassOne()
m.process()


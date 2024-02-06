from CheckException import CheckException
import re

def writeNewInfo():
    positions = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4")]

    lista = CheckException("testando.txt").exception1()[4]
    text = open("testando.txt").read()

    allPositions = []
    for i in range(0,5):
        for j in range(0,5):
            allPositions.append(f"{j}x{i}")


    stringBlock = re.findall("\w \w+ \w \w+",text)
    stringBlock = [i[8].lower() for i in stringBlock]
    realPos = re.findall("o: \w+",text)
    realPos = [i[3:6]for i in realPos]


    nL =[]
    bloPos = list(zip(stringBlock,realPos))
    for i in bloPos:
        for j in positions:
            if(i[1] in j):
                nL.append([i[0],j[0]])
                

    for i in bloPos:
        
        for j in allPositions:
            if(i[1][0]=="0"):
                continue
            else:
                for k in bloPos:
                    if(allPositions[allPositions.index(i[1])-1] == k[1] and [i[0],k[0]] not in nL):
                        nL.append([i[0],k[0]])
                        
                        break

    info =[]
    for l in lista:
        
        check = re.search(f"{l}\(:init\(on {l} \w+\)\)\(:objective-0\(on {l} \w+\)\)",text)
        print(l)
        info.append(check.group())

    pos=[]
    repetidos = set()
    repPos = re.findall("on \w+",text)
    for i in repPos:
        if i not in pos:
            
            if(i[3]==" "):
                pos.append(i)
                
            else:
                pos.append(i)
                
        else:
            repetidos.add(i)

    newcheck =[]
    for x in nL:
            if(x[0] in lista):
                newcheck.append(f"(:init(on {x[0]} {x[1]}))")

    for y in range(0,len(newcheck)):
        newcheck[y] +=info[y][info[0].find("(:objective-0"):]

    
    for z in range(0,len(lista)):
        newcheck[z] = lista[z]+newcheck[z]

    return newcheck














    
    
    

    
    

    


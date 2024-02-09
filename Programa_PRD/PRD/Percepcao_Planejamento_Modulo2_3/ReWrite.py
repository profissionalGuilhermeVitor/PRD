from CheckException import CheckException
import re
import checkExc

def writeNewInfo(num):
    positions = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4")]
    actPosition = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4"),["a",""],["b",""],["c",""],["d",""],["e",""]]
    
    blocks = ["a","b","c","d","e"]
    blocksMiss = []
    b1ocksMis = []
    positionMiss =[]
    info = []

    
    

    
    text = open("testando.txt").read()
    iniPos = re.findall("co \w",text)
    iniPos = [a[3].lower() for a in iniPos]
    bloPosition = re.findall("\wx\w",text)
    obj = re.findall("\(:objective-0\(on \w \w+\)\)",text)
   
    for pos in bloPosition:
        if bloPosition.count(pos)>1:
            bloPosition.remove(pos)

    Amap = list(zip(iniPos,bloPosition))
    for i in Amap:
        for j in actPosition:
            if i[0] == j[0]:
                j[1] = i[1]
                break

    
    
    text2 = open('testando.txt').read()
    c=[]

    allPositions = []
    for i in range(0,5):
        for j in range(0,5):
            allPositions.append(f"{j}x{i}")
    c =""
    for u in actPosition[5:]:
        for c in Amap:
            if c[0] == u[0]: 
                if c[1][0] == "0":
                    for y in positions:
                        if y[1] == c[1]:
                            u[1] = y[0]
                else:
                    for f in Amap:
                        if allPositions[allPositions.index(c[1])-1] in f:
                            
                            u[1]=f[0]             

    if (num[0]=="6"):
        return checkExc.checkPosInit("testando.txt")[1]
        
        


    if num[0] =="3" or num[0]=="2":
        blocksMiss = [a[4] for a in num[1]]
        if len(num[1])<5:
            for h in blocks:
                if h not in blocksMiss:
                    b1ocksMis.append(h)
        else:
            for j in num[1]:
                for l in num[1]:
                    if(j[4] == l[6]):
                        b1ocksMis.append(j[4])
                        b1ocksMis.append(l[6])

        for u in b1ocksMis:
            if b1ocksMis.count(u)>1:
                b1ocksMis.remove(u)

        
        
        check = re.findall("O bloco \w",text2)
        posix = re.findall("\wx\w",text2)
        for i in posix:
            if posix.count(i)>1:
                posix.remove(i)

        
        check = [a[8].lower() for a in check]
        for u in b1ocksMis:
            
            checkB = re.search(f"\(:objective-0\(on {u} \w+\)\)",text2)

            info.append(checkB.group())

        
        map = list(zip(check,posix))
        for u in b1ocksMis:
            for c in map:
                if c[0] == u: 
                    if c[1][0] == "0":
                        for y in positions:
                            if y[1] == c[1]:
                                positionMiss.append(y[0])
                    else:
                        for f in map:
                            if allPositions[allPositions.index(c[1])-1] in f:
                                positionMiss.append(f[0])
        
        infoprint = list(zip(b1ocksMis,positionMiss))

        final =[]
        for b in range(0,len(infoprint)):
            for c in info:
                
                if f"on {infoprint[b][0]}" in c:
                    final.append(f"{infoprint[b][0]}(:init(on {infoprint[b][0]} {infoprint[b][1]}))" + c)
        
        return final


    elif(num[0]=="1i"):
        lista = CheckException("testando.txt").exception1()[4]

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
            print(check)
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
    
    elif(num[0] == '1o' or num[0]): return
    elif(num[0] == "6"): return checkExc.checkPosInit()[0]

excrt = CheckException("testando.txt")

#print(writeNewInfo(excrt.exception1()))












        
        
        

        
        

        


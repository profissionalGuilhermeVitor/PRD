import re
def checkPosInit(text1):
    positions = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4")]
    actPosition = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4"),["a",""],["b",""],["c",""],["d",""],["e",""]]
    text = open(text1,"r").read()
    
    iniPos = re.findall("co \w",text)
    iniPos = [a[3].lower() for a in iniPos]
    bloPosition = re.findall(": \wx\w",text)
    bloPosition = [a[2:] for a in bloPosition]
    obj = re.findall("\(:objective-0\(on \w \w+\)\)",text)
    check = re.findall(f"\w\(:init\(on \w \w+\)\)\(:objective-0\(on \w \w+\)\)",text)

    
    for pos in bloPosition:

        if bloPosition.count(pos)>1:

            bloPosition.remove(pos)

    Amap = list(zip(iniPos,bloPosition))

    
    for i in Amap:
        for j in actPosition:
            if i[0] == j[0]:
                j[1] = i[1]
                break

    c=[]


    allPositions = []
    for i in range(0,5):
        for j in range(0,5):
            allPositions.append(f"{j}x{i}")
    
    
    save = ""
    listas = []
    for i in Amap:
        if i[1][0] == "0":
            for j in positions:
                if i[1] == j[1]:
                    listas.append([i[0],j[0]])
    
        
        else:
            for k in allPositions:
                if i[1] == k:
                    save = allPositions[allPositions.index(k)-1]
                    for g in Amap:
                        if(g[1]==save):
                            listas.append([i[0],g[0]])

    final = []   
    itens =[]             

    for z in check:
        for c in listas:
            if f":init(on {c[0]} {c[1]}" not in z and c[0]==z[0]:
                itens.append(c[0])
                final.append(f"{c[0]}(:init(on {c[0]} {c[1]}))" + z[16:])

    if final ==[]:
        return None        


    return ["6"] + [final] + [obj] + [check] + [itens]
    


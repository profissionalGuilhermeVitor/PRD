import re
import checkExc
relacoesFixo = {
            "t1":("0x0","1x0","2x0","3x0","4x0"),
            "t2":("0x1","1x1","2x1","3x1","4x1"),
            "t3":("0x2","1x2","2x2","3x2","4x2"),
            "t4":("0x3","1x3","2x3","3x3","4x3"),
            "t5":("0x4","1x4","2x4","3x4","4x4") 
        }
class CheckException:
    def __init__(self,file):
        self.file = file
        
        

    def tratarArquivo(self):
        arq = open(self.file,'r')
        texto = arq.read()
        return texto
    
    def exception1(self):#Pegar objetivos e inits e verificar se posições batem
        txt1 = CheckException(self.file).tratarArquivo()
        #Listas para exceções
        actPosition = [('t1',"0x0"),('t2',"0x1"),('t3',"0x2"),('t4',"0x3"),('t5',"0x4"),["a",""],["b",""],["c",""],["d",""],["e",""]]
        excecao2 = re.findall("O bloco \w",txt1)
        excecao2 = [p[8].lower() for p in excecao2]
        excecao3 =re.findall("O bloco \w",txt1)
        excecao3 = [r[8].lower() for r in excecao3]

        #Filtro para inicio e objetivos
        init = re.findall(":init\(on \w \w+\)",txt1)#Predicados dos iniciais
        for act in actPosition[5:]:
            for g in init:
                if (g[9]==act[0]):
                    if(g[12]==")"):
                        act[1]=g[11]
                    else:
                        act[1]=g[11:13]
        init = [i[5:] for i in init]
        
        for g in init:
            for h in excecao3:
                if h == g[4]:
                    excecao3.remove(h)
                else:
                    continue
        
        
        objective = re.findall(":objective-0\(on \w \w+\)",txt1)#Predicados dos objetivos
        objteste = re.findall(":objective-0(\w+\s)",txt1)
        
        objective = [i[12:] for i in objective]
        #Criação de dicionarios com relações
        relacoesPiso = {
            "t1":"0x0",
            "t2":"0x1",
            "t3":"0x2",
            "t4":"0x3",
            "t5":"0x4",
        }

        filpos = re.findall(r'o: \wx\w',txt1)#Filtro de posições encontradas
        
        #Filtragem de posições repetidas no arquivo
        pos=[]
        repetidos = set()
        for i in filpos:
            if i not in pos:
                pos.append(i[3:6])
            else:
                repetidos.add(i)

        for i in pos:#Checar posições iguais colhidas-Exceção 0
            if(pos.count(i)>1):
                return '0'
            
        #Exceção de posicionamento 
            if (checkExc.checkPosInit(self.file) is None):
                continue
            else:
                return checkExc.checkPosInit(self.file)
        #Criar relação da posição com o bloco
        blocosIniciais = re.findall(":init\(on \w \w+\)",txt1)
        blocosIniciais = [i[9] for i in blocosIniciais]
        posicoesIniciaisI = re.findall(":init\(on \w \w+\)",txt1)
        posicoesIniciais = [i[11] if i[12]==')' else i[11:13] for i in posicoesIniciaisI]
        blocosOBJ = re.findall(":objective-0\(on \w \w+\)",txt1)
        blocosOBJ = [i[9] for i in blocosOBJ]
        posicoesOBJI = re.findall(":objective-0\(on \w \w+\)",txt1)
        posicoesOBJ = [i[18] if i[19]==')' else i[18:20] for i in posicoesOBJI]

        
        zipBV = list(zip(blocosIniciais,pos))
        mapa = [list(i) for i in relacoesFixo.values()]

        if len(init)<5:return ['3'] + [init] + [mapa] + [zipBV]+ [excecao3]
        elif len(objective)<5: return ['3o']

        relacao ={}

        for elemento1, elemento2 in zipBV:#Cria relação por meio de dicionário
            relacao[elemento1] = elemento2
            relacao[elemento2] = elemento1
        for i in range(0,5):
            for j in range(0,5):
                if mapa[i][j] in pos:
                    mapa[i][j] = relacao[mapa[i][j]]
                else:
                    mapa[i][j] = '0'

        #Objetivos e Posições iniciais iguais-Exceçao 1
        relacao.update(relacoesPiso)
        
        listaBoa = []
        blc =[]

        for i in list(enumerate(posicoesIniciais)):
            if((posicoesIniciais).count(i[1])>1):
                blc.append(blocosIniciais[i[0]])

        if(len(blc)!=0):
            return ['1i'] + [init] + [list(relacao)] + [listaBoa] + [blc]
            

        
        for i in posicoesOBJ:
            if(posicoesOBJ.count(i)>1):
                return ['1o']

        #Inconsistências em objetivos ou iniciais-Blocos na mesma posição que outros-Exceção 2
        counto =0
        counti = 0
        blt2 = []

        for a in objective:
            for j in objective:
                if(j[6] == a[4] and j[4]==a[6]):
                    counto +=1
                    if(counto>1):
                        blt2.append(j[6])
                        blt2.append(j[4])

        
        for a in init:
            for j in init:
                if(j[6] == a[4] and j[4]==a[6]):
                    counti +=1
                    if(counti>1):
                        blt2.append(j[6])
                        blt2.append(j[4])

        if(counto > 1 or counti > 1):return ['2'] + [init] + [mapa] + [zipBV] + [blt2]
        #Objetivo vazio-Exceção 3
        
        
        #Situações Impossíveis
        
        #Checagem de exceções por meio de mapa-Exceção 4
        #Checar posições impossíveis-Exceção 4_Parte 1 - blocos vazios no piso
        for checkImpossible in mapa:
            if(checkImpossible[0] == '0'):
                for index in checkImpossible:
                    if(checkImpossible.index(index)!=0 and index !='0'):
                        return ['4']
                    
        #Checar posições impossiveis em todo o mapa-Exceção 4_Parte 2 - blocos vazios em posições inferiores a existentes
        for checkImpossible2 in mapa:
            for i in checkImpossible2:
                if (i=='0'):
                    if(checkImpossible2[checkImpossible2.index(i)+1] !='0'):
                        return ['4_2']

#exEstatica = CheckException('tct.txt')
#print(exEstatica.exception1())

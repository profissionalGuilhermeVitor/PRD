import re
import numpy
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
        #Filtro para inicio e objetivos
        init = re.findall(":init\(\w on \w+\)",txt1)#Predicados dos iniciais
        init = [i[5:] for i in init]
        objective = re.findall(":objective-0\(\w on \w+\)",txt1)#Predicados dos objetivos
        objective = [i[12:] for i in objective]
        print(f'Vetor de estados iniciais:{init}')
        print(f'Vetor de estados Objetivos:{objective}')
        #Criação de dicionarios com relações
        relacoes = {
            "t1":["0x0","1x0","2x0","3x0","4x0"],
            "t2":["0x1","1x1","2x1","3x1","4x1"],
            "t3":["0x2","1x2","2x2","3x2","4x2"],
            "t4":["0x3","1x3","2x3","3x3","4x3"],
            "t5":["0x4","1x4","2x4","3x4","4x4"] 
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

        print(f'Posições dos Blocos: {pos}')
        for i in pos:#Checar posições iguais colhidas-Exceção 1
            if(pos.count(i)>1):
                return '0'
        #Criar relação da posição com o bloco
        mapa = [0 for i in range(0,25)]#Inicial para mapa de blocos
        piso = list(relacoes.keys())
        blocos = [f[1] for f in init]
        posicoes = [g[6] if g[7]==')' else g[6:8] for g in init]
        mapa = list(relacoes.values())
        zipBV = list(zip(blocos,pos))#Cria relação entre blocos e posições
        relacao = {}
        for elemento1, elemento2 in zipBV:#Cria relação por meio de dicionário
            relacao[elemento1] = elemento2
            relacao[elemento2] = elemento1
        for i in range(0,5):
            for j in range(0,5):
                if mapa[i][j] in pos:
                    mapa[i][j] = relacao[mapa[i][j]]
                else:
                    mapa[i][j] = '0'
        #Checagem de exceções por meio de mapa
        #Objetivos iguais-Exceçao 2
        exc1 = []
        exc2 = []
        for ex1 in objective:
            exc1.append(ex1[1])
            if ex1[7] ==')':
                exc2.append(ex1[6])
            else:
                exc2.append(ex1[6:8])

        for f1 in range(0,5):
            for f2 in range(0,5):
                try:#Tenta checcar a exceção de objetivos iguais, caso aconteça algum erro de objetivo vazio, retorna a exceção 3
                    if(f1==f2):
                        continue
                    elif(exc2[f1]==exc2[f2]):
                        return '1'
                except:
                    return '3'

        #Inconsistências em objetivos-Blocos na mesma posição que outros-Exceção 3
        count =0
        BlocosExcecao = []
        for f1 in objective:
            for f2 in objective:
                if(f1[1] == f2[6] and f2[1]==f1[6] and (f1[1] or f2[6]) not in BlocosExcecao):
                    count +=1
                    BlocosExcecao.append(f2[1])
                    BlocosExcecao.append(f2[6])
                else:
                    continue
        
                
        if count > 0:
            return '2'
        #Objetivo vazio-Exceção 4
        for testeOV in objective:
            if len(testeOV)<7:
                return '3'
            
        #Situações Impossíveis
        valores = []
        for x in list(zip(mapa,list(relacoesFixo.values()))):
            valores.append(list(zip(x[0],x[1])))
        count =0

        posicaoPiso = [(chave,valor[0]) for chave,valor in relacoesFixo.items()]
        
        #Checar posições impossíveis-Exceção 5_Parte 1 - blocos vazios no piso
        for check in mapa:
            if check[0] == '0':
                for j in check:
                    if j != '0':
                        return '4'
                    
        #Checar posições impossiveis em todo o mapa-Exceção 5_Parte 2 - blocos vazios em posições inferiores a existentes
        
        for iterator in mapa:
            posicaoanterior = ''
            for seconditerator in iterator:
                if seconditerator !='0':
                    if posicaoanterior == '0':
                        return '4'
                    else:
                        continue
                if seconditerator == '0':
                    posicaoanterior = seconditerator
                else:
                    continue


ex1 = CheckException('arquivo3_Exc4_2.txt')
print(ex1.exception1())

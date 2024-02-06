from CheckException import CheckException
exEstatica = CheckException('testando.txt')# Cria objeto de Verificador de exceção
def transfString():
    stringBlc=""
    for str in exEstatica.exception1()[4]:
        stringBlc += str
    
    return stringBlc

print(transfString())
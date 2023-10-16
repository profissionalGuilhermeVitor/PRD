//========================================= Configurações do Motor ==================================================================//    MOTOR 
// Pinos do motor X //
#define X_PIN_PASSO        54    // Pino de envio do sinal 
#define X_PIN_DIR          55    // Pino da direção do motor
#define X_PIN_ATIVAR       38    // Pino da ativação do motor
#define X_PIN_MAX           2    // Pino da chave de fim de curso em X (maximo)
#define X_PIN_MIN           3    // Pino da chave de fim de curso em X (mínimo)

//Pinos do motor Y //
#define Y_PIN_PASSO        60    // Pino de envio do sinal
#define Y_PIN_DIR          61    // Pino da direção do motor
#define Y_PIN_ATIVAR       56    // Pino da ativação do motor
#define Y_PIN_MAX          15    // Pino da chave de fim de curso em Y (maximo)
#define Y_PIN_MIN          14    // Pino da chave de fim de curso em Y (mínimo)

// Pinos do motor Z //
#define Z_PIN_PASSO        46    // Pino de envio do sinal
#define Z_PIN_DIR          48    // Pino da direção do motor
#define Z_PIN_ATIVAR       62    // Pino da ativação do motor
#define Z_PIN_MAX          19    // Pino da chave de fim de curso em Z (maximo)
#define Z_PIN_MIN          18    // Pino da chave de fim de curso em Z (mínimo)


int chaveFimCursoMIN_X = 0;  // Variável para a chave de fim de curso
int chaveFimCursoMAX_X = 0;  // Variável para a chave de fim de curso

int chaveFimCursoMIN_Y = 0;  // Variável para a chave de fim de curso

int chaveFimCursoMIN_Z = 0;  // Variável para a chave de fim de curso
int chaveFimCursoMAX_Z = 0;  // Variável para a chave de fim de curso

int contZeragem = 0;  // Contador
int contReiniciar = 0;  // Contador
int contCodigoPrincipal = 0;

int cont2 = 0;  // Contador

int posicaoAtual = 0;

int posicaoBlocoA = 10;
int posicaoBlocoB = 10;
int posicaoBlocoC = 10;

String MkA = "";
String MkB = "";
String MkC = "";
//============================================  Definir o Estado Final e Inicial da iPNRD  ===================================================//    iPNRD FINAL e INICIAL

String iPnrdFinalString = "BAC_";
String iPnrdInicialString = "";

//============================================  Definir o Vetor UK e sua Sequencia de Disparo  ===================================================//   
int vetorMKDaTag [3] = {0, 0, 0};
int matrizATDaTag [3][6] = {{0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0}
                           };

int vetorUKA [6] = {0, 0, 0, 0, 0, 0};
int vetorUKB [6] = {0, 0, 0, 0, 0, 0};
int vetorUKC [6] = {0, 0, 0, 0, 0, 0};
  
//================================================  Definir Matriz AT da PNRD  ======================================================//    Matriz AT da PNRD

const String matrizIncidenciaPNRDString = {"-1, 1,-1, 1, 0, 0, 1,-1, 0, 0,-1, 1, 0, 0, 1,-1, 1,-1"}; // Mater os espaçamentos identicos ao apresentado.

//================================================================  Acha o Vetor de Transições Com Melhor Caminho   ===========================================//   Busca em Largura 

const int matrizIncidenciaIPNRD[13][30] = { {-1,  1, -1,  1, -1,  1, -1,  1, -1,  1, -1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                                            { 1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1,  0,  0},
                                            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1}
                                          };
                               
int vetorTransicoes [4] = {0, 0, 0, 0};
int tamanhoVetorTransicoes = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int A_B_C_ = 1 ;

const int BA_C_ = 2 ;
const int BC_A_ = 3 ;
const int AB_C_ = 4 ;
const int AC_B_ = 5 ;
const int CA_B_ = 6 ;
const int CB_A_ = 7 ;

const int CBA_ = 8 ;
const int ABC_ = 9 ;
const int CAB_ = 10 ;
const int BAC_ = 11 ;
const int BCA_ = 12 ;
const int ACB_ = 13 ;

int iPnrdInicial = 0;
int iPnrdAtual = 0;
int iPnrdFinal = BAC_;


const int verticesDeA_B_C_ [6] = {BA_C_, BC_A_, AB_C_, AC_B_, CA_B_, CB_A_};

const int verticesDeBA_C_ [3] = {A_B_C_, BC_A_, CBA_};
const int verticesDeBC_A_ [3] = {A_B_C_, BA_C_, ABC_};
const int verticesDeAB_C_ [3] = {A_B_C_, AC_B_, CAB_};
const int verticesDeAC_B_ [3] = {A_B_C_, AB_C_, BAC_};
const int verticesDeCA_B_ [3] = {A_B_C_, CB_A_, BCA_};
const int verticesDeCB_A_ [3] = {A_B_C_, CA_B_, ACB_};

const int verticesDeCBA_ [1] = {BA_C_};
const int verticesDeABC_ [1] = {BC_A_};
const int verticesDeCAB_ [1] = {AB_C_};
const int verticesDeBAC_ [1] = {AC_B_};
const int verticesDeBCA_ [1] = {CA_B_};
const int verticesDeACB_ [1] = {CB_A_};

int fila [13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
int filaAux [14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int verticesMarcados [] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
int melhorCaminho [13] = {iPnrdFinal,0,0,0,0,0,0,0,0,0,0,0,0}; 
int ultimoValor = iPnrdFinal;

//========================================= Configurações da Biblioteca AccelStepper ==============================================//    AccelStepper
#include <AccelStepper.h>

#define InterfaceMotor 1
 
// Cria uma instância
AccelStepper stepperX (InterfaceMotor, X_PIN_PASSO, X_PIN_DIR);
AccelStepper stepperY (InterfaceMotor, Y_PIN_PASSO, Y_PIN_DIR);
AccelStepper stepperZ (InterfaceMotor, Z_PIN_PASSO, Z_PIN_DIR);


//========================================= Configurações do Leitor RFID =========================================================//    RFID

#include <Pn532NfcReader.h>
#include <PN532_HSU.h>
#include <NfcAdapter.h>

//Rotinas relacionadas à comunicação com o leitor RFID PN532
PN532_HSU pn532hsu(Serial2);
NfcAdapter nfc = NfcAdapter(pn532hsu);


//========================================= Configurações da Garra(Servo) =======================================================//    SERVO

#include <Servo.h> 
#define SERVO 6 // Porta Digital 6 PWM
Servo s; // Variável Servo

//=================================================== VOID SETUP ===============================================================//    *VOID SETUP*

void setup()
{  

//=============================================================================================================================//     MOTOR
// ========== Motor X ======================== //
  // Define a velocidade máxima, fator de aceleração,
 
  stepperX.setMaxSpeed(1000);   // Velocidade máxima
  stepperX.setAcceleration(250);   // Aceleração

  pinMode(X_PIN_ATIVAR, OUTPUT);  // Define o pino de ativação do motor X como saída
  digitalWrite(X_PIN_ATIVAR, LOW);  // O sinal LOW ativa o motor X

  pinMode(X_PIN_MIN, INPUT_PULLUP);  // Define o pino da chave de fim de curso de X como entrada

// ========== Motor Y ======================== //
  // Define a velocidade máxima, fator de aceleração,
 
  stepperY.setMaxSpeed(1000);   // Velocidade máxima
  stepperY.setAcceleration(250);   // Aceleração

  pinMode(Y_PIN_ATIVAR, OUTPUT);  // Define o pino de ativação do motor Y como saída
  digitalWrite(Y_PIN_ATIVAR, LOW);  // O sinal LOW ativa o motor Y

  pinMode(Y_PIN_MIN, INPUT_PULLUP);  // Define o pino da chave de fim de curso de Y como entrada

// ========== Motor Z ======================== //
  // Define a velocidade máxima, fator de aceleração,
 
  stepperZ.setMaxSpeed(1000);   // Velocidade máxima
  stepperZ.setAcceleration(250);   // Aceleração

  pinMode(Z_PIN_ATIVAR, OUTPUT);  // Define o pino de ativação do motor Z como saída
  digitalWrite(Z_PIN_ATIVAR, LOW);  // O sinal LOW ativa o motor Z

  pinMode(Z_PIN_MIN, INPUT_PULLUP);  // Define o pino da chave de fim de curso de Z como entrada

//=============================================================================================================================//    SERVO  

  s.attach(SERVO);//Liga o servo
    //Posição 170 = Maximo aberto
    //posição 130 = Maximo fechado
  //s.write(170); // Inicia motor posição zero, variar de 75 a 160
  delay(2000);
  //s.detach();//Desliga o servo
  
//===========================================================================================================================//     Iniciação
//Iniciação do leitor e da serial
  Serial.begin(9600);
  nfc.begin(); 
}

//=================================================== VOID LOOP ============================================================//    *VOID LOOP*
void loop()
{ 

    for(int i = 0; i < 180; i++){
    s.write(i); 
    delay(15); 
  }  
    
    /*
    if(contZeragem == 0){
       
       Serial.println("\nZeragem do Robo:"); 
       zeragem();
       contZeragem++;
    } 

    if (contCodigoPrincipal == 0) {
      if (contReiniciar == 1) {
        reiniciar();
      }

       contReiniciar = 1;

       bool excecaoVarredura = true;
       bool verificacao = true;

       excecaoVarredura = varredura();
       
///////Verificação do Posicionamento dos Blocos.
       if (excecaoVarredura == true) {
        
       Serial.println("\n\n\n====================================================================================================================");
       Serial.println("\nMelhor Caminho das Transições:");
       
///////Realiza a Busca em Largura.
       buscaEmLargura(iPnrdInicial);
       
///////Encontra o vetor Uk da iPNRD.
       verificacao = acharVetorTransicoesFinal();
       
       if (verificacao == true){
          Serial.println("\nEtapa Final Alcançada, Retornando a Posição 0x0 !");
          movimentaY(0);
          posicoes(1);
          Serial.println("\nPrograma Finalizado com Sucesso !!!");
          contCodigoPrincipal++;
       } else if (verificacao == false) {
          Serial.println("\n*************************************************************************************************");
          Serial.println("\nReiniciando, refazendo a Varredura: ");
          contCodigoPrincipal = 0;
       }
       
       //Serial.println("\nSegunda varredura:");
       //varredura();
      } else if (excecaoVarredura == false) {
           movimentaY(0);
           posicoes(1);
           Serial.println("ERRO NA VARREDURA!!! Verifique as condições iniciais e reinicie o programa!");
           contCodigoPrincipal++; 
      }
    }  */
}

//====================================================  Reiniciar os Valores das Variaveis Globais   =======================================================//     *FUNÇÕES*
void reiniciar(){
  
   cont2 = 0;
   posicaoAtual = 0;

   posicaoBlocoA = 10;
   posicaoBlocoB = 10;
   posicaoBlocoC = 10;

   MkA = "";
   MkB = "";
   MkC = "";
   
   String iPnrdInicialString = "";

   for (int i = 0; i < 6; i++){
    vetorUKA [i] = 0;
    vetorUKB [i] = 0;
    vetorUKC [i] = 0;
   }

   for (int i = 0; i < 4; i++){
      vetorTransicoes [i] = 0;
   }
   
   tamanhoVetorTransicoes = 0;

   iPnrdInicial = 0;
   iPnrdAtual = 0;

   for (int i = 0; i < 13; i++){
      fila [i] = 0;
      verticesMarcados [i] = 0;
      filaAux [i] = 0;
      melhorCaminho [i] = 0;
   }
   
   filaAux [13] = 0;
   melhorCaminho [0] = iPnrdFinal;
    
   ultimoValor = iPnrdFinal;
   
}

//====================================================  Zera a Posição do Robo  ============================================================================//    
void zeragem(){
  
    chaveFimCursoMIN_X = digitalRead(X_PIN_MIN); // Verfica se a chave de fim de curso de X foi acionada
    chaveFimCursoMIN_Y = digitalRead(Y_PIN_MIN); // Verfica se a chave de fim de curso de Y foi acionada
    chaveFimCursoMIN_Z = digitalRead(Z_PIN_MIN); // Verfica se a chave de fim de curso de Z foi acionada

    stepperX.moveTo(-17000);
    stepperY.moveTo(-35000);
    stepperZ.moveTo(-17000);
    
    if (chaveFimCursoMIN_Y != LOW){
      while (chaveFimCursoMIN_Y != LOW){
        stepperY.run();
        chaveFimCursoMIN_Y = digitalRead(Y_PIN_MIN); // Verfica se a chave de fim de curso de Y foi acionada
      }
       
    }
    
    if (chaveFimCursoMIN_X != LOW){
      while (chaveFimCursoMIN_X != LOW){
        stepperX.run();
        chaveFimCursoMIN_X = digitalRead(X_PIN_MIN); // Verfica se a chave de fim de curso de X foi acionada
      }
       
    }

    if (chaveFimCursoMIN_Z != LOW){
      while (chaveFimCursoMIN_Z != LOW){
        stepperZ.run();
        chaveFimCursoMIN_Z = digitalRead(Z_PIN_MIN); // Verfica se a chave de fim de curso de Z foi acionada
      }
       
    }

    delay(1000);

    chaveFimCursoMIN_X = digitalRead(X_PIN_MIN); // Verfica se a chave de fim de curso de X foi acionada
    chaveFimCursoMIN_Y = digitalRead(Y_PIN_MIN); // Verfica se a chave de fim de curso de Y foi acionada
    chaveFimCursoMIN_Z = digitalRead(Z_PIN_MIN); // Verfica se a chave de fim de curso de Z foi acionada

    if (chaveFimCursoMIN_X == LOW && chaveFimCursoMIN_Y == LOW && chaveFimCursoMIN_Z == LOW){
      
      stepperX.setCurrentPosition(0);
      stepperY.setCurrentPosition(0);
      stepperZ.setCurrentPosition(0);

      // Ponto 0x0(X-Z), origem.
      stepperX.moveTo(3137);
      stepperY.moveTo(10000); // YMax = 30000, YMin = 10000.
      stepperZ.moveTo(3773);

      while (stepperY.currentPosition() < 10000){
        stepperX.run();
        stepperZ.run();
        stepperY.run();
      }

      stepperX.setCurrentPosition(0);
      stepperY.setCurrentPosition(0);
      stepperZ.setCurrentPosition(0);
    }

    stepperY.setMaxSpeed(2500);   // Velocidade máxima
    stepperY.setAcceleration(500);   // Aceleração
    
    posicaoAtual = 1; 
    Serial.println( "\nOrigem(Z-X): " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3764) );
   
}

//=======================================================  Sobe ou Desce o Y  ==============================================================================//
void movimentaY(int direcao){
   
   // direcao == 0, Y sobe.
   // direcao == 1, Y desce.
   
   if (direcao == 0){

       stepperY.moveTo(0); // YMax = 20000, YMin = 0, depois da zeragem.
   
       while (stepperY.currentPosition() > 0){
          stepperY.run();
       }
       
   } else if (direcao == 1){
       
       stepperY.moveTo(20000); // YMax = 20000, YMin = 0, depois da zeragem.
   
       while (stepperY.currentPosition() < 20000){
          stepperY.run();
       }
   }
}

//=================================================  Garra(Abre, Fecha, Liga e Desliga)  ====================================================================//
void garra(int comando){

  switch (comando){
    case 0:
      s.detach();// Desliga o servo.  
      break;
    case 1:
      s.attach(SERVO);// Liga o servo.  
      break;
    case 2:
      s.write(170); // Abre a garra.
      delay(500);
      break;
    case 3:
      s.write(130); // Fecha a garra.
      delay(500);
      break;
  }
  
}

//====================================================  Varredura Inicial do Robo  =========================================================================//
bool varredura(){
   
   Serial.println("\nVerificação do Posicionamento dos Blocos:");
   movimentaY(0);
   posicoes(1);
  
   String temBloco = "";
   String MK = "";
   int contBlocos = 0;
   int contPosicoes = 0;
   int contErros = 0; // Se der 3 erros significa que ha algo de errado na configuração inicial dos blocos. 
   int contRepeticoes[3] = {0, 0, 0};
   int posicaoPassada = 0;
   
   garra(1); // Liga o servo.
   garra(2); // Abre a garra.
   
   
   
   while ( (contBlocos < 5) && (contPosicoes < 25)){
      
      // 0 -> Y Sobe.
      // 1 -> Y Desce.
      movimentaY(1);
      
      temBloco = identifica();
  
      if (temBloco == "A" || temBloco == "B" || temBloco == "C"){
  
        if (temBloco == "A"){
            ++contRepeticoes[0];
          } else if (temBloco == "B"){
            ++contRepeticoes[1];
          }else if (temBloco == "C"){
            ++contRepeticoes[2];
          }
        
        if (contRepeticoes[0] >= 2 || contRepeticoes[1] >= 2 || contRepeticoes[2] >= 2){
            Serial.println("ERRO: Bloco Repetido em Posição Diferente!");
            return false;
          }
                  
        
        salvarPosicoes(temBloco);
        MK = vetorMk(temBloco);
        gravarEtiquetas(MK);
        
        movimentaY(0);
        posicaoPassada = posicaoAtual;
        ++contBlocos;
        ++contPosicoes;
        
        if(contBlocos == 3){
          Serial.println("\nSUCESSO: Todos os Blocos Foram Encontrados!");
          printar();
          iPnrdInicialString = pnrdToIPnrd ();
          iPnrdInicial = iPnrdAtual;
          Serial.println("\nEstado inicial da iPNRD: ");
          Serial.println(iPnrdInicialString);
          cont2++;
          break;
        }
        posicoes(posicaoAtual + 3);
        
       
     } else if (temBloco == "false"){

        movimentaY(0);
        contErros++;
        ++contPosicoes;

        if (contErros == 3) {
          Serial.println("ERRO: Condição inicial de blocos não confere!");
          return false;
        }

        if ((posicaoAtual - posicaoPassada) <= 2){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual + 1);  
        } else if ( ((posicaoAtual - posicaoPassada) == 3) && (posicaoAtual < 7) ){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual - 2);
        } else if (((posicaoAtual - posicaoPassada) == 3) && (posicaoAtual >= 7)){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual - 5);
        }
     } 
  }

  // Retorna ao inicio.
  posicoes(1);
  Serial.println("Varredura Finalizada!");
  return true;
}

//======================================================  Identifica os Blocos  ============================================================================//
String identifica(){
   
   unsigned long tempo = 0;
   tempo = millis();

   String uid = "";
   
   while((millis() - tempo) <= 2000){
        if (nfc.tagPresent()){
          NfcTag tag = nfc.read();
          uid = tag.getUidString();
        }
   }

   //Serial.println(uid);

   if (uid == "42 1B E5 DD"){
      Serial.println("\nO bloco A esta na posição: " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3764)  );
      
      return "A";
   } else if (uid == "82 A9 C5 DF"){
      Serial.println("\nO bloco B esta na posição: " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3764)  );
      
      return "B";
   } else if (uid == "C2 AD C5 DF"){
      Serial.println("\nO bloco C esta na posição: " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3764)  );
      
      return "C";
   } else {
      Serial.println("ERRO 1!");
      return "false";
   }
    
}


//=======================================================  Movimentação do Robo  ===========================================================================//
void movimentacao(int posicaoZ, int posicaoX){

  stepperX.moveTo(posicaoX);
  stepperZ.moveTo(posicaoZ);

    while ( (stepperX.currentPosition() != posicaoX) || (stepperZ.currentPosition() != posicaoZ) ){
        stepperX.run();
        stepperZ.run();
      }
   
    Serial.println( "\nPosição(Z-X): " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3764) );
}

//================================================  Posições Possiveis para os Blocos  =====================================================================//

void posicoes(int posicao){

    int posicao_X = 0;
    int posicao_Z = 0;

    posicaoAtual = posicao;
        
    switch (posicao){
      
      case 1: 
          //0x0

          posicao_Z = 0;
          posicao_X = 0;

          movimentacao(posicao_Z, posicao_X);
          
        break;
      
      case 2:
          //0x1
          
          posicao_Z = 0;
          posicao_X = 1509;
          
          movimentacao(posicao_Z, posicao_X);
      
        break;
      
      case 3:
          //0x2
          posicao_Z = 0;
          posicao_X = 3018;

          movimentacao(posicao_Z, posicao_X);

        break;
        
        case 4:
          //0x3
          posicao_Z = 0;
          posicao_X = 4527;

          movimentacao(posicao_Z, posicao_X);

        break;

      case 5:
          //0x4
          posicao_Z = 0;
          posicao_X = 6036;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 6:
          //1x0
          posicao_Z = 1509;
          posicao_X = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

      case 7:
          //1x1
          posicao_Z = 1509;
          posicao_X = 1509;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 8:
          //1x2
          posicao_Z = 1509;
          posicao_X = 3018;

          movimentacao(posicao_Z, posicao_X);
          
        break;
        
      case 9:
          //1x3
          posicao_Z = 1509;
          posicao_X = 4527;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 10:
          //1x4
          posicao_Z = 1509;
          posicao_X = 6036;

          movimentacao(posicao_Z, posicao_X);

        break;
        
        case 11:
          //2x0
          posicao_Z = 3018;
          posicao_X = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 12:
          //2x1
          posicao_Z = 3018;
          posicao_X = 1509;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 13:
          //2x2
          posicao_Z = 3018;
          posicao_X = 3018;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 14:
          //2x3
          posicao_Z = 3018;
          posicao_X = 4527;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 15:
          //2x4
          posicao_Z = 3018;
          posicao_X = 6036;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 16:
          //3x0
          posicao_Z = 4527;
          posicao_X = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 17:
          //3x1
          posicao_Z = 4527;
          posicao_X = 1509;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 18:
          //3x2
          posicao_Z = 4527;
          posicao_X = 3018;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 19:
          //3x3
          posicao_Z = 4527;
          posicao_X = 4527;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 20:
          //3x4
          posicao_Z = 4527;
          posicao_X = 6036;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 21:
          //4x0
          posicao_Z = 6036;
          posicao_X = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 22:
          //4x1
          posicao_Z = 6036;
          posicao_X = 1509;
          movimentacao(posicao_Z, posicao_X);

        break;

        case 23:
          //4x2
          posicao_Z = 6036;
          posicao_X = 3018;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 24:
          //4x3
          posicao_Z = 6036;
          posicao_X = 4527;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 25:
          //4x4
          posicao_Z = 6036;
          posicao_X = 6036;

          movimentacao(posicao_Z, posicao_X);

        break;
  }
  
}

//==============================================  Salvar as Posições Atuais dos Blocos  ====================================================================//

int salvarPosicoes(String Bloco){

  int posicao = 10;
  
  int Z = (stepperZ.currentPosition() / 3773);
  int X = (stepperX.currentPosition() / 3764);

  if (Z == 0 && X == 0){
      posicao = 1;
    } else if (Z == 0 && X == 1){
      posicao = 2;
    }else if (Z == 0 && X == 2){
      posicao = 3;
    }else if (Z == 1 && X == 0){
      posicao = 4;
    }else if (Z == 1 && X == 1){
      posicao = 5;
    }else if (Z == 1 && X == 2){
      posicao = 6;
    }else if (Z == 2 && X == 0){
      posicao = 7;
    }else if (Z == 2 && X == 1){
      posicao = 8;
    }else if (Z == 2 && X == 2){
      posicao = 9;
    }

  if (Bloco == "A"){
      posicaoBlocoA = posicao;
    } else if (Bloco == "B"){
      posicaoBlocoB = posicao;
    }else if (Bloco == "C"){
      posicaoBlocoC = posicao;
    } else if (Bloco == "PosicaoAtual"){
      return posicao;
    }
}

//=================================================  Printar as Posições dos Blocos ========================================================================//

void printar(){

  Serial.println("Bloco A: " + (String)(posicaoBlocoA) + "; Bloco B: " + (String)(posicaoBlocoB) + "; Bloco C: " + (String)(posicaoBlocoC));

}

//================================================  Determinar o Vetor Mk dos Blocos =======================================================================//

String vetorMk(String temBloco){

// MkA:
  if (posicaoBlocoA == 1){ // Bloco A sobre a mesa.
      MkA = "1, 0, 0";
    } else if (posicaoBlocoA == 6 || posicaoBlocoA == 8){ // Bloco A sobre C.
      MkA = "0, 1, 0";
    } else if (posicaoBlocoA == 5 || posicaoBlocoA == 9){ // Bloco A sobre B.
      MkA = "0, 0, 1";
    }
    
// MkB:
  if (posicaoBlocoB == 2){ // Bloco B sobre a mesa.
      MkB = "1, 0, 0";
    } else if (posicaoBlocoB == 6 || posicaoBlocoB == 7){ // Bloco B sobre C.
      MkB = "0, 1, 0";
    } else if (posicaoBlocoB == 4 || posicaoBlocoB == 9){ // Bloco B sobre A.
      MkB = "0, 0, 1";
    }

// MkC:
  if (posicaoBlocoC == 3){ // Bloco C sobre a mesa.
      MkC = "1, 0, 0";
    } else if (posicaoBlocoC == 5 || posicaoBlocoC == 7){ // Bloco C sobre B.
      MkC = "0, 1, 0";
    } else if (posicaoBlocoC == 4 || posicaoBlocoC == 8){ // Bloco C sobre A.
      MkC = "0, 0, 1";
    }

    if (temBloco == "A"){
        return MkA;
      } else if (temBloco == "B"){
        return MkB;
      }else if (temBloco == "C"){
        return MkC;
      }
}

//===========================================  Gravar Vetor Mk e Matriz AT nas Etiquetas  ==================================================================//

void gravarEtiquetas(String vetorMk){

  String aux = "";
  
  if (cont2 == 0) {
    aux = "AT: " + matrizIncidenciaPNRDString + "; MK: " + vetorMk; // Primeira gravação das informações é feita na varredura.
  } else {
      aux = vetorMk; // Gravação feita apos atualizar o vetor MK, ou seja, depois que os blocos foram movidos, ja contendo a matriz AT que não é alterada.
    }
  boolean success = false;
  
  Serial.println("\nGravando Etiqueta:");

  while(success != true){
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addUriRecord(aux);

        success = nfc.write(message);
        if (success) {
          Serial.println("Sucesso na Gravação da Etiqueta!");        
        } else {
          Serial.println("ERRO! A Gravação da Etiqueta Falhou!");
        }
    }
    delay(2000);
  }
}

//===========================================  Lê e Altera o Vetor Mk mas Mantem a Matriz AT   =================================================================//
String alterarVetorMK (String vetor) {

  int index = 0;

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    NdefMessage message = tag.getNdefMessage();
    NdefRecord record = message.getRecord(0);

    int payloadLength = record.getPayloadLength();
    byte payload[payloadLength];
    record.getPayload(payload);

    String payloadAsString = "";
    for (int i = 0; i < payloadLength; i++) {
       payloadAsString += (String)(char)payload[i];
    }

    index = payloadAsString.indexOf("MK:");
    payloadAsString.remove((index + 4));
    payloadAsString.concat(vetor);

    return payloadAsString;
 }
}

//================================================  Mapeamento da PNRD para a iPNRD   ======================================================================//
String pnrdToIPnrd () {
  
  String iPnrdStateString = "";
  
  if (MkA == "1, 0, 0" && MkB == "1, 0, 0" && MkC == "1, 0, 0") {
    iPnrdStateString = "A_B_C_";
    iPnrdAtual = A_B_C_; 
  } else if (MkA == "1, 0, 0" && MkB == "0, 0, 1" && MkC == "1, 0, 0") {
    iPnrdStateString = "BA_C_";
    iPnrdAtual = BA_C_; 
  } else if (MkA == "1, 0, 0" && MkB == "1, 0, 0" && MkC == "0, 0, 1") {
    iPnrdStateString = "CA_B_";
    iPnrdAtual = CA_B_; 
  } else if (MkA == "1, 0, 0" && MkB == "0, 0, 1" && MkC == "0, 1, 0") {
    iPnrdStateString = "CBA_";
    iPnrdAtual = CBA_; 
  } else if (MkA == "1, 0, 0" && MkB == "0, 1, 0" && MkC == "0, 0, 1") {
    iPnrdStateString = "BCA_";
    iPnrdAtual = BCA_; 
  } else if (MkA == "0, 0, 1" && MkB == "1, 0, 0" && MkC == "1, 0, 0") {
    iPnrdStateString = "AB_C_";
    iPnrdAtual = AB_C_;
  } else if (MkA == "1, 0, 0" && MkB == "1, 0, 0" && MkC == "0, 1, 0") {
    iPnrdStateString = "CB_A_";
    iPnrdAtual = CB_A_;
  } else if (MkA == "0, 0, 1" && MkB == "1, 0, 0" && MkC == "0, 0, 1") {
    iPnrdStateString = "CAB_";
    iPnrdAtual = CAB_;
  } else if (MkA == "0, 1, 0" && MkB == "1, 0, 0" && MkC == "0, 1, 0") {
    iPnrdStateString = "ACB_";
    iPnrdAtual = ACB_;
  } else if (MkA == "0, 1, 0" && MkB == "1, 0, 0" && MkC == "1, 0, 0") {
    iPnrdStateString = "AC_B_";
    iPnrdAtual = AC_B_;
  } else if (MkA == "1, 0, 0" && MkB == "0, 1, 0" && MkC == "1, 0, 0") {
    iPnrdStateString = "BC_A_";
    iPnrdAtual = BC_A_;
  } else if (MkA == "0, 1, 0" && MkB == "0, 0, 1" && MkC == "1, 0, 0") {
    iPnrdStateString = "BAC_";
    iPnrdAtual = BAC_;
  } else if (MkA == "0, 0, 1" && MkB == "0, 1, 0" && MkC == "1, 0, 0") {
    iPnrdStateString = "ABC_";
    iPnrdAtual = ABC_;
  } else {
    Serial.println("ERRO 2!");
  }

  return iPnrdStateString;
  
}


//========================================  Descobrir a Melhor Rota de Transições da iPNRD (Busca em Largura)  ================================================================//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool acharVetorTransicoesFinal () {
  bool verificacao = true;
  
  for (int i = 0; i < 4; i++) {
    if (vetorTransicoes[i] != 0) {
      tamanhoVetorTransicoes++;
    }
  }

  int vetorTransicoesFinal [tamanhoVetorTransicoes] = {};
  
  for (int i = 0; i < tamanhoVetorTransicoes; i++) {
      vetorTransicoesFinal[i] = vetorTransicoes[i];
  }

  Serial.println("\nVetor Transições Final: ");
  printarFilas (vetorTransicoesFinal, tamanhoVetorTransicoes);

  Serial.println("\nMovimentação da Posição Inicial para a Final: ");
  Serial.println("O Robo ira de " + iPnrdInicialString + " Para " + iPnrdFinalString + " :");
  
  verificacao = transicoesIPnrdToPetriSpace (vetorTransicoesFinal, tamanhoVetorTransicoes);
  
  return verificacao;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void buscaEmLargura(int vertice){

    int x = 0;
    int contAux = 0;
    int tamanhoVetor = 0;
    
    
/////////////////////////////////////////////////////////    
   if(contAux == 0){
    fila [0] = vertice;
    verticesMarcados [0] = vertice;
      
    contAux++;
   
   }
///////////////////////////////////////////////////////////    
    
  while (x != iPnrdFinal) {

    switch (vertice) {
      case 1:
      
        saiPrimeiroFila();
        tiraRepetidos(6, verticesDeA_B_C_);            
        break;
        
      case 2:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeBA_C_);   
        break;
          
      case 3:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeBC_A_);   
        break;
          
      case 4:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeAB_C_);   
        break;
          
      case 5:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeAC_B_);   
        break;
          
      case 6:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeCA_B_);   
        break;
          
      case 7:
      
        saiPrimeiroFila();
        tiraRepetidos(3, verticesDeCB_A_);   
        break;
          
      case 8:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeCBA_);   
        break;
          
      case 9:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeABC_);   
        break;
          
      case 10:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeCAB_);   
        break;
          
      case 11:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeBAC_);   
        break;
          
      case 12:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeBCA_);   
        break;
          
      case 13:
      
        saiPrimeiroFila();
        tiraRepetidos(1, verticesDeACB_);   
        break;
          
      break;
    }

    vertice = fila[0];

    for (int i = 0; i < 13; i++) {
      if (verticesMarcados[i] == 0){
        verticesMarcados[i] = fila[0];
        break;
      }
    }

    for (int i = 0; i < 13; i++) {
      if (fila[i] == iPnrdFinal){
        x = iPnrdFinal;
        break;
      }
    }
  }

// Tamanho Vetor de Marcados:    
   
    tamanhoVetor = tamanhoArray(verticesMarcados);

///////////////////////////////////////////////////////
  if ((x == iPnrdFinal)) {

   Serial.println("\nEncontrado!!!");
   
   analisaVertice(tamanhoVetor);
   
   // Tamanho Vetor do Melhor Caminho :    
   int tamanho = tamanhoArray(melhorCaminho); 

   // Colocar o Vetor Melhor Caminho na Ordem Correta :

   int melhorCaminhoFinal [tamanho] = {};
   
   for (int i = 0; i < tamanho; i++) {
      melhorCaminhoFinal[i] = melhorCaminho [(tamanho - (1 + i))];
   }

   Serial.println("\nMelhor Caminho Final: ");
   printarFilas(melhorCaminhoFinal, tamanho);

   transicoesIPnrd(tamanho, melhorCaminhoFinal);

  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void transicoesIPnrd (int tamanhoVetor, int vetorMelhorCaminho[]) { 
  
   for (int i = 1; i < tamanhoVetor; i++) {
    for (int j = 0; j < 30; j++) {
      if (matrizIncidenciaIPNRD[(vetorMelhorCaminho[(i - 1)] - 1)][j] == -1 &&  matrizIncidenciaIPNRD[(vetorMelhorCaminho[(i)] - 1)][j] == 1) {
        for (int k = 0; k < 4; k++) {
          if (vetorTransicoes[k] == 0) {
            vetorTransicoes[k] = (j + 1);
            break;
          }
        }
      }
    }
   }
}

////////////////////////////////////////////////////////  Calcula o tamanho Real do Vetor   ////////////////////////////////////////////////////

int tamanhoArray (int vetor []) {
  
  int espaco = 0;
  
  for (int i = 0; i < 13; i++) {
      if (vetor[i] != 0){
        espaco++;
      }
    }
  return espaco;
}

/////////////////////////////////////////////////  Procura o Ultimo Valor nos Vertices Marcados   //////////////////////////////////////////////
void analisaVertice (int tamanhoVetor){
  
       int verifica = 0;
       
       for (int i = 0; i < tamanhoVetor; i++) {
       
       switch (verticesMarcados[i]){
        
        case 1:
            verifica = caminho (6, verticesDeA_B_C_, verticesMarcados[i]);
          break;
          
        case 2:
            verifica = caminho (3, verticesDeBA_C_, verticesMarcados[i]);
          break;
          
        case 3:
            verifica = caminho (3, verticesDeBC_A_, verticesMarcados[i]);
          break;
          
        case 4:
            verifica = caminho (3, verticesDeAB_C_, verticesMarcados[i]);
          break;
          
        case 5:
            verifica = caminho (3, verticesDeAC_B_, verticesMarcados[i]);
          break;
          
        case 6:
            verifica = caminho (3, verticesDeCA_B_, verticesMarcados[i]);
          break;
          
        case 7:
            verifica = caminho (3, verticesDeCB_A_, verticesMarcados[i]);
          break;
          
        case 8:
            verifica = caminho (1, verticesDeCBA_, verticesMarcados[i]);
          break;
          
        case 9:
            verifica = caminho (1, verticesDeABC_, verticesMarcados[i]);
          break;
          
        case 10:
            verifica = caminho (1, verticesDeCAB_, verticesMarcados[i]);
          break;
          
        case 11:
            verifica = caminho (1, verticesDeBAC_, verticesMarcados[i]);
          break;
          
        case 12:
            verifica = caminho (1, verticesDeBCA_, verticesMarcados[i]);
          break;
          
        case 13:
            verifica = caminho (1, verticesDeACB_, verticesMarcados[i]);
          break;
      }

      if (verifica == 1) {
        i = -1;
        verifica = 0;
      } else if (verifica == 2){
        i = tamanhoVetor;
      }
  }
}

/////////////////////////////////////////////////  Achar Menor Caminho Entre os Vertices  //////////////////////////////////////////////
int caminho (int numVertices, int vertices[], int vetor){

   for (int j = 0; j < numVertices; j++) {
      if (vertices[j] == ultimoValor){
        for (int k = 0; k < 13; k++){
          if (melhorCaminho[k] == 0){
            melhorCaminho[k] = vetor;
            ultimoValor = vetor;
            break;
          }
        }
        if (ultimoValor == iPnrdInicial){
          return 2;
        } else {
          return 1;
        }
      }
   }
   return 0; 
}

///////////////////////////////////////////////////////  Tira o Primeiro Valor da Fila  /////////////////////////////////////////////////
void saiPrimeiroFila () {
  
  for (int i = 0; i < 13; i++) {
        filaAux[i] = fila[i];
  }
  for (int i = 0; i < 13; i++) {
        fila[i] = filaAux[i+1];
  }
}

/////////////////////////////////////////////////  Verificar Repetição e Acrescentar a Fila  ///////////////////////////////////////////
void tiraRepetidos (int numVertices, int vertices[]) {
  
  int y = 0;
  
  for (int j = 0; j < numVertices; j++) {
    for (int k = 0; k < 13; k++) {
      if ((vertices[j] == verticesMarcados[k]) || (vertices[j] == fila[k])) {
        y = 1;
        break;
      }
    }
                    
    if (y == 0){
     for (int i = 0; i < 13; i++){
        if (fila[i] == 0){
          fila[i] = vertices[j];
          break;
        }
     }
    } else {
          y = 0;
      }
  }  
}
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printarFilas (int filas[], int tamanhoVetor) {

  for (int i = 0; i < tamanhoVetor; i++) {
        Serial.println(filas[i]);
      }
}

//=============================================  Transições no Espaço de Petri do Robo  ====================================================================//
void transicoesEspacoDePetri (int transicao) {
  switch (transicao) {
    // 0 -> Y Sobe.
    // 1 -> Y Desce.
    
    case 0:
      posicoes(7);
      movimentaY(1);
      break;
    case 1:
      movimentaY(0);
      break;
    case 2:
      posicoes(4);
      movimentaY(1);
      break;
    case 3:
      movimentaY(0);
      break;
    case 4:
      posicoes(1);
      movimentaY(1);
      break;
    case 5:
      movimentaY(0);
      break;
    case 6:
      posicoes(8);
      movimentaY(1);
      break;
    case 7:
      movimentaY(0);
      break;
    case 8:
      posicoes(5);
      movimentaY(1);
      break;
    case 9:
      movimentaY(0);
      break;
    case 10:
      posicoes(2);
      movimentaY(1);
      break;
    case 11:
      movimentaY(0);
      break;
    case 12:
      posicoes(9);
      movimentaY(1);
      break;
    case 13:
      movimentaY(0);
      break;
    case 14:
      posicoes(6);
      movimentaY(1);
      break;
    case 15:
      movimentaY(0);
      break;
    case 16:
      posicoes(3);
      movimentaY(1);
      break;
    case 17:
      movimentaY(0);
      break;
    case 18:
      posicoes(8);
      break;
    case 19:
      posicoes(7);
      break;
    case 20:
      posicoes(9);
      break;
    case 21:
      posicoes(8);
      break;
    case 22:
      posicoes(9);
      break;
    case 23:
      posicoes(7);
      break;
    case 24:
      movimentaY(0);
      posicoes(4);
      movimentaY(1);
      break;
    case 25:
      movimentaY(0);
      posicoes(7);
      movimentaY(1);
      break;
    case 26:
      movimentaY(0);
      posicoes(5);
      movimentaY(1);
      break;
    case 27:
      movimentaY(0);
      posicoes(8);
      movimentaY(1);
      break;
    case 28:
      movimentaY(0);
      posicoes(6);
      movimentaY(1);
      break;
    case 29:
      movimentaY(0);
      posicoes(9);
      movimentaY(1);
      break;
  }
}

//=============================================  Movimenta o Robo Para a Posição de Inicio das Transições  ====================================================================//
bool condicaoInicialTransicoes (int posicaoDesejada) {
  // 0 -> Y Sobe.
  // 1 -> Y Desce.
  String temBloco = "";
  
  if (salvarPosicoes("PosicaoAtual") != posicaoDesejada){
          // Abre Garra:
          movimentaY(0);
          posicoes(posicaoDesejada);
          movimentaY(1);
          
          temBloco = identifica();
          
          if (temBloco == "false") {
            // Reiniciar o codigo pela Varedura Inicial.
            return false;
          } else {
            return true;
          }
        }
}

//=============================================  Movimenta o Robo de Acordo com o Vetor de Transições  ====================================================================//
bool transicoesIPnrdToPetriSpace (int transicoes[] ,int tamanhoVetor) {

  bool verificacao = true;
  String temBloco = "";
  String MK = "";
  String MKAlterado = "";
  
  for (int i = 0; i < tamanhoVetor; i++){ 
   Serial.print("\nTransição ");
   Serial.print(transicoes[i]);
   Serial.print(" :\n");

   vetorDisparo (transicoes[i]);
   
   switch(transicoes[i]) {
      case 1:

        verificacao = condicaoInicialTransicoes(2);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(11);
        //transicoesEspacoDePetri(19);
        transicoesEspacoDePetri(2);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 2:

        verificacao = condicaoInicialTransicoes(4);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(3);
        //transicoesEspacoDePetri(18);
        transicoesEspacoDePetri(10);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 3:

        verificacao = condicaoInicialTransicoes(2);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(11);
        //transicoesEspacoDePetri(20);
        transicoesEspacoDePetri(14);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 4:

        verificacao = condicaoInicialTransicoes(6);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(15);
        //transicoesEspacoDePetri(21);
        transicoesEspacoDePetri(10);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 5:

        verificacao = condicaoInicialTransicoes(1);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(5);
        //transicoesEspacoDePetri(18);
        transicoesEspacoDePetri(8);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 6:

        verificacao = condicaoInicialTransicoes(5);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(9);
        //transicoesEspacoDePetri(19);
        transicoesEspacoDePetri(4);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 7:

        verificacao = condicaoInicialTransicoes(1);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(5);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(14);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 8:

        verificacao = condicaoInicialTransicoes(6);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(15);
        //transicoesEspacoDePetri(23);
        transicoesEspacoDePetri(4);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 9:

        verificacao = condicaoInicialTransicoes(3);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(17);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(2);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 10:

        verificacao = condicaoInicialTransicoes(5);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(9);
        //transicoesEspacoDePetri(20);
        transicoesEspacoDePetri(16);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 11:

        verificacao = condicaoInicialTransicoes(3);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(17);
        //transicoesEspacoDePetri(21);
        transicoesEspacoDePetri(8);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 12:

        verificacao = condicaoInicialTransicoes(4);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(3);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(16);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 13:

        verificacao = condicaoInicialTransicoes(6);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(15);
        //transicoesEspacoDePetri(23);
        transicoesEspacoDePetri(2);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 14:

        verificacao = condicaoInicialTransicoes(4);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(3);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(14);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 15:

        verificacao = condicaoInicialTransicoes(5);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(9);
        //transicoesEspacoDePetri(20);
        transicoesEspacoDePetri(14);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 16:

        verificacao = condicaoInicialTransicoes(6);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(15);
        //transicoesEspacoDePetri(21);
        transicoesEspacoDePetri(8);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 17:

        verificacao = condicaoInicialTransicoes(5);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(9);
        //transicoesEspacoDePetri(19);
        transicoesEspacoDePetri(2);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 18:

        verificacao = condicaoInicialTransicoes(4);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(3);
        //transicoesEspacoDePetri(18);
        transicoesEspacoDePetri(8);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 19:

        verificacao = condicaoInicialTransicoes(3);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(17);
        //transicoesEspacoDePetri(23);
        transicoesEspacoDePetri(0);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 20:

        verificacao = condicaoInicialTransicoes(7);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(1);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(16);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 21:

        verificacao = condicaoInicialTransicoes(1);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(5);
        //transicoesEspacoDePetri(22);
        transicoesEspacoDePetri(12);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 22:

        verificacao = condicaoInicialTransicoes(9);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(13);
        //transicoesEspacoDePetri(23);
        transicoesEspacoDePetri(4);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 23:

        verificacao = condicaoInicialTransicoes(3);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(17);
        //transicoesEspacoDePetri(21);
        transicoesEspacoDePetri(6);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 24:

        verificacao = condicaoInicialTransicoes(8);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(7);
        //transicoesEspacoDePetri(20);
        transicoesEspacoDePetri(16);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 25:

        verificacao = condicaoInicialTransicoes(2);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(11);
        //transicoesEspacoDePetri(20);
        transicoesEspacoDePetri(12);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 26:

        verificacao = condicaoInicialTransicoes(9);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(13);
        //transicoesEspacoDePetri(21);
        transicoesEspacoDePetri(10);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 27:

        verificacao = condicaoInicialTransicoes(2);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(11);
        //transicoesEspacoDePetri(19);
        transicoesEspacoDePetri(0);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 28:

        verificacao = condicaoInicialTransicoes(7);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(1);
        //transicoesEspacoDePetri(18);
        transicoesEspacoDePetri(10);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 29:

        verificacao = condicaoInicialTransicoes(1);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(5);
        //transicoesEspacoDePetri(18);
        transicoesEspacoDePetri(6);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;
        
      case 30:

        verificacao = condicaoInicialTransicoes(8);
        if (verificacao == false ) {
          break; 
        }

        // Fecha Garra:
        transicoesEspacoDePetri(7);
        //transicoesEspacoDePetri(19);
        transicoesEspacoDePetri(4);

        verificacao = verificacaoVetorMarcacao ();
        // Abre Garra:
        
        break;

   }

   if (verificacao == false) {
      return verificacao;
    }
   
   
   temBloco = identifica();
   
   salvarPosicoes(temBloco);
   MK = vetorMk(temBloco);
   MKAlterado = alterarVetorMK(MK);
   gravarEtiquetas(MKAlterado); 
   
  }
  
  return true;
}

//========================================  Criar Vetor de Disparo (Uk) da PNRD com Base nas Transições do Vetor de Transições Final   ==============================================//
void vetorDisparo (int transicoesIPNRD) {
  
    for (int i = 0; i < 6; i++){
    vetorUKA [i] = 0;
    vetorUKB [i] = 0;
    vetorUKC [i] = 0;
   }
    
    if ( transicoesIPNRD == 1 || transicoesIPNRD == 25 ) {
      vetorUKB [(3 - 1)] = 1;
    } else if ( transicoesIPNRD == 2 || transicoesIPNRD == 26 ) {
      vetorUKB [(4 - 1)] = 1;
    } else if ( transicoesIPNRD == 3 || transicoesIPNRD == 27 ) {
      vetorUKB [(1 - 1)] = 1;
    } else if ( transicoesIPNRD == 4 || transicoesIPNRD == 28 ) {
      vetorUKB [(2 - 1)] = 1;
    } 
    
    else if ( transicoesIPNRD == 5 || transicoesIPNRD == 21 ) {
      vetorUKA [(3 - 1)] = 1; 
    } else if ( transicoesIPNRD == 6 || transicoesIPNRD == 22 ) {
      vetorUKA [(4 - 1)] = 1; 
    } else if ( transicoesIPNRD == 7 || transicoesIPNRD == 29 ) {
      vetorUKA [(1 - 1)] = 1;
    } else if ( transicoesIPNRD == 8 || transicoesIPNRD == 30 ) {
      vetorUKA [(2 - 1)] = 1;
    } 
    
    else if ( transicoesIPNRD == 9 || transicoesIPNRD == 23 ) {
      vetorUKC [(3 - 1)] = 1;
    } else if ( transicoesIPNRD == 10 || transicoesIPNRD == 24 ) {
      vetorUKC [(4 - 1)] = 1;
    } else if ( transicoesIPNRD == 11 || transicoesIPNRD == 19 ) {
      vetorUKC [(1 - 1)] = 1; 
    } else if ( transicoesIPNRD == 12 || transicoesIPNRD == 20 ) {
      vetorUKC [(2 - 1)] = 1;
    } 

    else if ( transicoesIPNRD == 13 ) {
      vetorUKB [(5 - 1)] = 1; 
    } else if ( transicoesIPNRD == 14 ) {
      vetorUKB [(6 - 1)] = 1;
    } else if ( transicoesIPNRD == 15 ) {
      vetorUKA [(6 - 1)] = 1;
    } else if ( transicoesIPNRD == 16 ) {
      vetorUKA [(5 - 1)] = 1;
    } else if ( transicoesIPNRD == 17 ) {
      vetorUKC [(5 - 1)] = 1;
    } else if ( transicoesIPNRD == 18 ) {
      vetorUKC [(6 - 1)] = 1;
    } 
}

//=============================================  Verificação do Vetor de Marcações (Mk+1) para Verificar se o Caminho esta Correto  ================================================//
bool verificacaoVetorMarcacao () {
   
  String temBloco = "";
  String MK = "";
  String MKAux = "";
  
  int vetorATxUK_A [3] = {0, 0, 0};
  int vetorATxUK_B [3] = {0, 0, 0};
  int vetorATxUK_C [3] = {0, 0, 0};
  
  int vetorMk1_A [3] = {0, 0, 0};
  int vetorMk1_B [3] = {0, 0, 0};
  int vetorMk1_C [3] = {0, 0, 0};
  
  int multAux = 0;
  
  temBloco = identifica();
  salvarPosicoes(temBloco);
  
  retiraATeMK();
  
  MK = vetorMk(temBloco);
  
  // Mk+1 = Mk + At x Uk
  if ( temBloco == "A" ) { 
 
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 6; j++) {
        multAux += matrizATDaTag [i][j] * vetorUKA [j] ;
      }
      
      vetorATxUK_A [i] = multAux;
      vetorMk1_A [i] = vetorATxUK_A [i] + vetorMKDaTag [i];
      multAux = 0;
      MKAux = MK.substring((i*3), (i*3)+1);
      
      if (vetorMk1_A [i] != MKAux.toInt()) {
         Serial.println("ERRO!!! O Bloco A seguiu por um caminho diferente!");
         // Reiniciar o codigo pela Varedura Inicial.
         return false;
      } else if (vetorMk1_A [i] == MKAux.toInt()) {
        Serial.println("A OK");
      }
    }
    
  } else   if ( temBloco == "B" ) {
 
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 6; j++) {
        multAux += matrizATDaTag [i][j] * vetorUKB [j] ;
      }
      
      vetorATxUK_B [i] = multAux;
      vetorMk1_B [i] = vetorATxUK_B [i] + vetorMKDaTag [i];
      multAux = 0;
      MKAux = MK.substring((i*3), (i*3)+1);
      
      if (vetorMk1_B [i] != MKAux.toInt()) {
         Serial.println("ERRO!!! O Bloco B seguiu por um caminho diferente!");
         // Reiniciar o codigo pela Varedura Inicial.
         return false;
      } else if (vetorMk1_B [i] == MKAux.toInt()) {
        Serial.println("B OK");
      }
    }
    
  } else if ( temBloco == "C" ) {
    
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 6; j++) {
        multAux += matrizATDaTag [i][j] * vetorUKC [j] ;
      }
      
      vetorATxUK_C [i] = multAux;
      vetorMk1_C [i] = vetorATxUK_C [i] + vetorMKDaTag [i];
      multAux = 0;
      MKAux = MK.substring((i*3), (i*3)+1);
      
      if (vetorMk1_C [i] != MKAux.toInt()) {
         Serial.println("ERRO!!! O Bloco C seguiu por um caminho diferente!");
         // Reiniciar o codigo pela Varedura Inicial.
         return false;
      } else if (vetorMk1_C [i] == MKAux.toInt()) {
        Serial.println("C OK");
      }
    }
  } else if (temBloco == "false") {
    Serial.println("ERRO!!! O Bloco não foi encontrado!");
    // Reiniciar o codigo pela Varedura Inicial.
    return false;
  }
}

//=============================================  Retira a Matriz AT e o Vetor MK da Tag  ================================================//
void retiraATeMK () {
  
  int indexAT = 0;
  int indexMK = 0;
  
  String aux = "";
  String StringAuxiliarAT = "";
  String StringAuxiliarMK = "";

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    NdefMessage message = tag.getNdefMessage();
    NdefRecord record = message.getRecord(0);

    int payloadLength = record.getPayloadLength();
    byte payload[payloadLength];
    record.getPayload(payload);

    String payloadAsString = "";
    for (int i = 0; i < payloadLength; i++) {
       payloadAsString += (String)(char)payload[i];
    }

    indexAT = payloadAsString.indexOf("AT:");
    indexMK = payloadAsString.indexOf("MK:");
    
    StringAuxiliarAT = payloadAsString.substring((indexAT + 4), 57);
    StringAuxiliarMK = payloadAsString.substring((indexMK + 4));
    
    for (int i = 0; i < 3; i++) {
      aux = StringAuxiliarMK.substring((i*3), (i*3)+1);
      vetorMKDaTag [i] = aux.toInt();
    }

    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 6; j++) {
        aux = StringAuxiliarAT.substring((3*j + 18*i),(3*j + 18*i) + 2);
        matrizATDaTag [i][j] = aux.toInt();
      }
    }
    
  }
}

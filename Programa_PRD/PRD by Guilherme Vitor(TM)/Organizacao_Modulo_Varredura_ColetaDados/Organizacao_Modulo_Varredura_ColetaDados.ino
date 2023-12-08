//========================================= Configurações do Motor ==================================================================//    MOTOR 
//========================================= SETS necessários ==================================================================//
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

// Declaração de váriaveis

String messages[5][5] = {{"0","0","0","0","0"},{"0","0","0","0","0"},{"0","0","0","0","0"},
                          {"0","0","0","0","0"},{"0","0","0","0","0"}};// mensagens inseridas nos blocos
String mapa[5][5] = {{"0","0","0","0","0"},{"0","0","0","0","0"},{"0","0","0","0","0"},
                          {"0","0","0","0","0"},{"0","0","0","0","0"}};//mapa com as strings de identificação dos blocos
String mapaObjetivo[5][5] = {{"0","0","0","0","0"},{"0","0","0","0","0"},{"0","0","0","0","0"},
                          {"0","0","0","0","0"},{"0","0","0","0","0"}};// mapa apenas com os (:objective-0) dos blocos
String mensagemPred = "";
String mensagemMapa = "";
String mensagemObj = "";

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

int i = 0;
int j = 0;



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
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#if 1
//Rotinas relacionadas à comunicação com o leitor RFID PN532
PN532_HSU pn532hsu(Serial2);
NfcAdapter nfc = NfcAdapter(pn532hsu);
#else
//Criação de objeto para leitura e escrita da Tag RFID considerando o modo I2C do PN532
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

//========================================= Configurações da Garra(Servo) =======================================================//    SERVO

#include <Servo.h> 
#define SERVO 6 // Porta Digital 6 PWM
Servo s; // Variável Servo

//=================================================== VOID SETUP ===============================================================// 
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
  zeragem();
  varredura();
  
  } 

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
      stepperY.moveTo(2500); // YMax = 30000, YMin = 10000.
      stepperZ.moveTo(3773);

      while (stepperY.currentPosition() < 2500){
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
    Serial.println( "\nOrigem(Z-X): " + (String)(stepperZ.currentPosition() / 3773) + "x" + (String)(stepperX.currentPosition() / 3773) );
   
}
//====================================================  Varredura Inicial do Robo e funções de movimentação  =========================================================================//
bool varredura(){
   Serial.println(millis());
   Serial.println("\nVerificação do Posicionamento dos Blocos:");
   movimentaY(0);
   posicoes(1);
  
   String temBloco = "";
   int contBlocos = 0;
   int contPosicoes = 0;
   int contErros = 0; // Se der 5 erros significa que ha algo de errado na configuração inicial dos blocos. 
   int contRepeticoes[5] = {0, 0, 0, 0, 0};
   int posicaoPassada = 0;
   
   garra(1); // Liga o servo.
   garra(2); // Abre a garra.
   
   
   while ( ( contBlocos < 5 ) && (contPosicoes < 25)){
      // 0 -> Y Sobe.
      // 1 -> Y Desce.
      movimentaY(1);
      
      temBloco = identifica();// Descobre e atualiza qual bloco está sendo identificado

      if (temBloco == "A" || temBloco == "B" || temBloco == "C" || temBloco == "D" || temBloco == "E"){
        if (temBloco == "A"){
          messages[i][j] = tagToString();// Mensagem armazenada
            ++contRepeticoes[0];
          } else if (temBloco == "B"){
            messages[i][j] = tagToString();// Mensagem armazenada
            ++contRepeticoes[1];
          }else if (temBloco == "C"){
            messages[i][j] = tagToString();// Mensagem armazenada
            ++contRepeticoes[2];
          }else if (temBloco == "D"){
            messages[i][j] = tagToString();// Mensagem armazenada
            ++contRepeticoes[3];
          }else if (temBloco == "E"){
            messages[i][j] = tagToString();// Mensagem armazenada
            ++contRepeticoes[4];
          }
        
        if (contRepeticoes[0] >= 2 || contRepeticoes[1] >= 2 || contRepeticoes[2] >= 2|| contRepeticoes[3] >= 2|| contRepeticoes[4] >= 2){
            Serial.println("ERRO: Bloco Repetido em Posição Diferente!");
            return false;
          }
        
        movimentaY(0);
        posicaoPassada = posicaoAtual;
        ++contBlocos;
        ++contPosicoes;
        mapa[i][j] = temBloco;
      //Atualização de Mensagem de Predicados  
    for(int a =0;a<5;a++){
      if(a==0){
        mensagemPred.concat("(");
        }
      for(int b =0;b<5;b++){
        if(b ==0){
          mensagemPred.concat("(");
        }
        mensagemPred.concat(messages[a][b]);
         if(b !=4){
          mensagemPred.concat(",");
        }
        else{
          mensagemPred.concat(")");
          }
      }
        if(a !=4){
          mensagemPred.concat(",");
        }
        else{
          mensagemPred.concat(")");
          }
  }
      //Atualização de Mensagem de Mapa
    for(int a =0;a<5;a++){
      if(a==0){
        mensagemMapa.concat("(");
        }
      for(int b =0;b<5;b++){
        if(b ==0){
          mensagemMapa.concat("(");
        }
        mensagemMapa.concat(mapa[a][b]);
         if(b !=4){
          mensagemMapa.concat(",");
        }
        else{
          mensagemMapa.concat(")");
          }
      }
        if(a !=4){
          mensagemMapa.concat(",");
        }
        else{
          mensagemMapa.concat(")");
          }
  }

      //Atualização de objetivos
    for(int a =0;a<5;a++){
      if(a==0){
        mensagemObj.concat("(");
        }
      for(int b =0;b<5;b++){
        if(b ==0){
          mensagemObj.concat("(");
        }
        mensagemObj.concat(messages[a][b].substring(31,38));
         if(b !=4){
          mensagemObj.concat(",");
        }
        else{
          mensagemObj.concat(")");
          }
      }
        if(a !=4){
          mensagemObj.concat(",");
        }
        else{
          mensagemObj.concat(")");
          }
  } 
        posicoes(posicaoAtual + 5);
        
        if(contBlocos == 5 ){
          Serial.println("\nSUCESSO: 5 Blocos Foram Encontrados!");
          break;
        }else if(contBlocos == 4 && posicaoAtual == 10){
          Serial.println("\nSUCESSO: 4 Blocos Foram Encontrados!");
          
        }else if(contBlocos == 3 && posicaoAtual == 10){
          Serial.println("\nSUCESSO: 3 Blocos Foram Encontrados!");
          
        }else if(contBlocos < 3 && posicaoAtual == 15){
          Serial.println("\nERRO: FALTA MÍNIMO DE BLOCOS");
          break;
          }
        
       
     } else if (temBloco == "false"){
        movimentaY(0);
        contErros++;
        ++contPosicoes;

        if (contErros == 5) {
          Serial.println("ERRO: Condição inicial de blocos não confere!");
          return false;
        }
        if ((posicaoAtual - posicaoPassada) <= 4){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual + 1); 
        }  else if (((posicaoAtual - posicaoPassada) >= 5) && (posicaoAtual < 11 && posicaoAtual >=6)){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual - 4);
        }else if (((posicaoAtual - posicaoPassada) >= 5) && (posicaoAtual < 16 && posicaoAtual >=11)){
          posicaoPassada = posicaoAtual;

          posicoes(posicaoAtual - 9);
        }else if (((posicaoAtual - posicaoPassada) >= 5) && (posicaoAtual < 20 && posicaoAtual >=16)){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual - 14);
        }else if (((posicaoAtual - posicaoPassada) >= 5) && (posicaoAtual < 25 && posicaoAtual >=21)){
          posicaoPassada = posicaoAtual;
          posicoes(posicaoAtual - 19);
        }
     } 
  }

  // Retorna ao inicio.
  posicoes(1);
  Serial.println("Varredura Finalizada!");
  return true;
}
void movimentaY(int direcao){
   
   // direcao == 0, Y sobe.
   // direcao == 1, Y desce.
   
   if (direcao == 0){

       stepperY.moveTo(0); // YMax = 20000, YMin = 0, depois da zeragem.
   
       while (stepperY.currentPosition() > 0){
          stepperY.run();
       }
       
   } else if (direcao == 1){
       
       stepperY.moveTo(25500); // YMax = 20000, YMin = 0, depois da zeragem.
   
       while (stepperY.currentPosition() < 25500){
          stepperY.run();
       }
   }
}

void posicoes(int posicao){

    int posicao_X = 0;
    int posicao_Z = 0;

    posicaoAtual = posicao;
        
    switch (posicao){
      
      case 1: 
          //0x0

          posicao_Z = 0;
          i =0;
          posicao_X = 0;
          j=0;

          movimentacao(posicao_Z, posicao_X);
          
        break;
      
      case 2:
          //0x1
          
          posicao_Z = 0;
          i =0;
          posicao_X = 1509;
          j = 1;
          
          movimentacao(posicao_Z, posicao_X);
      
        break;
      
      case 3:
          //0x2
          posicao_Z = 0;
          posicao_X = 3018;
          i = 0;
          j = 2;

          movimentacao(posicao_Z, posicao_X);

        break;
        
        case 4:
          //0x3
          posicao_Z = 0;
          posicao_X = 4527;
          i = 0;
          j = 3;

          movimentacao(posicao_Z, posicao_X);

        break;

      case 5:
          //0x4
          posicao_Z = 0;
          posicao_X = 6036;
          i = 0;
          j = 4;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 6:
          //1x0
          posicao_Z = 1509;
          posicao_X = 0;
          i = 1;
          j = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

      case 7:
          //1x1
          posicao_Z = 1509;
          posicao_X = 1509;
          i = 1;
          j = 1;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 8:
          //1x2
          posicao_Z = 1509;
          posicao_X = 3018;
          i = 1;
          j = 2;

          movimentacao(posicao_Z, posicao_X);
          
        break;
        
      case 9:
          //1x3
          posicao_Z = 1509;
          posicao_X = 4527;
          i = 1;
          j = 3;

          movimentacao(posicao_Z, posicao_X);

        break;
        
      case 10:
          //1x4
          posicao_Z = 1509;
          posicao_X = 6036;
          i = 1;
          j = 4;

          movimentacao(posicao_Z, posicao_X);

        break;
        
        case 11:
          //2x0
          posicao_Z = 3018;
          posicao_X = 0;
          i = 2;
          j = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 12:
          //2x1
          posicao_Z = 3018;
          posicao_X = 1509;
          i = 2;
          j = 1;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 13:
          //2x2
          posicao_Z = 3018;
          posicao_X = 3018;
          i = 2;
          j = 2;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 14:
          //2x3
          posicao_Z = 3018;
          posicao_X = 4527;
          i = 2;
          j = 3;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 15:
          //2x4
          posicao_Z = 3018;
          posicao_X = 6036;
          i = 2;
          j = 4;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 16:
          //3x0
          posicao_Z = 4527;
          posicao_X = 0;
          i = 3;
          j = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 17:
          //3x1
          posicao_Z = 4527;
          posicao_X = 1509;
          i = 3;
          j = 1;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 18:
          //3x2
          posicao_Z = 4527;
          posicao_X = 3018;
          i = 3;
          j = 2;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 19:
          //3x3
          posicao_Z = 4527;
          posicao_X = 4527;
          i = 3;
          j = 3;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 20:
          //3x4
          posicao_Z = 4527;
          posicao_X = 6036;
          i = 3;
          j = 4;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 21:
          //4x0
          posicao_Z = 6036;
          posicao_X = 0;
          i = 4;
          j = 0;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 22:
          //4x1
          posicao_Z = 6036;
          posicao_X = 1509;
          i = 4;
          j = 1;
          
          movimentacao(posicao_Z, posicao_X);

        break;

        case 23:
          //4x2
          posicao_Z = 6036;
          posicao_X = 3018;
          i = 4;
          j = 2;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 24:
          //4x3
          posicao_Z = 6036;
          posicao_X = 4527;
          i = 4;
          j = 3;

          movimentacao(posicao_Z, posicao_X);

        break;

        case 25:
          //4x4
          posicao_Z = 6036;
          posicao_X = 6036;
          i = 4;
          j = 4;

          movimentacao(posicao_Z, posicao_X);

        break;
  }
  
}


void movimentacao(int posicaoZ, int posicaoX){

  stepperX.moveTo(posicaoX);
  stepperZ.moveTo(posicaoZ);

    while ( (stepperX.currentPosition() != posicaoX) || (stepperZ.currentPosition() != posicaoZ) ){
        stepperX.run();
        stepperZ.run();
      }

}

//====================================================  FIM DE DECLARAÇÃO DE FUNÇÕES DE MOVIMENTAÇÃO =======================================================


//===================================================== DECLARAÇÂO DE FUNÇÔES DO LEITOR PN532 ========================================================//
void readNFC()
{
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();
    }
    delay(5000);
}

void writeNFC(){
      Serial.println("\nPlace a formatted Mifare Classic NFC tag on the reader.");
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addUriRecord("(:init(E on t5))(:objective-0(E on t5))");

        bool success = nfc.write(message);
        if (success) {
          Serial.println("Success. Try reading this tag with your phone.");        
        } else {
          Serial.println("Write failed.");
        }
    }
    delay(5000);
  
  }

void clearNFC(){
      Serial.println("\nPlace a tag on the NFC reader to clean.");

    if (nfc.tagPresent()) {

        bool success = nfc.clean();
        if (success) {
            Serial.println("\nSuccess, tag restored to factory state.");
        } else {
            Serial.println("\nError, unable to clean tag.");
        }

    }
    delay(5000);
  
  }

void formatNFC(){
      Serial.println("\nPlace an unformatted Mifare Classic tag on the reader.");
    if (nfc.tagPresent()) {

        bool success = nfc.format();
        if (success) {
          Serial.println("\nSuccess, tag formatted as NDEF.");
        } else {
          Serial.println("\nFormat failed.");
        }

    }
    delay(5000);
  }
String tagToString()
{
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
    return payloadAsString;
 }
}
//===================================================== FIM DE DECLARAÇÂO DE FUNÇÔES DO LEITOR PN532 ========================================================//

//===================================================== FUNÇÃO DA GARRA ========================================================//

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


//===================================================== FIM DE DECLARAÇÂO DE FUNÇÃO DA GARRA ========================================================//


//============================================ FUNÇÃO DE IDENTIFICAR DADOS =================================================================

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
      Serial.println("\nO bloco A esta na posição: " + (String)(stepperZ.currentPosition() / 1509) + "x" + (String)(stepperX.currentPosition() / 1509)  );
      Serial.println(tagToString());
      
      return "A";
   } else if (uid == "82 A9 C5 DF"){
      Serial.println("\nO bloco B esta na posição: " + (String)(stepperZ.currentPosition() / 1509) + "x" + (String)(stepperX.currentPosition() / 1509)  );
      Serial.println(tagToString());
      
      return "B";
   } else if (uid == "C2 AD C5 DF"){
      Serial.println("\nO bloco C esta na posição: " + (String)(stepperZ.currentPosition() / 1509) + "x" + (String)(stepperX.currentPosition() / 1509)  );
      Serial.println(tagToString());
      
      return "C";
   }else if (uid == "E2 7A 55 DD"){
      Serial.println("\nO bloco D esta na posição: " + (String)(stepperZ.currentPosition() / 1509) + "x" + (String)(stepperX.currentPosition() / 1509)  );
      Serial.println(tagToString());
      
      return "D";
   }else if (uid == "E2 39 55 DD"){
    Serial.println("\nO bloco E esta na posição: " + (String)(stepperZ.currentPosition() / 1509) + "x" + (String)(stepperX.currentPosition() / 1509)  );
      Serial.println(tagToString());
      
      return "E";
   } else {
      Serial.println("ERRO 1!");
      return "false";
   }
    
}

// ============================================== FUNÇÃO DE TRATAMENTO DE EXCEÇÕES ==================================================
void trataExcecao(String typeMessage[]){
  int iter = 0;
  int jiter = 0;

  for(iter = 0;iter <5;iter++){
    for(jiter = 0;jiter <5;jiter++){
      Serial.println(typeMessage[iter][jiter]);
    
    }
    
  }
  
  
  }

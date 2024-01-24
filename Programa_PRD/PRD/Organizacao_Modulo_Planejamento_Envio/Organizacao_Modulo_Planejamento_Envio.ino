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
String mensagem = "";

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
    for(int a =0;a<5;a++){
      if(a==0){
        mensagem.concat("(");
        }
      for(int b =0;b<5;b++){
        if(b ==0){
          mensagem.concat("(");
        }
          mapa[a][b] = identifica(a,b);
          mensagem.concat(messages[a][b]);
         if(b !=4){
          mensagem.concat(",");
        }
        else{
          mensagem.concat(")");
          }
      }
        if(a !=4){
          mensagem.concat(",");
        }
        else{
          mensagem.concat(")");
          }
  }
  Serial.println(mensagem);
}
 /*   for(int a =0;a<5;a++){
      for(int b =0;b<5;b++){
        bloco = identifica();
        mapa[a][b] = bloco;
        Serial.println(mapa[a][b]);
        if(bloco != "false"){
          delay(5000);
        }
        else{
          mapa[a][b] = "0";
          }
      }
  }
Serial.println(" Mapa ");
    for(int a =0;a<5;a++){
      if(a==0){
        mensagem.concat("(");
        }
      for(int b =0;b<5;b++){
        if(b ==0){
          mensagem.concat("(");
        }
        mensagem.concat(mapa[a][b]);
         if(b !=4){
          mensagem.concat(",");
        }
        else{
          mensagem.concat(")");
          }
      }
        if(a !=4){
          mensagem.concat(",");
        }
        else{
          mensagem.concat(")");
          }
  }
      for(int a =0;a<5;a++){
      for(int b =0;b<5;b++){
        bloco = identifica();
        mapa[a][b] = bloco;
        Serial.println(mapa[a][b]);
        if(bloco != "false"){
          delay(5000);
        }
        else{
          mapa[a][b] = "0";
          }
      }
  }
Serial.println(" Conversao ");
char mensago[] = "";
int cont = 0;
    for(int a =0;a<5;a++){
      for(int b =0;b<5;b++){
        int temp = mapa[a][b].length() ;
        char buffer[temp];
        mensago[cont] = byte(mapa[a][b]);
        cont++;
  }
  Serial.write(mensago);
  
}
}
  
*/
void lerMessage(){
      unsigned long tempo = millis();
    String bloco = "";
    for(int i =0;i<4;i++){
      for(int j =0;j<4;j++){
        while((millis() - tempo) <= 2000){
        }
        if(tagToString() == ""){
          messages[i][j] = "0";
        }
        else{
          messages[i][j] = tagToString();
          Serial.println(messages[i][j]);
          }
        delay(1000);   
      
      }
  
  
  }
  }
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
        message.addUriRecord("(:init(D on t1))(:objective-0(D on E))");

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


//============================================ FUNÇÃO DE IDENTIFICAR DADOS =================================================================

String identifica(int i, int j){
   
   String uid = "";
   unsigned long tempo = millis();
   while((millis() - tempo) <= 5000){
        if (nfc.tagPresent()){
          NfcTag tag = nfc.read();
          uid = tag.getUidString();
          delay(5000);
        }
   }

   //Serial.println(uid);

   if (uid == "E2 7A 55 DD"){
      
      messages[i][j] = tagToString();
      
      return "A";
   } else if (uid == "82 A9 C5 DF"){
      
      messages[i][j] = tagToString();
      
      return "B";
   } else if (uid == "C2 AD C5 DF"){
      
      messages[i][j] = tagToString();
      
      return "C";
   }else if (uid == "D2 D5 54 DD"){
      
      messages[i][j] = tagToString();
      
      return "D";
   }else if (uid == "E2 39 55 DD"){
      
      messages[i][j] = tagToString();
      
      return "E";
   } else {
      Serial.println("ERRO 1!");
      return "false";
   }
    
}

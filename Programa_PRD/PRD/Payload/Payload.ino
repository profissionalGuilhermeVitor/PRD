#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);  // The Adafruit PN532 Shield


void setup(void) {
  Serial.begin(9600);
  Serial.println("NFC TAG READER");
  nfc.begin();
  Serial.println("\nScan your NFC tag on the Adafruit PN532 NFC Shield!");
  Serial.println("___________________________________________________\n");
}

void loop(void) {
  
 Serial.print(data());
}

String data(){
   if (nfc.tagPresent())
  {
    Serial.println("NFC tag Found!\n");
    NfcTag tag = nfc.read();
    Serial.print("Tag Type: ");
    Serial.println(tag.getTagType());
    Serial.print("UID: ");
    Serial.println(tag.getUidString());

    if (tag.hasNdefMessage())
    {
      
      NdefMessage message = tag.getNdefMessage();
      
      // If you have more than 1 Message then it wil cycle through them
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        
        NdefRecord record = message.getRecord(i);

        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);


        String payloadAsString = ""; // Processes the message as a string vs as a HEX value
        for (int c = 0; c < payloadLength; c++) 
        {
          payloadAsString += (char)payload[c];
        }
        
        
        Serial.println("\nTag Content Shown Below\n");
        
        Serial.print("Original String: ");
        Serial.println(payloadAsString);
        
        Serial.println("\nBy Manually removing the first 3 characters\n"); 
        String cleanString = payloadAsString;
        cleanString.remove(0,3);
         
        Serial.print("Cleaned String: ");
        Serial.println(cleanString);


        String uid = record.getId();
        if (uid != "") 
        {
          Serial.print("  ID: ");
          Serial.println(uid);
        }
      }
      delay(5000);
    }
  }
  
  }

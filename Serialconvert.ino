#define SKY_PANEL_BYTE_SIZE 26
#define FEELTNG_PANEL_BYTE_SIZE 38
byte feeltngpacket[FEELTNG_PANEL_BYTE_SIZE] = {0}; 
byte skypacket[SKY_PANEL_BYTE_SIZE] = {0};
void setup() {
  Serial.begin(38400); //for debug purpose
  Serial1.begin(38400); //from 300L mainboard
  Serial2.begin(19200); //to singcus panel
}

void loop() {
  if(Serial2.available()){
    byte d = Serial2.read();
    Serial1.write(d);
  }
  if(Serial1.available()){
    byte d = Serial1.read();
    if(d == 0x55){
      
      feeltngpacket[0] = 0x55;
      byte temp[FEELTNG_PANEL_BYTE_SIZE-1] = {0};
      Serial1.readBytes(temp,FEELTNG_PANEL_BYTE_SIZE-1);
      Serial.print("FND;");
      for(int i=0; i< FEELTNG_PANEL_BYTE_SIZE-1; i++){
        feeltngpacket[i+1] = temp[i];
        Serial.print(temp[i], DEC);
        if (i < (FEELTNG_PANEL_BYTE_SIZE-1) - 1)
            Serial.print(",");
      }
      Serial.println();
      skypacket[0] = 0x55;
      skypacket[10] = (bitRead(feeltngpacket[5],7) << 7)
      +(bitRead(feeltngpacket[4],1) << 3)+(bitRead(feeltngpacket[4],2) << 1)+(bitRead(feeltngpacket[4],3) << 4) + (bitRead(feeltngpacket[4],4) << 6)
      +(bitRead(feeltngpacket[4],5) << 5)+(bitRead(feeltngpacket[4],6) << 2) +(bitRead(feeltngpacket[4],7));
      send_skypaneldata(skypacket, SKY_PANEL_BYTE_SIZE - 1);
      skypacket[11] = (bitRead(feeltngpacket[5],2)) + (bitRead(feeltngpacket[5],6) << 1)+(bitRead(feeltngpacket[5],1) << 2)+(bitRead(feeltngpacket[5],3) << 3)
      +(bitRead(feeltngpacket[5],5) << 4) + (bitRead(feeltngpacket[5],4) << 5) + (bitRead(feeltngpacket[6],7) << 6) + (bitRead(feeltngpacket[6],2) << 7);
      skypacket[12] = (bitRead(feeltngpacket[6],6)) + (bitRead(feeltngpacket[6],1) << 1) +(bitRead(feeltngpacket[6],3) << 2)+(bitRead(feeltngpacket[6],5) << 3)  
      +(bitRead(feeltngpacket[6],4) << 4) 
      +(bitRead(feeltngpacket[7],0) << 5)+(bitRead(feeltngpacket[3],0) << 6)+(bitRead(feeltngpacket[4],0) << 7);
      skypacket[6] = (bitRead(feeltngpacket[16],6))+
      (bitRead(feeltngpacket[7],7) << 1) +(bitRead(feeltngpacket[7],2) << 2) +(bitRead(feeltngpacket[7],6) << 3) +(bitRead(feeltngpacket[7],1) << 4) 
      +(bitRead(feeltngpacket[7],3) << 5) +(bitRead(feeltngpacket[7],5) << 6) +(bitRead(feeltngpacket[7],4) << 7) ;
      skypacket[13] = (bitRead(feeltngpacket[8],7)) + (bitRead(feeltngpacket[8],2) << 1) + (bitRead(feeltngpacket[8],6) << 2) + (bitRead(feeltngpacket[8],1) << 3)
      +(bitRead(feeltngpacket[8],3) << 4)+(bitRead(feeltngpacket[8],5) << 5)+(bitRead(feeltngpacket[8],4) <<6) + (bitRead(feeltngpacket[16],5) << 7);
      skypacket[19] = (bitRead(feeltngpacket[1],7)) + (bitRead(feeltngpacket[1],2) << 1)+(bitRead(feeltngpacket[1],6) << 2)+(bitRead(feeltngpacket[1],1) << 3)
      +(bitRead(feeltngpacket[1],3) << 4) + (bitRead(feeltngpacket[1],5) << 5) + (bitRead(feeltngpacket[1],4) << 6) + (bitRead(feeltngpacket[4],0) << 7);
      skypacket[20] = (bitRead(feeltngpacket[2],7)) + (bitRead(feeltngpacket[2],2) << 1)+(bitRead(feeltngpacket[2],6) << 2)+(bitRead(feeltngpacket[2],1) << 3)
      +(bitRead(feeltngpacket[2],3) << 4) + (bitRead(feeltngpacket[2],5) << 5) + (bitRead(feeltngpacket[2],4) << 6) + (bitRead(feeltngpacket[3],7) << 7);
      skypacket[21] = (bitRead(feeltngpacket[3],2)) + (bitRead(feeltngpacket[3],6) << 1)+(bitRead(feeltngpacket[3],1) << 2)+(bitRead(feeltngpacket[3],3) << 3)
      +(bitRead(feeltngpacket[3],5) << 4) + (bitRead(feeltngpacket[3],4) << 5) + (0 << 6) + (0 << 7);
      
      
      skypacket[1] = feeltngpacket[9];
      skypacket[2] = feeltngpacket[10];
      skypacket[3] = feeltngpacket[11];
      skypacket[4] = feeltngpacket[12];
      skypacket[5] = feeltngpacket[13];
      skypacket[7] = feeltngpacket[14];
      skypacket[8] = feeltngpacket[15];
      skypacket[9] = (bitRead(feeltngpacket[16],0) << 0) + (bitRead(feeltngpacket[16],1) << 1) + (bitRead(feeltngpacket[16],2) << 2) +(bitRead(feeltngpacket[16],3) << 3)
      +(bitRead(feeltngpacket[16],4) << 4) + (0 << 5) + (0 << 6) + (bitRead(feeltngpacket[16],7) << 7);
      skypacket[14] = feeltngpacket[17];
      skypacket[15] = feeltngpacket[18];
      skypacket[16] = feeltngpacket[19];
      skypacket[17] = feeltngpacket[20];
      skypacket[18] = feeltngpacket[9];
      skypacket[22] = feeltngpacket[12];
      skypacket[23] = feeltngpacket[10];
      skypacket[24] = feeltngpacket[11];
      
    }
    
  }
}
int getBit(int n, int k)
{
    return (n & (1<<k)) != 0;
}
void send_skypaneldata(byte data[], byte leng){
  byte newdata[leng+1] = {0};
  byte checksum = 0;
  unsigned int sum = 0;
  for(int i = 0; i < leng; i++){
    newdata[i] = data[i];
    sum = sum + data[i];
  }
  checksum = sum % 256;
  newdata[leng] = checksum;
  Serial2.write(newdata,leng + 1);
}

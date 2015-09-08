#include <Wire.h>

#define SLAVE_ADDR 0x40
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

char read_value;
bool sucess = false;

char read8(char addr) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(addr);
  if(Wire.endTransmission() != 0){
    Serial.println("Slave did not respond.");
    return false;
  }

  Wire.requestFrom(SLAVE_ADDR, 1);
  read_value = Wire.read();
  return true;
}

bool write8(char addr, char d) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(addr);
  Wire.write(d);
  if(Wire.endTransmission() != 0){
    Serial.println("Slave did not respond.");
    return false;
  }
  return true;
}

void print_options(){
  Serial.println("A) Mode1");
          Serial.println("B) Prescale");
          Serial.println("C) LED0_ON_L");
          Serial.println("D) LED0_ON_H");
          Serial.println("E) LED0_OFF_L");
          Serial.println("F) LED0_OFF_H");
          Serial.println("G) ALLLED_ON_L");
          Serial.println("H) ALLLED_ON_L");
          Serial.println("I) ALLLED_ON_L");
          Serial.println("J) ALLLED_ON_L");
}

void console(){
  char action;
  char value;
  Serial.println("Please select if you want to (R)ead or (W)rite a register!");
  while(Serial.available() == 0);
  action = Serial.read();
  switch(action){
    case 'r':
    case 'R':
          Serial.println("Please enter the register you want to read:");
          print_options();
          while(Serial.available() == 0);
          action = Serial.read();
          switch(action)
          {
            case 'a':
            case 'A':
              if(read8(PCA9685_MODE1)){
                  sucess = true;  
              }
              break;
            case 'b':
            case 'B':
              if(read8(PCA9685_PRESCALE)){
                  sucess = true;  
              }
              break;
            case 'c':
            case 'C':
              if(read8(LED0_ON_L)){
                  sucess = true;  
              }
              break;
              case 'd':
            case 'D':
              if(read8(LED0_ON_H)){
                  sucess = true;  
              }
              break;
              case 'e':
            case 'E':
              if(read8(LED0_OFF_L)){
                  sucess = true;  
              }
              break;

              case 'f':
            case 'F':
              if(read8(LED0_OFF_H)){
                  sucess = true;  
              }
              break;
              case 'g':
            case 'G':
              if(read8(ALLLED_ON_L)){
                  sucess = true;  
              }
              break;
              case 'h':
            case 'H':
              if(read8(ALLLED_ON_H)){
                  sucess = true;  
              }
              break;
              case 'i':
            case 'I':
              if(read8(ALLLED_OFF_L)){
                  sucess = true;  
              }
              break;
              case 'j':
            case 'J':
              if(read8(ALLLED_OFF_H)){
                  sucess = true;  
              }
              break;
              default:
                Serial.println("Unknown command");
                break;
          }
          if(sucess){
            Serial.print("OK ! The read value is ");
            Serial.println(read_value,HEX);
            sucess = false;
          }
          else{
            Serial.println("Command unsuccessful");
          }
          break;
    case 'w':
    case 'W':
          Serial.println("Please enter the register you want to write:");
          while(Serial.available() == 0);
          action = Serial.read();
          Serial.println("Please enter the value you want to write:");
          while(Serial.available() == 0);
          value = Serial.read();
          switch(action)
          {
            case 'a':
            case 'A':
              if(write8(PCA9685_MODE1,value)){
                  sucess = true;  
              }
              break;
            case 'b':
            case 'B':
              if(write8(PCA9685_PRESCALE,value)){
                  sucess = true;  
              }
              break;
            case 'c':
            case 'C':
              if(write8(LED0_ON_L,value)){
                  sucess = true;  
              }
              break;
              case 'd':
            case 'D':
              if(write8(LED0_ON_H,value)){
                  sucess = true;  
              }
              break;
              case 'e':
            case 'E':
              if(write8(LED0_OFF_L,value)){
                  sucess = true;  
              }
              break;

              case 'f':
            case 'F':
              if(write8(LED0_OFF_H,value)){
                  sucess = true;  
              }
              break;
              case 'g':
            case 'G':
              if(write8(ALLLED_ON_L,value)){
                  sucess = true;  
              }
              break;
              case 'h':
            case 'H':
              if(write8(ALLLED_ON_H,value)){
                  sucess = true;  
              }
              break;
              case 'i':
            case 'I':
              if(write8(ALLLED_OFF_L,value)){
                  sucess = true;  
              }
              break;
              case 'j':
            case 'J':
              if(write8(ALLLED_OFF_H,value)){
                  sucess = true;  
              }
              break;
              default:
                Serial.println("Unknown command");
                break;
          }
          if(sucess){
            Serial.println("Register written sucessfuly!");
            sucess = false;
          }else{
            Serial.println("Command unsuccessful");
          }
          break;
    default:
          Serial.println("Unknown command");
          break;
  }
}
void setup(){
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Welcome to the I2C testing tool for Arduino!");
}

void loop(){
  console(); 
}


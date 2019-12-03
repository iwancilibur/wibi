#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include "HX711.h"
#define DOUT1  A0
#define CLK1  A1
#define DOUT2  A8
#define CLK2  A9
#define DOUT3  A4
#define CLK3  A5
#define DOUT4  A6
#define CLK4  A7

HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);
HX711 scale3(DOUT3, CLK3);
HX711 scale4(DOUT4, CLK4);

float calibration_factor1 = 650;
float calibration_factor2 = 650;
float calibration_factor3 = 650;
float calibration_factor4 = 650;
int GRAM1;
int GRAM2;
int GRAM3;
int GRAM4;
int total=0;
 
void setup() {
  Serial.begin(115200);
  Serial.println("SISTEM EMISI AKUSTIK");
  scale1.set_scale();
  scale1.tare();
  scale2.set_scale();
  scale2.tare();
  scale3.set_scale();
  scale3.tare();
  scale4.set_scale();
  scale4.tare();
  long zero_factor = scale1.read_average();
  lcd.begin();
}
 
void loop() {
  scale1.set_scale(calibration_factor1);
  GRAM1 = scale1.get_units(), 4;
  scale2.set_scale(calibration_factor2);
  GRAM2 = scale2.get_units(), 4;
  scale3.set_scale(calibration_factor3);
  GRAM3 = scale3.get_units(), 4;
  scale4.set_scale(calibration_factor4);
  GRAM4 = scale4.get_units(), 4;
  

  if (GRAM1<5){
    GRAM1=0;
  }
  if (GRAM2<5){
    GRAM2=0;
  }
  if (GRAM3<5){
    GRAM3=0;
  }
  if (GRAM4<5){
    GRAM4=0;
  }

  Serial.print("SENSOR 1: ");
  Serial.print(GRAM1);
  Serial.print(" Gram");
  
  Serial.print(" | SENSOR 2: ");
  Serial.print(GRAM2);
  Serial.print(" Gram");

  Serial.print(" | SENSOR 3: ");
  Serial.print(GRAM3);
  Serial.print(" Gram");

  Serial.print(" | SENSOR 4: ");
  Serial.print(GRAM4);
  Serial.print(" Gram");
  Serial.println();
  
  lcd.setCursor(0,0);
  lcd.print("SEN1: ");
  lcd.setCursor(5,0);
  lcd.print(GRAM1);

  lcd.setCursor(10,0);
  lcd.print("SEN2: ");
  lcd.setCursor(15,0);
  lcd.print(GRAM2);


  lcd.setCursor(0,1);
  lcd.print("SEN3: ");
  lcd.setCursor(5,1);
  lcd.print(GRAM3);

  lcd.setCursor(10,1);
  lcd.print("SEN4: ");
  lcd.setCursor(15,1);
  lcd.print(GRAM4);

  if(GRAM1<=1 && GRAM2<=1 && GRAM3<=1 && GRAM4<=1){
    lcd.setCursor(2,3);
    lcd.print("Tidak Ada Beban");
  }else if(GRAM1>=GRAM2 && GRAM1>=GRAM3 && GRAM1>=GRAM4){
    lcd.setCursor(2,3);
    lcd.print("Condong ke SEN1");
  }else if(GRAM2>=GRAM1 && GRAM2>=GRAM3 && GRAM2>=GRAM4){
    lcd.setCursor(2,3);
    lcd.print("Condong ke SEN2");
  }else if(GRAM3>=GRAM1 && GRAM3>=GRAM2 && GRAM3>=GRAM4){
    lcd.setCursor(2,3);
    lcd.print("Condong ke SEN3");
  }else if(GRAM4>=GRAM1 && GRAM4>=GRAM2 && GRAM4>=GRAM4){
    lcd.setCursor(2,3);
    lcd.print("Condong ke SEN4");
  }


lcd.setCursor(2,2);
lcd.print("Total Berat :");
lcd.setCursor(15,2);
lcd.print(GRAM1+GRAM2+GRAM3+GRAM4);
delay(300);
lcd.clear();
}

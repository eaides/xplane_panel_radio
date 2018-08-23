//================================
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <ArdSimX.h>          //  -- ArdSimX library 
//================================

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

int anteriorTransponder = -1;
int actualTransponder = -1;
int modoTranspondedor = -1;
int changes = 0;

//------------------------------------------
void setup()  {

  BoardNumber 1;   // - board number from 1  to 9

  //  Serial.begin(9600);
  //  Serial.println("--- Start Serial Monitor ---");

  lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.begin (20, 4);
  lcd.clear();
  lcd.home ();                   // go home
  lcd.print("!! Ernesto Aides !!");
  lcd.setCursor ( 0, 2 );        // go to the 3rd line
  lcd.print("Test Ardsimx Outputs");

  // Serial.println("Escribi...");
}

//------------------------------------------
void loop()   {


  ArdSimScan;

  if (anteriorTransponder != actualTransponder) {
    changes++;
    anteriorTransponder = actualTransponder;
    lcd.begin (20, 4);
    lcd.clear();
    lcd.home ();                   // go home
    lcd.print("Transponder Val");
    lcd.setCursor ( 0, 1 );        // go to the 2nd line
    lcd.print(actualTransponder);
    lcd.setCursor ( 0, 2 );        // go to the 3rd line
    lcd.print("Transponder Mode");
    lcd.setCursor ( 0, 3 );        // go to the 4th line
    lcd.print(modoTranspondedor);
    lcd.setCursor ( 2, 3 );        // go to the 4th line
    lcd.print("changes ");
    lcd.print(changes);
    //    Serial.println("Valor de Transponder");
    //    Serial.println(actualTransponder);
    //    Serial.println("Modo Transponder");
    //    Serial.println(modoTranspondedor);
    //    Serial.println();
  }

  if (changes == 15) {
    //    Serial.println("Cambio Transpondedor a 2200");
    //    Serial.println("y modo a 3");   // 3 = ??
    SimInput(1, 2200 );
    //    Serial.println();
    changes++;
    lcd.setCursor ( 15, 3 );        // go to the 4th line
    lcd.print("2200?");
  }

}
//========================================

void ProgOut(byte id, float val) {
  switch (id) {
    case 1:
      break;
    case 37:
      actualTransponder = val;
      break;
    case 38: ;
      modoTranspondedor = val;
      break;
  }
}


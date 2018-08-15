//================================
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <ArdSimX.h>
//================================

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

unsigned long last_t = 0;
unsigned long Dt = 2500;

int val_1 = -1;
float val_2 = -1;
float val_3 = -1;

void setup()  {
  BoardNumber 2;   // - board number from 1  to 9
  lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin (20, 4);
  lcd.clear();
  lcd.home ();
}

void loop()   {
  ArdSimScan;
  //ArdSimX(2) ;         // -- Assign Board Number here  (1...9)

  if ((millis() - last_t) >= Dt) {

    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    lcd.setCursor(0, 0);
    lcd.print(val_1);

    lcd.setCursor(0, 1);
    lcd.print(val_2);

    lcd.setCursor(0, 2);
    lcd.print(val_3);

  }
}

void ProgOut(byte id, float val) {
  switch (id) {
    case 1:
      val_1 = val;
      break;
    case 2:
      val_2 = val;
      break;
    case 3:
      val_3 = val;
      break;
  }
}


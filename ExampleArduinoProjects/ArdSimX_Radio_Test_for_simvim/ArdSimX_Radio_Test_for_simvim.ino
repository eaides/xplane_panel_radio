//================================
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <ArdSimX.h>
//================================

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

bool do_fake = false;
unsigned long last_t = 0;
unsigned long Dt = 4000;
unsigned long counter_progout;
unsigned int counter = 0;
unsigned int displayed = 0;
unsigned int send_fake_data_to_ardsimx_count = 0;

unsigned int Battery = 0;
unsigned int Avionics = 0;

unsigned long TransponderCode = 0;
unsigned int TransponderMode = 0;

unsigned int SoundCom1Led = 0;
unsigned int SoundNav1Led = 0;
unsigned int SoundMarkerLed = 0;
unsigned int SoundDme1Led = 0;
unsigned int SoundAdf1Led = 0;

unsigned long Com1Active = 0;
unsigned long Com1Stdby = 0;
unsigned long Com2Active = 0;
unsigned long Com2Stdby = 0;

unsigned long Nav1Active = 0;
unsigned long Nav1Stdby = 0;
unsigned long Nav2Active = 0;
unsigned long Nav2Stdby = 0;

unsigned long Adf1Active = 0;
unsigned long Adf1Stdby = 0;
unsigned long Adf2Active = 0;
unsigned long Adf2Stdby = 0;

void setup()  {
  BoardNumber 1;   // - board number from 1  to 9
  lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin (20, 4);
  lcd.clear();
  lcd.home ();
  lcd.setCursor(0, 0);
  lcd.print("   setup done!      ");
}

void do_send_fake_data_to_ardsimx(int fake_data_to_ardsimx_count) {
  // switch com1 and com2 , nav1 and nav2, adf1 and adf2
  if (fake_data_to_ardsimx_count == 1)      SimInput(10, 1);
  else if (fake_data_to_ardsimx_count == 2) SimInput(11, 1);
  else if (fake_data_to_ardsimx_count == 3) SimInput(14, 1);
  else if (fake_data_to_ardsimx_count == 4) SimInput(15, 1);
  else if (fake_data_to_ardsimx_count == 5) SimInput(18, 1);
  else if (fake_data_to_ardsimx_count == 6) SimInput(19, 1);

  // second time
  else if (fake_data_to_ardsimx_count == 7) SimInput(10, 1);
  else if (fake_data_to_ardsimx_count == 8) SimInput(11, 1);
  else if (fake_data_to_ardsimx_count == 9) SimInput(14, 1);
  else if (fake_data_to_ardsimx_count == 10) SimInput(15, 1);
  else if (fake_data_to_ardsimx_count == 11) SimInput(18, 1);
  else if (fake_data_to_ardsimx_count == 12) SimInput(19, 1);

  // change transponder code and mode
  else if (fake_data_to_ardsimx_count == 13) SimInput(6, 3);
  else if (fake_data_to_ardsimx_count == 14) SimInput(5, 2000);
  else if (fake_data_to_ardsimx_count == 15) {
    SimInput(6, 1);
    do_fake = false;
    Dt = 4000;
  }
  return;
}

void loop()   {

  ArdSimScan;
  //ArdSimX(1) ;         // -- Assign Board Number here  (1...9)

  main_loop();;

}

void main_loop() {
  if (do_fake && (millis() - last_t) >= Dt) {
    last_t = millis();
    Dt = 150;
    send_fake_data_to_ardsimx_count++;
    do_send_fake_data_to_ardsimx(send_fake_data_to_ardsimx_count);
  }

  if (!do_fake && (millis() - last_t) >= Dt) {
    last_t = millis();
    counter++;

    lcd.setCursor(2, 0);
    lcd.print("                  ");
    lcd.setCursor(2, 0);
    lcd.print("Bat ");
    lcd.print(Battery);
    lcd.print(" Av ");
    lcd.print(Avionics);
    lcd.print(" ");
    lcd.print(TransponderCode);
    lcd.print(" / ");
    lcd.print(TransponderMode);

    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("SC");
    lcd.print(SoundCom1Led);
    lcd.print(" SN");
    lcd.print(SoundNav1Led);
    lcd.print(" SM");
    lcd.print(SoundMarkerLed);
    lcd.print(" SD");
    lcd.print(SoundDme1Led);
    lcd.print(" SA");
    lcd.print(SoundAdf1Led);

    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    switch (counter) {
      case 1:
        // com
        lcd.setCursor(0, 2);
        lcd.print("C1A ");
        lcd.print(Com1Active);
        lcd.print(" /S");
        lcd.print(Com1Stdby);
        lcd.setCursor(0, 3);
        lcd.print("C2A ");
        lcd.print(Com2Active);
        lcd.print(" /S");
        lcd.print(Com2Stdby);
        break;
      case 2:
        // nav1
        lcd.setCursor(0, 2);
        lcd.print("N1A ");
        lcd.print(Nav1Active);
        lcd.print(" /S");
        lcd.print(Nav1Stdby);
        lcd.setCursor(0, 3);
        lcd.print("N2A ");
        lcd.print(Nav2Active);
        lcd.print(" /S");
        lcd.print(Nav2Stdby);
        break;
      case 3:
        // adf1
        lcd.setCursor(0, 2);
        lcd.print("A1A ");
        lcd.print(Adf1Active);
        lcd.print(" /S");
        lcd.print(Adf1Stdby);
        lcd.setCursor(0, 3);
        lcd.print("A2A ");
        lcd.print(Adf2Active);
        lcd.print(" /S");
        lcd.print(Adf2Stdby);
        break;
    }
    if (counter == 3) {
      counter = 0;
    }
    displayed++;
    if (displayed == 12) {
      lcd.setCursor(2, 0);
      lcd.print(" GOTO FAKE INIT   ");
      lcd.setCursor(0, 1);
      lcd.print("...                 ");
      lcd.setCursor(0, 2);
      lcd.print(" ...                ");
      lcd.setCursor(0, 3);
      lcd.print("  ...               ");
      do_fake = true;
    }
  }
}

void ProgOut(byte id, float val) {

  counter_progout++;
  lcd.setCursor(0, 0);
  lcd.print(counter_progout);
  
  
  switch (id) {
    case 1:
      Battery = val;
      break;
    case 2:
      Avionics = val;
      break;
    case 3:
      SoundCom1Led = val;
      break;
    case 4:
      SoundNav1Led = val;
      break;
    case 5:
      SoundMarkerLed = val;
      break;
    case 6:
      SoundDme1Led = val;
      break;
    case 7:
      SoundAdf1Led = val;
      break;
    case 8:
      TransponderCode = val;
      break;
    case 9:
      TransponderMode  = val;
      break;
    case 10:
      Com1Active = val;
      break;
    case 11:
      Com1Stdby = val;
      break;
    case 12:
      Com2Active = val;
      break;
    case 13:
      Com2Stdby = val;
      break;
    case 14:
      Nav1Active = val;
      break;
    case 15:
      Nav1Stdby = val;
      break;
    case 16:
      Nav2Active = val;
      break;
    case 17:
      Nav2Stdby = val;
      break;
    case 18:
      Adf1Active = val;
      break;
    case 19:
      Adf1Stdby = val;
      break;
    case 20:
      Adf2Active = val;
      break;
    case 21:
      Adf2Stdby = val;
      break;
  }
}


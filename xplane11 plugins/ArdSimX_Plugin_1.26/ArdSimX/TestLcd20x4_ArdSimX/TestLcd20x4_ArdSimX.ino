//================================
// #include <ArdSimX.h>          //  -- ArdSimX library (for v1.20+ only!!)
// #include <Pushbutton.h>
// #include <Rotary.h>

//Inicializacion LCD
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
//================================

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

float Com1stb = 0;
float Com2stb = 0;
float Adf1stb = 0;
float Adf2stb = 0;
int test = 1;

// Pushbutton button_flip_com1_stdby_active(45, PULL_UP_DISABLED);
// Pushbutton button_flip_com1_stdby_active(45);
// Rotary r = Rotary(6, 7);
// LiquidCrystal_I2C lcd(0x27, 20, 4);

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

void setup()  {
  // BoardNumber 1; // -- Numero de Placa  (0...9)
  if (test == 2) {
    Wire.begin();
  }
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor ---");
  Serial.println();

  if (test == 1) {
    Serial.println("Inicializar el display con 20 caraceres 4 lineas");
    lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);
  }
}

void loop()   {
  // ArdSimScan;

  //  if (button_flip_com1_stdby_active.getSingleDebouncedRelease()) {
  //    // SimInput(7, 1);
  //    Serial.println("presione boton");
  //  }

  //  unsigned char result = r.process();
  //  if (result) {
  //    Serial.println(result == DIR_CW ? "Right" : "Left");
  //  }

  if (test == 1) {
    lcd.home ();                   // go home
    lcd.print("Ernesto Aides");
    lcd.setCursor ( 5, 2 );        // go to the 3rd line
    lcd.print("Test Display");
    //Tiempo de espera para que reinicie el ciclo
    delay(10000);
  }

  if (test == 2) {
    searchI2C();
    delay(5000);           // wait 5 seconds for next scan
  }
}

void ProgOut(byte id, float val) {
  switch (id) {
    case 1: Com1stb = val / 1000; break;
    case 3: Adf1stb = val / 1; break;
    case 14: Com2stb = val / 1000; break;
    case 16: Adf2stb = val / 1; break;
  }
}

void searchI2C() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}

//================================
#include <LiquidCrystal_I2C.h>
#include <ArdSimX.h>
//================================

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

// BUTTONS define - Start ----------------------------------------------------------

#define IDENTBUTTON 31

// BUTTONS define - End ------------------------------------------------------------

// LEDs defines - Start ------------------------------------------------------------

// LEDs defines - End --------------------------------------------------------------

// Debug Definition - Start --------------------------------------------------------
bool is_debug = true;
// Debug Definition - End ----------------------------------------------------------

// Variables - Start ---------------------------------------------------------------

bool first_time = true;
long count = 0;

byte Battery = -1;
byte _Battery = -1;
byte Avionics = -1;
byte _Avionics = -1;

byte SoundCom1Led = -1;
byte _SoundCom1Led = -1;
byte SoundNav1Led = -1;
byte _SoundNav1Led = -1;
byte SoundMarkerLed = -1;
byte _SoundMarkerLed = -1;
byte SoundDme1Led = -1;
byte _SoundDme1Led = -1;
byte SoundAdf1Led = -1;
byte _SoundAdf1Led = -1;

char selector1 = 'C';
char selector2 = 'C';

long Com1Active = -1;
long _Com1Active = -1;
long Com1Stdby = -1;
long _Com1Stdby = -1;

long Com2Active = -1;
long _Com2Active = -1;
long Com2Stdby = -1;
long _Com2Stdby = -1;

int Nav1Active = -1;
int _Nav1Active = -1;
int Nav1Stdby = -1;
int _Nav1Stdby = -1;

int Nav2Active = -1;
int _Nav2Active = -1;
int Nav2Stdby = -1;
int _Nav2Stdby = -1;

int Adf1Active = -1;
int _Adf1Active = -1;
int Adf1Stdby = -1;
int _Adf1Stdby = -1;

int Adf2Active = -1;
int _Adf2Active = -1;
int Adf2Stdby = -1;
int _Adf2Stdby = -1;

int TransponderMode = -89;
int _TransponderMode = -89;
int TransponderCode = -89;
int _TransponderCode = -89;

// Variables - End  -----------------------------------------------------------------



// setup function - Start -----------------------------------------------------------
void setup()  {
  BoardNumber 1;   // - board number from 1  to 9

  if (is_debug) {
    lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);

    lcd.begin (20, 4);
    lcd.clear();
    lcd.home ();                   // go home
    lcd.print("Initializing...");
  }
}
// setup function - End -------------------------------------------------------------

void loop()   {

  ArdSimScan;
  if (first_time) {
    first_time = false;
    SimInput (1, 1);
    SimInput (1, 0);
    SimInput (2, 1);
    SimInput (2, 0);
    SimInput (3, 0);
    SimInput (3, 1);
    SimInput (4, 1);
    SimInput (4, 0);
    SimInput (5, 1);
    SimInput (5, 0);
    SimInput (6, 1);
    SimInput (6, 0);
    SimInput (7, 1);
    SimInput (7, 0);
    SimInput (8, 330);
    SimInput (8, 331);
    SimInput (9, 332);
    SimInput (9, 333);
    SimInput (10, 334);
    SimInput (10, 335);
    SimInput (11, 336);
    SimInput (11, 337);
    SimInput (12, 10801);
    SimInput (12, 10801);
    SimInput (13, 10901);
    SimInput (13, 10900);
    SimInput (14, 10801);
    SimInput (14, 10800);
    SimInput (15, 10901);
    SimInput (15, 10900);
    SimInput (16, 122000);
    SimInput (16, 122800);
    SimInput (17, 122000);
    SimInput (17, 122800);
    SimInput (18, 122000);
    SimInput (18, 122800);
    SimInput (19, 122000);
    SimInput (19, 122800);
    SimInput (20, 0);
    SimInput (20, 1);
    SimInput (21, 7777);
    SimInput (21, 2222);
  }
}
//========================================

void ProgOut(byte id, float val) {
  count++;
  if (is_debug) {
    lcd.setCursor(0, 0);
    lcd.print("               ");
    lcd.setCursor(2, 1);
    lcd.print("id: ");
    lcd.print(id);
    lcd.setCursor(2, 2);
    lcd.print("count: ");
    lcd.print(count);
  }
  if (id == 1) {
    Battery = val;
    if (_Battery != Battery) {
      _Battery = Battery;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("1");
    }
  }
  if (id == 2) {
    Avionics = val;
    if (_Avionics != Avionics) {
      _Avionics = Avionics;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("2");
    }
  }
  if (id == 3) {
    SoundCom1Led = val;
    if (_SoundCom1Led != SoundCom1Led) {
      _SoundCom1Led = SoundCom1Led;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("3");
    }
  }
  if (id == 4) {
    SoundNav1Led = val;
    if (_SoundNav1Led != SoundNav1Led) {
      _SoundNav1Led != SoundNav1Led;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("4");
    }
  }
  if (id == 5) {
    SoundMarkerLed = val;
    if (_SoundMarkerLed != SoundMarkerLed) {
      _SoundMarkerLed != SoundMarkerLed;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("5");
    }
  }
  if (id == 6) {
    SoundDme1Led = val;
    if (_SoundDme1Led != SoundDme1Led) {
      _SoundDme1Led = SoundDme1Led;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("6");
    }
  }
  if (id == 7) {
    SoundAdf1Led = val;
    if (_SoundAdf1Led != SoundAdf1Led) {
      _SoundAdf1Led = SoundAdf1Led;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("7");
    }
  }
  if (id == 8) {
    Adf1Active = val;
    if (_Adf1Active != Adf1Active) {
      _Adf1Active = Adf1Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("8");
    }
  }
  if (id == 9) {
    Adf1Stdby = val;
    if (_Adf1Stdby != Adf1Stdby) {
      _Adf1Stdby = Adf1Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("9");
    }
  }
  if (id == 10) {
    Adf2Active = val;
    if (_Adf2Active != Adf2Active) {
      _Adf2Active = Adf2Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("a");
    }
  }
  if (id == 11) {
    Adf2Stdby = val;
    if (_Adf2Stdby != Adf2Stdby) {
      _Adf2Stdby = Adf2Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("b");
    }
  }
  if (id == 12) {
    Nav1Active = val;
    if (_Nav1Active != Nav1Active) {
      _Nav1Active = Nav1Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("c");
    }
  }
  if (id == 13) {
    Nav1Stdby = val;
    if (_Nav1Stdby != Nav1Stdby) {
      _Nav1Stdby = Nav1Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("d");
    }
  }
  if (id == 14) {
    Nav2Active = val;
    if (_Nav2Active != Nav2Active) {
      _Nav2Active = Nav2Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("e");
    }
  }
  if (id == 15) {
    Nav2Stdby = val;
    if (_Nav2Stdby != Nav2Stdby) {
      _Nav2Stdby = Nav2Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("f");
    }
  }
  if (id == 16) {
    Com1Active = val;
    if (_Com1Active != Com1Active) {
      _Com1Active = Com1Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("g");
    }
  }
  if (id == 17) {
    Com1Stdby = val;
    if (_Com1Stdby != Com1Stdby) {
      _Com1Stdby = Com1Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("h");
    }
  }
  if (id == 18) {
    Com2Active = val;
    if (_Com2Active != Com2Active) {
      _Com2Active = Com2Active;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("i");
    }
  }
  if (id == 19) {
    Com2Stdby = val;
    if (_Com2Stdby != Com2Stdby) {
      _Com2Stdby = Com2Stdby;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("j");
    }
  }
  if (id == 20) {
    TransponderCode = val;
    if (_TransponderCode != TransponderCode) {
      _TransponderCode = TransponderCode;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("k");
    }
  }
  if (id == 21) {
    TransponderMode  = val;
    if (_TransponderMode != TransponderMode) {
      _TransponderMode = TransponderMode;
    }
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("L@");
    }
  }
}

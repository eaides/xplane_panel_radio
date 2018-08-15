//================================
#include <Pushbutton.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Rotary.h>
#include <ArdSimX.h>
//================================

#define I2C_ADDR    0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7);

// BUTTONS define - Start ----------------------------------------------------------
#define SOUNDNAV1BUTTON 22
#define SOUNDMARKBUTTON 23
#define SOUNDDME1BUTTON 24
#define SOUNDADF1BUTTON 25

#define SELECTORTOC1B 26
#define SELECTORTON1B 27
#define SELECTORTOA1B 28
#define STDACT1B      29

#define SELECTORTOC2B 30
#define SELECTORTON2B 31
#define SELECTORTOA2B 32
#define STDACT2B      33

#define IDENTBUTTON   34

#define TRPOS1        14
#define TRPOS2        15
#define TRPOS3        16
#define TRPOS4        17
#define TRPOS5        18
#define TRPOS6        19
// BUTTONS define - End ------------------------------------------------------------

// ENCODERS define - Start ----------------------------------------------------------
#define TRANSPONDERENCODER1PINDERECHO  43
#define TRANSPONDERENCODER1PINIZQUIERDO  45

#define TRANSPONDERENCODER2PINDERECHO  44
#define TRANSPONDERENCODER2PINIZQUIERDO  46

// ENCODERS define - End ------------------------------------------------------------

// PUSHBUTTONS - Start -------------------------------------------------------------
Pushbutton SoundNav1Button(SOUNDNAV1BUTTON);
Pushbutton SoundMarkButton(SOUNDMARKBUTTON);
Pushbutton SoundDme1Button(SOUNDDME1BUTTON);
Pushbutton SoundAdf1Button(SOUNDADF1BUTTON);

Pushbutton selectorToC1B(SELECTORTOC1B);
Pushbutton selectorToN1B(SELECTORTON1B);
Pushbutton selectorToA1B(SELECTORTOA1B);
Pushbutton StdAct1B(STDACT1B);

Pushbutton selectorToC2B(SELECTORTOC2B);
Pushbutton selectorToN2B(SELECTORTON2B);
Pushbutton selectorToA2B(SELECTORTOA2B);
Pushbutton StdAct2B(STDACT2B);

Pushbutton TransponderPos1Button(TRPOS1);
Pushbutton TransponderPos2Button(TRPOS2);
Pushbutton TransponderPos3Button(TRPOS3);
Pushbutton TransponderPos4Button(TRPOS4);
Pushbutton TransponderPos5Button(TRPOS5);
Pushbutton TransponderPos6Button(TRPOS6);

Pushbutton IdentButton(IDENTBUTTON);


// PUSHBUTTONS - End ---------------------------------------------------------------

// ENCODERS - Start --------------------------------------------------------------------------------------
Rotary TransponderEncoder1 = Rotary(TRANSPONDERENCODER1PINIZQUIERDO, TRANSPONDERENCODER1PINDERECHO);
Rotary TransponderEncoder2 = Rotary(TRANSPONDERENCODER2PINIZQUIERDO, TRANSPONDERENCODER2PINDERECHO);

// ENCODERS - End ----------------------------------------------------------------------------------------

// LEDs defines - Start ------------------------------------------------------------
#define LED_INITIALIZED 2

#define LED_SOUND_COM1 13
#define LED_SOUND_NAV1 12
#define LED_SOUND_MARK 11
#define LED_SOUND_DME1 10
#define LED_SOUND_ADF1 9

#define LED_SELECTED_COM_1 8
#define LED_SELECTED_NAV_1 7
#define LED_SELECTED_ADF_1 8
#define LED_SELECTED_COM_2 5
#define LED_SELECTED_NAV_2 4
#define LED_SELECTED_ADF_2 3

// LEDs defines - End --------------------------------------------------------------

// Debug Definition - Start --------------------------------------------------------
bool is_debug = true;
// Debug Definition - End ----------------------------------------------------------


// Variables - Start ---------------------------------------------------------------
bool send_fake_data_to_ardsimx = true;
int send_fake_data_to_ardsimx_count = 0;
bool doPowerOn = false;
unsigned long last_t = 0;
unsigned long Dt = 2500;
unsigned long last_t_xpdr = 0;
unsigned long Dt_xpdr = 250;
bool waitForButtons = false;
bool was_initialized = false;

int Battery = -89;
int _Battery = -89;
int Avionics = -89;
int _Avionics = -89;

int SoundCom1Led = -89;
int _SoundCom1Led = -89;
int SoundNav1Led = -89;
int _SoundNav1Led = -89;
int SoundMarkerLed = -89;
int _SoundMarkerLed = -89;
int SoundDme1Led = -89;
int _SoundDme1Led = -89;
int SoundAdf1Led = -89;
int _SoundAdf1Led = -89;

char selector1 = 'C';
char selector2 = 'C';

long Com1Active = -89;
long _Com1Active = -89;
long Com1Stdby = -89;
long _Com1Stdby = -89;

long Com2Active = -89;
long _Com2Active = -89;
long Com2Stdby = -89;
long _Com2Stdby = -89;

long Nav1Active = -89;
long _Nav1Active = -89;
long Nav1Stdby = -89;
int _Nav1Stdby = -89;

long Nav2Active = -89;
long _Nav2Active = -89;
long Nav2Stdby = -89;
long _Nav2Stdby = -89;

long Adf1Active = -89;
long _Adf1Active = -89;
long Adf1Stdby = -89;
long _Adf1Stdby = -89;

long Adf2Active = -89;
long _Adf2Active = -89;
long Adf2Stdby = -89;
long _Adf2Stdby = -89;

int TransponderMode = -89;
int _TransponderMode = -89; // to send at startup
int ___TransponderMode = -89; // to send at startup

long TransponderCode = -89;
long _TransponderCode = -89;

// Variables - End  -----------------------------------------------------------------

// function setupLeds() - Start -----------------------------------------------------
void setupLeds() {
  // TODO: initialize all Leds here
  pinMode(LED_INITIALIZED, OUTPUT);

  pinMode(LED_SOUND_COM1, OUTPUT);
  pinMode(LED_SOUND_NAV1, OUTPUT);
  pinMode(LED_SOUND_MARK, OUTPUT);
  pinMode(LED_SOUND_DME1, OUTPUT);
  pinMode(LED_SOUND_ADF1, OUTPUT);

  pinMode(LED_SELECTED_COM_1, OUTPUT);
  pinMode(LED_SELECTED_NAV_1, OUTPUT);
  pinMode(LED_SELECTED_ADF_1, OUTPUT);
  pinMode(LED_SELECTED_COM_2, OUTPUT);
  pinMode(LED_SELECTED_NAV_2, OUTPUT);
  pinMode(LED_SELECTED_ADF_2, OUTPUT);
}
// function setupLeds() - End -------------------------------------------------------

// function setupLCD() - Start ------------------------------------------------------
void setupLCD() {
  if (is_debug) {
    lcd.begin (20, 4);   // Inicializar el display con 20 caraceres 4 lineas
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.begin (20, 4);
    lcd.clear();
    lcd.home ();                   // go home
    lcd.print("Initializing...!");
  }
}
// function setupLCD() - End ------------------------------------------------------

// function setup7segments() - Start ----------------------------------------------
void setup7segments() {
  // todo
}
// function setup7segments() - End ------------------------------------------------

// function readInitialStates() - Start -------------------------------------------
void readInitialStates() {
  int xpdr_mode = 0;
  ___TransponderMode = checkSwitchTransponder(true);
  return;
}
// function readInitialStates() - End ---------------------------------------------

// function setup() - Start -------------------------------------------------------
void setup()  {
  BoardNumber 1;   // - board number from 1  to 9
  setupLeds();
  setupLCD();
  setup7segments();
  readInitialStates();
}
// function setup() - End -----------------------------------------------------------

// function turnOffFrequecies(whichDisplay) - Start ---------------------------------
void turnOffFrequecies(int whichDisplay) {
  if (whichDisplay == 99) {

    // TODO turn off all displays within loop

    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    return;
  }

  // else TODO turnoff display number whichDisplay (check limit and remember start with 0

  if (is_debug) {
    if (whichDisplay == 0) {
      lcd.setCursor(0, 3);
      lcd.print("          ");
    }
    if (whichDisplay == 1) {
      lcd.setCursor(0, 2);
      lcd.print("          ");
    }
    if (whichDisplay == 2) {
      lcd.setCursor(0, 1);
      lcd.print("          ");
    }
    if (whichDisplay == 3) {
      lcd.setCursor(10, 1);
      lcd.print("          ");
    }
    if (whichDisplay == 4) {
      lcd.setCursor(10, 2);
      lcd.print("          ");
    }
  }
  return;
}
// function turnOffFrequecies(whichDisplay) - End -----------------------------------

// function doDisplayFreq() - Start -------------------------------------------------
void doDisplayFreq(String whatFreq, int selector) {
  if (selector == 1) {
    if (whatFreq == "Com1Active" && selector1 == 'C') {
      turnOffFrequecies(2);
      if (Battery == 1 && Avionics == 1 && Com1Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 1);
          lcd.print("          ");
          lcd.setCursor(0, 1);
          lcd.print("C1:");
          lcd.print(Com1Active);
        }
        // TODO: print Com1Active in lcd2
      }
    }
    if (whatFreq == "Com1Stdby" && selector1 == 'C') {
      turnOffFrequecies(3);
      if (Battery == 1 && Avionics == 1 && Com1Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 1);
          lcd.print("          ");
          lcd.setCursor(10, 1);
          lcd.print("C1:");
          lcd.print(Com1Stdby);
          // TODO: print Com1Stdby in lcd3
        }
      }
    }
    if (whatFreq == "Nav1Active" && selector1 == 'N') {
      turnOffFrequecies(2);
      if (Battery == 1 && Avionics == 1 && Nav1Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 1);
          lcd.print("          ");
          lcd.setCursor(0, 1);
          lcd.print("N1:");
          lcd.print(Nav1Active);
        }
        // TODO: print Nav1Active in lcd2
      }
    }
    if (whatFreq == "Nav1Stdby" && selector1 == 'N') {
      turnOffFrequecies(3);
      if (Battery == 1 && Avionics == 1 && Nav1Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 1);
          lcd.print("          ");
          lcd.setCursor(10, 1);
          lcd.print("N1:");
          lcd.print(Nav1Stdby);
        }
        // TODO: print Nav1Stdby in lcd3
      }
    }
    if (whatFreq == "Adf1Active" && selector1 == 'A') {
      turnOffFrequecies(2);
      if (Battery == 1 && Avionics == 1 && Adf1Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 1);
          lcd.print("          ");
          lcd.setCursor(0, 1);
          lcd.print("A1:");
          lcd.print(Adf1Active);
        }
        // TODO: print Adf1Active in lcd2
      }
    }
    if (whatFreq == "Adf1Stdby" && selector1 == 'A') {
      turnOffFrequecies(3);
      if (Battery == 1 && Avionics == 1 && Adf1Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 1);
          lcd.print("          ");
          lcd.setCursor(10, 1);
          lcd.print("A1:");
          lcd.print(Adf1Stdby);
        }
        // TODO: print Adf1Stdby in lcd3
      }
    }
  }

  if (selector == 2) {
    if (whatFreq == "Com2Active" && selector2 == 'C') {
      turnOffFrequecies(1);
      if (Battery == 1 && Avionics == 1 && Com2Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 2);
          lcd.print("          ");
          lcd.setCursor(0, 2);
          lcd.print("C2:");
          lcd.print(Com2Active);
        }
        // TODO: print Com2Active in lcd1
      }
    }
    if (whatFreq == "Com2Stdby" && selector2 == 'C') {
      turnOffFrequecies(4);
      if (Battery == 1 && Avionics == 1 && Com2Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 2);
          lcd.print("          ");
          lcd.setCursor(10, 2);
          lcd.print("C2:");
          lcd.print(Com2Stdby);
        }
        // TODO: print Com2Stdby in lcd4
      }
    }
    if (whatFreq == "Nav2Active" && selector2 == 'N') {
      turnOffFrequecies(1);
      if (Battery == 1 && Avionics == 1 && Nav2Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 2);
          lcd.print("          ");
          lcd.setCursor(0, 2);
          lcd.print("N2:");
          lcd.print(Nav2Active);
        }
        // TODO: print Nav2Active in lcd1
      }
    }
    if (whatFreq == "Nav2Stdby" && selector2 == 'N') {
      turnOffFrequecies(4);
      if (Battery == 1 && Avionics == 1 && Nav2Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 2);
          lcd.print("          ");
          lcd.setCursor(10, 2);
          lcd.print("N2:");
          lcd.print(Nav2Stdby);
        }
        // TODO: print Nav2Stdby in lcd4
      }
    }
    if (whatFreq == "Adf2Active" && selector2 == 'A') {
      turnOffFrequecies(1);
      if (Battery == 1 && Avionics == 1 && Adf2Active > 0) {
        if (is_debug) {
          lcd.setCursor(0, 2);
          lcd.print("          ");
          lcd.setCursor(0, 2);
          lcd.print("A2:");
          lcd.print(Adf2Active);
        }
        // TODO: print Adf2Active in lcd1
      }
    }
    if (whatFreq == "Adf2Stdby" && selector2 == 'A') {
      turnOffFrequecies(4);
      if (Battery == 1 && Avionics == 1 && Adf2Stdby > 0) {
        if (is_debug) {
          lcd.setCursor(10, 2);
          lcd.print("          ");
          lcd.setCursor(10, 2);
          lcd.print("A2:");
          lcd.print(Adf2Stdby);
        }
        // TODO: print Adf2Stdby in lcd4
      }
    }
  }

  if (selector == 0) {
    if (whatFreq == "TransponderCode") {
      turnOffFrequecies(0);
      if (Battery == 1 && Avionics == 1 && TransponderCode != -89) {
        if (is_debug) {
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          lcd.setCursor(0, 3);
          lcd.print("XPDR: ");
          lcd.print(TransponderCode);
          lcd.setCursor(12, 3);
          lcd.print("Mode:");
          lcd.print(TransponderMode);
        }
        // TODO: print TransponderCode in lcd0
      }
    }
  }
}
// function doDisplayFreq() - End ---------------------------------------------------

// function powerOn() - Start -------------------------------------------------------
void powerOn() {
  if (!doPowerOn) {
    doPowerOn = true;

    if ( Com1Active >= 0 && Com1Stdby >= 0 && Com2Active >= 0 && Com2Stdby >= 0
         && Nav1Active >= 0 && Nav1Stdby >= 0 && Nav2Active >= 0 && Nav2Stdby >= 0
         && Adf1Active >= 0 && Adf1Stdby >= 0 && Adf2Active >= 0 && Adf2Stdby >= 0
         && TransponderCode != -89 && TransponderMode != -89
       ) {
      digitalWrite(LED_INITIALIZED, HIGH);
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("OK");
      }
    }
  } else {
    digitalWrite(LED_INITIALIZED, LOW);
    if (is_debug) {
      lcd.setCursor(18, 0);
      lcd.print("??");
    }
  }

  // TODO: initialize all displays

  // initialize leds --------------------------------------
  digitalWrite(LED_SOUND_COM1, LOW);
  digitalWrite(LED_SOUND_NAV1, LOW);
  digitalWrite(LED_SOUND_MARK, LOW);
  digitalWrite(LED_SOUND_DME1, LOW);
  digitalWrite(LED_SOUND_ADF1, LOW);
  if (SoundCom1Led == 1 && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SOUND_COM1, HIGH);
  } else {
    digitalWrite(LED_SOUND_COM1, LOW);
  }
  if (SoundNav1Led == 1 && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SOUND_NAV1, HIGH);
  } else {
    digitalWrite(LED_SOUND_NAV1, LOW);
  }
  if (SoundMarkerLed == 1 && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SOUND_MARK, HIGH);
  } else {
    digitalWrite(LED_SOUND_MARK, LOW);
  }
  if (SoundDme1Led == 1 && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SOUND_DME1, HIGH);
  } else {
    digitalWrite(LED_SOUND_DME1, LOW);
  }
  if (SoundAdf1Led == 1 && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SOUND_ADF1, HIGH);
  } else {
    digitalWrite(LED_SOUND_ADF1, LOW);
  }

  digitalWrite(LED_SELECTED_COM_1, LOW);
  digitalWrite(LED_SELECTED_NAV_1, LOW);
  digitalWrite(LED_SELECTED_ADF_1, LOW);
  if (selector1 == 'C' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_COM_1, HIGH);
  }
  if (selector1 == 'N' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_NAV_1, HIGH);
  }
  if (selector1 == 'A' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_ADF_1, HIGH);
  }

  if (selector1 == 'C') {
    doDisplayFreq("Com1Active", 1);
    doDisplayFreq("Com1Stdby", 1);
  }
  if (selector1 == 'N') {
    doDisplayFreq("Nav1Active", 1);
    doDisplayFreq("Nav1Stdby", 1);
  }
  if (selector1 == 'A') {
    doDisplayFreq("Adf1Active", 1);
    doDisplayFreq("Adf1Stdby", 1);
  }

  digitalWrite(LED_SELECTED_COM_2, LOW);
  digitalWrite(LED_SELECTED_NAV_2, LOW);
  digitalWrite(LED_SELECTED_ADF_2, LOW);
  if (selector2 == 'C' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_COM_2, HIGH);
  }
  if (selector2 == 'N' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_NAV_2, HIGH);
  }
  if (selector2 == 'A' && Battery == 1 && Avionics == 1) {
    digitalWrite(LED_SELECTED_ADF_2, HIGH);
  }

  if (selector2 == 'C') {
    doDisplayFreq("Com2Active", 2);
    doDisplayFreq("Com2Stdby", 2);
  }
  if (selector2 == 'N') {
    doDisplayFreq("Nav2Active", 2);
    doDisplayFreq("Nav2Stdby", 2);
  }
  if (selector2 == 'A') {
    doDisplayFreq("Adf2Active", 2);
    doDisplayFreq("Adf2Stdby", 2);
  }

  doDisplayFreq("TransponderCode", 0);
}
// function powerOn() - End ---------------------------------------------------------

// function powerOff() - Start ------------------------------------------------------
void powerOff() {
  doPowerOn = false;

  // turn off displays
  turnOffFrequecies(99);

  // turn off LEDs
  digitalWrite(LED_INITIALIZED, LOW);

  digitalWrite(LED_SOUND_COM1, LOW);
  digitalWrite(LED_SOUND_NAV1, LOW);
  digitalWrite(LED_SOUND_MARK, LOW);
  digitalWrite(LED_SOUND_DME1, LOW);
  digitalWrite(LED_SOUND_ADF1, LOW);

  digitalWrite(LED_SELECTED_COM_1, LOW);
  digitalWrite(LED_SELECTED_NAV_1, LOW);
  digitalWrite(LED_SELECTED_ADF_1, LOW);

  digitalWrite(LED_SELECTED_COM_2, LOW);
  digitalWrite(LED_SELECTED_NAV_2, LOW);
  digitalWrite(LED_SELECTED_ADF_2, LOW);

  // clear LCD
  if (is_debug) {
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
  }
}
// function powerOff() - End --------------------------------------------------------

// function do_send_fake_data_to_ardsimx(fake_data_to_ardsimx_count) - Start --------
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
    if (___TransponderMode == -89) {
      SimInput(6, 1);
    } else {
      SimInput(6, ___TransponderMode);
      ___TransponderMode = -89;
    }
    // -----------------------------------------------------------
    // the next 2 instructions always in the last count==??
    // -----------------------------------------------------------
    send_fake_data_to_ardsimx = false;
    waitForButtons = true;
    // -----------------------------------------------------------
  }
  return;
}
// function do_send_fake_data_to_ardsimx(fake_data_to_ardsimx_count) - End ----------

// function checkButtonsDebouncedRelease() - Start ----------------------------------
void checkButtonsDebouncedRelease() {
  if (SoundNav1Button.getSingleDebouncedRelease())
  {
    if (SoundNav1Led == 1) {
      SimInput(1, 0);
    } else {
      SimInput(1, 1);
    }
  }

  if (SoundMarkButton.getSingleDebouncedRelease())
  {
    if (SoundMarkerLed == 1) {
      SimInput(2, 0);
    } else {
      SimInput(2, 1);
    }
  }

  if (SoundDme1Button.getSingleDebouncedRelease())
  {
    if (SoundDme1Led == 1) {
      SimInput(3, 0);
    } else {
      SimInput(3, 1);
    }
  }

  if (SoundAdf1Button.getSingleDebouncedRelease())
  {
    if (SoundAdf1Led == 1) {
      SimInput(4, 0);
    } else {
      SimInput(4, 1);
    }
  }

  if (selectorToC1B.getSingleDebouncedRelease()) {
    selector1 = 'C';
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_COM_1, HIGH);
    } else {
      digitalWrite(LED_SELECTED_COM_1, LOW);
    }
    digitalWrite(LED_SELECTED_NAV_1, LOW);
    digitalWrite(LED_SELECTED_ADF_1, LOW);
    doDisplayFreq("Com1Active", 1);
    doDisplayFreq("Com1Stdby", 1);
  }

  if (selectorToN1B.getSingleDebouncedRelease()) {
    selector1 = 'N';
    digitalWrite(LED_SELECTED_COM_1, LOW);
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_NAV_1, HIGH);
    } else {
      digitalWrite(LED_SELECTED_NAV_1, LOW);
    }
    digitalWrite(LED_SELECTED_ADF_1, LOW);
    doDisplayFreq("Nav1Active", 1);
    doDisplayFreq("Nav1Stdby", 1);
  }

  if (selectorToA1B.getSingleDebouncedRelease()) {
    selector1 = 'A';
    digitalWrite(LED_SELECTED_COM_1, LOW);
    digitalWrite(LED_SELECTED_NAV_1, LOW);
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_ADF_1, HIGH);
    } else {
      digitalWrite(LED_SELECTED_ADF_1, LOW);
    }
    doDisplayFreq("Adf1Active", 1);
    doDisplayFreq("Adf1Stdby", 1);
  }

  if (StdAct1B.getSingleDebouncedRelease()) {
    if (selector1 == 'C') {
      SimInput(10, 1);
      doDisplayFreq("Com1Active", 1);
      doDisplayFreq("Com1Stdby", 1);
    }
    if (selector1 == 'N') {
      SimInput(14, 1);
      doDisplayFreq("Nav1Active", 1);
      doDisplayFreq("Nav1Stdby", 1);
    }
    if (selector1 == 'A') {
      SimInput(18, 1);
      doDisplayFreq("Adf1Active", 1);
      doDisplayFreq("Adf1Stdby", 1);
    }
  }

  if (selectorToC2B.getSingleDebouncedRelease()) {
    selector2 = 'C';
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_COM_2, HIGH);
    } else {
      digitalWrite(LED_SELECTED_COM_2, LOW);
    }
    digitalWrite(LED_SELECTED_NAV_2, LOW);
    digitalWrite(LED_SELECTED_ADF_2, LOW);
    doDisplayFreq("Com2Active", 2);
    doDisplayFreq("Com2Stdby", 2);
  }

  if (selectorToN2B.getSingleDebouncedRelease()) {
    selector2 = 'N';
    digitalWrite(LED_SELECTED_COM_2, LOW);
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_NAV_2, HIGH);
    } else {
      digitalWrite(LED_SELECTED_NAV_2, LOW);
    }
    digitalWrite(LED_SELECTED_ADF_2, LOW);
    doDisplayFreq("Nav2Active", 2);
    doDisplayFreq("Nav2Stdby", 2);
  }

  if (selectorToA2B.getSingleDebouncedRelease()) {
    selector2 = 'A';
    digitalWrite(LED_SELECTED_COM_2, LOW);
    digitalWrite(LED_SELECTED_NAV_2, LOW);
    if (Battery == 1 && Avionics == 1) {
      digitalWrite(LED_SELECTED_ADF_2, HIGH);
    } else {
      digitalWrite(LED_SELECTED_ADF_2, LOW);
    }
    doDisplayFreq("Adf2Active", 2);
    doDisplayFreq("Adf2Stdby", 2);
  }

  if (StdAct2B.getSingleDebouncedRelease()) {
    if (selector2 == 'C') {
      SimInput(11, 1);
      doDisplayFreq("Com2Active", 2);
      doDisplayFreq("Com2Stdby", 2);
    }
    if (selector2 == 'N') {
      SimInput(15, 1);
      doDisplayFreq("Nav2Active", 2);
      doDisplayFreq("Nav2Stdby", 2);
    }
    if (selector2 == 'A') {
      SimInput(19, 1);
      doDisplayFreq("Adf2Active", 2);
      doDisplayFreq("Adf2Stdby", 2);
    }
  }

  if (IdentButton.getSingleDebouncedRelease()) {
    SimInput(7, 1);
  }
}
// function checkButtonsDebouncedRelease() - End ------------------------------------

// function checkSwitchTransponder(now) - Start--------------------------------------
int checkSwitchTransponder(bool now) {
  if (now || (millis() - last_t_xpdr) >= Dt_xpdr) {
    last_t_xpdr = millis();
    if (TransponderPos1Button.isPressed()) {
      return 3;
    } else if (TransponderPos2Button.isPressed()) {
      return 1;
    } else if (TransponderPos3Button.isPressed()) {
      return 2;
    } else if (TransponderPos4Button.isPressed()) {
      return 2;
    } else if (TransponderPos5Button.isPressed()) {
      return 2;
    } else if (TransponderPos6Button.isPressed()) {
      return 2;
    }
    return 2;
  }
  if (now) {
    // default value when required without wait to millis
    return 1;
  }
  // wait to millis to read actual value
  return -89;
}
// function checkSwitchTransponder(now) - End ---------------------------------------

void changeTranspoder(int posChange, bool positive) {
  long actualTransponder = TransponderCode;
  String stringActualTransponder =  String(actualTransponder);
  stringActualTransponder  = "0000" + stringActualTransponder;
  int ends = stringActualTransponder.length();
  int starts = ends - 4;
  stringActualTransponder = stringActualTransponder.substring(starts, ends);
  String pos1 = stringActualTransponder.substring(0, 1);
  int pos1i = pos1.toInt();
  String pos2 = stringActualTransponder.substring(1, 2);
  int pos2i = pos2.toInt();
  String pos3 = stringActualTransponder.substring(2, 3);
  int pos3i = pos3.toInt();
  String pos4 = stringActualTransponder.substring(3, 4);
  int pos4i = pos4.toInt();
  int addTo = -1;
  if (positive) {
    addTo = 1;
  }
  if (posChange==1) {
    pos1i = pos1i + addTo;
    if (pos1i > 7) {
      pos1i = 0;
    } else if (pos1i < 0) {
      pos1i = 7;
    }
  } else if (posChange==2) {
    pos2i = pos2i + addTo;
    if (pos2i > 7) {
      pos2i = 0;
    } else if (pos2i < 0) {
      pos2i = 7;
    }
  } else if (posChange==3) {
    pos3i = pos3i + addTo;
    if (pos3i > 7) {
      pos3i = 0;
    } else if (pos3i < 0) {
      pos3i = 7;
    }
  } else if (posChange==4) {
    pos4i = pos4i + addTo;
    if (pos4i > 7) {
      pos4i = 0;
    } else if (pos4i < 0) {
      pos4i = 7;
    }
  }
  String newPos1 = String(pos1i);
  String newPos2 = String(pos2i);
  String newPos3 = String(pos3i);
  String newPos4 = String(pos4i);
  String newTransponder = newPos1 +newPos2 + newPos3 + newPos4;
  long newTransponderL = atol(newTransponder.c_str());
  SimInput(5, newTransponderL);
  return;
}

// function checkEncodersPositions() - Start ----------------------------------------
void checkEncodersPositions() {
  // transponder1 ( 1 2 3 4)
  unsigned char result1 = TransponderEncoder1.process();
  if (result1) {
      if (result1 == DIR_CW) {
        changeTranspoder(1,true);
      } else {
        changeTranspoder(1,false);
      }
  }
  unsigned char result2 = TransponderEncoder2.process();
  if (result2) {
      if (result2 == DIR_CW) {
        changeTranspoder(2,true);
      } else {
        changeTranspoder(2,false);
      }
  }
  // todo
}
// function checkEncodersPositions() - End ------------------------------------------

// function loop() - Start ----------------------------------------------------------
void loop()   {

  ArdSimScan;
  //ArdSimX(1) ;         // -- Assign Board Number here  (1...9)

  if (send_fake_data_to_ardsimx && (millis() - last_t) >= Dt) {
    last_t = millis();
    Dt = 150;
    send_fake_data_to_ardsimx_count++;
    do_send_fake_data_to_ardsimx(send_fake_data_to_ardsimx_count);
  }

  if (!send_fake_data_to_ardsimx) {
    checkButtonsDebouncedRelease();

    int xpdr_mode = 0;
    xpdr_mode = checkSwitchTransponder(false);
    if (xpdr_mode != -89 && _TransponderMode != TransponderMode) {
      SimInput(6, xpdr_mode);
    }

    checkEncodersPositions();
  }
}
// function loop() - End ------------------------------------------------------------

// function ProgOut - Start ---------------------------------------------------------
void ProgOut(byte id, float val) {
  switch (id) {
    case 1:
      Battery = val;
      if (_Battery != Battery) {
        _Battery = Battery;
      }
      if (Avionics == 1 && Battery == 1) {
        powerOn();
      } else {
        powerOff();
      }
      if (is_debug) {
        lcd.setCursor(0, 0);
        lcd.print("      ");
        lcd.setCursor(10, 0);
        lcd.print("        ");
        lcd.setCursor(0, 0);
        lcd.print("      ");
        lcd.setCursor(0, 0);
        lcd.print("Bat: ");
        lcd.print(Battery);
        lcd.setCursor(10, 0);
        lcd.print("        ");
        lcd.setCursor(10, 0);
        lcd.print("Av: ");
        lcd.print(Avionics);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("1");
      }
      break;
    case 2:
      Avionics = val;
      if (_Avionics != Avionics) {
        _Avionics = Avionics;
      }
      if (Avionics == 1 && Battery == 1) {
        powerOn();
      } else {
        powerOff();
      }
      if (is_debug) {
        lcd.setCursor(0, 0);
        lcd.print("      ");
        lcd.setCursor(10, 0);
        lcd.print("        ");
        lcd.setCursor(0, 0);
        lcd.print("      ");
        lcd.setCursor(0, 0);
        lcd.print("Bat: ");
        lcd.print(Battery);
        lcd.setCursor(10, 0);
        lcd.print("        ");
        lcd.setCursor(10, 0);
        lcd.print("Av: ");
        lcd.print(Avionics);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("2");
      }
      break;
    case 3:
      SoundCom1Led = val;
      if (_SoundCom1Led != SoundCom1Led) {
        _SoundCom1Led = SoundCom1Led;
        digitalWrite(LED_SOUND_COM1, LOW);
        if (SoundCom1Led == 1 && Battery == 1 && Avionics == 1) {
          digitalWrite(LED_SOUND_COM1, HIGH);
        }
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("3");
      }
      break;
    case 4:
      SoundNav1Led = val;
      if (_SoundNav1Led != SoundNav1Led) {
        _SoundNav1Led != SoundNav1Led;
        digitalWrite(LED_SOUND_NAV1, LOW);
        if (SoundNav1Led == 1 && Battery == 1 && Avionics == 1) {
          digitalWrite(LED_SOUND_NAV1, HIGH);
        }
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("4");
      }
      break;
    case 5:
      SoundMarkerLed = val;
      if (_SoundMarkerLed != SoundMarkerLed) {
        _SoundMarkerLed != SoundMarkerLed;
        digitalWrite(LED_SOUND_MARK, LOW);
        if (SoundMarkerLed == 1 && Battery == 1 && Avionics == 1) {
          digitalWrite(LED_SOUND_MARK, HIGH);
        }
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("5");
      }
      break;
    case 6:
      SoundDme1Led = val;
      if (_SoundDme1Led != SoundDme1Led) {
        _SoundDme1Led = SoundDme1Led;
        digitalWrite(LED_SOUND_DME1, LOW);
        if (SoundDme1Led == 1 && Battery == 1 && Avionics == 1) {
          digitalWrite(LED_SOUND_DME1, HIGH);
        }
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("6");
      }
      break;
    case 7:
      SoundAdf1Led = val;
      if (_SoundAdf1Led != SoundAdf1Led) {
        _SoundAdf1Led = SoundAdf1Led;
        digitalWrite(LED_SOUND_ADF1, LOW);
        if (SoundAdf1Led == 1 && Battery == 1 && Avionics == 1) {
          digitalWrite(LED_SOUND_ADF1, HIGH);
        }
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("7");
      }
      break;
    case 8:
      TransponderCode = val;
      if (_TransponderCode != TransponderCode) {
        _TransponderCode = TransponderCode;
        doDisplayFreq("TransponderCode", 0);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("8");
      }
      break;
    case 9:
      TransponderMode  = val;
      if (_TransponderMode != TransponderMode) {
        _TransponderMode = TransponderMode;
        doDisplayFreq("TransponderCode", 0);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("9");
      }
      break;
    case 10:
      Com1Active = val;
      if (_Com1Active != Com1Active) {
        _Com1Active = Com1Active;
        doDisplayFreq("Com1Active", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("a");
      }
      break;
    case 11:
      Com1Stdby = val;
      if (_Com1Stdby != Com1Stdby) {
        _Com1Stdby = Com1Stdby;
        doDisplayFreq("Com1Stdby", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("b");
      }
      break;
    case 12:
      Com2Active = val;
      if (_Com2Active != Com2Active) {
        _Com2Active = Com2Active;
        doDisplayFreq("Com2Active", 2);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("c");
      }
      break;
    case 13:
      Com2Stdby = val;
      if (_Com2Stdby != Com2Stdby) {
        _Com2Stdby = Com2Stdby;
        doDisplayFreq("Com2Stdby", 2);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("d");
      }
      break;
    case 14:
      Nav1Active = val;
      if (_Nav1Active != Nav1Active) {
        _Nav1Active = Nav1Active;
        doDisplayFreq("Nav1Active", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("e");
      }
      break;
    case 15:
      Nav1Stdby = val;
      if (_Nav1Stdby != Nav1Stdby) {
        _Nav1Stdby = Nav1Stdby;
        doDisplayFreq("Nav1Stdby", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("f");
      }
      break;
    case 16:
      Nav2Active = val;
      if (_Nav2Active != Nav2Active) {
        _Nav2Active = Nav2Active;
        doDisplayFreq("Nav2Active", 2);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("g");
      }
      break;
    case 17:
      Nav2Stdby = val;
      if (_Nav2Stdby != Nav2Stdby) {
        _Nav2Stdby = Nav2Stdby;
        doDisplayFreq("Nav2Stdby", 2);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("h");
      }
      break;
    case 18:
      Adf1Active = val;
      if (_Adf1Active != Adf1Active) {
        _Adf1Active = Adf1Active;
        doDisplayFreq("Adf1Active", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("i");
      }
      break;
    case 19:
      Adf1Stdby = val;
      if (_Adf1Stdby != Adf1Stdby) {
        _Adf1Stdby = Adf1Stdby;
        doDisplayFreq("Adf1Stdby", 1);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("j");
      }
      break;
    case 20:
      Adf2Active = val;
      if (_Adf2Active != Adf2Active) {
        _Adf2Active = Adf2Active;
        doDisplayFreq("Adf2Active", 2);
      }
      if (is_debug) {
        lcd.setCursor(18, 0);
        lcd.print("k");
      }
      break;
    case 21:
      Adf2Stdby = val;
      if (_Adf2Stdby != Adf2Stdby) {
        _Adf2Stdby = Adf2Stdby;
        doDisplayFreq("Adf2Stdby", 2);
      }
      if (is_debug) {
        lcd.setCursor(17, 0);
        lcd.print("@L@");
      }
      break;
  }
}
// function ProgOut - End ---------------------------------------------------------

/*
  TODO send data to Simulator

  SimInput(5, 1);      transpoder Code 0000 to 7777    C18 sim/cockpit2/radios/actuators/transponder_code 0 1
  SimInput(6, 1);      transponder Mode 0 to 6??       C17 sim/cockpit2/radios/actuators/transponder_mode 0 1

  SimInput(8, 1);      stanby COM1                     C14 sim/cockpit2/radios/actuators/com1_standby_frequency_hz_833 0 1
  SimInput(12, 1);      stanby NAV1                     C10 sim/cockpit2/radios/actuators/nav1_standby_frequency_hz 0 1
  SimInput(16, 1);       stanby ADF1                     C6 sim/cockpit2/radios/actuators/adf1_standby_frequency_hz 0 1

  SimInput(9, 1);      stanby COM2                     C16 sim/cockpit2/radios/actuators/com2_standby_frequency_hz_833 0 1
  SimInput(13, 1);      stanby NAV2                     C12 sim/cockpit2/radios/actuators/nav2_standby_frequency_hz 0 1
  SimInput(17, 1);       stanby ADF2                     C8 sim/cockpit2/radios/actuators/adf2_standby_frequency_hz 0 1

*/


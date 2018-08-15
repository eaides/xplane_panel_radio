/*
Base code for ArdSimX Library  v1.20+
LCD Output example (with custom programmed outputs)

The latest version and manuals at http://www.simvim.com
Copyright © SimVim 20012-2018 
/
Previous projects: XPData (UDP), ARDref, ArdSim Interfaces.
/
The newest interface is  ASX2 (ArdSimX.2) project,
see details, plans and development status at https://ardsimx.blogspot.com
/
*/
//==========================================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>    // download the library here: https://github.com/marcoschwartz/LiquidCrystal_I2C
#include <Ethernet.h>     //comment or delete this line if USB connection is used
//================================ 
#include <ArdSimX.h>          //  -- ArdSimX library 
//================================


LiquidCrystal_I2C lcd(0x27,16,2);  // i2c address 0x27

//------------------------------------------
void setup()  { 
  
    BoardNumber 1;            // -- Assign Board Number here  (0...9)

  lcd.init();                      
  lcd.backlight();
} 

//------------------------------------------
void loop()   { 
  
     ArdSimScan;               // main loop  - scan inputs and read incoming data for output

}      
//===========================================



void ProgOut(byte id, float val) {
	        
switch (id) {
  
  case 1: lcd.setCursor(0, 0);  if (val > 0)  lcd.print("FD");   else lcd.print("  ");
          lcd.setCursor(14, 0); if (val == 2) lcd.print("AP");   else lcd.print("  ");   break;
  case 2: lcd.setCursor(0, 1);  if (val == 2) lcd.print("HDG");  else lcd.print("   ");  break;         
  case 3: lcd.setCursor(0, 1);  if (val > 0)  lcd.print("BC");   else lcd.print("  ");   break;    
  case 4: lcd.setCursor(4, 1);  if (val > 0)  lcd.print("APPR"); else lcd.print("    "); break;  
  case 5: lcd.setCursor(4, 0);  if (val > 0)  lcd.print("NAV");  else lcd.print("   ");  break;
  case 6: lcd.setCursor(9, 0);  if (val == 2) lcd.print("ALT");  else lcd.print("   ");  break;
  case 7: lcd.setCursor(9, 0);  if (val == 2) lcd.print("V/S");  else lcd.print("   ");  break; 
  case 8: lcd.setCursor(10, 1); if (val == 1) lcd.print("YAW");  else lcd.print("   ");  break;
  }
	
}

//=========

/*  Lines in the "data.cfg"  file:

1D 0 sim/cockpit2/autopilot/flight_director_mode
2D 0 sim/cockpit2/autopilot/heading_status
3D 0 sim/cockpit2/autopilot/backcourse_status
4D 0 sim/cockpit2/autopilot/approach_status
5D 0 sim/cockpit2/autopilot/nav_status
6D 0 sim/cockpit2/autopilot/altitude_hold_status
7D 0 sim/cockpit2/autopilot/vvi_status
8D 0 sim/cockpit2/switches/yaw_damper_on    
  */



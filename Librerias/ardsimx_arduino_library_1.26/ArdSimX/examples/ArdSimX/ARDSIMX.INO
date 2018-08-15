/*
Base code for ArdSimX Library  v1.20+
/
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


#include <Ethernet.h>     // !!! comment or delete this line if USB connection is used
//================================ 
#include <ArdSimX.h>          //  -- ArdSimX library (for v1.20+ only!!)
//================================



//------------------------------------------
void setup()  { 
  
    BoardNumber 1;            // -- Assign Board Number here  (1...9)

  
} 

//------------------------------- // main loop -----------
void loop()   { 
  
     ArdSimScan;               // Dont't delete!!!



}      
//===========================================

//---- Custom Outputs

void ProgOut(byte id, float val) {
 	if (id==1) { 	 } // here is your custom code or function call 
	else if (id==2 && val>0) {    }  //example
}

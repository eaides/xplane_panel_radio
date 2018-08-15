/*
Base code for ArdSimX Library  v1.30+
/
The latest versions and manuals at http://www.simvim.com/ardsimx
Copyright © SimVim 20012-2018 
/
Previous projects: XPData (UDP), ARDref, ArdSim Interfaces.
/
The newest interface is  SimVimCockpit project,
see details, plans and development status at https://simvim.com
/
*/
//==========================================================================


#include <Ethernet.h>     // !!! comment or delete this line if USB connection is used
//================================ 
#include <ArdSimX.h>          //  -- ArdSimX library (for v1.27+ only!!)
//================================



//------------------------------------------
void setup()  { 
  
  
} 

//------------------------------- // main loop -----------
void loop()   { 
  
     ArdSimX (1);         // -- Assign Board Number here  (1...9) 

// ====== DON't include here your code that executes in each loop!!! 

}      
//===========================================



//---- Custom Outputs function (try to keep your code inside this function!)

void ProgOut(byte id, float val) { 
				
	switch (id) {
		case 1:		inx = val;	break;				// just example (see more in "ArdSimX_Output_LCD" sketch)
		case 12:							break;
	}
}

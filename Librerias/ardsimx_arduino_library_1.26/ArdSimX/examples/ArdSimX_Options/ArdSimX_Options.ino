/*
Base code for ArdSimX Library v.1.20+ - Options

 */


#include <Ethernet.h>     //comment or delete this line if USB connection is used
//================================ 
#include <ArdSimX.h>          //  -- ArdSimX library 
//================================



//------------------------------------------
void setup()  { 
  
BoardNumber 1;   // - board number from 1  to 9

/*=== for LAN connection ONLY ====
/
/     Use these settings only if your board cannot ot connct in "Auto" mode
/
*/
// MAC_ADDR ( 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF );  // Only if you have label with MAX address on your Ethernet shield 

// XPLANE_IP (192,168,0,104);  // set IP address of X-Plane PC

// ARDUINO_IP (192,168,0,3);   //  set IP address of Arduino

// ARDSIM_PORT 5080;			// change port number if nedeed (in the config.ini file should be changed too)


} 

//------------------------------------------
void loop()   { 
  
     ArdSimScan; 
   
    

}      
//========================================

void ProgOut(byte id, float val) {
 
	if (id==1) {  }
	else if (id==2 && val>0) {    }  //example
  
//.. etc., or use "case"
	
}


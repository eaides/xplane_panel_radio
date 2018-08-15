/*
Base code for ArdSimX Library v.1.30+ - Options for Ethernet connection
*/

#include <Ethernet.h>     //comment or delete this line if USB connection is used
//================================ 
#include <ArdSimX.h>          //  -- ArdSimX library 
//================================


//------------------------------------------
void setup()  { 
  
/*========== for LAN connection ONLY ====
/
/     try to use these settings only if your board doesn't connect automatically
*/

// ar_ip (192,168,0,3);   //  set IP address of Arduino
// xp_ip (192,168,0,104);  // set IP address of X-Plane PC
// mac_a ( 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF );  // Only if you have label with MAX address on your Ethernet shield! 

} 

//------------------------------- // main loop -----------
void loop()   { 
  
     ArdSimX (1) ;         // -- Assign Board Number here  (1...9) 

// ====== DON't include here your code that executes in each loop!!! 

}      
//===========================================



//---- Custom Outputs function (try to keep your code inside this function!)

void ProgOut(byte id, float val) {
 	if (id==1) { inx=val; }
}


/*	ArdSimX Interface */
#ifndef ArdSimDf_h
#define ArdSimDf_h
#define BoardNumber bnr=
#define USB_Serial serial=
#define ARDSIM_PORT lprt=
#define SW Serial.write
#define DOUT digitalWrite
#define ASRG { DOUT(p, r&1); DOUT(n, 1); r>>=1; DOUT(n, 0); }
#define ASRL DOUT(l, 1); DOUT(l, 0); 
#define DMS  delayMicroseconds
#define DBN tact-dbnc>30
#define ABN tact-atime>25
#define MBN tact-mdbn>30
#define RDIN !digitalRead
#define FRST in=DREAD;if(in==88)
#define RIN digitalRead
#define FST dtostrf
#define ArdSimScan AX6()
#define DBE tact-ebnc
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
EthernetUDP lCom; 
IPAddress ipa (0,0,0,0); 
IPAddress ipx (0,0,0,0);
int lprt=5080;
byte mad[6]={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
byte is_ipa, is_ipx,is_mac=0,ucom=0;
#define ARDUINO_IP ARip
#define XPLANE_IP XPip
#define MAC_ADDR Madd
void ARip (byte a1,byte a2,byte a3,byte a4){ipa[0]=a1;ipa[1]=a2;ipa[2]=a3;ipa[3]=a4;is_ipa=1;}
void XPip (byte a1,byte a2,byte a3,byte a4){ipx[0]=a1;ipx[1]=a2;ipx[2]=a3;ipx[3]=a4;is_ipx=1;}
void Madd (byte a1,byte a2,byte a3,byte a4,byte a5,byte a6){
mad[0]=a1;mad[1]=a2;mad[2]=a3;mad[3]=a4;mad[4]=a5;mad[5]=a6;is_mac=1;}
#define DCHECK ps=lCom.parsePacket();
#define DByte lCom.write
#define DVAL lCom.write(dfv,8);
#define DStart lCom.beginPacket(ipx, lprt);
#define DStop lCom.endPacket();
#define DREAD lCom.read() 
#define Ssp 300
#define DBRead lCom.read
#define DIND lCom.write
#define Lstart Ethernet.begin
#define Ladr Ethernet.localIP()
#else
#define DCHECK ps=Serial.available();
#define DByte SW
#define DVAL SW(dfv); 
#define DStart SW(123);
#define DStop SW(125);
#define DREAD Serial.read()
#define DBRead Serial.readBytes
#define DIND SW
byte ucom=1;
#endif
#define ARN bnr+48
#define Espd espd<24
#define eDBE espd>1
#define unis conf[27]
#define LV 2
#define Ecorr 24-espd
#define ARC 10000
#define RES 255
#define DRES 120
#define ACFG 97
#define SCFG 115
#define DCFG 100
#define DGET conf[28]
#define D1MS delay(1000); 
#define D5MS delay (500);
#define D3MS delay (300);
#define HARDR id==conf[22]
#define SOFTR id==conf[23]
#define Esmx conf[22]+conf[21]
#define D3McS delayMicroseconds(300);

//----------------------------------------------------------------------------------------------------------
/*	
ArdSimX Interface  v.1.25a - Jan, 26, 2018
/
/
The newest interface is  SimVimControl (or ArdSimX.2) project,
see details, plans and development status at https://ardsimx.blogspot.com
/
*/
//----------------
//----------------
#define tact millis()
#define Asb Serial.begin(Ssp)
#define TIC micros()
#endif

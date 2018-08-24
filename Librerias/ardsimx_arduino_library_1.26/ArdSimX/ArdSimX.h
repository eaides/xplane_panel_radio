/* 
ArdSimX - the input/output interface for X-Plane flight simulator. 
/
ArdSimX	Ver v.1.26 - March, 16, 2018
/
The latest version and manuals at http://www.simvim.com
Copyright © SimVim 20012-2018 
/
Previous projects: XPData (UDP), ARDref, ArdSim Interfaces.
/
The newest interface is  SimVimControl (or ArdSimX.2) project,
see details, plans and development status at https://ardsimx.blogspot.com
*/
#ifndef ArdSimX_h
#define ArdSimX_h
#include "ArdSimDf.h"
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
byte fdata[54]; 
byte dapd=54; 
byte dinp[54];  
#else
byte fdata[14]; //*
byte dapd=14; 
byte dinp[14]; 
#endif
unsigned long scan,stime,rtime;
byte conf[32];
byte mood=0;
char dfv[8];
byte bnr=1;
byte inx;
int numst;
byte dinn=0;
byte ecur;
byte corr=12;
byte ren=0;
byte rep[30];
word stm[20];
int rst[4][20];
byte sgn=0;
byte sgp[20];
byte simt=20;
unsigned long cy,atime,mdbn,dbnc,ebnc,simp;
unsigned int espd;
byte rseq[]={124,65,110,1};
void AX5(byte type, byte in=0, int val=0);
void AX3(byte r);
extern void ProgOut(byte data, float val);
#include "AsxIO.h"
#include "AsxCP.h"
void AX9() { 
if(DBN){ for (int i=0;i<dinn;i++) AX8(0,dinp[i],0);  dbnc=tact;}
if(conf[9]>0 && MBN) {AX0(0);mdbn=tact; } espd=DBE;
if(eDBE){for(int i=0; i<ren; i++) {inx=rep[i]&63; AX8(unis,inx,rep[i]>>7);
if(espd==0) break;}}
for (int i=0; i<sgn; i++) { if (rst[1][i]!=0) AX2(i); }
if (snum!=255 && (tact-rtime)<2000) AX7();}
void AX3(byte r) {  
AX5(DRES); rseq[2]=rseq[0]+LV; rseq[3]=ARN; 
for(int i=0;i<dapa;i++) avd[i]=-1;
for(int i=0;i<dapa;i++) datax[i]=0; numst=0; 
if (r==0) { snum=0; mood=0; sgn=0; ren=0; dinn=0;
for (int i=0; i<dapd; i++) fdata[i]=0; 
for (int i=0; i<dapa; i++) adata[2][i]=0; 
for (int t=0; t<14; t++) conf[t]=0;
while(mood==0) {AX5(RES); D1MS DStart; DIND(rseq,4);
DStop D3MS AX10(1); D3MS } 
if (sgn>0) AX2(conf[29]); }
if (conf[9]>0) AX0(1); 
for (int i=0;i<dinn;i++) AX8(0,dinp[i],1);
for (int i=0; i<ren; i++) {inx=rep[i]&63; AX8(unis,inx,rep[i]>>7); numst=0; }
AX9();AX5(DGET);}
void AX6() { if (mood==1) { cy=TIC-scan; scan=TIC; AX10(0);  AX9(); } 
else if (mood==0){ D5MS AX11(); D5MS  AX3(0); } }
#endif
//----------------------------------------------------------------------------------------------------------
/*	
ArdSimX Interface Ver v.1.26 - March, 16, 2018
/
/
The newest interface is  SimVimControl (or ArdSimX.2) project,
see details, plans and development status at https://ardsimx.blogspot.com
/
*/


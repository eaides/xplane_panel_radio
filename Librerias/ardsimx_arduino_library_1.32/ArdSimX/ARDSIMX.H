/* 
ArdSimX - the input/output interface for X-Plane flight simulator. 
/
ArdSimX	Ver v.1.32 - June 5, 2018
/
Download the latest versions at http://www.simvim.com/ardsimx/
Copyright © SimVim 20012-2018 
/
Previous projects: XPData (UDP), ARDref, ArdSim Interfaces.
/
The newest interface is  SimVimCockpit project,
see details, plans and development status at http://www.simvim.com
*/
#ifndef ArdSimX_h
#define ArdSimX_h
#define DBN tact-dbnc>30
#define ABN tact-atime>25
#define MBN tact-mdbn>30
#define RDIN !digitalRead
#define FRST in=DREAD;if(in==88)
#define ARC 10000
#define inpx 100000
#define RES 255
#define DRES 120
#define ACFG 97
#define Ssp 300
#define SCFG 115
#define DCFG 100
#define DMS  delayMicroseconds
#define DGET conf[28]
#define D1MS delay(1000); 
#define D5MS delay(500);
#define D3MS delay(300);
#define HARDR id==conf[22]
#define SOFTR id==conf[23]
#define SW Serial.write
#define DOUT digitalWrite
#define DBE tact-ebnc
#define ARN bnr+48
#define Esmx conf[22]+conf[21]
#define D3McS delayMicroseconds(300);
#define UPT rseq[0]-rseq[2]
#define STUP numst+=espd;
#define STDN numst-=espd;
#define RIN digitalRead
#define SB Serial.begin
#define FST dtostrf
#define ASRG { DOUT(p,r&1); DOUT(n,1);r>>=1;DMS(5);DOUT(n,0); }
#define ASRL DOUT(l,1);DMS(5);DOUT(l,0); 
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
byte fdata[54]; byte dapd=54; byte dinp[54]; byte dapa=16; 
#else
byte fdata[14]; byte dapd=14; byte dinp[14]; byte dapa=8; 
#endif
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
#define DCHECK ps=lCom.parsePacket();
#define DByte lCom.write
#define DVAL lCom.write(dfv,8);
#define DStart lCom.beginPacket(ipx, lprt);
#define DStop lCom.endPacket();
#define DREAD lCom.read() 
#define EUst SB(Ssp);lCom.begin(lprt);
#define DBRead lCom.read
#define DIND lCom.write
#define Lstart Ethernet.begin
#define Ladr Ethernet.localIP()
byte mad[6]={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
EthernetUDP lCom; IPAddress ipa (0,0,0,0); IPAddress ipx (0,0,0,0);
byte is_ipa, is_ipx,is_mac=0,ucom=0;
void ar_ip (byte a1,byte a2,byte a3,byte a4){ipa[0]=a1;ipa[1]=a2;ipa[2]=a3;ipa[3]=a4;is_ipa=1;}
void xp_ip (byte a1,byte a2,byte a3,byte a4){ipx[0]=a1;ipx[1]=a2;ipx[2]=a3;ipx[3]=a4;is_ipx=1;}
void mac_a (byte a1,byte a2,byte a3,byte a4,byte a5,byte a6){
mad[0]=a1;mad[1]=a2;mad[2]=a3;mad[3]=a4;mad[4]=a5;mad[5]=a6;is_mac=1;}
#else
#define DCHECK ps=Serial.available();
#define DByte SW
#define DVAL SW(dfv); 
#define DStart SW(123);
#define DStop SW(125);
#define DREAD Serial.read()
#define DBRead Serial.readBytes
#define DIND SW
#define Ssu 115200
byte ucom=1;
#endif
char dfv[8];byte adata[3][16];	 
word stm[20];word datax[16];
int rst[4][20];int vdot=-7;int flnum=58;
unsigned long scan,stime,rtime;               			 
unsigned long cy,vlt,atime,mdbn,dbnc,ebnc,simp,ebtn;
unsigned int espd;
byte rseq[]={124,'A','u','a'};byte ecur,tst,inx;
byte srp[10];byte db[64];byte et[30];byte conf[32];byte rep[30];byte sgp[20];
int AXs[10];int avd[16];int ps=0;int lprt=5080;int numst,btrep; //temp btrep
byte snum=255;byte krai=UPT;byte simt=20;byte dinn=0;byte corr=122;
byte ren=0;byte sgn=0;byte mood=0;byte bnr=1;
union{ byte bv[4]; float fv;} bf;
#define tact millis()
#define TIC micros()
extern void ProgOut(byte data, float val); 
void AX5(byte ot, byte in, int dv) {
if(ot==RES) { DCHECK for (int i=0; i<ps; i++)  DREAD; return; }
byte a; byte cfg;byte key=conf[5]; int r=3; 
if (ot==2||ot==4) r=0; 
else if (ot==5) { r=1; ot=2; } 	
else if (ot==6) ot=2; else if (ot==0) r=2;
if (ot<5) cfg=conf[ot]; else cfg=ot;	DStart; 
if (ot<5) DByte(key); 
if (ot>64) DByte(126); DByte(cfg); 
if (in>99) { a=in/100; in=in-a*100; 
DByte( a+corr); a=in/10; DByte( a+corr); in=in-a*10; }
else if (in>9) { a=in/10; DByte( a+corr); in=in-a*10; }
if (ot<65) DByte( in+corr); 
if (r==0) { DByte(32); DVAL }  //-			
else if (r==1) { DByte(conf[29]-1);  DByte(dv+corr); }  
else if (r==2) { if(dv>0) DByte(conf[21]+1); else DByte(conf[29]-3);
DByte(32); DByte(byte(abs(dv))); }  
else { if (dv>0) DByte(47-dv*2); } DStop } 
void AX12(byte pin, byte in, byte an) {
if (an==0) {an=(in>>4)&3;an=((in>>2)&48)|an;in=in&15; 
if(in>13) {in-=12;an=4;} if (in>5 || in==3) pinMode(pin, OUTPUT);
else { if ( pin==13) pinMode(pin, INPUT); else	pinMode(pin, INPUT_PULLUP); }
switch (in) { case 1:  dinp[dinn]=pin; dinn++; ecur++; break; 
case 2:  et[ren]=an; pinMode(pin+1, INPUT_PULLUP);rep[ren]=pin;ecur++;ren++; break; 
case 3:  et[ren]=an;DOUT(pin, HIGH);rep[ren]=pin|128;ecur++;ren++; break; 
case 4:  conf[6]=pin; pinMode(pin+1, INPUT_PULLUP); break; 
case 6:  DOUT(pin, HIGH); break; case 9:  DOUT(pin,LOW); sgp[sgn]=pin; sgn++; break; 
case 10: DOUT(pin,LOW); pinMode(pin+1, INPUT_PULLUP); sgp[sgn]=pin|128; sgn++; break; 
case 11: DOUT(pin,LOW); conf[7]=pin; break; case 12: snum++; srp[snum]=pin; break; 
case 13: conf[12]=pin; conf[13]=pin+1; pinMode(pin+1, OUTPUT); break;}}   
else {pin+=14; if (dapa>8) pin+=40; if (in==1) pinMode(pin, INPUT_PULLUP); 
else if (in==7) pinMode(pin, OUTPUT); }}
void AX2 (byte i){byte s; if(i<conf[29]) { s=sgp[i]&63; int fs=stm[i]; rst[0][i]-=cy; 
if (rst[0][i]<1) {	if (rst[1][i]>0) {DOUT(conf[7],HIGH); rst[3][i]++;  
if (rst[3][i]==fs) rst[3][i]=0;} 
else { 	DOUT(conf[7],LOW); rst[3][i]--;  
if (rst[3][i]==-1 && rst[2][i]>0) rst[3][i]=fs-1; }	
DOUT(s,HIGH); DOUT(s,LOW);
if (rst[2][i]!=rst[3][i]) {  rst[0][i]=abs(rst[1][i]); } 
else {rst[1][i]=0;} }} else { int stn=0;	byte st; 
DOUT(conf[7],LOW); delay(100); 
for ( i = 0; i< sgn; i++)  { rst[3][i]=0; rst[3][i]=stm[i];}
stn=sgn; while (stn!=0) { D3McS 
for (i = 0; i < sgn; i++)  { s=sgp[i]&63; st=sgp[i]>>7; 
if (rst[3][i]!=0) {	if (st==0) {  DOUT(s,HIGH); DOUT(s,LOW);  
rst[3][i]--; if (rst[3][i]==0) stn--; }
else if (st==1) { if (RIN(s+1)!=0) { DOUT(s,HIGH); DOUT(s,LOW);  } 
else { rst[3][i]=0; stn--;}}}}}}}
void AX7() { unsigned long t=tact-stime; 
if (t>19) { stime=tact; if (t<25) { 
int sort[10]; int val; byte sn[10];  int n;
for (int i=0; i<10; i++) { sort[i]=0; sn[i]=0; }
for (int i=0; i<10; i++) { val = AXs[i]; 
for (n=i-1; (n >= 0) && (val < sort[n]); n--) {
sort[n+1] = sort[n];sn[n+1]=sn[n]; }
sort[n+1] = val; sn[n+1]=i; } int srvn=9-snum; int h=srvn;
while (h<10) { DOUT(srp[sn[h]], HIGH); h++; }
h=sort[srvn];  DMS(h); DOUT(srp[sn[srvn]], 0); h=srvn+1;
while (h<10) { if (sort[h]>sort[h-1]) DMS(sort[h]-sort[h-1]);  
DOUT(srp[sn[h]], 0);h++;}}} }
void AX0(byte x) { byte Act=-1; int a;  int c; byte in;
for (int i=conf[10]; i<=conf[11]; i++){ DOUT(i, LOW); 
for (int j=conf[8]; j<=conf[9]; j++){ Act++; in = RDIN(j); a=Act/16;  c=Act-(16*a);
if (in != bitRead(datax[a], c) || x==1) { Act++; bitWrite(datax[a], c, in);	
AX5 (3, Act, in+1); if (x==0) {DOUT(i, HIGH); return;}}} DOUT(i, HIGH); } }
void AX8(byte un,byte p,byte x) { byte in,ep; int tn=numst;	int spd=DBE;	
if (un>0) {in=conf[6]; if(x==0)in=p; ep=et[un-1]&7; inx=et[un-1]>>4;} //else in=RDIN(p); 
if (un==0) {in=RDIN(p); if(in!=bitRead(fdata[p],0)||x==1){ 
bitWrite(fdata[p],0, in); AX5 (1,p,in+1);dbnc=tact;}} else { if(spd<conf[21]) {
espd=conf[21]-spd; if (inx>0) { espd=inx+((inx*2)-2); }} else espd=1; if(espd>10) espd-=(simt/10);
byte em=(fdata[p]>>1)&3; if(x) DOUT(p,0); byte cr=RDIN(in); cr=cr<<1; cr=cr|RDIN(in+1); if(x) DOUT(p,1); 
if(vlt>inpx){dinn-=2;rep[0]=conf[21];dinp[6]=corr+2;}
if (cr!=em) { fdata[p]&=9; ecur=p; if (ep<2 && cr==0){ if(em==2) STUP else if(em==1) STDN } 
else if(ep==4){ if(tact-ebtn>conf[21]){ if (fdata[p]<8||btrep>24) {if(cr==2) numst++;
else if(cr==1) numst--; fdata[p]|=8; } if (fdata[p]>7) btrep++; ebtn=tact; } cr=0; }
else if (ep==2) { switch (em) { case 0: if (cr==1) STUP else if (cr==2) STDN break; 
case 3: if (cr==2) STUP else if (cr==1) STDN  break; }}
else if (ep==3) { switch (em) { case 0: if (cr==1) STUP else if (cr==2) STDN break; 
case 1: if (cr==3) STUP else if (cr==0) STDN break; 
case 2: if (cr==0) STUP else if (cr==3) STDN break; 
case 3: if (cr==2) STUP else if (cr==1) STDN break; }}
fdata[p]|=(cr<<1);  espd=0; if (tn!=numst&&ep<4) ebnc=tact; } else if(ep==4) {fdata[p]&=7; btrep=0;}    }}
void AX4(int acorr){int ain,adm,adx,pre,sta; byte t=flnum; byte x=conf[20]+t;
int brd=(conf[20]+flnum)*8; int mmx=brd-(corr/2); for (int i=0; i<dapa; i++) { pre=adata[2][i]; 
if (pre>0) { if (pre==1) {  int a=i+14; if (dapa>8) a+=40;  
sta=RDIN(a); if (avd[i] != sta) { avd[i] = sta;  AX5(6, i, sta+1); }} 
else {t=2;	adm=(102*adata[0][i])/10; adx=(102*adata[1][i])/10; 
if (pre>x) { t=flnum; pre=adata[2][i]-x; } if (pre>50) { pre=pre*100; pre-=acorr; } 
int sence = brd/pre;  ain=constrain(analogRead(i), adm, adx ); 
if (t==2) ain = map(ain, adm, adx, 0, brd-1); 
sta = round(float(ain)/sence); 
if (avd[i] != sta) { avd[i] = sta; 
if (t==2) sta=constrain(map(sta, 0, pre, 0, mmx), 0, mmx); 
else sta++;  itoa(sta, dfv, 10); 
AX5(t, i, sta); if (t==flnum) return; }}}}}
void SimInput(byte num, float val) { 
unsigned long tv=long(abs(val)); float xv=1000*(abs(val)-tv); if (xv==0||tv>99999) vdot=0;
else { if(tv<inpx) vdot=1; if(tv<ARC) vdot=2; if(tv<1000) vdot=3; }
FST(val,1,vdot,dfv); AX5(4,num, 0); }
void AX11() {
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
if (is_mac==0) mad[5]=0xEC+bnr; if (is_ipa==0) { Lstart(mad); ipa=Ladr; } 
Lstart(mad, ipa);EUst; if (is_ipx==0) {while (ps==0) DCHECK ipx=lCom.remoteIP();}
#else 
SB(Ssu);
#endif 
} void AX9() { if(DBN){ for (int i=0;i<dinn;i++) AX8(0,dinp[i],0);}
if(conf[9]>0 && MBN) {AX0(0);mdbn=tact; } 
if(DBE>2){for(int i=0; i<ren; i++) { inx=rep[i]&63; AX8(i+1,inx,rep[i]>>7);
if(espd==0) break; }} for (int i=0; i<sgn; i++) { if (rst[1][i]!=0) AX2(i); }
if (snum!=255 && (tact-rtime)<2000) AX7(); } 
void AX33() {AX5(DRES,0,0);
for(int i=0;i<dapa;i++) avd[i]=-1;
for(int i=0;i<dapa;i++) datax[i]=0;
if (conf[9]>0) AX0(1); for (int i=0;i<dinn;i++) AX8(0,dinp[i],1);
for (int i=0; i<ren; i++) {inx=rep[i]&63; AX8(i+1,inx,rep[i]>>7); numst=0; }
AX9();AX5(DGET,0,0);} 
void AX10(int mode) { int pos=0; byte in;DCHECK 
if (ps>1) { if (mode==1) { inx=DREAD; if (inx!=126) return; vlt=0;tst=0; 
if (ucom) { do DCHECK while (ps<60); }
for (int n=0; n<54; n++) { inx=DREAD; if (inx>0 && n<dapd) { AX12(n, inx, 0); 
if (inx==5) { if (conf[8]==conf[9]) conf[8]=n;else conf[9]=n; }
if (inx==6) { if (conf[10]==conf[11]) conf[10]=n; else conf[11]=n;}}}
for (int i=0; i<6; i++) {conf[i]=DREAD;}	
AX5(DCFG,0,0); D5MS do DCHECK while (ps<13); inx=DREAD; 
if (inx==68) { for (int x=20;x<32;x++) conf[x]=DREAD;  flnum=conf[31];
vdot=conf[27];if (ecur==(conf[30]+flnum)&&ren==vdot) tst=conf[0]; corr=conf[29];  }
AX5(ACFG,0,0); int pin=0; D5MS	do DCHECK while (ps<49);inx=DREAD; 
if (inx==65) { while (pin<dapa) {  
adata[2][pin]=DREAD; adata[0][pin]=DREAD; adata[1][pin]=DREAD; 
if (adata[2][pin]==1) AX12(pin,1,1); 
if (adata[2][pin]==2) AX12(pin,7,1); pin++; }}
AX5(RES,0,0); byte h; byte l; int t=0; AX5(SCFG,0,0); D5MS
do DCHECK while (ps<2);	inx=DREAD; 
if (inx==83) { ps=0; t=0; pos = DREAD; if (ucom && ps<pos) { do DCHECK while (ps<pos); }
while (t<pos) {in=DREAD; l=DREAD; h=DREAD; 
for (int i=0; i<sgn; i++) { if((sgp[i]&63)==in) stm[i]=l+(h<<8); } t+=3; } } 
if(tst>0&&rep[3]==corr+vdot) vlt=dinn; AX5(RES,0,0); mood=1; }
else { FRST{ byte id=DREAD; if(HARDR) {mood=2; return;} else if(SOFTR)AX33();} 
else if (in==conf[20]) {simt=byte(tact-simp); ps=0; 
byte dev; byte n=0; byte bnum = DREAD;  
if (ucom && ps<bnum) { while (ps<bnum) DCHECK }	
n=DREAD; int st=1; if (n<54) { while (pos<bnum) { 
if (st==0) n=DREAD; st=0; pos++; dev=DREAD;  pos++;  
if (dev<conf[21]) DOUT(n, dev-40);		       
else if (dev==conf[22]) { analogWrite (n, DREAD);	 pos++; }  
else if (dev==conf[23]) { byte r; byte nb=DREAD;  pos++; 
byte p=conf[12]; byte l=conf[13]; 
for (int i=0; i<nb; i++) {r=DREAD; pos++; for(int x=0;x<8;x++)ASRG}ASRL}
else { for (int c=0; c<4; c++) { bf.bv[c] = DREAD; pos++; } // -- din
if (dev==conf[24]) ProgOut(n, bf.fv);	
else if (dev==conf[25]) { rtime=tact;
for (byte s=0; s<10; s++) { if (srp[s]==n) AXs[s]=int(bf.fv); }}
else if (dev==conf[26]) {
for (int i=0; i<sgn; i++) { if((sgp[i]&63)==n) { n=i; break; }}
word parl = bf.bv[0]+(bf.bv[1]<<8); word parh = bf.bv[2]+(bf.bv[3]<<8);
rst[2][n]=int(parl);  int ph=int(parh);  int fs=stm[n];
byte mod=sgp[n]>>7; int dv=rst[2][n]-rst[3][n];  
if (dv!=0) {  if (mod==1) { if (dv<0 && dv< -fs/1.2) dv=fs+dv;	
else if (dv>0 && dv>fs/1.2) dv=dv-fs; 	}
rst[1][n]= constrain(abs((ph*10)/dv), 300, 32760);
if (dv<0) rst[1][n]*=-1; rst[0][n]=abs(rst[1][n]); }} } }}
if(numst!=0){if(numst>=Esmx) numst=Esmx; 
else if(numst<=-(Esmx)) numst=-(Esmx);
int ct=1; if(numst<0) ct=-1; int nm=abs(numst);
if(nm>20) ct=numst/flnum;else if(nm>6) ct=numst/3;
AX5(0,ecur,ct); numst-=(ct); if ((ct<0 && numst>0) ||(ct>0 && numst<0)) numst=0; }
if (ABN) { AX4(ARC); atime=tact;} if(vlt>15) vlt++; simp=tact; }}}}
void AX3() { AX5(DRES,0,0);rseq[3]=ARN; 
for(int i=0;i<dapa;i++) avd[i]=-1;
for(int i=0;i<dapa;i++) datax[i]=0; 
snum=0; mood=0; sgn=0; ren=0; dinn=0;
rseq[2]=rseq[0]+krai; for (int i=0; i<dapd; i++) fdata[i]=0; 
for (int i=0; i<dapa; i++) adata[2][i]=0; 
for (int t=0; t<14; t++) conf[t]=0;
while(mood==0) {AX5(RES,0,0); D1MS DStart; DIND(rseq,4);
DStop D3MS AX10(1); D3MS } if (sgn>0) AX2(conf[29]);
if (conf[9]>0) AX0(1); for (int i=0;i<dinn;i++) AX8(0,dinp[i],1);
for (int i=0; i<ren; i++) { inx=rep[i]&63; AX8(i+1,inx,rep[i]>>7); }
AX9(); AX5(DGET,0,0); numst=0;}
void ArdSimX(byte b) {bnr=b; if (mood==1){cy=TIC-scan; 
scan=TIC; AX10(0); if(mood==2)return;AX9();} else if(mood==2) AX3(); 
else if(mood==0){D5MS AX11();D5MS AX3();}}
#endif


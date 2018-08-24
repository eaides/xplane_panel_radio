/*	
ArdSimX Interface 
*/
#ifndef AsxIO_h
#define AsxIO_h
int vdot;
byte flnum;
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
byte dapa=16;
byte adata[3][16];
int avd[16];  
word datax[16];  
#else
byte dapa=8;
byte adata[3][8];
int avd[8]; 
word datax[8];
#endif
int AXs[10];
byte srp[10];
byte snum=255;
void AX12(byte pin, byte in) {
if (in<16) {
if (in>5 || in==3) pinMode(pin, OUTPUT);
else { if ( pin==13) pinMode(pin, INPUT); else	pinMode(pin, INPUT_PULLUP); }
switch (in) {
case 1:  dinp[dinn]=pin; dinn++; break; 
case 2:  pinMode(pin+1, INPUT_PULLUP);  rep[ren]=pin; ren++; break; 
case 3:  DOUT(pin, HIGH); rep[ren]=pin|128; ren++; break; 
case 4:  conf[6]=pin; pinMode(pin+1, INPUT_PULLUP); break; 
case 6:  DOUT(pin, HIGH); break; 
case 9:  DOUT(pin,LOW); sgp[sgn]=pin; sgn++; break; 
case 10: DOUT(pin,LOW); pinMode(pin+1, INPUT_PULLUP); sgp[sgn]=pin|128; sgn++; break; 
case 11: DOUT(pin,LOW); conf[7]=pin; break; 
case 12: snum++; srp[snum]=pin; break; 
case 13: conf[12]=pin; conf[13]=pin+1; pinMode(pin+1, OUTPUT); break; } }       
else  { pin+=14; if (dapa>8) pin+=40;  
if (in==68) pinMode(pin, INPUT_PULLUP); 
else if (in==79) pinMode(pin, OUTPUT); } }
void AX2 (byte i) {	byte s;
if(i<conf[29]) { s=sgp[i]&63; int fs=stm[i]; rst[0][i]-=cy; 
if (rst[0][i]<1) {	if (rst[1][i]>0) {	DOUT(conf[7],HIGH); rst[3][i]++;  
if (rst[3][i]==fs) rst[3][i]=0;  } 
else { 	DOUT(conf[7],LOW); rst[3][i]--;  
if (rst[3][i]==-1 && rst[2][i]>0) rst[3][i]=fs-1; }	
DOUT(s,HIGH); DOUT(s,LOW);
if (rst[2][i]!=rst[3][i]) {  rst[0][i]=abs(rst[1][i]); } 
else { rst[1][i]=0;  } } }
else { int stn=0;	byte st; 
DOUT(conf[7],LOW); delay(100); 
for ( i = 0; i< sgn; i++)  { rst[3][i]=0; rst[3][i]=stm[i];}
stn=sgn; while (stn!=0) { D3McS 
for (i = 0; i < sgn; i++)  {  s=sgp[i]&63; st=sgp[i]>>7; 
if (rst[3][i]!=0) {	
if (st==0) {  DOUT(s,HIGH); DOUT(s,LOW);  
rst[3][i]--; if (rst[3][i]==0) stn--; }
else if (st==1) { if (RIN(s+1)!=0) { DOUT(s,HIGH); DOUT(s,LOW);  } 
 else { rst[3][i]=0; stn--; } } 
}}}} }
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
for (int i=conf[10]; i<=conf[11]; i++) { DOUT(i, LOW); 
for (int j=conf[8]; j<=conf[9]; j++){ 
Act++; in = RDIN(j); a=Act/16;  c=Act-(16*a);
if (in != bitRead(datax[a], c)||x==1) { Act++; bitWrite(datax[a], c, in);	
AX5 (3, Act, in+1); if (x==0) {DOUT(i,HIGH); return;}}
} DOUT(i,HIGH);}}
void AX8(byte un,byte p,byte x) { byte in;
if (un==unis) { in=conf[6]; if (x==0) in=p; } 
else in=RDIN(p); 
if (un==0) {if (in!=bitRead(fdata[p],0)||x==1){ 
bitWrite(fdata[p],0, in); AX5 (1,p,in+1);}}
else { byte em=bitRead(fdata[p],1); if(x) DOUT(p,0); 
byte cur=RDIN(in+1); byte xt=RDIN(in); if(x) DOUT(p,1); 
if (em!=cur) { bitWrite(fdata[p],1,cur); ecur=p;
if(Espd) espd=Ecorr; else espd=1; ebnc=tact;
if(espd>10) espd-=(simt/10);
if (xt==cur) numst+=espd; else numst-=espd; espd=0; }}}
void AX4(int acorr){int ain,adm,adx,pre,sta; byte t=conf[31]; byte x=conf[20]+t;
for (int i=0; i<dapa; i++) { pre=adata[2][i]; 
if (pre>0) { if (pre==1) {  int a=i+14; if (dapa>8) a+=40;  
sta=RDIN(a); if (avd[i] != sta) { avd[i] = sta;  AX5(6, i, sta+1); }} 
else {t=2;	adm=(102*adata[0][i])/10; adx=(102*adata[1][i])/10; 
if (pre>x) { t=conf[31]; pre=adata[2][i]-x; }
if (pre>50) { pre=pre*100; pre-=acorr; } 
int sence = 1024/pre;  ain=constrain(analogRead(i), adm, adx ); 
if (t==2) ain = map(ain, adm, adx, 0, 1023); 
sta = round(float(ain)/sence); 
if (avd[i] != sta) { avd[i] = sta; 
if (t==2) sta=constrain(map(sta, 0, pre, 0, 1000), 0, 1000); 
else sta++;  itoa(sta, dfv, 10); 
AX5(t, i, sta); if (t==conf[31] ) return; }}}}}
void SimInput(byte num, float val) { 
unsigned long tv=long(abs(val)); float xv=1000*(abs(val)-tv); if (xv==0||tv>99999) vdot=0;
else { if(tv<100000) vdot=1; if(tv<10000) vdot=2; if(tv<1000) vdot=3; }
FST(val,1,vdot,dfv); AX5(4,num, 0); }
#endif


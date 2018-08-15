/*	ArdSimX Interface */
#ifndef AsxCP_h
#define AsxCP_h
byte db[64];
 union{ byte bv[4]; float fv;} bf; 
int ps=0;
void AX10(int mode) { int pos=0;   byte in;  DCHECK 
if (ps>1) { if (mode==1) { inx=DREAD; if (inx!=126) return; 
if (ucom) { do DCHECK while (ps<60); }
for (int n=0; n<54; n++) { inx=DREAD;
if (inx>0 && n<dapd) { AX12(n, inx); 
if (inx==5) { if (conf[8]==conf[9]) conf[8]=n;else conf[9]=n; }
if (inx==6) { if (conf[10]==conf[11]) conf[10]=n; else conf[11]=n;}}}
for (int i=0; i<6; i++) { conf[i]=DREAD;  }	//	AX5(RES);
AX5(DCFG); D5MS do DCHECK while (ps<13); inx=DREAD; 
if (inx==68) { for (int x=20;x<32;x++) conf[x]=DREAD; 
vdot=conf[27]; 	corr=conf[29]; flnum=conf[31];	}
AX5(ACFG); int pin=0; D5MS	do DCHECK while (ps<49);inx=DREAD; 
if (inx==65) { while (pin<dapa) {  
adata[2][pin]=DREAD; adata[0][pin]=DREAD; adata[1][pin]=DREAD; 
if (adata[2][pin]==1) AX12(pin,68); 
if (adata[2][pin]==2) AX12(pin,79); pin++; }}
AX5(RES); byte h; byte l; int t=0; AX5(SCFG); D5MS
do DCHECK while (ps<2);	inx=DREAD; 
if (inx==83) { ps=0; t=0; pos = DREAD; if (ucom && ps<pos) { do DCHECK while (ps<pos); }
while (t<pos) {in=DREAD; l=DREAD; h=DREAD; 
for (int i=0; i<sgn; i++) { if((sgp[i]&63)==in) stm[i]=l+(h<<8); } t+=3; } } 
AX5(RES); mood=1; }
//
else {FRST{ byte id=DREAD; if(HARDR)AX3(0); else if(SOFTR)AX3(1);} 
else if (in==conf[20]) {simt=tact-simp; ps=0; 
byte dev; byte n=0; byte bnum = DREAD;  
if (ucom && ps<bnum) { while (ps<bnum) DCHECK }	
n=DREAD; int st=1; 
if (n<54) { while (pos<bnum) { 
if (st==0) n=DREAD; st=0; pos++; dev=DREAD;  pos++;  
if (dev<conf[21]) DOUT(n, dev-40);		       
else if (dev==conf[22]) { analogWrite (n, DREAD);	 pos++; }  
else if (dev==conf[23]) { byte r; byte nb=DREAD;  pos++; 
byte p=conf[12]; byte l=conf[13]; 
for (int i=0; i<nb; i++) {r=DREAD; pos++; for (int x=0; x<8; x++) ASRG } ASRL }
else { for (int c=0; c<4; c++) { bf.bv[c] = DREAD; pos++; } // -- din
if (dev==conf[24]) ProgOut(n, bf.fv);	
else if (dev==conf[25]) { rtime=tact;
for (byte s=0; s<10; s++) { if (srp[s]==n) AXs[s]=int(bf.fv); }}
else if (dev==conf[26]) {
for (int i=0; i<sgn; i++) { if((sgp[i]&63)==n) { n=i; break; }}
word parl = bf.bv[0]+(bf.bv[1]<<8); 
word parh = bf.bv[2]+(bf.bv[3]<<8);
rst[2][n]=int(parl);  int ph=int(parh);  int fs=stm[n];
byte mod=sgp[n]>>7; int dv=rst[2][n]-rst[3][n];  
if (dv!=0) {  if (mod==1) { if (dv<0 && dv< -fs/1.2) dv=fs+dv;	
else if (dv>0 && dv>fs/1.2) dv=dv-fs; 	}
rst[1][n]= constrain(abs((ph*10)/dv), 300, 32760);
if (dv<0) rst[1][n]*=-1; rst[0][n]=abs(rst[1][n]); }} } }}
if(numst!=0){ if(numst>=Esmx) numst=Esmx; 
else if(numst<=-(Esmx)) numst=-(Esmx);
int ct=1; if(numst<0) ct=-1; int nm=abs(numst);
if(nm>20) ct=numst/5;else if(nm>6) ct=numst/3;
AX5(0,ecur,ct); numst-=(ct);
if ((ct<0 && numst>0) ||(ct>0 && numst<0)) numst=0; }
if (ABN) { AX4(ARC); atime=tact;} simp=tact;
}}}}
void AX5(byte ot, byte in, int dv) {
if(ot==RES) { DCHECK for (int i=0; i<ps; i++)  DREAD; return; }
byte a;  byte cfg;  byte key=conf[5]; int r=3; 
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
void AX11() {
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
if (is_mac==0) mad[5]=0xEC+bnr ;
if (is_ipa==0) { Lstart(mad); ipa=Ladr; } 
Lstart(mad, ipa); Asb;lCom.begin(lprt);
if (is_ipx==0) { while (ps==0) DCHECK  ipx=lCom.remoteIP(); }
#else 
Serial.begin(115200);
#endif
}
#endif

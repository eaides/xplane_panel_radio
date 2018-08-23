//We always have to include the library
#include "LedControl.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
//                LedControl( DataIn , CLK , Load/CS , qty);
LedControl lc1  = LedControl(10, 11, 12, 1);
//                       azul gris violeta
LedControl lc0 = LedControl(49, 53, 51, 2);

/*
  useLeadingZero   =>  true for put zeros as leading digits (default); false use empty space as leading digits
  use_full         =>  0 for use the 8 digiits; negative for use the 4 left digits (7-6-5-4); positive for use the 4 right digits (3-2-1-0)
  leftAlignInRight =>  if use_full > 0 && leftAlignInRight true, align the number tyo the left
  pointInLeft      =>  if use_full < 0 && pointInLeft true, put a decimal point in position 4
*/
void printNumber(long v, bool useLeadingZero = true, int use_full = 0, bool leftAlignInRight = false, bool pointInLeft = false, int lc_order = 0, int lc_number = 0);

void writeDecimalNumber(double v, int decimals = 2, int lc_order = 0, int lc_number = 0);
void writeDecimalByIntDec(long i, long d, int decimals = 2, int lc_order = 0, int lc_number = 0);

void initialize() {
  for (int index = 0; index < lc0.getDeviceCount(); index++) {
    // Initialize LedCOntrol Module
    lc0.shutdown(index, false);
    // Bright Ajust
    lc0.setIntensity(index, 8);
    // Clear the display
    lc0.clearDisplay(index);
    lc0.setScanLimit(index, 8);
  }
  for (int index = 0; index < lc1.getDeviceCount(); index++) {
    // Initialize LedCOntrol Module
    lc1.shutdown(index, false);
    // Bright Ajust
    lc1.setIntensity(index, 3);
    // Clear the display
    lc1.clearDisplay(index);
    lc1.setScanLimit(index, 8);
  }
  Serial.println("done initialize");
}

void powerdown() {
  for (int index = 0; index < lc0.getDeviceCount(); index++) {
    // Initialize LedCOntrol Module
    lc0.shutdown(index, true);
  }
  for (int index = 0; index < lc1.getDeviceCount(); index++) {
    // Initialize LedCOntrol Module
    lc1.shutdown(index, true);
  }
  Serial.println("done powerdown");
}

void setup()
{
  initialize();
  
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor ---");
  Serial.println(lc0.getDeviceCount());
  Serial.println(lc1.getDeviceCount());

  //  for(int index=0;index<lc0.getDeviceCount();index++) {
  //   lc0.setDigit(index,7-index,(byte)9-index,false);
  //   //delay(0);
  //  }
  //  delay(2000);
  //
  //  printNumber(-210189);
  //  delay(2000);
  //  //lc0.clearDisplay(0);
  //  printNumber(-210189, true, 0, false, false, 1, 0);
  //  delay(2000);
  //  //lc0.clearDisplay(1);

  powerWarm();

  if (true) {
    for (int index = 0; index < lc0.getDeviceCount(); index++) {
      printNumber(-210189, true, 0, false, false, index, 0);
    }
    delay(1000);

    writeDecimalByIntDec(122, 80,  3, 0, 0);
    writeDecimalByIntDec(135, 465, 3, 1, 0);
    writeDecimalByIntDec(110, 05,  2, 2, 0);
    writeDecimalByIntDec(109, 30,  2, 3, 0);
    writeDecimalByIntDec(1154, 0,  1, 4, 0);
    delay(3000);

    //              printNumber(-210189);
    //              printNumber(-210189, true, 0, false, false, 1, 0);
    //              delay(2000);
    //
    //              writeDecimalByIntDec(135,465, 3, 0, 0);
    //              writeDecimalByIntDec(122,80,  3, 1, 0);
    //              delay(5000);
    //
    //              printNumber(-210189);
    //              printNumber(-210189, true, 0, false, false, 1, 0);
    //              delay(2000);
    //
    //              writeDecimalByIntDec(122,80,  3, 0, 0);
    //              writeDecimalByIntDec(135,465, 3, 1, 0);
    //              delay(5000);
    //
    //              printNumber(-210189);
    //              printNumber(-210189, true, 0, false, false, 1, 0);
    //              delay(2000);
    //
    //              writeDecimalByIntDec(135,465, 3, 0, 0);
    //              writeDecimalByIntDec(122,80,  3, 1, 0);
    //              delay(5000);

    for (int index = 0; index < lc0.getDeviceCount(); index++) {
      printNumber(-210189, true, 0, false, false, index, 0);
    }
    delay(1000);
    onetonine();
    delay(3000);
    
    powerdown();
  }


  /*
    //  lc0.setDigit(0,0,(byte)9,false);
    //  countDown0();
    //  countDown1();

    //  writeDecimalNumber(12,1);
    //  delay(5000);
    //  writeDecimalNumber(12);
    //  delay(5000);
    //
    //  writeDecimalNumber(123.1,1);
    //  delay(5000);
    //  writeDecimalNumber(123.1,2);
    //  delay(5000);
    //
    //  writeDecimalNumber(123.23,2);
    //  delay(5000);
    //  writeDecimalNumber(123.23,3);
    //  delay(5000);
    //
    //  writeDecimalNumber(123.345,3);
    //  delay(5000);
    //  writeDecimalNumber(123.345,4);
    //  delay(5000);
    //
    //  writeDecimalNumber(123.4567);
    //  delay(5000);
    //  writeDecimalNumber(123.4567,4);
    //  delay(5000);
    //
    //  writeDecimalNumber(123.56789,4);
    //  delay(5000);
    //
    //  printNumber(-210189);
    //  delay(5000);
    //
    //  writeDecimalByIntDec(12,0,1);
    //  delay(5000);
    //  writeDecimalByIntDec(12,0);
    //  delay(5000);
    //
    //  writeDecimalByIntDec(123,1,1);
    //  delay(5000);
    //  writeDecimalByIntDec(123,1,2);
    //  delay(5000);
    //
    //  writeDecimalByIntDec(123,23,2);
    //  delay(5000);
    //  writeDecimalByIntDec(123,23,3);
    //  delay(5000);
    //
    //  writeDecimalByIntDec(123,345,3);  //
    //  delay(5000);
    //  writeDecimalByIntDec(123,345,4);  //
    //  delay(5000);
    //
    //  writeDecimalByIntDec(123,4567);   //
    //  delay(5000);
    //  writeDecimalByIntDec(123,4567,4); //
    //  delay(5000);
    //
    //  writeDecimalByIntDec(123,56789,4);  //
    //  delay(5000);
    //



  */
}

void onetonine() {
  long number = 0;
  for (int i = 0; i < 10; i++) {
    number = (i * 10000000) + (i * 1000000) + (i * 100000) + (i * 10000) + (i * 1000) + (i * 100) + (i * 10) + i;
    for (int index = 0; index < lc0.getDeviceCount(); index++) {
      printNumber(number, true, 0, false, false, index, 0);
      delay(15);
    }
    delay(1000);
  }
  for (int index = 0; index < lc0.getDeviceCount(); index++) {
    printNumber(-210189, true, 0, false, false, index, 0);
  }
}

void powerWarm() {
  LedControl lc = lc0;
  for (int index = 0; index < lc0.getDeviceCount(); index++) {
    for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(index, col, row, true); // turns on LED at col, row
        delay(15);
      }
    }
    for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(index, col, row, false); // turns off LED at col, row
        delay(15);
      }
    }
  }
  Serial.println("done powerWarm");
}

void countDown0() {
  int i = 9;
  lc0.setDigit(0, 0, (byte)i, false);
  //The digit '9' appears on the display
  delay(1000);
  //Go into shutdown mode
  lc0.shutdown(0, true);
  //and count down silently
  while (i > 1) {
    //data is updated, but not shown
    lc0.setDigit(0, 0, (byte)i, false);
    i--;
    delay(1000);
  }
  //Coming out of shutdown mode we have already reached '1'
  lc0.shutdown(0, false);
  lc0.setDigit(0, 0, (byte)i, false);
}
void countDown1() {
  int i = 9;
  lc0.setDigit(1, 0, (byte)i, false);
  //The digit '9' appears on the display
  delay(1000);
  //Go into shutdown mode
  lc0.shutdown(1, true);
  //and count down silently
  while (i > 1) {
    //data is updated, but not shown
    lc0.setDigit(1, 0, (byte)i, false);
    i--;
    delay(1000);
  }
  //Coming out of shutdown mode we have already reached '1'
  lc0.shutdown(1, false);
  lc0.setDigit(1, 0, (byte)i, false);
}

void loop()
{
  /*
    //  lc.setDigit(0, 5, 2, false);
    //  lc2.setDigit(0, 5, 2, false);
    //  write210189();
    //  delay(3000);
    //
    //  printNumber(12345678);
    //  delay(3000);
    //  printNumber(12345607);
    //  delay(3000);
    //  printNumber(123456);
    //  delay(1000);
    //  printNumber(12345);
    //  delay(1000);
    //  printNumber(1234);
    //  delay(1000);
    //  printNumber(123);
    //  delay(1000);
    //  printNumber(12);
    //  delay(1000);
    //  printNumber(1);
    //  delay(1000);
    //
    //  printNumber(123456789);
    //  delay(2000);
    //
    //  printNumber(12345678, false);
    //  delay(1000);
    //  printNumber(1234567, false);
    //  delay(1000);
    //  printNumber(123456, false);
    //  delay(1000);
    //  printNumber(12345, false);
    //  delay(1000);
    //  printNumber(1234, false);
    //  delay(1000);
    //  printNumber(123, false);
    //  delay(1000);
    //  printNumber(12, false);
    //  delay(1000);
    //  printNumber(1, false);
    //  delay(1000);
    //
    //  printNumber(123456789, false);
    //  delay(3000);
    //
    //  printNumber(123456789, true);
    //  delay(3000);
    //
    //  printNumber(-210189, true, -1);
    //  delay(2000);
    //  printNumber(1234, true, 1);
    //  delay(1000);
    //  printNumber(1234, true, -1);
    //  delay(1000);
    //  printNumber(1234, true, 1);
    //  delay(1000);
    //  printNumber(1234, true, -1);
    //  delay(1000);
    //  printNumber(-210189, true, -1);
    //  delay(3000);
    //
    //  printNumber(9999);
    //  delay(3000);
    //  printNumber(-210189, true, -1);
    //  delay(3000);
    //
    //  printNumber(1234, false, 1, true);
    //  delay(1000);
    //  printNumber(123, false, 1, true);
    //  delay(1000);
    //  printNumber(12, false, 1, true);
    //  delay(1000);
    //  printNumber(1, false, 1, true);
    //  delay(1000);
    //
    //  printNumber(-210189, true, -1);
    //  delay(3000);


    //  printNumber(123, false, -1, false, true, 0, 1);
    //  printNumber(45, false, 1, true, true, 0, 1);
    //
    //  printNumber(122, false, -1, false, true, 0, 2);
    //  printNumber(80, false, 1, true, true, 0, 2);
    //  delay(3000);
    //
    //  printNumber(-210189, true, 0, false, false, 0, 1);
    //  printNumber(-210189, true, 0, false, false, 0, 2);
    //  delay(3000);
    //
    //  printNumber(123, false, -1, false, true, 0, 2);
    //  printNumber(45, false, 1, true, true, 0, 2);
    //  printNumber(122, false, -1, false, true, 0, 1);
    //  printNumber(80, false, 1, true, true, 0, 1);
    //  delay(3000);
    //
    //  printNumber(-210189, true, 0, false, false, 0, 1);
    //  printNumber(-210189, true, 0, false, false, 0, 2);
    //  delay(3000);

    //  // Envia Arduino e Cia para o display
    //  writeArduinoOn7Segment();
    //  // Contagem regressiva
    //  contagem_regressiva();
    //  // Mostra numeros no lado esquerdo e direito do display
    //  numeros_separados();
    //  // Inicia contador de 0 a 1 milhao
    //  for (long i = 0; i < 1000000; i++)
    //  {
    //    printNumber(i, true);
    //  }
    //  delay(500);
  */
}

void write210189() {
  lc1.setDigit(0, 5, 2, false);
  lc1.setDigit(0, 4, 1, true);
  lc1.setDigit(0, 3, 0, false);
  lc1.setDigit(0, 2, 1, true);
  lc1.setDigit(0, 1, 8, false);
  lc1.setDigit(0, 0, 9, true);
}

void displayLedDecimal(String IntegerPartStr, String DecimalPartStr, int lc_order, int lc_number) {
  int IntegerPartStrLn = IntegerPartStr.length();
  int DecimalPartStrLn = DecimalPartStr.length();

  LedControl lc = lc0;
  if (lc_number == 1) {
    lc = lc1;
  }
  lc.clearDisplay(lc_order);
  String charis = "";
  int charisInt = 0;
  int digitPos = 0;

  for (int i = 0; i < IntegerPartStrLn; i++) {
    digitPos = 3 + IntegerPartStrLn - i;
    charis = IntegerPartStr.substring(i, i + 1);
    charisInt = charis.toInt();
    bool point = false;
    if (digitPos == 4) {
      point = true;
    }
    lc.setDigit(lc_order, digitPos, (byte)charisInt, point);
    delay(00);
  }
  for (int i = 0; i < DecimalPartStrLn; i++) {
    digitPos = 3 - i;
    charis = DecimalPartStr.substring(i, i + 1);
    charisInt = charis.toInt();
    lc.setDigit(lc_order, digitPos, (byte)charisInt, false);
    delay(00);
  }
}

void writeDecimalByIntDec(long i, long d, int decimals, int lc_order, int lc_number)
{
  if (i > 9999) {
    return;
  }
  if (decimals < 1) {
    decimals = 1;
  }
  if (decimals > 4) {
    decimals = 4;
  }
  String IntegerPartStr =  String(i);
  String DecimalPartStr =  String(d);
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr = DecimalPartStr.substring(0, decimals);
  displayLedDecimal(IntegerPartStr, DecimalPartStr, lc_order, lc_number);
}

void writeDecimalNumber(double v, int decimals, int lc_order, int lc_number)
{
  if (v >= 10000) {
    return;
  }
  if (decimals < 1) {
    decimals = 1;
  }
  if (decimals > 4) {
    decimals = 4;
  }
  String stringV =  String(v, 4);
  int firstPoint = stringV.indexOf('.');
  String IntegerPartStr = stringV.substring(0, firstPoint);
  String DecimalPartStr = stringV.substring(firstPoint + 1);
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr += '0';
  DecimalPartStr = DecimalPartStr.substring(0, decimals);
  displayLedDecimal(IntegerPartStr, DecimalPartStr, lc_order, lc_number);
}

void printNumber(long v, bool useLeadingZero, int use_full, bool leftAlignInRight, bool pointInLeft, int lc_order, int lc_number)
{
  if (lc_number < 0) {
    lc_number = 0;
  }
  if (lc_number > 1) {
    lc_number = 1;
  }
  if (lc_order < 0) {
    lc_order = 0;
  }
  if (lc_order > 7) {
    lc_order = 7;
  }
  LedControl lc = lc0;
  if (lc_number == 1) {
    lc = lc1;
  }

  if (v == -210189) {
    lc.clearDisplay(lc_order);
    lc.setChar(lc_order, 7, '-', false);
    lc.setChar(lc_order, 6, '-', false);
    lc.setChar(lc_order, 5, '-', false);
    lc.setChar(lc_order, 4, '-', false);
    lc.setChar(lc_order, 3, '-', false);
    lc.setChar(lc_order, 2, '-', false);
    lc.setChar(lc_order, 1, '-', false);
    lc.setChar(lc_order, 0, '-', false);
    return;
  }
  if (use_full != 0 && v > 9999) {
    lc.clearDisplay(lc_order);
    return;
  }
  if (v > 99999999) {
    lc.clearDisplay(lc_order);
    return;
  }
  if (lc_order > 7) {
    lc.clearDisplay(lc_order);
    return;
  }

  bool isLeading = true;
  if (useLeadingZero) {
    isLeading = false;
  }

  int digito1;
  int digito2;
  int digito3;
  int digito4;
  int digito5;
  int digito6;
  int digito7;
  int digito8;

  digito1 = v % 10;
  digito2 = (v / 10) % 10;
  digito3 = (v / 100) % 10;
  digito4 = (v / 1000) % 10;
  digito5 = (v / 10000) % 10;
  digito6 = (v / 100000) % 10;
  digito7 = (v / 1000000) % 10;
  digito8 = (v / 10000000) % 10;

  int d7 = 7;
  int d6 = 6;
  int d5 = 5;
  int d4 = 4;
  int d3 = 3;
  int d2 = 2;
  int d1 = 1;
  int d0 = 0;

  if (use_full < 0) {
    d3 = 7;
    d2 = 6;
    d1 = 5;
    d0 = 4;
    if (!pointInLeft) {
      lc.setChar(lc_order, 3, ' ', false);
      lc.setChar(lc_order, 2, ' ', false);
      lc.setChar(lc_order, 1, ' ', false);
      lc.setChar(lc_order, 0, ' ', false);
    }
  }
  if (use_full > 0) {
    if (!pointInLeft) {
      lc.setChar(lc_order, 7, ' ', false);
      lc.setChar(lc_order, 6, ' ', false);
      lc.setChar(lc_order, 5, ' ', false);
      lc.setChar(lc_order, 4, ' ', false);
    }
    if (leftAlignInRight) {
      if (v < 10) {
        lc.setDigit(lc_order, 3, (byte)digito1, false);
        lc.setChar(lc_order, 2, ' ', false);
        lc.setChar(lc_order, 1, ' ', false);
        lc.setChar(lc_order, 0, ' ', false);
        return;
      }
      if (v < 100) {
        lc.setDigit(lc_order, 3, (byte)digito2, false);
        lc.setDigit(lc_order, 2, (byte)digito1, false);
        lc.setChar(lc_order, 1, ' ', false);
        lc.setChar(lc_order, 0, ' ', false);
        return;
      }
      if (v < 1000) {
        lc.setDigit(lc_order, 3, (byte)digito3, false);
        lc.setDigit(lc_order, 2, (byte)digito2, false);
        lc.setDigit(lc_order, 1, (byte)digito1, false);
        lc.setChar(lc_order, 0, ' ', false);
        return;
      }
    }
  }

  if (use_full == 0)
  {
    if (digito8 > 0 || !isLeading) {
      isLeading = false;
      lc.setDigit(lc_order, d7, (byte)digito8, false);
    } else {
      lc.setChar(lc_order, d7, ' ', false);
    }
    if (digito7 > 0 || !isLeading) {
      isLeading = false;
      lc.setDigit(lc_order, d6, (byte)digito7, false);
    } else {
      lc.setChar(lc_order, d6, ' ', false);
    }
    if (digito6 > 0 || !isLeading) {
      isLeading = false;
      lc.setDigit(lc_order, d5, (byte)digito6, false);
    } else {
      lc.setChar(lc_order, d5, ' ', false);
    }
    if (digito5 > 0 || !isLeading) {
      isLeading = false;
      lc.setDigit(lc_order, d4, (byte)digito5, false);
    } else {
      lc.setChar(lc_order, d4, ' ', false);
    }
  }
  if (digito4 > 0 || !isLeading) {
    isLeading = false;
    lc.setDigit(lc_order, d3, (byte)digito4, false);
  } else {
    if (!leftAlignInRight) {
      lc.setChar(lc_order, d3, ' ', false);
    }
  }
  if (digito3 > 0 || !isLeading) {
    isLeading = false;
    lc.setDigit(lc_order, d2, (byte)digito3, false);
  } else {
    if (!leftAlignInRight) {
      lc.setChar(lc_order, d2, ' ', false);
    }
  }
  if (digito2 > 0 || !isLeading) {
    isLeading = false;
    lc.setDigit(lc_order, d1, (byte)digito2, false);
  } else {
    if (!leftAlignInRight) {
      lc.setChar(lc_order, d1, ' ', false);
    }
  }
  if (pointInLeft && use_full < 0) {
    lc.setDigit(lc_order, d0, (byte)digito1, true);
  } else {
    lc.setDigit(lc_order, d0, (byte)digito1, false);
  }
  delay(00);
}

void writeArduinoOn7Segment()
{
  // Escreve Arduino e Cia no display
  for (int i = 0; i < 21; i++)
  {
    lc1.setChar(0, i, 'a', false);
    lc1.setRow(0, i - 1, 0x05);
    lc1.setChar(0, i - 2, 'd', false);
    lc1.setRow(0, i - 3, 0x1c);
    lc1.setRow(0, i - 4, B00010000);
    lc1.setRow(0, i - 5, 0x15);
    lc1.setRow(0, i - 6, 0x1D);
    lc1.setChar(0, i - 7, ' ', false);
    lc1.setChar(0, i - 8, 'e', false);
    lc1.setChar(0, i - 9, ' ', false);
    lc1.setRow(0, i - 10, B1001110);
    lc1.setRow(0, i - 11, B0010000);
    lc1.setChar(0, i - 12, 'a', false);
    lc1.setChar(0, i - 13, ' ', false);
    delay(300);
  }
}

void contagem_regressiva()
{
  for (int x = 8; x > -1; x--)
  {
    lc1.setDigit(0, x, x + 1, false);
    lc1.setChar(0, x + 1, ' ', false);
    delay(300);
  }
  lc1.clearDisplay(0);
}

void numeros_separados()
{
  for (int i = 0 ; i < 10 ; i++)
  {
    lc1.setDigit(0, 0, i, false);
    lc1.setDigit(0, 1, i, false);
    lc1.setDigit(0, 6, i, false);
    lc1.setDigit(0, 7, i, false);
    delay(300);
  }
  lc1.clearDisplay(0);
}

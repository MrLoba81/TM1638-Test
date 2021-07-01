/*
    A simple, non blocking animation, to test the TM1638 with a custom display
    No libraries are needed
    
    Paolo Loberto - @mrloba81
*/
const uint8_t strobe = 7;
const uint8_t clock = 9;
const uint8_t data = 8;

uint8_t digit = 0x01;
uint8_t segAddr = 0x00;

unsigned long lastTimeCheck = 0;
unsigned long currMillis;
  
enum stateEnum {
  DIGITS = 0,
  BARS = 1,
  FULL = 2
};
stateEnum state = DIGITS;

void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, value);
  digitalWrite(strobe, HIGH);
}

void setSegment(uint8_t segAddr, uint8_t digit)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xC0 | segAddr); // segment
  shiftOut(data, clock, LSBFIRST, digit); //digit
  digitalWrite(strobe, HIGH);
}

void reset()
{
  sendCommand(0x40); // set auto increment mode
  
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(data, clock, LSBFIRST, 0x00);
  }
  digitalWrite(strobe, HIGH);
}

void setup() 
{
  Serial.begin(9600);
  
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  
  // Display control command 0x80 
  sendCommand(0x80 | 8 | 0); // 8 -> display on | 0 -> duty cycle 1/16 (set the brightness to the minimum value)
  reset();
}

void testDigitsSegments() 
{ 
  setSegment(segAddr, digit);
  segAddr += 2;

  if (segAddr > 0x0E) {
    digit = digit << 1;
    segAddr = 0x00;
  }
  
  if (digit == 0) {
    Serial.println("Resetting digits");
    reset();
    digit = 0x01;
    segAddr = 0x01;
    state = BARS;
  }
}

void testBarSegments() 
{ 
  setSegment(segAddr, digit);
  segAddr += 2;

  if (segAddr > 0x0F) {
    digit = digit << 1;
    segAddr = 0x01;
  }
  
  if (digit > 2) {
    Serial.println("Resetting segments");
    reset();
    digit = 0x01;
    segAddr = 0x00;
    state = FULL;
  }
}

void testFull() 
{
  static uint8_t localState = 0;
  static unsigned long localTimeCheck = 0;

  if (localState == 0) 
  {
    setSegment(0xC0 | 0x00, 255);
    setSegment(0xC0 | 0x02, 255);
    setSegment(0xC0 | 0x04, 255);
    setSegment(0xC0 | 0x06, 255);
    setSegment(0xC0 | 0x08, 255);
    setSegment(0xC0 | 0x0A, 255);
    setSegment(0xC0 | 0x0C, 255);
    setSegment(0xC0 | 0x0E, 255);
    localState = 1;
    localTimeCheck = millis();
  } 
  else if (localState == 1 && (currMillis - localTimeCheck) >= 1000)
  {
    setSegment(0xC0 | 0x01, 3);
    setSegment(0xC0 | 0x03, 3);
    setSegment(0xC0 | 0x05, 3);
    setSegment(0xC0 | 0x07, 3);
    setSegment(0xC0 | 0x09, 3);
    setSegment(0xC0 | 0x0B, 3);
    setSegment(0xC0 | 0x0D, 3);
    setSegment(0xC0 | 0x0F, 3);
    localState = 3;
    localTimeCheck = millis();
  }
  else if (localState == 3 && (currMillis - localTimeCheck) >= 1500)
  {
    Serial.println("Resetting full");
    reset();
    localState = 0;
    state = DIGITS;
    digit = 0x01;
    segAddr = 0x00;
    localTimeCheck = millis();
  }
}

void loop() 
{
  sendCommand(0x44);  // set single address

  currMillis = millis();

  if (currMillis - lastTimeCheck >= 125 || lastTimeCheck == 0) 
  {
    if (state == DIGITS)
      testDigitsSegments();
    else if (state == BARS)
      testBarSegments();
    else if (state == FULL)
      testFull();
    
    lastTimeCheck = currMillis;
  }
}

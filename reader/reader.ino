#include <stdint.h>

#define MAX_ADDR 2000000L
#define START 0

void setup() {

  DDRB = B00000000; //Port B all inputs - Data bits 7/0
  DDRC = B11111111; //Port C all outputs - Address bits 6/-1
  DDRA = B11111111; //Port A all outputs - Address bits 14/7
  DDRL = B00011111; //Port L 5 outputs - Address bits 19/15

  Serial.begin(500000);
}

void writeAddr(uint32_t addr) {
  uint32_t mask = B11111111;
  PORTC = addr & mask;
  mask = mask << 8;
  PORTA = (addr & mask) >> 8;
  mask = B11111;
  mask = mask << 16;
  PORTL = (addr & mask) >> 16;
}

void loop() {
  uint32_t addr = START;
  Serial.print("start");
  delay(3000);

  while (addr < MAX_ADDR) {
    writeAddr(addr);

    addr = addr + 1;
    byte b = PINB;
    //Write data
    Serial.write(b);
  }
  Serial.print("done");
  while (1) {}
}

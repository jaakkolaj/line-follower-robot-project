/*
 */
#define oikeaEtu 7
#define vasenEtu 12
#define vasenTaka 11
#define oikeaTaka 8
#define enableVasen 9
#define enableOikea 6

#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

void setup() {
  pinMode(oikeaEtu, OUTPUT);
  pinMode(oikeaTaka, OUTPUT);
  pinMode(vasenEtu, OUTPUT);
  pinMode(vasenTaka, OUTPUT);
  pinMode(enableVasen, OUTPUT);
  pinMode(enableOikea, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  Serial.begin(9600);
}
//vauhti asteikolla 0-255
void loop() {
  int sensori1 = digitalRead(ir1);
  int sensori2 = digitalRead(ir2);
  int sensori3 = digitalRead(ir3);
  int sensori4 = digitalRead(ir4);
  int sensori5 = digitalRead(ir5);

  Serial.print(!sensori1);
  Serial.print(!sensori2);
  Serial.print(!sensori3);
  Serial.print(!sensori4);
  Serial.print(!sensori5);
}

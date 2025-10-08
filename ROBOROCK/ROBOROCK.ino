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
}

  //if only middle sensor detects black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 0) && (ir4 == 1) && (ir5 == 1))
  {
    //going forward with full speed 
    analogWrite(enableVasen, 120); //you can adjust the speed of the motors from 0-255
    analogWrite(enableOikea, 120); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, HIGH);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }
  
  //if only left sensor detects black line
  if((ir1 == 1) && (ir2 == 0) && (ir3 == 1) && (ir4 == 1) && (ir5 == 1))
  {
    //going left
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
    

  }
  
  //if only left most sensor detects black line
  if((ir1 == 0) && (ir2 == 1) && (ir3 == 1) && (ir4 == 1) && (ir5 == 1))
  {
    //going left with full speed 
    analogWrite(enableOikea, 180); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 180); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, HIGH);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
    

  }

  //if only right sensor detects black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 1) && (ir4 == 0) && (ir5 == 1))
  {
    //going right
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }

  //if only right most sensor detects black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 1) && (ir4 == 1) && (ir5 == 0))
  {
    //going right with full speed 
    analogWrite(enableOikea, 180); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 180); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, HIGH);
  }

  //if middle and right sensor detects black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 0) && (ir4 == 0) && (ir5 == 1))
  {
    //going right
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }

  //if middle and left sensor detects black line
  if((ir1 == 1) && (ir2 == 0) && (ir3 == 0) && (ir4 == 1) && (ir5 == 1))
  {
    //going left
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
  }

  //if middle, left and left most sensor detects black line
  if((ir1 == 0) && (ir2 == 0) && (ir3 == 0) && (ir4 == 1) && (ir5 == 1))
  {
    //going left
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
  }

  //if middle, right and right most sensor detects black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 0) && (ir4 == 0) && (ir5 == 0))
  {
    //going right
    analogWrite(enableOikea, 150); //you can adjust the speed of the motors from 0-255
    analogWrite(enableVasen, 150); //you can adjust the speed of the motors from 0-255
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }

  //if all sensors are on a black line
  if((ir1 == 1) && (ir2 == 1) && (ir3 == 0) && (ir4 == 1) && (ir5 == 1))
  {
    //stop
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }
}

/*
 */
#include <Servo.h>
#include <NewPing.h>

#define vasenEteen 7
#define oikeaEteen 12
#define oikeaTaakse 11
#define vasenTaakse 8
#define enableOikea 3
#define enableVasen 6

#define LPT 2

#define servoPin 9

#define echoPin 2
#define trigPin 10

#define piip 13

#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

int maxEtaisyys = 25;
int etaisyys = 100;

bool vaistoliike = false;

NewPing sonar(trigPin,  echoPin, maxEtaisyys);
Servo servo;

void setup() {
  pinMode(vasenEteen, OUTPUT);
  pinMode(oikeaTaakse, OUTPUT);
  pinMode(oikeaEteen, OUTPUT);
  pinMode(oikeaTaakse, OUTPUT);
  pinMode(enableVasen, OUTPUT);
  pinMode(enableOikea, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piip, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);


   digitalWrite(piip, HIGH);

  servo.attach(9);

  servo.write(90);
  delay(2000);
  etaisyys = skannaa();

  Serial.begin(9600);
}

void piippaus(){
  digitalWrite(piip, LOW);
  delay(500);
  digitalWrite(piip, HIGH);
}
int  skannaa(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=200;
  }
  return cm;
}
float Kp = 10.0;   
float Kd = 0.0;   
float previousError = 0;
int baseSpeed = 120;

// === Recovery memory ===
unsigned long lastLineTime = 0;
int lastDirection = 0; // -1 = left, 1 = right

void viivanSeurantaPD() {
  int s1 = !digitalRead(ir1);
  int s2 = !digitalRead(ir2);
  int s3 = !digitalRead(ir3);
  int s4 = !digitalRead(ir4);
  int s5 = !digitalRead(ir5);

  Serial.print(s1);
  Serial.print(s2);
  Serial.print(s3);
  Serial.print(s4);
  Serial.println(s5);

  int position = (-2 * s1) + (-1 * s2) + (0 * s3) + (1 * s4) + (2 * s5);
  int activeSensors = s1 + s2 + s3 + s4 + s5;
  float error = 0;
  if (activeSensors != 0) error = (float)position / activeSensors;

  float derivative = error - previousError;
  float correction = (Kp * error) + (Kd * derivative);
  previousError = error;

  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // --- Movement ---
  if (activeSensors > 0 && activeSensors < 5) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    eteenpain();
    if (error < 0) lastDirection = -1;
    else if (error > 0) lastDirection = 1;
    lastLineTime = millis();
  }
  else if (activeSensors == 5) {
    seis();
  }
  else if (activeSensors == 0) {
    unsigned long timeLost = millis() - lastLineTime;
    if (timeLost < 800) {
      if (lastDirection == -1) {
        analogWrite(enableVasen, 60);
        analogWrite(enableOikea, 160);
        vasen();
      } else {
        analogWrite(enableVasen, 160);
        analogWrite(enableOikea, 60);
        oikea();
      }
    } else {
      analogWrite(enableVasen, 100);
      analogWrite(enableOikea, 100);
      oikea(); // spin search
    }
  }
}


void asetaNopeus(int vasen, int oikee){
  analogWrite(enableVasen, vasen);
  analogWrite(enableOikea, oikee);
}
void eteenpain(){
  digitalWrite(vasenEteen, HIGH);
  digitalWrite(oikeaEteen, HIGH);
  digitalWrite(vasenTaakse, LOW);
  digitalWrite(oikeaTaakse, LOW);
}
void oikea(){
  digitalWrite(vasenEteen, HIGH);
  digitalWrite(oikeaEteen, LOW);
  digitalWrite(vasenTaakse, LOW);
  digitalWrite(oikeaTaakse, HIGH);
}
void vasen(){
  digitalWrite(vasenEteen, LOW);
  digitalWrite(oikeaEteen, HIGH);
  digitalWrite(vasenTaakse, HIGH);
  digitalWrite(oikeaTaakse, LOW);
}
void taaksepain(){
  digitalWrite(vasenEteen, LOW);
  digitalWrite(oikeaEteen, LOW);
  digitalWrite(vasenTaakse, HIGH);
  digitalWrite(oikeaTaakse, HIGH);
}
void seis(){
  digitalWrite(vasenEteen, LOW);
  digitalWrite(oikeaEteen, LOW);
  digitalWrite(vasenTaakse, LOW);
  digitalWrite(oikeaTaakse, LOW);
}
void vaista(){
  seis();
  asetaNopeus(150,150);
  piippaus();
  delay(500);
  oikea();
  delay(500);
  asetaNopeus(75,75);
  eteenpain();
  delay(1500);
  asetaNopeus(150,150);
  vasen();
  delay(500);
  asetaNopeus(75,75);
  eteenpain();
  delay(1000);
  asetaNopeus(150,150);
  vasen();
  delay(400);
  asetaNopeus(75,75);
  eteenpain();

}
//vauhti asteikolla 0-255
void loop() {
  etaisyys = skannaa();
  if(etaisyys<maxEtaisyys){
    vaistoliike = true;
    vaista();
    delay(500);
 }
  if(vaistoliike){
    int s1 = !digitalRead(ir1);
    int s2 = !digitalRead(ir2);
    int s3 = !digitalRead(ir3);
    int s4 = !digitalRead(ir4);
    int s5 = !digitalRead(ir5);

    Serial.print(s1);
    Serial.print(s2);
    Serial.print(s3);
    Serial.print(s4);
    Serial.println(s5);
    if((s1 == 1) || (s2 == 1) || (s3 == 1) || (s4 == 1) || (s5 == 1)){
      vaistoliike  = false;
    }
  }
  if(!vaistoliike){
  viivanSeurantaPD();
  }
  

}

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

int maxEtaisyys = 20;
int etaisyys = 100;

bool vaistoliike = false;

NewPing sonar(trigPin,  echoPin, maxEtaisyys);
Servo servo;

void setup() {
  pinMode(vasenEteen, OUTPUT);
  pinMode(oikeaTaua, OUTPUT);
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

  servo.write(115);
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

void viivanSeuranta(){
  int sensori1 = digitalRead(ir1);
  int sensori2 = digitalRead(ir2);
  int sensori3 = digitalRead(ir3);
  int sensori4 = digitalRead(ir4);
  int sensori5 = digitalRead(ir5);

  Serial.print(!sensori1);
  Serial.print(!sensori2);
  Serial.print(!sensori3);
  Serial.print(!sensori4);
  Serial.println(!sensori5);




  //Keskimmäinen lukee mustaa jotenka mennään eteenpäin
  if((sensori1 == 1) && (sensori2 == 1) && (sensori3 == 0) && (sensori4 == 1) && (sensori5 == 1))
  {
    analogWrite(enableVasen, 200); 
    analogWrite(enableOikea, 200); 
    digitalWrite(vasenEteen, HIGH);
    digitalWrite(oikeaEteen, HIGH);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
  }
  
  //Keskivasen lukee mustaa jotenka käännytään vasemalle
  if((sensori1 == 1) && (sensori2 == 0) && (sensori3 == 1) && (sensori4 == 1) && (sensori5 == 1))
  {
    analogWrite(enableOikea, 180); 
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, HIGH);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
    

  }
  
  //Vasen lukee mustaa jotenka käännytään vasemalle
  if((sensori1 == 0) && (sensori2 == 1) && (sensori3 == 1) && (sensori4 == 1) && (sensori5 == 1))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, HIGH);
    digitalWrite(vasenTaakse, HIGH);
    digitalWrite(oikeaTaakse, LOW);
    

  }

  //keskioikea lukee mustaa jotenka käännytään oikealle
  if((sensori1 == 1) && (sensori2 == 1) && (sensori3 == 1) && (sensori4 == 0) && (sensori5 == 1))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, LOW);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, HIGH);
  }

  //Oikea lukee mustaa jotenka käännytään oikealle
  if((sensori1 == 1) && (sensori2 == 1) && (sensori3 == 1) && (sensori4 == 1) && (sensori5 == 0))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, HIGH);
    digitalWrite(oikeaEteen, LOW);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, HIGH);
  }

  //Keskimmäinen ja keskioikee lukee mustaa jotenka käännytään oikealle
  if((sensori1 == 1) && (sensori2 == 1) && (sensori3 == 0) && (sensori4 == 0) && (sensori5 == 1))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, HIGH);
    digitalWrite(oikeaEteen, LOW);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
  }

  //Keskimmäinen ja keskivasen lukee mustaa jotenka käännytään vasemmalle
  if((sensori1 == 1) && (sensori2 == 0) && (sensori3 == 0) && (sensori4 == 1) && (sensori5 == 1))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, HIGH);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
  }

  //Keskimmäinen ja siitä vasemmalle lukee mustaa jotenka käänytään vasemmalle
  if((sensori1 == 0) && (sensori2 == 0) && (sensori3 == 0) && (sensori4 == 1) && (sensori5 == 1))
  {
   
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180);
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, HIGH);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
  }

  //Keskimmäisestä oikealle kaikki lukee mustaa jotenka käännytään oikealle
  if((sensori1 == 1) && (sensori2 == 1) && (sensori3 == 0) && (sensori4 == 0) && (sensori5 == 0))
  {
    analogWrite(enableOikea, 180);
    analogWrite(enableVasen, 180); 
    digitalWrite(vasenEteen, HIGH);
    digitalWrite(oikeaEteen, LOW);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
  }

  //Kaikki sensorit lukee mustaa eli pysähtyy
  if((sensori1 == 0) && (sensori2 == 0) && (sensori3 == 0) && (sensori4 == 0) && (sensori5 == 0))
  {
    digitalWrite(vasenEteen, LOW);
    digitalWrite(oikeaEteen, LOW);
    digitalWrite(vasenTaakse, LOW);
    digitalWrite(oikeaTaakse, LOW);
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
  piippaus();
  delay(500);
  oikea();
  delay(2000);
  eteenpain();
  delay(700);
  vasen();
  delay(2000);
  eteenpain();
  vaistoliike = false;
}
//vauhti asteikolla 0-255
void loop() {

  if(etaisyys<20){
    asetaNopeus(100,100);
    vaistoliike = true;
    vaista();
    delay(500);
  }
  
  etaisyys = skannaa();

}

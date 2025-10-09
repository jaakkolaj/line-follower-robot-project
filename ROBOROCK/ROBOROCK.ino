#define vasenEtu 7
#define oikeaEtu 12
#define vasenTaka 11
#define oikeaTaka 8
#define enableVasen 6
#define enableOikea 9

#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

// --- PD Controller constants ---
float Kp = 25.0;  // Proportional gain
float Kd = 10.0;  // Derivative gain
float previousError = 0;
int baseSpeed = 120;  // Base motor speed (0–255)

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

void loop() {
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

  // --- Compute position error ---
  // Sensor weighting: leftmost = -2, rightmost = +2
  int position = (-2 * s1) + (-1 * s2) + (0 * s3) + (1 * s4) + (2 * s5);
  int activeSensors = s1 + s2 + s3 + s4 + s5;
  float error = 0;
  if (activeSensors != 0) error = (float)position / activeSensors;

  // --- PD Control ---
  float derivative = error - previousError;
  float correction = (Kp * error) + (Kd * derivative);
  previousError = error;

  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Clamp speeds to [0, 255]
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // --- Your existing logic (still active) ---
  // Keskimmäinen lukee mustaa jotenka mennään eteenpäin
  if ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0)) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    digitalWrite(oikeaEtu, HIGH);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }

  // Keskivasen lukee mustaa jotenka käännytään vasemmalle
  if ((s1 == 0) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    digitalWrite(oikeaEtu, HIGH);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, HIGH);
  }

  // Keskioikea lukee mustaa jotenka käännytään oikealle
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 0)) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
  }

  // Vasen lukee mustaa (suurempi korjaus vasemmalle)
  if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    digitalWrite(oikeaEtu, HIGH);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, HIGH);
    digitalWrite(vasenTaka, LOW);
  }

  // Oikea lukee mustaa (suurempi korjaus oikealle)
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1)) {
    analogWrite(enableVasen, leftSpeed);
    analogWrite(enableOikea, rightSpeed);
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, HIGH);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, HIGH);
  }

  // Kaikki sensorit mustalla (pysähdys)
  if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
    analogWrite(enableVasen, 0);
    analogWrite(enableOikea, 0);
    digitalWrite(oikeaEtu, LOW);
    digitalWrite(vasenEtu, LOW);
    digitalWrite(oikeaTaka, LOW);
    digitalWrite(vasenTaka, LOW);
  }
}

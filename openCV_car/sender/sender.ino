int motor1Pin1 = 4;
int motor1Pin2 = 5;
int enable1Pin = 3;
int motor2Pin1 = 12;
int motor2Pin2 = 13;
int enable2Pin = 11;

int buzzer = 6;
int led = 7;
bool flagBuz = false;
int state;
struct Data_Pack {
  //LED Values
  byte flag;
};
Data_Pack data;  // Creating Variables with above structure

void setup() {

  Serial.begin(9600);
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    data.flag = Serial.parseInt();
    state = data.flag;

    // if the state is 'F' the DC motor will  go forward
    if (state == 1) {

      digitalWrite(led, HIGH);

      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      flagBuz = false;
    }

    // if the  state is 'R' the motor will turn left
    else if (state == 12) {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

      flagBuz = true;
    }
    // if the state is 'S' the motor will Stop
    else if (state == 0) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);

      flagBuz = false;
    }
    // if the  state is 'L' the motor will turn right
    else if (state == 11) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);

      flagBuz = true;

    }
    // if the state is 'B' the motor will backward
    else if (state == 13) {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);

      flagBuz = true;
    }
    if (flagBuz == true) {
      for (int i = 0; i < 3; i++) {
        tone(buzzer, 1000);
        delay(500);
        noTone(buzzer);
        delay(500);
      }
    }
    delay(1000);
  }
}
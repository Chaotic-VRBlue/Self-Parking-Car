int e1 = 3, i1 = 2, i2 = 4, s;
int e2 = 6, i3 = 8, i4 = 7;
int ir1 = 5, ir2 = 12;
int trig = 10;
int echo = A0;
long duration;
int distance;

int parkk = 10;
int park1 = 9;


void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(e1, OUTPUT);  //m1
  pinMode(i1, OUTPUT);  //motor1
  pinMode(i2, OUTPUT);  //m1

  pinMode(e2, OUTPUT);  //m2
  pinMode(i3, OUTPUT);  //m2
  pinMode(i4, OUTPUT);  //motor2

  pinMode(ir1, INPUT);  //ir1
  pinMode(ir2, INPUT);  //ir2

  pinMode(parkk, OUTPUT);  //mcu
  pinMode(park1, INPUT);   //mcu1

  pinMode(13, OUTPUT);  //led
  Serial.begin(9600);
}


void loop() {
  int s, space1 = 0;
  s = sense();
  Serial.println(s);

  analogWrite(e1, 100);
  analogWrite(e2, 100);

  int p1 = digitalRead(9);
  if (p1 == 1) {
    moveon(100);
    s = sense();
    if (s == 0) {
      space1 = 0;
    } else {
      delay(2000);
      moveon(80);
      park();
    }
  } else {
    stopp();
  }
}


int park() {
  int i, s = 1;

  for (i = 0; s == 0; i++) {
    moveon(100);
    delay(100);
    s = sense();
  }

  back(200);
  rotate(900);
  backs();
  digitalWrite(parkk, HIGH);
  delay(500);
  Serial.println("car parked");
}

int unpark() {
  moveon(800);
  delay(1000);

  rotatel(900);
  moveon(500);
  stopp();
}

int moveon(int t) {
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
  Serial.println("front");
  delay(t);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
  Serial.println("stop");
}

int back(int t) {
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  Serial.println("back");
  delay(t);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
  Serial.println("stop");
}

int backs() {
  back(100);
  delay(100);
  int s = sense1();
  if (s == 0) {
    stopp();
  }
  backs();
}

int rotate(int t) {
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  Serial.println("rotate");
  delay(t);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
  Serial.println("stop");
}

int rotatel(int t) {
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
  Serial.println("rotate");
  delay(t);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
  Serial.println("stop");
}

int stopp() {
  analogWrite(e1, 0);
  analogWrite(e2, 0);
}

int sonar() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance < 30) {
    return (1);
  } else {
    return (0);
  }
}

int sense() {
  int d = digitalRead(5);
  if (d == 1) {
    return (1);
  } else {
    return (0);
  }
}

int sense1() {
  int d = digitalRead(12);
  if (d == 1) {
    return (1);
  } else {
    return (0);
  }
}

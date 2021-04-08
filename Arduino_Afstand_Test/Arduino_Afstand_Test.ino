// konstant til ultralydssensoren
const int echoPin = 2;
const int trigPin = 3;

int counter = 0;

long beginTime, endTime;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize serial communication:
  Serial.begin(57600);
  beginTime = micros();
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration;
  float cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // A different pin is used to read the signal from the PING. A HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  if (counter < 100) {
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  }
  
  counter++;
  if (counter == 100) {
    endTime = micros();
    long durationInMicros = endTime - beginTime;
    Serial.print(durationInMicros);
    Serial.print("mikro sekunder");
    Serial.println();
  }
  
  delay(5);
}

float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (float) microseconds / 29 / 2;
}

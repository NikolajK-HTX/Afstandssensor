// konstant til ultralydssensorens ben
const int echoPin = 2;
const int trigPin = 3;

// holder øje med antal totale målinger
int counter = 0;

// programmet starter først når man skriver start fra Python
bool started = false;

// indstillinger til antallet af målinger
// det kan være de skal indtastes fra Python programmet
int measurementsPerSecond = 10;
int measuringTimeInSeconds = 10;

int timeBetweenMeasurement = 1000 / measurementsPerSecond;
int totalAmountOfMeasurements = measurementsPerSecond * measuringTimeInSeconds;

// variabler til timer så målingerne bliver taget på
// det rigtige tidspunkt
unsigned long t_lastMeasurement;
unsigned long timeInMillisSinceStart;
unsigned long t_start;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize serial communication:
  Serial.begin(57600);
}

void loop() {
  if (Serial.available()) {
    String incomingString = Serial.readStringUntil('\n');
    if (incomingString == "Start") {
      started = true;
      t_start = millis();
    }
  }

  if (counter >= totalAmountOfMeasurements) {
    Serial.print("Done\n");
    started = false;
    counter = 0;
  }
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
  timeInMillisSinceStart = millis() - t_start;
  cm = microsecondsToCentimeters(duration);
  // only print the result if enough time has passed since last measurement
  if (started && t_lastMeasurement + timeBetweenMeasurement < millis()) {
    t_lastMeasurement = millis();
    Serial.print(timeInMillisSinceStart);
    Serial.print(';');
    Serial.print(cm);
    Serial.print('\n');
    counter++;
  }

  delay(5);
}

float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (float) microseconds / 29 / 2;
}

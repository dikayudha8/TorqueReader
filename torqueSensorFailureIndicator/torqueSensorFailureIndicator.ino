#define INPUT_PIN 2
#define INPUT_PIN_2 3
#define OUTPUT_LED 13

unsigned long timeBefore, deltaTime;
unsigned long timeBefore2, deltaTime2;
long ledOutputTimer, deltaLedOutputTimer;
bool turnOnLedFlag;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(OUTPUT_LED, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  pinMode(INPUT_PIN_2, INPUT);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ReadingInterrupt, CHANGE);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN_2), ReadingInterrupt_2, CHANGE);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ReadingInterrupt_High, RISING);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN_2), ReadingInterrupt_2_High, RISING);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ReadingInterrupt_Low, FALLING);
  //  attachInterrupt(digitalPinToInterrupt(INPUT_PIN_2), ReadingInterrupt_2_Low, FALLING);
}

bool NonBlockingDelay(long desiredTimeOut) {
  static bool firstTimer = 0;
  static long timeBefore, deltaTime;
  if (firstTimer == 0) {
    timeBefore = millis();
    firstTimer = 1;
  } else {
    deltaTime = millis() - timeBefore;
    if (deltaTime >= desiredTimeOut) {
      firstTimer = 0;
      return true;
    } else {
      return false;
    }
  }
}

void loop() {
  unsigned long duration = pulseIn(INPUT_PIN, HIGH);
  unsigned long duration2 = pulseIn(INPUT_PIN_2, HIGH);
  Serial.print(duration);
  Serial.print(" ");
  Serial.println(duration2);
  //  if (NonBlockingDelay(50)) {
  //    Serial.print(deltaTime);
  //    Serial.print(",");
  //    Serial.println(deltaTime2);
  //
  //  }


  //  // put your main code here, to run repeatedly:
  //  if ((deltaTime >= 400 && deltaTime % 400 == 0) || (deltaTime2 >= 400 &&deltaTime2 % 400 == 0)) {
  //    turnOnLedFlag = true;
  //  } else {
  //    //turnOnLedFlag = false;
  //  }
  //
  //  if (turnOnLedFlag == true) {
  //    if (NonBlockingDelay(200) == false) {
  //      Serial.print(deltaTime);
  //      Serial.print(",");
  //      Serial.println(deltaTime2);
  //
  //      digitalWrite(OUTPUT_LED, HIGH);
  //    } else {
  //      digitalWrite(OUTPUT_LED, LOW);
  //      turnOnLedFlag = false;
  //    }
  //  }
}

void ReadingInterrupt() {
  if (digitalRead(INPUT_PIN) == HIGH) {
    timeBefore = millis();
    deltaTime = 0;
  } else {
    deltaTime = millis() - timeBefore;
  }
}

void ReadingInterrupt_2() {
  if (digitalRead(INPUT_PIN_2) == HIGH) {
    timeBefore2 = millis();
    deltaTime2 = 0;
  } else {
    deltaTime2 = millis() - timeBefore2;
  }
}

void ReadingInterrupt_High() {
  timeBefore = millis();
  deltaTime = 0;
}

void ReadingInterrupt_Low() {
  deltaTime = millis() - timeBefore;
}

void ReadingInterrupt_2_High() {
  timeBefore2 = millis();
  deltaTime2 = 0;
}

void ReadingInterrupt_2_Low() {
  deltaTime2 = millis() - timeBefore2;
}


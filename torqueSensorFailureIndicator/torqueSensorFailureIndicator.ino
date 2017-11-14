#define INPUT_PIN 2
#define OUTPUT_LED 4

long timeBefore, deltaTime;
long ledOutputTimer, deltaLedOutputTimer;
bool turnOnLedFlag;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(OUTPUT_LED, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ReadingInterrupt, CHANGE);
}

bool NonBlockingDelay(long desiredTimeOut){
  static bool firstTimer = 0;
  static long timeBefore, deltaTime;
  if(firstTimer == 0){
    timeBefore = millis();
    firstTimer = 1;
  } else {
    deltaTime = millis() - timeBefore;
    if(deltaTime >= desiredTimeOut){
      firstTimer = 0;
      return true;
    } else {
      return false;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(deltaTime >= 400){
    turnOnLedFlag = true;
  }

  if(turnOnLedFlag == true){
    if(NonBlockingDelay(200) == false){
      digitalWrite(OUTPUT_LED, HIGH);
    } else {
      digitalWrite(OUTPUT_LED, LOW);
      turnOnLedFlag = false;
    }
  }
}

void ReadingInterrupt(){
  if(digitalRead(INPUT_PIN) == HIGH){
      timeBefore = millis();
  } else {
    deltaTime = millis() - timeBefore;
  }
}


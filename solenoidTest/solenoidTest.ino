float freq = 10;
float delayTime = 1/freq / 2 * 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
//  pinMode(13, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0, HIGH);
//  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(0, LOW);
//  digitalWrite(13, LOW);
  delay(delayTime);
}

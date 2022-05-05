//D2: Input, pushButton
//D3: Output, Led
#define OFF LOW
#define ON  HIGH
int BtnVal = 0;
int BtnStt = OFF;

int Btn = 2;
//int LED = 3;

//void readSereal();
void switchLed();

void setup() {
  // put your setup code here, to run once:
  pinMode(Btn, INPUT);
  //pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //readSereal();
  BtnVal = digitalRead(Btn);
  if(BtnVal != 0)
    BtnStt = (BtnStt == ON)? OFF : ON; 
  switchLed();
  delay(200);
}

void readSereal(){
  BtnVal = digitalRead(Btn);
  if(Serial.available() >0){
    char sCmd = Serial.read();
    //Serial.println(sCmd);
    if(sCmd == '1')
      BtnStt = ON;
    else if(sCmd == '0')
      BtnStt = OFF;
  }
}

void switchLed(){
  //digitalWrite(LED, BtnStt); 
  if(BtnStt == OFF)
    Serial.println('0');
  else if(BtnStt == ON)
    Serial.println('1');
}

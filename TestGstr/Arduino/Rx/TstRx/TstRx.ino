//D2: Input, pushButton
//D3: Output, Led
#define OFF LOW
#define ON  HIGH
int sStt = OFF;
int LED = 2;

void readSereal();

void setup() {
  // put your setup code here, to run once:
  //pinMode(Btn, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //readSereal();
  //char BtnVal = digita;
  if(sStt != 0)
    sStt = (sStt == ON)? OFF : ON; 
  readSereal();
  //switchLed();
  delay(200);
}

void readSereal(){
  //BtnVal = digitalRead(Btn);
  if(Serial.available() >0){
    char sCmd = Serial.read();
    if(sCmd == '1')
      sStt = ON;
    else if(sCmd == '0')
      sStt = OFF;
  }
  digitalWrite(LED,sStt);
}

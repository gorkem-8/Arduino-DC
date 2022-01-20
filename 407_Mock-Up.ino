
int vel;
int enablePin = 7;
int inputPin1 = 10;
int inputPin2 = 11;
int target = 425;
int error= 425 ;
int Kp=5;
int dir = 1;
int PWM = 0;
String inputmode;
int mode = 1;
int serialNumber=0;

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB =0 ;
int lastLSB =0 ;

void setup() {
  Serial.begin(115200);
  //L293D
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  //ENCODER
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

 
}

void loop() {

  if(encoderValue>3035){encoderValue=encoderValue-3035;}
  if(encoderValue<-3035){encoderValue=encoderValue+3035;}
  
  Serial.println(encoderValue);
  delay(2);

  if(Serial.available()){
    analogWrite(enablePin,0);
    
    String inputmode=Serial.readString(); 
    if (inputmode =="!60"){
      mode = 60;}
    if (inputmode =="!30"){
      mode = 30;}
    if (inputmode =="!0"){
      mode = 0;}
     serialNumber=1;
      
  Serial.println(mode);
  }
  if (serialNumber==1){
    if (encoderValue>0){
    digitalWrite(inputPin2,LOW);
    digitalWrite(inputPin1,HIGH);   
    }
    else {
    digitalWrite(inputPin2,HIGH);
    digitalWrite(inputPin1,LOW);
    }
  }
  while (serialNumber==1){
    Serial.println(encoderValue);
    Serial.println("sex");
    analogWrite(enablePin,50);
    target = 0;
    error = target-encoderValue;  
    if (error<=2 && error>=-2){
    serialNumber = 0;
    encoderValue=0;}
  }
   
  if (mode==60){PWM=255;}
  if (mode ==30) {PWM=123;}
  
  //proportinal controller
  vel = abs(error * Kp) ;
  analogWrite(enablePin, min(vel,PWM));
              
  if(dir==2){
    digitalWrite(inputPin2,LOW);
    digitalWrite(inputPin1,HIGH);
    }
  if(dir==1){
    digitalWrite(inputPin2,HIGH);
    digitalWrite(inputPin1,LOW);
    }
  //integral controller
  //derivative controller  
  }

void updateEncoder(){
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);

  int encoded = (MSB <<1)| LSB ;
  int sum = (lastEncoded << 2)| encoded ;

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
  
  error = target - encoderValue;
  if(dir==1 & error<=0){
    if(mode==60){
    target = -506;
      
    }
    else if(mode==30){
    target = -253;
      
    }
    dir = 2;
    }
  if(dir==2 & error>=0){
    if(mode==60){
    target = 506;
     
    }
    else if(mode==30){
    target = 253;
     
    }
    dir=1;
    }
   if (mode==0){
    if (encoderValue>=0){dir=2;}
    else {dir=1;}
    target = 0;
    if (error ==0){
      PWM=0;
    }
   }
  }

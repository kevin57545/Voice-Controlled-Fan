//新的

const int digitalPin = A3;
const int threshold = 400;

const byte IN1 = 4; //開啟
const byte IN2 = 6; //加速
const byte IN3 = 7; //定時
const byte IN4 = 5; //擺頭
const byte IN5 = 8; //模式

int speed = 177;
int isHello = 0; //1=hello  
int digitalValue;

unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(digitalPin, INPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, HIGH);
}

//開啟
void open(){
  //if( analogRead(digitalPin) < 100 && analogRead(digitalPin) < 10 ){
    pinMode(digitalPin, INPUT_PULLUP);
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  //}
}

//加速
void accelerate(){
  //if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100 ){
    digitalWrite(IN2, LOW);
    delay(100);
    digitalWrite(IN2, HIGH);
  //}
}

//定時
void settime(){
  //if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN3, LOW);
    delay(100);
    digitalWrite(IN3, HIGH);
  //}
}

//擺頭
void turn(){
  //if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN4, LOW);
    delay(100);
    digitalWrite(IN4, HIGH);
 // }
}

void mode(){
  //if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN5, LOW);
    delay(100);
    digitalWrite(IN5, HIGH);
  //}
}

//關閉
void close(){
  int value = analogRead(digitalPin);
  //if(value > 10 && value < 100){
    pinMode(digitalPin, INPUT);
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  //}
}

void loop() {
  
  int countdown = 30;
  startTime = millis(); // 設定起始時間為目前的時間
  while(countdown > 0){ // 當倒數計時器仍然大於0時
      unsigned long currentTime = millis(); // 讀取目前時間
      if (currentTime - startTime >= 1000) { // 每經過1秒
        Serial.println(countdown); // 輸出倒數計時器的數值到序列埠
        countdown--; // 將倒數計時器減1
        startTime = currentTime; // 更新起始時間
      }
      int number = Serial.parseInt();
      switch(number){
        case 4: //開啟
          open();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;

        case 9: //關閉
          close();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;

        case 6: //加速
          accelerate();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;
        
        case 7: //計時
          settime();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;

        case 5: //擺頭
          turn();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;

        case 8: //模式
          mode();
          countdown = 30;
          Serial.print("Received number: ");
          Serial.println(number);
          break;

        default:
          Serial.print("進入default");
          break;
      }
      
    digitalValue = analogRead(digitalPin);
  
    Serial.print(" Digital Value: ");
    Serial.println(digitalValue);
    delay(0.1);
    Serial.flush();
  }Serial.println("倒數結束");
  
}



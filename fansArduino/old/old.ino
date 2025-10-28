//原本

const byte IN3 = 9;
const byte IN1 = 7;
const byte IN2 = 6;
int speed = 177;
int isHello = 0; //1=hello 
int isOpen = 0;
unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(IN3, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

//開啟
void open(){
  if(isOpen == 0){
    isOpen = 1;
    digitalWrite(IN1, LOW); // 也可以顛倒 調整轉向
  }
}

//加速
void accelerate(){
  if(isOpen == 1){
    speed = speed + 39;
    if(speed < 256){
      analogWrite(IN3, speed); 
    }
    else{
      speed = 255;
      analogWrite(IN3, speed); 
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
}

//減速
void decelerate(){
  if(isOpen == 1){
    speed = speed - 39;
    if(speed > 98){
      analogWrite(IN3, speed); 
    }
    else{
      speed = 99;
      analogWrite(IN3, speed); 
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);;
  }
}

//關閉
void close(){
  isOpen = 0;
  analogWrite(ENA, 0);
}

void loop() {
  int countdown = 30;
  if (Serial.available()) {
    int number;
    if(isHello == 0){
      number = Serial.parseInt();
      if(number == 1)
        isHello = 1;
    }
    if(isHello == 1){
      startTime = millis(); // 設定起始時間為目前的時間
      while(countdown > 0){ // 當倒數計時器仍然大於0時
          unsigned long currentTime = millis(); // 讀取目前時間
          if (currentTime - startTime >= 1000) { // 每經過1秒
          Serial.println(countdown); // 輸出倒數計時器的數值到序列埠
          countdown--; // 將倒數計時器減1
          startTime = currentTime; // 更新起始時間

          number = Serial.parseInt();
          switch(number){
            case 3: //開啟
              open();
              countdown = 30;
              Serial.print("Received number: ");
              Serial.println(number);
              break;

            case 2: //關閉
              close();
              countdown = 30;
              Serial.print("Received number: ");
              Serial.println(number);
              break;

            case 4: //加速
              accelerate();
              countdown = 30;
              Serial.print("Received number: ");
              Serial.println(number);
              break;

            case 5: //減速
              decelerate();
              countdown = 30;
              Serial.print("Received number: ");
              Serial.println(number);
              break;

            default:
              Serial.print("進入default");
              break;
            }
          }
      }
      Serial.println("倒數結束");
      isHello = 0;
    }
  }
}


//新的
#include "pitches.h"  //載入音調和頻率的對照檔

const byte IN1 = 4; //開啟
const byte IN2 = 6; //加速
const byte IN3 = 7; //定時
const byte IN4 = 5; //擺頭
const byte IN5 = 8; //模式

int speed = 177;
int isHello = 0; //1=hello  
int isopen = 0;

// 旋律
int melody[] = {
  NOTE_D6,NOTE_E6
};

// 每個音的的拍子，4：4分音符，8：8分音符
int noteDurations[] = {
  8,4
};

unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, HIGH);
}

//開啟
void open(){
  if(!isopen){
    isopen = 1;
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  }
}

//加速
void accelerate(){
  if(isopen){
    digitalWrite(IN2, LOW);
    delay(100);
    digitalWrite(IN2, HIGH);
  }
}

//定時
void settime(){
  if(isopen){
    digitalWrite(IN3, LOW);
    delay(100);
    digitalWrite(IN3, HIGH);
  }
}

//擺頭
void turn(){
  if(isopen){
    digitalWrite(IN4, LOW);
    delay(100);
    digitalWrite(IN4, HIGH);
  }
}

void mode(){
  if(isopen){
    digitalWrite(IN5, LOW);
    delay(100);
    digitalWrite(IN5, HIGH);
  }
}

//關閉
void close(){
  if(isopen){
    isopen = 0;
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  }
}


void helloVoice(){
  pinMode(2, OUTPUT);
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);   //tone(PIN腳,音調,拍子)

    // 每個音之間要停一小段時間，範例是建議拍子的長度加30%
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2);  // 停止播放
   }
   pinMode(2, INPUT);
 
}






void loop() {

  int countdown = 30;
  if (Serial.available()) {
    int number;
    if(isHello == 0){
      number = Serial.parseInt();
      if(number == 1){
        isHello = 1;
        helloVoice();
      }
    }
    if(isHello == 1){
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
          case 1: //哈囉
            helloVoice();
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            break;
            
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
      }
      Serial.println("倒數結束");
      isHello == 0;
    }
      
  }
      
    
}


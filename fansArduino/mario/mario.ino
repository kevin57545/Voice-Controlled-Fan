//新的
#include "pitches.h"  //載入音調和頻率的對照檔
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

// 旋律
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int melody2[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

// 每個音的的拍子，4：4分音符，8：8分音符
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

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
  if( analogRead(digitalPin) < 100 && analogRead(digitalPin) < 10 ){
    pinMode(digitalPin, INPUT_PULLUP);
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  }
}

//加速
void accelerate(){
  if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100 ){
    digitalWrite(IN2, LOW);
    delay(100);
    digitalWrite(IN2, HIGH);
  }
}

//定時
void settime(){
  if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN3, LOW);
    delay(100);
    digitalWrite(IN3, HIGH);
  }
}

//擺頭
void turn(){
  if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN4, LOW);
    delay(100);
    digitalWrite(IN4, HIGH);
  }
}

void mode(){
  if(analogRead(digitalPin) > 10 && analogRead(digitalPin) < 100){
    digitalWrite(IN5, LOW);
    delay(100);
    digitalWrite(IN5, HIGH);
  }
}

//關閉
void close(){
  int value = analogRead(digitalPin);
  if(value > 10 && value < 100){
    pinMode(digitalPin, INPUT);
    digitalWrite(IN1, LOW);
    delay(100);
    digitalWrite(IN1, HIGH);
  }
}


void buzz(int targetPin, long frequency, long length, int volume) {
  analogWrite(targetPin, volume);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);

}


void helloVoice(){
  /*pinMode(2, OUTPUT);
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody2[thisNote], noteDuration);   //tone(PIN腳,音調,拍子)

    // 每個音之間要停一小段時間，範例是建議拍子的長度加30%
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2);  // 停止播放
   }
   pinMode(2, INPUT);*/


   Serial.println(" 'Mario Theme'");
    int size = sizeof(melody2) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(2, melody2[thisNote], noteDuration, 200); // 增加音量到 200


      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(2, 0, noteDuration,200);
}
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
      helloVoice();
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
          case 1: //開啟
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
        digitalValue = analogRead(digitalPin);
        Serial.print(" Digital Value: ");
        Serial.println(digitalValue);
        delay(0.1);
        Serial.flush();
      }
      Serial.println("倒數結束");
      isHello == 0;
    }
      
  }
      
    
}

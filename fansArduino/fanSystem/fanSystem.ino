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
int oritime = 9; //9 indicates 0hr
int firstSetTime = 0;//是否第一次set time，若是，0
int airQuantity = 3;  //預設風量
int orimode = 1; //mode原先是一般模式(一般1->自然風2->睡眠風3->一般1)
// 旋律
int melody[] = {
  NOTE_D6,NOTE_E6,NOTE_F6
};

// 每個音的的拍子，4：4分音符，8：8分音符
int noteDurations[] = {
  8,4,4
};



void setup() {
  Serial.begin(115200);
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
  Serial.println("傳給樹梅派:1");
  Serial.println(1);
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
    airQuantity++;
  }
}

void setAirQuantity(){
  if(isopen){
    Serial.println("傳給樹梅派:3");
    Serial.println(3);
    //發出聲音
    setSpeedVoice();
    //接收修改的風量
    int number = -1;
    unsigned long startTime = millis(); // 紀錄開始時間
    int countdown = 15;
    while(number > 12 || number <= 0){
      number = Serial.parseInt();
      Serial.print("等待setWind指令 倒數:");
      Serial.println(countdown);
      countdown--;
      // 檢查是否超過 15 秒，若是則 return
      if (number > 12 || number < 0 || millis() - startTime >= 15000) {
        errorVoice();
        Serial.println("Timed out");
        Serial.println("傳給樹梅派:2");
        Serial.println(2);
        return;
      }
    }

    int executeOfSet = number - airQuantity;
    if(executeOfSet == 0) repeatedVoice();
    if(executeOfSet<0) executeOfSet = 13 - airQuantity + number -1;

    for(int i=0; i < executeOfSet; i++){
      digitalWrite(IN2, LOW);
      delay(100);
      digitalWrite(IN2, HIGH);
      delay(100);
      Serial.print(" ⏱️ ");
    }

    airQuantity = number;
    Serial.println();
    Serial.print("Now air quantity: ");
    Serial.print(airQuantity);
    Serial.println(".");
    Serial.println("傳給樹梅派:2");
    Serial.println(2);
  }
}

//定時
void settimes(){
  if(isopen){
    Serial.println("傳給樹梅派:4");
    Serial.println(4);
    // 發出聲音
    setTimeVoice();
    // 接收修改的時間
    int number = -1;
    unsigned long startTime = millis(); // 紀錄開始時間
    int countdown = 15;
    while(number > 9 || number <= 0){
      number = Serial.parseInt();
      Serial.print("等待setTime指令 倒數:");
      Serial.println(countdown);
      countdown--;
      // 檢查是否超過 15 秒，若是則 return
      if (number > 9 || number < 0 || millis() - startTime >= 15000) {
        errorVoice();
        Serial.println("Timed out");
        Serial.println("傳給樹梅派:2");
        Serial.println(2);
        return;
      }
    }
    if(oritime==9)oritime = 0;
    if(number==9)number = 0;

    //決定出執行定時按鈕的次數
    int executeOfSet = number - oritime;
    if(executeOfSet < 0)executeOfSet = 9 - oritime + number;
    
    //是否第一次執行定時+此次執行定時按鈕的次數 即此迴圈所需執行之次數
    for(int i=0; i < firstSetTime + executeOfSet; i++){
      digitalWrite(IN3, LOW);
      delay(100);
      digitalWrite(IN3, HIGH);
      delay(100);
      Serial.print(" ⏱️ ");
    }
    Serial.println();
    Serial.print("Set to ");
    Serial.print(number);
    Serial.println("hr.");
    oritime = number;
    firstSetTime = 1;
    if(oritime==0){
      oritime = 9;
      firstSetTime = 0;
    }
    delay(5500);
    Serial.println("傳給樹梅派:2");
    Serial.println(2);
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

void setMode(int number){
  if(isopen){
    //決定出執行模式按鈕的次數
    int executeOfSet = number - orimode;
    if(executeOfSet == 0) repeatedVoice();
    if(executeOfSet<0)executeOfSet = 3 - orimode + number;

    //按鈕的執行
    for(int i=0; i < executeOfSet; i++){
      digitalWrite(IN5, LOW);
      delay(100);
      digitalWrite(IN5, HIGH);
      delay(100);
      Serial.print(" ⏱️ ");
    }

    Serial.println();
    Serial.print("set to ");
    if(number == 1){
      Serial.println("normal mode.");
    }else if(number == 2){
      Serial.println("natural mode.");
    }else if(number == 3){
      Serial.println("sleep mode.");
    }
    orimode = number;
  }
} 


//關閉
void close(){
  if(isopen){
    isopen = 0;
    oritime = 9;
    firstSetTime = 0;
    orimode = 1; 
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

void setSpeedVoice(){
  pinMode(2, OUTPUT);
  for (int thisNote = 1; thisNote >= 0; thisNote--) {
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

void setTimeVoice(){
  pinMode(2, OUTPUT);
  for (int thisNote = 2; thisNote >= 0; thisNote--) {
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

void repeatedVoice(){
  pinMode(2, OUTPUT);
  for (int thisNote = 0; thisNote >= 0; thisNote--) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 4000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);   //tone(PIN腳,音調,拍子)

    // 每個音之間要停一小段時間，範例是建議拍子的長度加30%
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2);  // 停止播放
  }
  pinMode(2, INPUT);
 
}

void errorVoice(){
  pinMode(2, OUTPUT);
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[1], noteDuration);   //tone(PIN腳,音調,拍子)

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
        Serial.print("Received number: ");
        Serial.println(number);
        Serial.println("傳給樹梅派:2");
        Serial.println(2);
      }
    }
    if(isHello == 1){
      unsigned long startTime = millis(); // 設定起始時間為目前的時間
      while(countdown > 0){ // 當倒數計時器仍然大於0時
        unsigned long currentTime = millis(); // 讀取目前時間
        if (currentTime - startTime >= 1000) { // 每經過1秒
          Serial.print("倒數:"); // 輸出倒數計時器的數值到序列埠
          Serial.println(countdown);
          countdown--; // 將倒數計時器減1
          startTime = currentTime; // 更新起始時間
        }
        int number = Serial.parseInt();
        switch(number){
            
          case 3: //設定風量
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            setAirQuantity();
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
          
          case 7: //定時
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            settimes();
            break;
  
          case 5: //擺頭
            turn();
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            break;
  
          case 11: //模式:一般
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            setMode(1);
            break;

          case 12: //模式:自然
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            setMode(2);
            break;

          case 13: //模式:睡眠
            countdown = 30;
            Serial.print("Received number: ");
            Serial.println(number);
            setMode(3);
            break;
  
          default:
            Serial.print("等待Function指令");
            break;
        } 
      }
      Serial.println("end");
      isHello = 0;
      Serial.println("傳給樹梅派:1");
      Serial.println(1);
    }
      
  }
      
    
}

const int buttonPin = 2; // 按鈕連接到數位腳位2
int buttonState = 0;     // 儲存按鈕的狀態，0代表未按下，1代表按住

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // 初始化串口通信
}

void loop() {
  buttonState = digitalRead(buttonPin); // 讀取按鈕狀態

  if (buttonState == HIGH) {
    // 按鈕未被按住
    Serial.println("按鈕未被按住");
  } else {
    // 按住按鈕
    Serial.println("按鈕被按住");
  }

  delay(100); // 延遲一段時間以避免按鈕彈跳
}

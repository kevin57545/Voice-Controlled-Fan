const byte IN6 = A0; // MIC感測器1
//const byte IN7 = A1; // MIC感測器2

void setup() {
  Serial.begin(9600);  // 開始輸出訊息到監控視窗
}

void loop() {
  int sensorValue1 = analogRead(IN6);  // 讀取A0的值
  //int sensorValue2 = analogRead(IN7);  // 讀取A1的值
  Serial.print("MIC感測器1: "); // Print the label
  Serial.println(sensorValue1);  // 在監控視窗顯示讀取的值
  //Serial.print("MIC感測器2: "); // Print the label
  //Serial.println(sensorValue2);
  delay(100);
}
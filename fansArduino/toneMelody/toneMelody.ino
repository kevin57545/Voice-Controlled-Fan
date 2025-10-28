/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
*/

#include "pitches.h"  //載入音調和頻率的對照檔

// 旋律
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// 每個音的的拍子，4：4分音符，8：8分音符
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);   //tone(PIN腳,音調,拍子)

    // 每個音之間要停一小段時間，範例是建議拍子的長度加30%
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2);  // 停止播放
  }
}

void loop() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //計算每個音的長度，4分音符： 1000 / 4，8分音符：1000/8
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);   //tone(PIN腳,音調,拍子)

    // 每個音之間要停一小段時間，範例是建議拍子的長度加30%
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2);  // 停止播放
  }
  // no need to repeat the melody.
}

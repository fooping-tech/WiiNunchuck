
// FastLEDライブラリの設定（CRGB構造体）
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 16) | (g << 8) | b);
}

//Timer設定
hw_timer_t * timer = NULL;
bool flag = true;
void IRAM_ATTR onTimer() {
  if (flag) {         //ボタンが押されていれば
    M5.dis.drawpix(0, dispColor(0, 0, 255)); //LED（指定色）
  } else {                        //ボタンが押されてなければ
    M5.dis.drawpix(0, dispColor(20, 20, 20));    //LED（白）
  }
  flag = !flag;
}

void LED_setup(){
    //Timer設定
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
  
}
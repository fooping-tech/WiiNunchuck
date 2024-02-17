#include <M5Atom.h>
#include "AtomMotion.h"
#include <esp_now.h>
#include <WiFi.h>

// 送信機のMACアドレスを設定
uint8_t specificMacAddress[] = { 0xF4, 0x12, 0xFA, 0x9E, 0x31, 0x0C };
// サーボモータの取り付け角度誤差オフセット値を設定
const int r_offset_angle = 5;
const int l_offset_angle = -3;

AtomMotion Atom;

int JoyX = 0;
int JoyY = 0;
int AccX = 0;
int AccY = 0;
int AccZ = 0;
int BtnC = 0;
int BtnZ = 0;


xSemaphoreHandle CtlSemaphore;

void GetStatus() {
  for (int ch = 1; ch < 5; ch++) {
    Serial.printf("Servo Channel %d: %d \n", ch, Atom.ReadServoAngle(ch));
  }
  Serial.printf("Motor Channel %d: %d \n", 1, Atom.ReadMotorSpeed(1));
  Serial.printf("Motor Channel %d: %d \n", 2, Atom.ReadMotorSpeed(2));
}

//servo angle range 0 ~ 180
//DC motor speed range -127~127
void TaskMotion(void *pvParameters) {
  while (1) {
    //サーボ角度計算
    int r_angle = map(JoyX, 0, 250, 90 - 10, 90 + 10);
    int l_angle = r_angle;

    //アクセス計算
    int duty = 0;
    if (BtnZ == 1) {
      duty = 110;
    }
    if (BtnC == 1) {
      duty = 127;
    }

    Atom.SetServoAngle(1, r_angle + r_offset_angle);
    Atom.SetServoAngle(3, l_angle + l_offset_angle);
    Atom.SetMotorSpeed(2, duty);


    vTaskDelay(10 / portTICK_RATE_MS);
  }
}

void setup() {
  // 本体初期化（UART有効, I2C無効, LED有効）
  M5.begin(true, false, true);
  Atom.Init();  //sda  25     scl  21
  // LED全消灯（赤, 緑, 青）
  M5.dis.drawpix(0, dispColor(0, 0, 0));

  vSemaphoreCreateBinary(CtlSemaphore);
  //Core0でタスク起動
  xTaskCreatePinnedToCore(
    TaskMotion  // タスク関数へのポインタ。無限ループで終了しないよう関数を指定します
    ,
    "TaskMotion"  // タスクの説明用名前。重複しても動きますがデバッグ用途。最大16文字まで
    ,
    4096  //スタックサイズ(Byte)
    ,
    NULL  //作成タスクのパラメータのポインタ
    ,
    2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest..  优先级，3 (configMAX_PRIORITIES - 1) 最高，0 最低。
    ,
    NULL  //作成タスクのHandleへのポインタ
    ,
    0);  //利用するCPUコア(0-1)

  ESPNOW_setup();
  LED_setup();
}

void loop() {
  M5.update();
}

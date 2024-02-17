#include <WiiChuck.h>
#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>
#include <M5Unified.h>
Accessory nunchuck1;

void setup() {
  auto cfg = M5.config(); 
  M5.begin(cfg);
  //Wireライブラリを初期化
  Wire.begin(M5.Ex_I2C.getSDA(), M5.Ex_I2C.getSCL());
  Serial.begin(115200); //Serial begin
  delay(50);   //delay 50ms.
  Serial.println("SERIAL setup was completed.");

	nunchuck1.begin();
	if (nunchuck1.type == Unknown) {
		nunchuck1.type = NUNCHUCK;
	}
  ESPNOW_setup();
}

void loop() {
  M5.update();
  nunchuck1.readData();    // Read inputs and update maps
  //以下の関数でヌンチャクの値を取得する関数
  //getJoyX();getJoyY();getRollAngle();getPitchAngle();getAccelX();getAccelY();getAccelZ();getButtonC();getButtonZ();
  //c,zボタンが押された1度だけtrueを返す関数
  //BUTTON_check_C();BUTTON_check_C();
  ESPNOW_SendData(nunchuck1.getJoyX(),nunchuck1.getJoyY(),nunchuck1.getAccelX(),nunchuck1.getAccelY(),nunchuck1.getAccelZ(),nunchuck1.getButtonC(),nunchuck1.getButtonZ());
  PrintValue();
}

void PrintValue(){
  Serial.print("JoyX:");
  Serial.print(nunchuck1.getJoyX());
  Serial.print(",JoyY:");
  Serial.print(nunchuck1.getJoyY());
  Serial.print(",AccX:");
  Serial.print(nunchuck1.getAccelX());
  Serial.print(",AccY:");
  Serial.print(nunchuck1.getAccelY());
  Serial.print(",AccZ:");
  Serial.print(nunchuck1.getAccelZ());
  Serial.print(",BtnZ:");
  Serial.print(nunchuck1.getButtonC());
  Serial.print(",BtnC:");
  Serial.print(nunchuck1.getButtonZ());
  Serial.println("");
}
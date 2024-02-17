int cur_value_C = 0;
int cur_value_Z = 0;
int last_value_C = 0;
int last_value_Z = 0;

bool BUTTON_check_C() {

  cur_value_C = nunchuck1.getButtonC();

  if (cur_value_C != last_value_C) {  //前回値と今回値が異なり
    if (cur_value_C == 1) {           //今回0のとき
      last_value_C = cur_value_C;     //前回値を更新
      return true;
    }
  }
  last_value_C = cur_value_C;  //前回値を更新
  return false;
}

bool BUTTON_check_Z() {

  cur_value_Z = nunchuck1.getButtonZ();

  if (cur_value_Z != last_value_Z) {
    if (cur_value_Z == 1) {  //今回0のとき
      last_value_Z = cur_value_Z;
      return true;
    }
  }
  last_value_Z = cur_value_Z;
  return false;
}

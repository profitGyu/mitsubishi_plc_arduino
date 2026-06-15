#include <Arduino.h>
/* 램프와 스위치 다루기
  1번 핀 스위치를 on 하면 1번 lamp가 on이 되도록 
  2번 핀 스위치를 on 하면 2번 lamp가 off가 되도록 
*/

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
#include <Arduino.h>

/* MsTimer2를 이용해서 실린더 계속 6초마다 반복하기 
  1. A+B+C+ C- B- A-
  2. 1번 스위치(on), 2번 스위치(off)
*/

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
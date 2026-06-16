#include <Arduino.h>

/* MsTimer2를 이용해서 실린더 계속 반복하기 
  실린더 위치를 기반의 로직으로 A+B+C+C-B-A- 코드를 기반으로
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
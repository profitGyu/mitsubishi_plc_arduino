#include <Arduino.h>
/* 램프와 스위치 다루기
  MsTimer2.h 를 사용하여
  1번 스위치를 눌르면 연결된 모든 램프가 계속 깜빡거리고 0.5초~1초()
  2번 스위치를 누르면 연결된 모든 램프가 종료 되됨

  ex) 응용 1. 깜빡거리는 속도가 점점 빨라짐
      응용 2. 깜빡거리는 속도가 점점 느려짐
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
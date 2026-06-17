#include <Arduino.h>
#include <io.h>

/* [블로그 검증 실험] delay() 방식의 치명적인 한계 확인하기
   - 1번 스위치(I00)를 누르면 -> 0.5초 켜지고 0.5초 꺼지는 깜빡임이 무한 반복됨
   - 2번 스위치(I01)를 누르면 -> 정지되어야 하지만, 딜레이 때문에 스위치가 먹통이 됨!
*/

#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};

bool isRunning = false; 

void setup() {
    Serial.begin(115200);

    for(int i=0; i<RELAY_NUM; i++) pinMode(relay[i], OUTPUT);
    for(int j=0; j<INPUT_NUM; j++) pinMode(input[j], INPUT);
}

void loop() {
    // 1. 루프의 시작점에서만 스위치 상태를 읽음
    bool isInputZeroPin = digitalRead(I00); // S1 (시작)
    bool isInputOnePin = digitalRead(I01);  // S2 (정지)

    if(isInputZeroPin){
        isRunning = true;
    }

    if(isInputOnePin){
        isRunning = false;
        digitalWrite(Q00, LOW); 
    }

    // 2. 문제의 깜빡임 로직 영역
    if(isRunning) {
        digitalWrite(Q00, HIGH); 
        delay(500); // ❌ 이 0.5초 동안 아두이노는 완전히 얼어붙습니다. (스위치 감지 불가능)
        
        digitalWrite(Q00, LOW);  
        delay(500); // ❌ 이 0.5초 동안도 역시 아두이노는 아무것도 하지 못합니다.
    }
}
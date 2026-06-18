#include <Arduino.h>
#include <io.h>

/* [프로젝트 매뉴얼] millis() 함수를 활용한 Non-blocking 램프 깜빡이기
   - 1번 스위치(I00)를 누르면 -> 시스템이 가동되어 0.5초 간격으로 램프가 깜빡임
   - 2번 스위치(I01)를 누르면 -> 시스템이 정지하고 램프가 즉시 소등됨
   - 핵심: delay()를 쓰지 않아 램프가 깜빡이는 중에도 정지 버튼이 즉각 반응함!
*/

#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};

// 시스템 상태 및 타이머 제어를 위한 변수들
bool isRunning = false;          // 시스템 가동 상태 플래그
unsigned long previousMillis = 0; // 마지막으로 램프 상태가 바뀐 시간을 저장 (시간 기록장)
const long interval = 500;       // 깜빡임 주기 설정 (500ms = 0.5초)
bool lampStatus = LOW;           // 현재 램프의 ON/OFF 상태를 기억하는 변수

void setup() {
    Serial.begin(115200);

    for(int i=0; i<RELAY_NUM; i++) pinMode(relay[i], OUTPUT);
    for(int j=0; j<INPUT_NUM; j++) pinMode(input[j], INPUT);
}

void loop() {
    // 1. 스위치 입력 상태 실시간 감지 (언제든 루프가 돌며 즉각 감지 가능)
    bool isInputZeroPin = digitalRead(I00); // S1 (시작)
    bool isInputOnePin = digitalRead(I01);  // S2 (정지)

    if(isInputZeroPin){
        isRunning = true;
    }

    if(isInputOnePin){
        isRunning = false;
        lampStatus = LOW;          // 램프 상태 변수 초기화
        digitalWrite(Q00, LOW);    // L1 램프 즉시 소등
    }

    // 2. millis() 기반 시간 측정 및 깜빡임 제어 영역
    if(isRunning) {
        // 아두이노가 켜진 후 흐른 현재 시간을 가져옴
        unsigned long currentMillis = millis();

        // (현재 시간 - 마지막 변경 시간)이 설정한 주기(500ms)보다 커졌는지 확인
        if (currentMillis - previousMillis >= interval) {
            Serial.println(currentMillis);
            Serial.println(previousMillis);
            Serial.println(interval);
            // 기준 시간을 현재 시간으로 갱신 (다음 0.5초를 재기 위함)
            previousMillis = currentMillis;

            // 램프 상태를 반전 (LOW 상태면 HIGH로, HIGH 상태면 LOW로)
            lampStatus = !lampStatus;
            
            // 실제 출력 핀에 반영
            digitalWrite(Q00, lampStatus);
        }
    }
}
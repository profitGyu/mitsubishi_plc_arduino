#include <Arduino.h>
#include <io.h> // 앞서 정의한 PLC 스타일의 I/O 핀 맵 헤더 파일 포함

/* [프로젝트 매뉴얼] 램프와 스위치 다루기
   - 1번 스위치(I00)를 ON 하면 -> 1번 Lamp(Q00)가 ON (인터록 셋)
   - 2번 스위치(I01)를 ON 하면 -> 1번 Lamp(Q00)가 OFF (인터록 리셋)
*/

#define RELAY_NUM 16 // 제어할 출력(릴레이) 채널 수 정의
#define INPUT_NUM 16 // 제어할 입력(스위치/센서) 채널 수 정의

// io.h에 정의된 핀 매크로를 활용해 입출력 배열(Array) 생성
int relay[RELAY_NUM] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[INPUT_NUM] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};

void setup() {
    // 시리얼 모니터 디버깅을 위한 통신 속도 설정 (115200 bps)
    Serial.begin(115200);

    // 반복문을 사용하여 16개의 릴레이 출력을 모두 OUTPUT 모드로 일괄 설정
    for(int i = 0; i < RELAY_NUM; i++)
        pinMode(relay[i], OUTPUT);

    // 반복문을 사용하여 16개의 스위치 입력을 모두 INPUT 모드로 일괄 설정
    for(int j = 0; j < INPUT_NUM; j++)
        pinMode(input[j], INPUT);
}

void loop() {
    // 맵핑 테이블에 정의된 S1 스위치(I00)와 S2 스위치(I01)의 상태를 실시간으로 읽음
    // PNP 결선 구조이므로 스위치가 켜지면 HIGH(1), 꺼지면 LOW(0)가 리턴됨
    bool isInputZeroPin = digitalRead(I00); // S1 스위치 상태 저장
    bool isInputOnePin = digitalRead(I01);  // S2 스위치 상태 저장
  
    // 조건문 처리: 1번 스위치(S1)가 켜졌을 때
    if(isInputZeroPin){
        digitalWrite(Q00, HIGH); // 1번 릴레이를 붙여 L1 램프 점등
    } 

    // 조건문 처리: 2번 스위치(S2)가 켜졌을 때
    if(isInputOnePin){
        digitalWrite(Q00, LOW);  // 1번 릴레이를 떨어뜨려 L1 램프 소등
    } 
}
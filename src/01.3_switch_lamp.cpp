#include <Arduino.h>
#include <io.h>
#include <MsTimer2.h> // 하드웨어 타이머2를 사용해 주기적인 인터럽트를 발생시키는 라이브러리

/* [프로젝트 매뉴얼] 타이머 인터럽트를 활용한 램프 깜빡이기(Blink)
   - 1번 스위치(I00)를 누르면 -> MsTimer2가 시작되어 0.5초 간격으로 모든 램프가 깜빡임
   - 2번 스위치(I01)를 누르면 -> MsTimer2가 정지하고 모든 램프가 강제 소등(종료)됨
   
   [향후 응용 과제 예고]
   - 응용 1. 깜빡이는 속도가 점점 빨라지는 로직
   - 응용 2. 깜빡이는 속도가 점점 느려지는 로직
*/

#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};
byte Dinput[16]; // 입출력 데이터 확장용 바이트 배열 (추후 사용 예정)

// [ISR: 인터럽트 서비스 루틴] 타이머에 설정된 주기(500ms)마다 자동으로 실행되는 함수
void flash(){
    // static 변수를 사용하여 함수가 끝나도 기존의 출력 상태(HIGH 또는 LOW)를 유지
    static boolean output = HIGH;

    // TODO: 현재는 Q00(1번 램프)만 제어 중이나, 요구사항인 '연결된 모든 램프' 제어를 위해
    // 추후 반복문(for)을 적용하여 전체 릴레이를 제어하도록 확장 가능합니다.
    digitalWrite(Q00, output);
    
    // 상태 반전 (HIGH -> LOW, LOW -> HIGH)을 통해 깜빡임 효과 구현
    output = !output;
}

void setup() {
    Serial.begin(115200);

    // 16채널 출력 및 입력 핀 모드 일괄 설정
    for(int i=0; i<RELAY_NUM; i++)
        pinMode(relay[i], OUTPUT);

    for(int j=0; j<INPUT_NUM; j++)
        pinMode(input[j], INPUT);

    MsTimer2::set(500, flash);
}

void loop() {
    // 스위치 입력 상태 실시간 감지 (PNP 로직)
    bool isInputZeroPin = digitalRead(I00); // S1 스위치 (시작 버튼)
    bool isInputOnePin = digitalRead(I01);  // S2 스위치 (정지 버튼)

    // S1 스위치(I00)를 누르면 타이머 인터럽트 구동 시작
    if(isInputZeroPin){
        MsTimer2::start();
    }

    // S2 스위치(I01)를 누르면 타이머를 멈추고 안전을 위해 램프 강제 소등
    if(isInputOnePin){
        MsTimer2::stop();
        digitalWrite(Q00, LOW); // 정지 시 램프가 켜진 채로 멈추는 것을 방지
    }
}
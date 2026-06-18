#include <Arduino.h>
#include <io.h>

/* MsTimer2를 이용해서 실린더 계속 6초마다 반복하기 
  1. A+B+C+ C- B- A-
  2. 1번 스위치(on), 2번 스위치(off)
*/

#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};

void step2Controler(){
  static int seq = 1;
  
  switch (seq)
  {
    // ==========================================
    // 1. A 실린더 전진 (A+)
    // ==========================================
    case 1:
      // Start 스위치(I00) ON + 모든 실린더가 초기 위치(후진 완료: I01, I03, I05)일 때 시작
      if(digitalRead(I00) == HIGH && digitalRead(I01) == HIGH && digitalRead(I03) == HIGH && digitalRead(I05) == HIGH){
        digitalWrite(Q01, HIGH); // A 전진 밸브 ON
        digitalWrite(Q02, LOW);  // A 후진 밸브 OFF
        seq = 2;
      }
      break;

    // ==========================================
    // 2. B 실린더 전진 (B+)
    // ==========================================
    case 2:
      if(digitalRead(I02) == HIGH){ // A 전진 완료(I02) 감지 시
        digitalWrite(Q01, LOW);     // A 전진 신호 OFF (양솔이므로 꺼도 전진 유지)
        digitalWrite(Q03, HIGH);    // B 전진 밸브 ON
        digitalWrite(Q04, LOW);     // B 후진 밸브 OFF
        seq = 3;
      }
      break;

    // ==========================================
    // 3. C 실린더 전진 (C+)
    // ==========================================
    case 3: 
      if(digitalRead(I04) == HIGH){ // B 전진 완료(I04) 감지 시
        digitalWrite(Q03, LOW);     // B 전진 신호 OFF
        digitalWrite(Q05, HIGH);    // C 전진 밸브 ON (★편솔이므로 HIGH 유지!)
        seq = 4;
      }
      break;

    // ==========================================
    // 4. A 실린더 후진 (A-)
    // ==========================================
    case 4:
      if(digitalRead(I06) == HIGH){ // C 전진 완료(I06) 감지 시
        digitalWrite(Q02, HIGH);    // A 후진 밸브 ON
        seq = 5;
      }
      break;

    // ==========================================
    // 5. B 실린더 후진 (B-)
    // ==========================================
    case 5:
      if(digitalRead(I01) == HIGH){ // A 후진 완료(I01) 감지 시
        digitalWrite(Q02, LOW);     // A 후진 신호 OFF
        digitalWrite(Q04, HIGH);    // B 후진 밸브 ON
        seq = 6;
      }
      break;

    // ==========================================
    // 6. C 실린더 후진 (C-) 및 공정 완료
    // ==========================================
    case 6:
      if(digitalRead(I03) == HIGH){ // B 후진 완료(I03) 감지 시
        digitalWrite(Q04, LOW);     // B 후진 신호 OFF
        digitalWrite(Q05, LOW);     // C 전진 밸브 OFF (★신호를 끊어서 스프링 힘으로 후진)
        seq = 7;
      }
      break;

    case 7:
      if(digitalRead(I05) == HIGH){ // C 후진 완료(I05) 감지 시 모든 공정 완료
        seq = 1;                    // 처음 단계로 돌아가 대기
      }
      break;
  }
}



// A+ B+ C+ A- B- C-
void stepControler(){
  static int seq = 1;
  
  switch (seq)
  {
    // ==========================================
    // 1. A 실린더 전진 (A+)
    // ==========================================
    case 1:
      // Start 스위치(I00)가 눌리고, 초기 위치(A후진:I01, B후진:I03, C후진:I05)일 때 시작
      if(digitalRead(I00) == HIGH && digitalRead(I01) == HIGH && digitalRead(I03) == HIGH && digitalRead(I05) == HIGH){
        digitalWrite(Q01, HIGH); // A 전진 밸브 ON
        digitalWrite(Q02, LOW);  // A 후진 밸브 OFF (안전을 위해)
        seq = 2;
      }
      break;

    // ==========================================
    // 2. B 실린더 전진 (B+)
    // ==========================================
    case 2:
      if(digitalRead(I02) == HIGH){ // A 전진 완료(I02) 감지되면
        digitalWrite(Q01, LOW);     // A 전진 자기유지 해제 (양솔이므로 꺼도 전진유지)
        digitalWrite(Q03, HIGH);    // B 전진 밸브 ON
        digitalWrite(Q04, LOW);     // B 후진 밸브 OFF
        seq = 3;
      }
      break;

    // ==========================================
    // 3. C 실린더 전진 (C+)
    // ==========================================
    case 3: 
      if(digitalRead(I04) == HIGH){ // B 전진 완료(I04) 감지되면
        digitalWrite(Q03, LOW);     // B 전진 자기유지 해제
        digitalWrite(Q05, HIGH);    // C 전진 밸브 ON (편솔이므로 켜짐 유지해야 함!)
        seq = 4;
      }
      break;

    // ==========================================
    // 4. C 실린더 후진 (C-)
    // ==========================================
    case 4:
      if(digitalRead(I06) == HIGH){ // C 전진 완료(I06) 감지되면
        digitalWrite(Q05, LOW);     // C 전진 밸브 OFF -> 편솔레노이드이므로 스스로 후진함
        seq = 5;
      }
      break;

    // ==========================================
    // 5. B 실린더 후진 (B-)
    // ==========================================
    case 5:
      if(digitalRead(I05) == HIGH){ // C 후진 완료(I05) 감지되면
        digitalWrite(Q04, HIGH);    // B 후진 밸브 ON
        seq = 6;
      }
      break;

    // ==========================================
    // 6. A 실린더 후진 (A-) 및 종료
    // ==========================================
    case 6:
      if(digitalRead(I03) == HIGH){ // B 후진 완료(I03) 감지되면
        digitalWrite(Q04, LOW);     // B 후진 자기유지 해제
        digitalWrite(Q02, HIGH);    // A 후진 밸브 ON
        seq = 7;
      }
      break;

    case 7:
      if(digitalRead(I01) == HIGH){ // A 후진 완료(I01) 감지되면 모든 공정 완료
        digitalWrite(Q02, LOW);     // A 후진 자기유지 해제
        seq = 1;                    // 다시 처음으로 (Start 버튼 대기)
      }
      break;
  }
}
  

void setup() {
  Serial.begin(115200); 
  // 16채널 출력 및 입력 핀 모드 일괄 설정
    for(int i=0; i<RELAY_NUM; i++)
        pinMode(relay[i], OUTPUT);

    for(int j=0; j<INPUT_NUM; j++)
        pinMode(input[j], INPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  // stepControler();
  step2Controler();
}

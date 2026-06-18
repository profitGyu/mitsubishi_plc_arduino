#include <Arduino.h>
#include <io.h>

/* MsTimer2를 이용해서 실린더 계속 6초마다 반복하기 
   1. A+B+C+ C- B- A-
   2. 1번 스위치(on), 2번 스위치(off)
*/

#define RELAY_NUM 16
#define INPUT_NUM 16

// 💡 속도 조절을 위한 전역 설정 변수 (밀리초 단위, 500 = 0.5초 대기)
#define CYLINDER_DELAY 500 

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};

// 💡 시간 측정을 위한 전역 변수들
unsigned long timerStart = 0; 
bool isTimerActive = false;

// A+ B+ C+ A- B- C- (속도 제어 버전)
void step2Controler(){
  static int seq = 1;
  
  switch (seq)
  {
    // ==========================================
    // 1. A 실린더 전진 (A+)
    // ==========================================
    case 1:
      if(digitalRead(I00) == HIGH && digitalRead(I01) == HIGH && digitalRead(I03) == HIGH && digitalRead(I05) == HIGH){
        digitalWrite(Q01, HIGH); // A 전진 밸브 ON
        digitalWrite(Q02, LOW);  // A 후진 밸브 OFF
        
        // 💡 다음 단계로 넘어가기 전 타이머 가동 시작
        timerStart = millis();
        Serial.print("case 1 timerStart:");
        Serial.println(timerStart);
        isTimerActive = true;
        seq = 2;
      }
      break;

    // ==========================================
    // 2. B 실린더 전진 (B+)
    // ==========================================
    case 2:
      // 이전 단계의 타이머(설정값만큼 대기)가 끝나고 + A 전진 완료 센서가 켜졌을 때 진입
      Serial.print("case2 Start: millis");
      Serial.println(millis());
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false; // 타이머 초기화 (센서 대기 상태로 전환)
      }

      if(!isTimerActive && digitalRead(I02) == HIGH){ 
        digitalWrite(Q01, LOW);     
        digitalWrite(Q03, HIGH);    // B 전진 밸브 ON
        digitalWrite(Q04, LOW);     
        
        timerStart = millis();      // 💡 동작 명령 내린 후 타이머 시작
        Serial.print("case 2 timerStart:");
        Serial.println(timerStart);
        isTimerActive = true;
        seq = 3;
      }
      break;

    // ==========================================
    // 3. C 실린더 전진 (C+)
    // ==========================================
    case 3: 
     Serial.print("case3 Start: millis");
      Serial.println(millis());
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false;
      }

      if(!isTimerActive && digitalRead(I04) == HIGH){ 
        digitalWrite(Q03, LOW);     
        digitalWrite(Q05, HIGH);    // C 전진 밸브 ON
        
        timerStart = millis();      // 💡 타이머 시작
        Serial.print("case 3 timerStart:");
        Serial.println(timerStart);
        isTimerActive = true;
        seq = 4;
      }
      break;

    // ==========================================
    // 4. A 실린더 후진 (A-)
    // ==========================================
    case 4:
     Serial.print("case4 Start: millis");
      Serial.println(millis());
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false;
      }

      if(!isTimerActive && digitalRead(I06) == HIGH){ 
        digitalWrite(Q02, HIGH);    // A 후진 밸브 ON
        
        timerStart = millis();      // 💡 타이머 시작
        Serial.print("case 4 timerStart:");
        Serial.println(timerStart);
        isTimerActive = true;
        seq = 5;
      }
      break;

    // ==========================================
    // 5. B 실린더 후진 (B-)
    // ==========================================
    case 5:
     Serial.print("case5 Start: millis");
      Serial.println(millis());
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false;
      }

      if(!isTimerActive && digitalRead(I01) == HIGH){ 
        digitalWrite(Q02, LOW);     
        digitalWrite(Q04, HIGH);    // B 후진 밸브 ON
        
        timerStart = millis();      // 💡 타이머 시작
        isTimerActive = true;
        Serial.print("case 5 timerStart:");
        Serial.println(timerStart);

        seq = 6;
      }
      break;

    // ==========================================
    // 6. C 실린더 후진 (C-) 및 공정 완료
    // ==========================================
    case 6:
     Serial.print("case6 Start: millis");
      Serial.println(millis());
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false;
      }

      if(!isTimerActive && digitalRead(I03) == HIGH){ 
        digitalWrite(Q04, LOW);     
        digitalWrite(Q05, LOW);     // C 전진 밸브 OFF (후진)
        
        timerStart = millis();      // 💡 타이머 시작
        Serial.print("case 6 timerStart:");
        Serial.println(timerStart);

        isTimerActive = true;
        seq = 7;
      }
      break;

    case 7:
      if(isTimerActive && (millis() - timerStart >= CYLINDER_DELAY)) {
        isTimerActive = false;
      }

      if(!isTimerActive && digitalRead(I05) == HIGH){ 
        seq = 1;                    // 처음 단계로 돌아가 대기
      }
      break;
  }
}

void setup() {
  Serial.begin(115200); 
  for(int i=0; i<RELAY_NUM; i++) pinMode(relay[i], OUTPUT);
  for(int j=0; j<INPUT_NUM; j++) pinMode(input[j], INPUT);
}

void loop() {
  step2Controler();
}
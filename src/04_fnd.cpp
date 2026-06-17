#include <Arduino.h>
#include <mio.h>

// put function declarations here:
#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[16] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[16] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};
byte Dinput[16];


void displayFND(int number) {
  // 0~15 범위로 제한 (4비트는 최대 15까지 표현 가능)
  if (number < 0 || number > 15) return; 

  // 각 비트별로 값을 추출하여 핀에 출력 (이진수 변환)
  digitalWrite(Q00, (number >> 0) & 0x01); // 1의 자리 (LSB)
  digitalWrite(Q01, (number >> 1) & 0x01); // 2의 자리
  digitalWrite(Q02, (number >> 2) & 0x01); // 4의 자리
  digitalWrite(Q03, (number >> 3) & 0x01); // 8의 자리 (MSB)
}


void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);

    for(int i=0; i<RELAY_NUM; i++)
        pinMode(relay[i], OUTPUT);

    for(int j=0; j<INPUT_NUM; j++)
        pinMode(input[j], INPUT);
}

void loop() {

  for (int i = 0; i <= 9; i++) {
    Serial.print("Current Number: ");
    Serial.println(i);
    
    displayFND(i); 
    delay(1000);
  }  
}



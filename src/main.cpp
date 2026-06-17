#include <Arduino.h>
#include <io.h>

// put function declarations here:
#define RELAY_NUM 16
#define INPUT_NUM 16

int relay[RELAY_NUM] = {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, Q08, Q09, Q10, Q11, Q12, Q13, Q14, Q15};
int input[INPUT_NUM] = {I00, I01, I02, I03, I04, I05, I06, I07, I08, I09, I10, I11, I12, I13, I14, I15};


void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
    for(int i=0; i<RELAY_NUM; i++)
        pinMode(relay[i], OUTPUT);

    for(int j=0; j<INPUT_NUM; j++)
        pinMode(input[j], INPUT);
}

void loop() {
  digitalWrite(Q00, HIGH);
  digitalRead(I00);
}



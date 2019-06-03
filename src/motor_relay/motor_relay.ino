#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define D5 6
#define D6 7
#define _5s   5000     // 5 seconds 
#define _2s   2000     // 2 seconds
#define DEBUG 1        // for DEBUGing 
int pins[] = {D1, D2, D3, D4, D5, D6};
void setup() {      // put your setup code here, to run once:
    Serial.begin(9600);
    
    #if DEBUG
    Serial.print(sizeof(pins)/sizeof(pins[0]));          // the length of the pins
    #endif
    
    for (byte i =0; i < sizeof(pins)/sizeof(pins[0]); i++) {
      pinMode(pins[i], OUTPUT);
    }

    delay(_2s/1);
  
}

void loop() {      // put your main code here, to run repeatedly:
  
    for (byte i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
      digitalWrite(pins[i], HIGH);
      delay(_2s/2);
      digitalWrite(pins[i],LOW);
      delay(_2s/2);
    }
}

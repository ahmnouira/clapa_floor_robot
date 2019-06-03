#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define D5 6
#define D6 7
#define verin_up A1
#define verin_down A2
#define _5s   5000     // 5 seconds 
#define _2s   2000     // 2 seconds
#define DEBUG 0        // for DEBUGing 
int pins[] = {D1, D2, D3, D4, D5, D6};
void setup() {      // put your setup code here, to run once:
    
    #if DEBUG
    Serial.begin(9600);
    Serial.print(sizeof(pins)/sizeof(pins[0]));          // the length of the pins
    #endif
    
    for (byte i =0; i < sizeof(pins)/sizeof(pins[0]); i++) {
      pinMode(pins[i], OUTPUT);
    }

    delay(_2s/1);
  
}

void verin_command() {

  
  // verin up
  if (digitalRead(verin_up) == HIGH && digitalRead(verin_down)== LOW){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    #if DEBUG
    Serial.println("Verin vers le haut");
    delay(50);
    #endif
    
  } 
  // verin down
   if (digitalRead(verin_up) == LOW && digitalRead(verin_down)== HIGH){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    #if DEBUG
    Serial.println("Verin vers le bas");
    delay(50);
    #endif
  } 
  // verin stop
  if (digitalRead(verin_up) == LOW || digitalRead(verin_down)==LOW) {
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    #if DEBUG
    Serial.println("Verin stop");
    delay(50);
    #endif
  }
  
}

void loop() {      // put your main code here, to run repeatedly:

  verin_command();
   

  
  }

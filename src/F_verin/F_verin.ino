#define D1 2      // vrein_sens+
#define D2 3      // verin_sens-
#define D3 4
#define D4 5
#define D5 6
#define D6 7
#define verin_up A1    // verin_up connected to A1
#define verin_down A2  // verin_down connected to A2
#define _5s   5000     // 5 seconds 
#define _2s   2000     // 2 seconds
#define DEBUG 1        // for DEBUGing 
int pins[] = {D1, D2, D3, D4, D5, D6};
void setup() {      // put your setup code here, to run once:
    
    #if DEBUG
    Serial.begin(9600);                  // serial for debuging
    //Serial.print(sizeof(pins)/sizeof(pins[0]));          // the length of the pins
    #endif
    
    for (byte i =0; i < sizeof(pins)/sizeof(pins[0]); i++) {
      pinMode(pins[i], OUTPUT);
    }

    delay(_2s/1);
  
}

void verin_command() {
  
  int dif_verin = digitalRead(verin_up) - digitalRead(verin_down);
  switch (dif_verin) {
    case 1 : 
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      #if DEBUG
      Serial.println("Verin vers le haut");
      #endif
      break;
    case -1 : 
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      #if DEBUG
      Serial.println("Verin vers le bas");
      #endif
      break;
    default : 
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      #if DEBUG
      Serial.println("Verin stop");
      #endif
      break;
  
}
}

void loop() {            // put your main code here, to run repeatedly:
     verin_command();    // verin_reglage
     delay(1000);        // for virtual monitor 
  }
 
  
   

  
  

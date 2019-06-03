#define D1 2            // verin sens 1 (up)
#define D2 3            // verin sens 2 (down)
#define D3 4            // translation_right_left
#define D4 5            // translation_left_right
#define D5 6            // helice 1   >> helice 1 and helice same sense !
#define D6 7            // helice 2
#define D7 8            // tapis_motor_right
#define D8 9            // tapis_motor_left

#define start A0        // start_cycle_button
#define verin_up A1     //up_verin_button
#define verin_down A2
#define CR 8
#define CL 9
#define _5s   5000     // 5 seconds 
#define _2s   2000     // 2 seconds
#define DEBUG 0        // for DEBUGing 
int pins[] = {D1, D2, D3, D4, D5, D6};
bool _start = false;
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

void stop_translation() {
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  delay(500);
}

void translation_to_lc() {
  // translation motor sens1
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  
  // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}
void translation_to_rc() {
  // translation motor sens2
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  
  // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}

void init_cycle() {
  while(digitalRead(CR) == LOW) {
    stop_translation();
    translation_to_rc();
    if (digitalRead(CR) == HIGH) {
      break;
    }
  }
}
  
void loop() {      // put your main code here, to run repeatedly:

  verin_command();
  if (digitalRead(start) == HIGH) {
    _start = true;
  }
  else {
    ;
  }
  while (_start) {
    if (digitalRead(CL)== LOW && digitalRead(CR) == LOW)   {
        init_cycle();
    if (digitalRead(CL) == LOW && digitalRead(CR) == HIGH) {
        stop_translation();
        translation_to_lc();
    }
    if (digitalRead(CL) == HIGH && digitalRead(CR) == LOW) {
      stop_translation();
      translation_to_rc();
    }
    if (digitalRead(CL) == HIGH && digitalRead(CL) == HIGH) {
        init_cycle();
    }
    }
    
  }

  }

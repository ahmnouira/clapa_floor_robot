#define D1 4            // verin sens 1 (up)
#define D2 5            // verin sens 2 (down)
#define D3 6            // translation_right_left
#define D4 7            // translation_left_right
#define D5 8            // helice 1   >> helice 1 and helice same sense !
#define D6 9            // helice 2

#define D7 10           // tapis_motor_right Forward
#define D8 11           // tapis_motor_left  Forward

#define start A0        // start_cycle_button
#define stopp 2         // stop_cycle_button retrun config verin
#define verin_up A1     // up_verin_button
#define verin_down A2   // down_verin_button
#define CR A3           // sensor_trans_right
#define CL A4           // sensor-trans_left
#define _5s   5000      // 5 seconds 
#define _2s   2000      // 2 seconds
#define DEBUG 1         // for DEBUGing 
int pins[] = {D1, D2, D3, D4, D5, D6, D7, D8};
bool _start = false;
bool _stop = false;

void setup() {      // put your setup code here, to run once:
    
    #if DEBUG
    Serial.begin(9600);
    Serial.print(sizeof(pins)/sizeof(pins[0]));          // the length of the pins
    #endif
    
    for (byte i =0; i < sizeof(pins)/sizeof(pins[0]); i++) {
      pinMode(pins[i], OUTPUT);
    }
    pinMode(stopp, INPUT);
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


void stop_all(){
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}


void stop_translation() {
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  delay(500);
}

void translation_to_cl() {
  // translation motor sens1
  if (digitalRead(stopp == LOW ) ){
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  
  // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  }
}
void translation_to_cr() {
  if(digitalRead(stopp == LOW)){
  // translation motor to right
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  
  // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}
}


void forward_step() {
  stop_translation();
  digitalWrite(D7,HIGH);
  digitalWrite(D8,HIGH);
  delay(500);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
   
}


void normal_cycle(bool cycle){
  
  while(cycle && digitalRead (stopp)== LOW){
     if (digitalRead(CL) == HIGH ){
      Serial.println("CLLLL");
      break;  
    }
    else if(digitalRead (stopp) == HIGH) {
      Serial.println("ssssssssssssssssssssss");
   
      _stop =true;
     
      break;
    }else {
     //stop_translation();
    translation_to_cl();
    }
  }
}

void init_cycle() {
  while(digitalRead(CR) == LOW && digitalRead (stopp) == LOW ) {
    
    if (digitalRead(CR) == HIGH ){
      Serial.println("CRRRRRRRRRRR");
      break;  
    }
    else if(digitalRead (stopp) == HIGH) {
      Serial.println("ssssssssssssssssssssss");
      
      _stop =true;
     
      break;
    }else {
     //stop_translation();
    translation_to_cr();
    }
  }
}

  
void loop() {      // put your main code here, to run repeatedly:

  verin_command();
  if (digitalRead(start)== HIGH) {
    _start = true;
    
  }else {
    ;
  }
  while (_start) {
    int diff_translation = digitalRead(CR) - digitalRead(CL);
    
    bool cycle = false;
    _stop = false;
    switch (diff_translation){
     
      case 1:

          forward_step();
          cycle = true;
          normal_cycle(cycle);
        
        break;
      case  -1 :
        
        forward_step();
        init_cycle();
        break;
      default:
      
      init_cycle();
      //stop_translation();
      
      break;     
    }
    if (_stop){
      _start = false;
      break;
    }

    }
     stop_all();
      
 
  }
    
  
  

    
  

  

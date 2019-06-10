#define D1 3            // verin sens 1 (up)
#define D2 4            // verin sens 2 (down)
#define D3 5            // translation_right_left
#define D4 6            // translation_left_right
#define D5 7            // helice 1   >> helice 1 and helice not same sense !
#define D6 8            // helice 2

#define D7 9            // tapis_motor_right  sens 1 (forward)
#define D8 10           // tapis_motor_right  sens2  (backward)
#define D9 11           // tapis motor_left   sens1  (forward)
#define D10 12          // tapis motpr_right  sens 2 (backward)
#define D11 13          // disque de lisage

#define start A0        // start_cycle_button
#define stopp 2         // stop_cycle_button retrun config verin
#define stop_rec A5     // stop_rec stop and backward
#define verin_up A1     // up_verin_button
#define verin_down A2   // down_verin_button
#define CR A3           // sensor_trans_right
#define CL A4           // sensor-trans_left
#define _5s   5000      // 5 seconds 
#define _2s   2000      // 2 seconds
#define DEBUG 1         // for DEBUGING 1 DEBUG 0 not DEBUG,  => still not all implemented
int pins[] = {D1, D2, D3, D4, D5, D6, D7, D8 , D9, D10, D11}; // arry stores Relays
bool _start = false;     // variable start 
bool _stop = false;      // variable stop
bool _stop_rec = false;  // variable stop_rec
void setup() {           // put your setup code here, to run once:
    
    #if DEBUG            // if DEBUG 1
    Serial.begin(9600);  // start serial 
    Serial.print(sizeof(pins)/sizeof(pins[0]));          // the length of the pins
    #endif
    
    for (byte i =0; i < sizeof(pins)/sizeof(pins[0]); i++) { // set all Relays as OUTPUTs
      pinMode(pins[i], OUTPUT);
    }
    
    pinMode(stopp, INPUT);  // set stopp  as INPUT
    delay(_2s/1);           // delay 1s
  
}

void verin_command() {   // reglage de verin

  int dif_verin = digitalRead(verin_up) - digitalRead(verin_down); // read v1 & v2 states 
  switch (dif_verin) {
    case 1 : 
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      #if DEBUG
      Serial.println("Verin vers le haut");
      #endif
      break;
    case -1 : 
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
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


void stop_all(){  // switch off all Relays 
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);
}


void stop_translation() {  // switch off only translation (reglage)
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  delay(500);
}

void translation_to_cl() { // HELPER: function defines the translation from right to left
  // translation motor sens1
  if (digitalRead(stopp == LOW) && digitalRead(stop_rec == LOW)){
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  
  // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);

  //lisageDisue
   digitalWrite(D11, HIGH);
  }
}
void translation_to_cr() { // HELPER: function defines the translation from left to right
  if(digitalRead(stopp == LOW) && digitalRead(stop_rec == LOW)){
  // translation motor to right
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  
  // helices truns
   digitalWrite(D5, HIGH);
   digitalWrite(D6, HIGH);
    //lisageDisue
   digitalWrite(D11, HIGH);
}
}


void forward_step() {  // robot forward a step
  stop_translation();
  digitalWrite(D8,HIGH);
  digitalWrite(D10,HIGH);
  delay(500);
  digitalWrite(D8,LOW);
  digitalWrite(D10,LOW);
}

void backward_stop() {
  digitalWrite(D7, HIGH);
  digitalWrite(D9, HIGH);
  
   // helices truns
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
    //lisageDisue
  digitalWrite(D11, HIGH);
  delay(1000);
  
  // stop tapis + translation (reclage)
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  digitalWrite(D9,LOW);
  digitalWrite(D10,LOW);
  // check if the verin in its initial position
  while (digitalRead(verin_up) == LOW) {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    if (digitalRead(verin_up) == HIGH) {
      stop_all();
      break;
    }
 }
}


void normal_cycle(bool cycle){  // function defines the normal_cycle right to left 
  
  while(cycle && digitalRead (stopp)== LOW && digitalRead(stop_rec) == LOW){
    
     if (digitalRead(CL) == HIGH ){
      //Serial.println("CLLLL");
      break;
    }
     if(digitalRead (stopp) == HIGH) {
      //Serial.println("stop");
   
      _stop =true;
     break;
      
     }

     if (digitalRead(stop_rec) == HIGH) {
      _stop_rec = true;
      break;
     }
    
     translation_to_cl();
    }
  }


void init_cycle() {   // verifies if the CR is HIGH and set the robot to CR
  while(digitalRead(CR) == LOW && digitalRead (stopp) == LOW && digitalRead(stop_rec) == LOW ) {
    
    if (digitalRead(CR) == HIGH ){
      Serial.println("CRRRRRRRRRRR");
       break;
    }
     if(digitalRead (stopp) == HIGH) {
     Serial.println("stop");
      
      _stop =true;
     break;
    
    }
    if(digitalRead(stop_rec) == HIGH){
      _stop_rec = HIGH;
      break;
    }
    translation_to_cr();
    }
  }

void loop() {                          // put your main code here, to run repeatedly:

  verin_command();                    // configure verin
  if (digitalRead(start)== HIGH) {    // check if the start button is preesed 
    _start = true;                    // if YES _start = true
  }else {                             // if NO do nothing
    ;
  }
  while (_start) {                          // as _start = true run 
    int diff_translation = digitalRead(CR) - digitalRead(CL); // check the values of CR and CL
    bool cycle = false;
    _stop = false;
    _stop_rec = false;
    switch (diff_translation){
     
      case 1:               // CR is pressed and CL is not pressed = > ROBOT is on the RIGHT 

          forward_step();   // one step forward
          cycle = true;     // to check if its the normal_step
          normal_cycle(cycle);
        
        break;
      case  -1 :          // CR is not pressed and RL is not pressed => ROBOT is on the LEFT
        
        forward_step();   // one step forward
        init_cycle();     // return to RIGHT
        break;
      default:     // if ROBOT is on the middle or when CR and CL are BOTH pressed !!! 
       
      init_cycle();
      //stop_translation();
      
      break;     
    }
    if (_stop == HIGH){        // if the STOP button is pressed 
      _start = false;
     break;
    }

    if (_stop_rec == HIGH) {   // if the STOP_REC is pressed 
      
      backward_stop();         // backawrd and reaction 
      _start = false;
      break;
    }

    }
     stop_all();              // stop all motors
      
  }
    
  
  

    
  

  

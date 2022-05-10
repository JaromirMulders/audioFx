#define CLOCKPINEFFECT 4
#define CLOCKPINTYPE   2

#define RESETPINEFFECT 6
#define RESETPINTYPE   7

#define BUTTONPIN      5

#define TYPELEDPIN     8
#define POT1LEDPIN     9
#define POT2LEDPIN     10
#define POT3LEDPIN     11


char potBuffer[5]; //char array for sending data
int effectButton = 0;

int effectNumber = 0;
int typeNumber = 0;

int pickup = 0;
int potPickup[3] = {0,0,0};

int effectMem[4] = {0,0,0,0};

int potMem1[3] = {0,0,0};
int potMem2[3] = {0,0,0};
int potMem3[3] = {0,0,0};
int potMem4[3] = {0,0,0};

void setup() {
  Serial.begin(9600);

  //initialsing pins
  pinMode(CLOCKPINEFFECT,OUTPUT);  
  pinMode(CLOCKPINTYPE,OUTPUT);
  pinMode(RESETPINEFFECT,OUTPUT);
  pinMode(RESETPINTYPE,OUTPUT);
  pinMode(BUTTONPIN,INPUT_PULLUP);
  pinMode(TYPELEDPIN,OUTPUT);
  pinMode(POT1LEDPIN,OUTPUT);
  pinMode(POT2LEDPIN,OUTPUT);
  pinMode(POT3LEDPIN,OUTPUT);

  //initialsing cd4017 Chips reset to step 1
  digitalWrite(RESETPINEFFECT, HIGH);
  digitalWrite(RESETPINEFFECT, LOW);
  digitalWrite(RESETPINTYPE, HIGH);
  digitalWrite(RESETPINTYPE, LOW);
  
}

void loop()
{

/*
potBuffer[0] = (analogRead(0) / 8) | 128; //setting identiefier for beginning of list
for(int i = 1; i <= 2; i++){
  potBuffer[i] =  analogRead(i) / 8;
}
*/

checkButtons();
potMem();

if(effectNumber == 0){
  potBuffer[0] = potMem1[0] | 128;
  for(int i = 1; i <= 2; i++){
    potBuffer[i] = potMem1[i];
  }
}
else
if(effectNumber == 1){
  potBuffer[0] = potMem2[0] | 128;
  for(int i = 1; i <= 2; i++){
    potBuffer[i] = potMem2[i];
  }
} else  
if(effectNumber == 2){
  potBuffer[0] = potMem3[0] | 128;
  for(int i = 1; i <= 2; i++){
    potBuffer[i] = potMem3[i];
  }
} else 
if(effectNumber == 3){
  potBuffer[0] = potMem4[0] | 128;
  for(int i = 1; i <= 2; i++){
    potBuffer[i] = potMem4[i];
  }
}  


typeNumber = analogRead(3) / 255; //reading selector potentiometer

if (pickup == 0){ // if selector pot is not at the stored value dont pickup value
  digitalWrite(TYPELEDPIN,LOW);
  
  if(effectMem[effectNumber] == typeNumber){
    pickup = 1;
  }
}else { // if selector pot is at stored value pickup value
  digitalWrite(TYPELEDPIN,HIGH);
  
  if(effectMem[effectNumber] != typeNumber){
    effectMem[effectNumber] = typeNumber;
    digitalWrite(RESETPINTYPE, HIGH);
    digitalWrite(RESETPINTYPE, LOW);         
    for(int i = 0;i < effectMem[effectNumber]; i++){ // multiple pulses for cd4017 chips
      digitalWrite(CLOCKPINTYPE,HIGH);
      digitalWrite(CLOCKPINTYPE,LOW);
    }
  }
   
}

potBuffer[3] = effectNumber;
potBuffer[4] = effectMem[effectNumber];

Serial.write(potBuffer,5);
}

void checkButtons()
{
effectButton = digitalRead(BUTTONPIN);
static int oldValue = effectButton;

//effectButton
if(effectButton != oldValue){
  oldValue = effectButton;
 
  
  digitalWrite(CLOCKPINEFFECT, LOW);
  pickup = 0; //reset Pickup mode for leds   
  digitalWrite(RESETPINTYPE, HIGH);
  digitalWrite(RESETPINTYPE, LOW);         
  for(int i = 0;i < effectMem[effectNumber]; i++){ //set leds to memmory location
    digitalWrite(CLOCKPINTYPE,HIGH);
    digitalWrite(CLOCKPINTYPE,LOW);    
  } 
    
  if(effectButton == 0){  
    effectNumber++;  
     
    
    digitalWrite(POT1LEDPIN, LOW);
    digitalWrite(POT2LEDPIN, LOW);     
    digitalWrite(POT3LEDPIN, LOW);      

    for(int i = 0; i <= 2; i++){
      potPickup[i] = 0;
    }
     
    if(effectNumber > 3){
      effectNumber = 0;
      digitalWrite(RESETPINEFFECT, HIGH);
      digitalWrite(RESETPINEFFECT, LOW);
    } else {
      digitalWrite(CLOCKPINEFFECT, HIGH); 
    }
     
  }
 
}
  
  //potBuffer[3] = effectNumber;
 
}

void potMem(){
  
  //potmem1
  if(effectNumber == 0) {      
    
    for(int i = 0; i <= 2; i++){
      if(analogRead(i) / 8 == potMem1[i]){
        potPickup[i] = 1;
      }
    }
    if(potPickup[0] == 1){
      potMem1[0] = (analogRead(0) / 8);
      digitalWrite(POT1LEDPIN, HIGH);
    }
    if(potPickup[1] == 1){
      potMem1[1] = (analogRead(1) / 8); 
      digitalWrite(POT2LEDPIN, HIGH);  
    }
    if(potPickup[2] == 1){
      potMem1[2] = (analogRead(2) / 8); 
      digitalWrite(POT3LEDPIN, HIGH);      
    }

  } else

  //potmem2
  if(effectNumber == 1) {      
    
    for(int i = 0; i <= 2; i++){
      if(analogRead(i) / 8 == potMem2[i]){
        potPickup[i] = 1;
      }
    }
    if(potPickup[0] == 1){
      potMem2[0] = (analogRead(0) / 8);
      digitalWrite(POT1LEDPIN, HIGH);
    }
    if(potPickup[1] == 1){
      potMem2[1] = (analogRead(1) / 8); 
      digitalWrite(POT2LEDPIN, HIGH);   
    }
    if(potPickup[2] == 1){
      potMem2[2] = (analogRead(2) / 8); 
      digitalWrite(POT3LEDPIN, HIGH);      
    }

  } else
  
  //potmem3
  if(effectNumber == 2) {      
    
    for(int i = 0; i <= 2; i++){
      if(analogRead(i) / 8 == potMem3[i]){
        potPickup[i] = 1;
      }
    }
    if(potPickup[0] == 1){
      potMem3[0] = (analogRead(0) / 8);
      digitalWrite(POT1LEDPIN, HIGH);
    }
    if(potPickup[1] == 1){
      potMem3[1] = (analogRead(1) / 8); 
      digitalWrite(POT2LEDPIN, HIGH);    
    }
    if(potPickup[2] == 1){
      potMem3[2] = (analogRead(2) / 8); 
      digitalWrite(POT3LEDPIN, HIGH);      
    }

  } else

  //potmem4
  if(effectNumber == 3) {      
    
    for(int i = 0; i <= 2; i++){
      if(analogRead(i) / 8 == potMem4[i]){
        potPickup[i] = 1;
      }
    }
    if(potPickup[0] == 1){
      potMem4[0] = (analogRead(0) / 8);
      digitalWrite(POT1LEDPIN, HIGH);
    }
    if(potPickup[1] == 1){
      potMem4[1] = (analogRead(1) / 8); 
      digitalWrite(POT2LEDPIN, HIGH);    
    }
    if(potPickup[2] == 1){
      potMem4[2] = (analogRead(2) / 8); 
      digitalWrite(POT3LEDPIN, HIGH);      
    }

  }  
  
}

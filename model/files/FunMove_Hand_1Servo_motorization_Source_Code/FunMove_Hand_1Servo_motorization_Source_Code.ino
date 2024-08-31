
#include <Servo.h>
Servo servoM1;

int m1=10; // servomotor pin num
int fsr_base=0; // FSR base value
int fsr_read=0; // FSR value
int fsr_sum=0; //  FSR read sum
int fsr_average=0;


int fsr_array_num=10; // FSR value array size
int fsr_array[10];

int i,x,y,z=0;
char action; // finger motion selection


void setup() {
  Serial.begin(9600);
  
  servoM1.attach(m1);

  pinMode (6,INPUT_PULLUP); // Mode selection Switch
  pinMode (13,OUTPUT); // LED indicator(Mode)

 
  action = 'E';  // finger extension signal
  motion();
  calibration(); // average FSR value setting

}

void loop() {
  if (digitalRead(6)==0){calibration();}
  
  fsr_read = analogRead(A0);
  x=(fsr_average - fsr_read)/fsr_average;     // FSR err -> re read
  if (x>0.5) {                          
    delay(1);
    fsr_read=analogRead(A0);
  }                                          //
  
  i++;                                          // ** Smoothing Method **
  if (i>fsr_array_num-1) {i=0;}                 //  FSR read -> array 
  fsr_sum=fsr_sum - fsr_array[i] + fsr_read;    //
  fsr_array[i]=fsr_read;                        //
  fsr_average=fsr_sum/fsr_array_num;            //
  
  x=map(fsr_average,fsr_base,fsr_base+250,0,180);
  x=x/15;
  x=x*15;
  
  if (x>=75){
    action='G';
    motion();
  }
  if (x<30){
    action='E';
    motion();
  }
  
  Serial.println("FSR base:" + String(fsr_base) + "  FSR read:"+ String(fsr_read)+"  correction:" + String(x) +" motion:"+String(action)+"avr: "+String(fsr_average));
}

void motion(){

  switch(action) {
    case 'G':  // grasp
       servoM1.write(170); 
       break;
   
       
    case 'E':  //extension
       servoM1.write(20);
      break; 
  }

}

void calibration(){                               // FSR_base value setting
  for (i=0; i<fsr_array_num; i++){
    fsr_read=analogRead(A0);
    
    x=(fsr_average - fsr_read)/fsr_average;
    if (x>0.5) {                               // FSR err -> re read
    delay(1);
    fsr_read=analogRead(A0);
    }
    
    fsr_sum=fsr_sum - fsr_array[i] + fsr_read;
    fsr_array[i]=fsr_read;
    fsr_average=fsr_sum/fsr_array_num;
  }
  fsr_base=fsr_average;
}


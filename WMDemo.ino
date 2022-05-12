// This code was written by William Herse, Ben Matsumaoto and Sarah Askey
//-----------------------------------------------------//
//Define all constants
#define PWMA 9
#define PWMB 10
#define PWMin1 5
#define CPR 12
#define Gearing 99
#define K 5
#define interruptPin 2
#define interruptPin2 3
#define LEDPin 7
#define SuperPin 13

// Define Global Variables
int pwm_value1;
int pwm = 50;
int superstate;
int state = 0;

// Declare function at start so it has scope during setup function
void PWM(int pwm);

//------------------------- setup routine ----------------------------//
void setup() {
  pinMode(PWMA, OUTPUT);          // output PWMA to Q1
  pinMode(PWMB, OUTPUT);          // output PWMB to Q2
  pinMode(PWMin1, INPUT);         // input for reading the encoder
  pinMode(interruptPin, INPUT);   // Set first interrupt pin to input
  pinMode(interruptPin2, INPUT_PULLUP);   // Set second interrupt pin to input
  pinMode(LEDPin, OUTPUT);        // Set emergency LED pin to output
  pinMode(SuperPin, INPUT);       // input for reading superstate value
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink1, FALLING); // Assign interrupt one to run function Blink
  attachInterrupt(digitalPinToInterrupt(interruptPin2), ESTOP, CHANGE);  // Assign interrupt two to run function ESTOP
  Serial.begin(115200);   //Intialise Serial at a baud rate of 1152000

  analogWrite(PWMA, 0);          // let PWMA=0
  analogWrite(PWMB, 0);          // let PWMB=0
  digitalWrite(LEDPin, LOW);     // Set the LEDPin to low
  

  TCCR1A = 0; // clear Timer1 control register TCCR1A & B
  TCCR1B = 0; 
  TCNT1 = 0; // clear Timer1 counter register

  TCCR1B |= _BV(CS11); //set prescaler=8 by lettin the bit value of CS11=1 in register TCCR1B, so the clock frequency=16MHz/8=2MHz
  ICR1 = 100;//  phase correct PWM. PWM frequency determined by counting up 0-100 and counting down 100-0 in the input compare register (ICR1), so freq=200*0.5us=10kHz 
}

//------------------------- main loop ----------------------------//
void loop() 
{
superstate = digitalRead(SuperPin);


// At start of loop check for which superstate and state
  if (!superstate) {
    // superstate is 0, run function acording to state
    if (state == 0){
      stopp();
    } else if (state ==1){
      wash();
    } else if (state ==2){
      spin();
    } else if (state ==3){
      dry();
    }
    
  } else {
    // superstate is 1 (closed loop)
    // Run controller to target speed
    // set target encoder value to 620
    
    int targ = 900;

    // Retreiver PWM value from controller
    pwm = controller(targ, pwm);
    
    // Run motor at controller value
    PWM(pwm);

    delay(100);
  }
}

// Function for dry state, Speeds up and spins one direction before slowing back down
void dry()
{
  for (int i = 57; i < 100; i++) {
    PWM(i);
    delay(100);
  }
  
  delay(7000);
  
  for (int i = 99; i > 57; i--) {  
    PWM(i);
    delay(100);
  }
}

// Function for stop, does not spin
void stopp(){
  pwm = 50;
  PWM(pwm);
  delay(1000);
}

// Function for wash, Spins fast one direction and then slows before repeating in the other direction
void wash(){
  PWM(80);
  delay(1000);
  PWM(60);
  delay(1000);
  PWM(20);
  delay(1000);
  PWM(40);
  delay(1000);
}

// Function for rinse, spins fast in one direction and then rapidly changes to spining fast in the other direction
void spin(){
  PWM(5);
  delay(1500);
  PWM(95);
  delay(1500);
}

// Function for the closed loop controller
int controller(int targ, int pwm){
  // Set curr to the current encoder value
  int curr =  pulseIn(PWMin1, HIGH);

  // Print to serial the PWM and the current encoder value
  Serial.println(pwm);
  Serial.println(curr);

  // If current = 0, the motor is currently not spining
  if (curr == 0) {
    // check if motor at limit
    if (pwm < 99) {
      // increase PWM by 5 so that the motor can ;build the potential to spin
      return pwm + 5;
    } else {
      return pwm
    }

  // If the current encoder value is larger then the target value, increase the pwm to decrease the encoder value
  }else if (curr > targ) {
    return pwm + 1;   

  // If the current encoder value is smaller then the target value, decrease the pwm to increase the encoder value
  } else if (curr < targ) {
    return pwm - 1;
  }
}

// Interrupt used to change state
void blink1(){
  // only change state if in open loop
  if (superstate == 0){
    
    //Iterate to next state
    if (state == 3){
      state = 0;
    } else {
      state += 1;
    }
    
    //Print the current state
    Serial.println("State");
    Serial.println(state);
  }
}

// Emergency stop function
void ESTOP(){
  //stop the motor
  PWM(50);
  // Turn LED on
  digitalWrite(LEDPin, HIGH);
  // Print to serial
  Serial.println("EMERGENCY STOP! PLEASE RESET!");

  // Loop forever
  while(1){

  }
}


//------------------------- subroutine PWM generate complementary PWM from OCR1A and OCR1B ----------------------------//
void PWM(int pwm)
{
  int temp = (int)pwm;
  temp = constrain(temp,1,99);

  OCR1A = temp; //duty of PWM for pin9 is from output compare register A 
  TCCR1A |= _BV(COM1A1) | _BV(COM1A0); //set output to low level

  OCR1B = temp;//duty of PWM for pin10 is from output compare register B
  TCCR1A |= _BV(COM1B1); //set output to high level

  TCCR1B |= _BV(WGM13); //
  TCCR1A |= _BV(WGM11); //Set ICR1 phas correct mode
}

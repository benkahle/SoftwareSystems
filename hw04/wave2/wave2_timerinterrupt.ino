/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
//#include <Tone2.cpp>
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;
int toggle0 = 0;
int toggle1 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
 DDRD = B11000000;
 DDRB = B00111111;
 
 cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  // Change this value to adjust frequency of interrupt
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  sei();
}

int high = 255;
int low = 36;
int button1;
int button2;

//timer0 interrupt
ISR(TIMER0_COMPA_vect){
  button1 = digitalRead(buttonPin1);
  button2 = digitalRead(buttonPin2);
  if(toggle0){
    writeByte(high);
    toggle0 = 0;
  }
  else{
    writeByte(low);
    toggle0 = 1;
  }
}

//Writes value of x across digital pins 6-13, one bit for each pin.
void writeByte(int x) {
  int d = B11000000 | (x<<6);
  int b = B00111111 | (x>>2);
  PORTB = b;
  PORTD = d;
}

int stride = 1;
int counter = low;

void loop() {
}

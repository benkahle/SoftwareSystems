/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
#include "waveforms.h"
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;
int toggle0 = 0;
int toggle1 = 0;
volatile int wave0 = 0, wave1 = 0;

void setup() {
  Serial.begin(9600);
  
  //pinMode(buttonPin1, INPUT_PULLUP);  
  //pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  attachInterrupt(buttonPin1, wave0Select, RISING);  // Interrupt attached to the button connected to pin 2
  attachInterrupt(buttonPin2, wave1Select, RISING);  // Interrupt attached to the button connected to pin 3
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
int i = 0;

// function hooked to the interrupt on digital pin 2
void wave0Select() {
  wave0++;
  if(wave0 == 4)
    wave0 = 0;
}

// function hooked to the interrupt on digital pin 3
void wave1Select() {
  wave1++;
  if(wave1 == 4)
    wave1 = 0;
}

//timer0 interrupt
// ISR(TIMER0_COMPA_vect){
//   writeByte(waveformsTable[wave0][i]);
//   i++;
//   if(i == maxSamplesNum)  // Reset the counter to repeat the wave
//     i = 0;
// }

//Writes value of x across digital pins 6-13, one bit for each pin.
void writeByte(int x) {
  int b = B11000000 | (x>>8);
  int d = B00111111 | x;
  PORTB = b;
  PORTD = d;
}

void loop() {
  writeByte(waveformsTable[wave0][i]);
  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;
  delayMicroseconds(100);
}

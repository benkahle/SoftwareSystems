/*
Example code from Head First C for HW 1 

Copyright 2014 Ben Kahle
License: GNU GPLv3
*/
#include <stdio.h>
#include <stdlib.h>

/*
  Prompts the user for input grabs the first 2 characters and sets the card_name equal to them.
  card_name: pointer to a character array.
*/
void get_input(char *card_name) {
  puts("Enture the card_name");
  scanf("%2s", card_name);
}

/*
  Takes a string input and returns an integer with the equivalent value of that string.
  card_name: A pointer to the string which is to be checked for equivalent value
  val: A pointer to the integer value
*/
void check_input(char* card_name, int* val) {
  switch(card_name[0]) {
  case 'K':
  case 'Q':
  case 'J':
    *val = 10;
    break;
  case 'A':
    *val = 11;
    break;
  case 'X':
    *val = -1;
    break;
  default:
    *val = atoi(card_name);
    if (*val < 1 || *val > 10) {
      puts("I don't understand that value");
      *val = 0;
    }
  }
}

/*
  Increments or decrements the counter appropriately given the value
  val: A pointer to an integer representing the value of the inputted card
  counter: A pointer to an integer keeping track of the count
*/
void set_counter(int *val, int *count) {
  if (*val > 2 && *val < 7) {
    ++*count;
  } else if (*val == 10) {
    --*count;
  }
  printf("Current count: %i\n", *count);
}

/*
  Main loop for the card counting program.
  Provides an exit condition and error handling for invalid input.
*/
int main() {
  char card_name[3];
  int val = 0;
  int count = 0;
  while (1) {
    get_input(card_name);
    check_input(card_name, &val);
    if (val == -1) {
      //escape sequence "X" submitted
      break;
    } else if (val == 0) {
      //input not understood
      continue;
    }
    set_counter(&val, &count);
  } 
  return 0;
}
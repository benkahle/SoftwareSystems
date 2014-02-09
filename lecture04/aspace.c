/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int global;

void add_stack() 
{
  int local;
  printf("%p\n", (void *)&local);
}

int main ()
{
  srand(time(NULL));
  int r = rand() % 32;
  int local = 5;
  void *p = malloc(128);
  void *a = malloc(256);
  void *b = malloc(512);

  void *d = malloc(r);
  void *e = malloc(r);

  printf ("Address of main is %p\n", (void *)main);
  printf ("Address of global is %p\n", (void *)&global);
  printf ("Address of local is %p\n", (void *)&local);
  printf ("Address of p is %p\n", p);
  printf("Address of local variable from another function is: ");
  add_stack();
  printf("Address of a is %p\n", a);
  printf("Address of b is %p\n", b);
  printf("%i\n", r);
  printf("Address of d is %p\n", d);
  printf("Address of e is %p\n", e);

  return 0;
}

/*
Hello world file for Glib demonstrating compilation and basic use.
*/

#include <glib.h>
#include <glib/gprintf.h>

int main()
{
  g_printf("Hello %s", "world!\n");
  return 0;
}
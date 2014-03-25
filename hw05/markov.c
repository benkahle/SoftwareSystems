/*
Hello world file for Glib demonstrating compilation and basic use.
*/
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <fcntl.h>

GScanner* make_scanner(char* filename){

  int fd = g_open(filename, O_RDONLY, NULL);
  if (fd == -1){
    g_printf("Error occur while opening %s\n.", filename);
    exit(1);
  }
  GScanner* scanner = g_scanner_new(NULL);
  scanner->input_name = filename;
  g_scanner_input_file(scanner, fd);
  scanner->config->scan_identifier_1char = 1;
  scanner->config->cset_skip_characters = " \t\r\n\"\'?.-()!";
  return scanner;
}

void insert_word(char *key, GHashTable* table) {
  int* val;
  char* low_key = g_string_ascii_down(g_string_new(key))->str;
  val = (int*)g_hash_table_lookup(table, low_key);
  if (val == NULL) {
    //g_printf("Val is null\n");
    val = malloc(sizeof(int));
    *val = 1;
    g_hash_table_insert(table, g_strdup(low_key), val);
  } else {
    //g_printf("initial val: %i\n", *val);
    *val += 1;
    g_hash_table_insert(table, g_strdup(low_key), val);
    //g_printf("post val: %i\n", *(int *)(g_hash_table_lookup(table, key)));
  }
}

void parse_file(GScanner *scanner, GHashTable* table) {
  char *key;
  int i = 0;
  while (1) {
    g_scanner_get_next_token(scanner);
    if (scanner->token == G_TOKEN_EOF) break;
    if (scanner->token == G_TOKEN_IDENTIFIER) {
      if (scanner->value.v_string != NULL) {
        g_printf("string: %s\n", scanner->value.v_string);
        insert_word(scanner->value.v_string, table);
        i++;
      }
    }
  }
  g_printf("Word Count: %i\n", i);
}

void print_results(char* key, int* val, void* data) {
  g_printf("Words: %s --> %i\n", key, *val);
}

static void free_key_value(gpointer key, gpointer value, gpointer user_data) {
  g_free(key);
  g_free(value);
}

int main(int argc, char const *argv[])
{
  char *filename = NULL;
  if (argc > 1) {
    size_t len = strlen(argv[1]);
    filename = malloc(len+1);
    g_stpcpy(filename, argv[1]);
    g_printf("Parsing file %s\n", argv[1]);
  } else {
    g_printf("Please provide a filename to parse.\n");
    return 0;
  }

  void (*free_value)(int*);
  void (*free_key)(char*);
  GHashTable* table = g_hash_table_new(g_str_hash,g_str_equal);
  //TODO: Put make_scanner inside parse_file
  GScanner* scanner = make_scanner(filename);
  parse_file(scanner, table);
  //TODO: remove Scanner;
  void (*print_keys)(char*, int*, void*);
  print_keys = print_results;
  int* testcount = g_hash_table_lookup(table, "a");
  g_printf("test: %i\n", *testcount);
  g_hash_table_foreach(table, (GHFunc) print_keys, NULL);
  g_hash_table_foreach(table, free_key_value, NULL);
  g_hash_table_destroy(table);
  return 0;
}
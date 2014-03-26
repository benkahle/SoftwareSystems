/*
Hello world file for Glib demonstrating compilation and basic use.
*/
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <fcntl.h>

/*
Creates a GScanner to parse the given file. Configures the Scanner to find all whole words.
@param {char *} filename - path of the file to parse
@returns {GScanner *} - pointer to the GScanner struct
*/
GScanner* make_scanner(char* filename){
  int fd = g_open(filename, O_RDONLY, NULL);
  if (fd == -1){
    g_printf("Error occur while opening %s\n.", filename);
    exit(1);
  }
  GScanner* scanner = g_scanner_new(NULL);
  if (scanner == NULL) {
    g_printf("Scanner not created, allocation failed.\n");
    exit(1);
  }
  scanner->input_name = filename;
  g_scanner_input_file(scanner, fd);
  scanner->config->scan_identifier_1char = 1;
  scanner->config->cset_skip_characters = " \t\r\n\"'?.-()!";
  scanner->config->cset_identifier_first = G_CSET_a_2_z G_CSET_A_2_Z;
  scanner->config->cset_identifier_nth = G_CSET_a_2_z G_CSET_A_2_Z;
  scanner->config->scan_string_sq = 0;
  scanner->config->scan_string_dq = 0;
  return scanner;
}

/*
Inserts a given word into the given hash table or increments the value if the word already exists.
@param {char *} key - string to insert into table
@param {GHashTable *} table - GHashTable object in which to store the string->count pairs
*/
void insert_word(char* key, GHashTable* table) {
  int* val;
  char* low_key = g_string_ascii_down(g_string_new(key))->str;
  val = (int*)g_hash_table_lookup(table, low_key);
  if (val == NULL) {
    val = malloc(sizeof(int));
    *val = 1;
    g_hash_table_insert(table, g_strdup(low_key), val);
  } else {
    *val += 1;
    g_hash_table_insert(table, g_strdup(low_key), val);
  }
}

/*
Parses a given file with a GScanner and stores a word count in the given GHashTable
@param {char *} filename - path of the file to parse
@param {GHashTable *} table - hash table in which to store the word counts
*/
void parse_file(char* filename, GHashTable* table) {
  GScanner* scanner = make_scanner(filename);
  char *key;
  int i = 0;
  while (1) {
    g_scanner_get_next_token(scanner);
    if (scanner->token == G_TOKEN_EOF) break;
    if (scanner->token == G_TOKEN_IDENTIFIER) {
      if (scanner->value.v_string != NULL) {
        //g_printf("string->%s\n", scanner->value.v_string);
        insert_word(scanner->value.v_string, table);
        i++;
      }
    }
  }
  g_printf("Total Word Count: %i\n", i);
  g_scanner_destroy(scanner);
}

/*
Prints a key/value pair - used as a callback by a call to g_hash_table_foreach()
@param {char *} key - key in a hashtable
@param {int *} val - value in a hashtable
@param {void *} data - additional data provided at calltime
*/
void print_results(char* key, int* val, void* data) {
  g_printf("Words: %s --> %i\n", key, *val);
}

/*
Deletes all internal memory within a hash table - used as a callback by a call to g_hash_table_foreach()
@param {gpointer} key - key in a hashtable
@param {gpointer} val - value in a hashtable
@param {gpointer} data - additional data provided at calltime
*/
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
  GHashTable* table = g_hash_table_new(g_str_hash,g_str_equal);
  if (!table) {
    g_printf("Failed to create table, allocation failure.\n");
    exit(1);
  }
  parse_file(filename, table);
  g_hash_table_foreach(table, (GHFunc) print_results, NULL);
  g_hash_table_foreach(table, free_key_value, NULL);
  g_hash_table_destroy(table);
  return 0;
}
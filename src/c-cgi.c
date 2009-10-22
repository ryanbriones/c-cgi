#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Param {
  char         *key;
  char         *value;
  struct Param *next;
} *requestParams, *requestParamsTail;

void parse_params(void);
char *get_param(char *);
void *malloc_param(char *, char *);

int main(void) {
  printf("Content-Type: text/plain\n\n");
  printf("Hello, World.\n");

  parse_params();
  printf("foo: %s\n", get_param("foo"));
  printf("baz: %s\n", get_param("baz"));
}

void parse_params(void) {
  char *query_string, *current_pair, *current_key, *current_value;
  int chars_read_for_pair, chars_read_for_part;
  struct Param *current_param;
  
  query_string = getenv("QUERY_STRING");

  current_pair = malloc( strlen(query_string) + 1 );
  while( sscanf(query_string, "%[^&]%n", current_pair, &chars_read_for_pair) == 1 ) {
    
    current_key = malloc( strlen(current_pair) + 1 );
    sscanf(current_pair, "%[^=]=%n", current_key, &chars_read_for_part);
    current_pair += chars_read_for_part;
    
    current_value = malloc( strlen(current_pair) + 1 );
    sscanf(current_pair, "%s", current_value);
    
    current_param = malloc_param( current_key, current_value );

    if(NULL == current_param) {
      printf("Out of memory.");
      exit(0);
    }

    current_param->key = current_key;
    current_param->value = current_value;

    if(requestParams == NULL) {
      requestParams = current_param;
    } else {
      requestParamsTail->next = current_param;
    }
    
    requestParamsTail = current_param;
    current_param->next = NULL;

    query_string += chars_read_for_pair;
    if(*query_string == '&') {
      ++query_string;
    }
  }
}

void *malloc_param(char *key, char *value) {
  return malloc( strlen(key) + strlen(value) + sizeof(void *) );
}

char *get_param(char *key) {
  struct Param *current_param = requestParams;

  for(; current_param != NULL; current_param = current_param->next) {
    if(strcmp(current_param->key, key) == 0) {
      return current_param->value;
    }
  }

  return NULL;
}

/**
 * helpers.c
 *
 * Implementation of the helper functions
 *
 * Author: Dennis J. McWherter, Jr. <dennis@deathbytape.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

/* Private globals for parsed object */
static parsed_graph_t graph;

/* Private globals for string building */
static char* regStr = NULL;
static int rsLen = 0;
static int rsCap = 0;

/** Parsed object helpers */
static void pg_insert(parsed_obj_t* obj) {
  if (obj == NULL) {
    return ;
  }
  if (graph.len >= graph.cap) {
    graph.cap *= 2;
    graph.links = realloc(graph.links, graph.cap * sizeof(parsed_obj_t*));
  }
  graph.links[graph.len++] = obj;
}

void pg_init() {
  graph.cap = 8;
  graph.len = 0;
  graph.links = malloc(graph.cap * sizeof(parsed_obj_t*));
}

void pg_destroy() {
  int i = 0;
  for (i = 0 ; i < graph.len ; ++i) {
    free(graph.links[i]->value);
    free(graph.links[i]);
  }
  free(graph.links);
  graph.links = NULL;
  graph.len = 0;
  graph.cap = 0;
}

void pg_insert_str(const char* str) {
  parsed_obj_t* obj = NULL;
  int len = 0;
  if (str != NULL) {
    len = strlen(str);
    obj = malloc(sizeof(parsed_obj_t));
    obj->type = STRING;
    obj->value = malloc((len + 1) * sizeof(char));
    strncpy(obj->value, str, len);
    ((char*)obj->value)[len] = '\0';
    pg_insert(obj);
  }
}

void pg_insert_int(int val) {
  parsed_obj_t* obj = malloc(sizeof(parsed_obj_t));
  obj->type = INT;
  obj->value = malloc(sizeof(int));
  *((int*)obj->value) = val;
  pg_insert(obj);
}

void pg_print_graph() {
  int i = 0;
  parsed_obj_t* obj = NULL;
  const char* str = NULL;
  const int* val = NULL;
  for (i = 0 ; i < graph.len ; ++i) {
    obj = graph.links[i];
    if (obj->type == STRING) {
      str = (const char*)obj->value;
      printf("%s", str);
    } else {
      val = (int*)obj->value;
      printf("%d", *val);
    }
  }
  printf("\n");
}

/** String helpers */
void str_update(char c) {
  static char val[2];
  val[0] = c;
  val[1] = '\0';
  str_update_str(val);
}

void str_update_str(const char* str) {
  int inLen = strlen(str);
  int newLen = rsLen + inLen;
  int limit = rsCap - 1;
  if (regStr == NULL) {
    rsLen = 0;
    rsCap = inLen + 1;
    regStr = malloc(rsCap * sizeof(char));
  } else if (newLen >= limit) {
    while (newLen >= limit) {
      rsCap *= 2;
      limit = rsCap - 1;
    }
    regStr = realloc(regStr, rsCap * sizeof(char));
  }
  strncat(regStr + rsLen, str, inLen);
  rsLen = newLen;
}

const char* str_get() {
  return regStr;
}

void str_clear() {
  rsLen = 0;
  if (regStr != NULL) {
    regStr[rsLen] = '\0';
  }
}

void str_free() {
  if (regStr != NULL) {
    free(regStr);
  }
  regStr = NULL;
  rsLen = 0;
  rsCap = 0;
}


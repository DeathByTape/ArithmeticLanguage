/**
 * arithlang.y
 *
 * arithmetic language yacc grammar definition and basic parser def.
 *
 * Author: Dennis J. McWherter, Jr. <dennis@deathbytape.com>
 */
%{
#include <stdio.h>
#include "helpers.h"

extern FILE* yyin;

int isInStr = 0;
char num[32];

void yyerror(const char* str) {
  fprintf(stderr, "Error: %s\n", str);
}

int yywrap() {
  return 1;
}

/** Main entry point to our parser. We are not compiling but interpreting, instead.
 * The interpreter is built into the grammar (i.e. pg_print_graph())
 */
int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: %s <file_to_execute>\n", argv[0]);
    return 1;
  }
  yyin = fopen(argv[1], "r");
  if (yyin == NULL) {
    fprintf(stderr, "Could not open file '%s': ", argv[1]);
    perror("");
    return 1;
  }
  pg_init();
  yyparse();
  pg_destroy();
  str_free();
  return 0;
}
%}

/* Define top-level label for grammar */
%start arithlang

/* Define stack members */
%union {
  int iVal;
  char cVal;
  const char* sPtr;
}

/* Define associativity and precedence */
%left ADD SUB
%left MUL DIV

/* Type declaration for non-terminals */
%type <iVal> exp

/* Specify tokens (i.e. terminals) */
%token NEWLINE
%token OPENPAREN
%token CLOSEPAREN
%token APPEND
%token PRINT
%token QUOTE
%token ESCAPE
%token <sPtr> WHITESPACE;
%token <iVal> NUM
%token <cVal> CHAR

%%
arithlang : /* Empty */
          | arithlang stmt  { pg_destroy(); pg_init(); } 
          | arithlang NEWLINE
          ;
stmt : append
     | PRINT append     { pg_print_graph(); } /* This is where we make the interpretation "observable" */
     ;
append : eval
       | append APPEND eval
eval : exp              { pg_insert_int($1); }
     | QUOTE str QUOTE  { isInStr = 0; pg_insert_str(str_get()); }
     ;
exp : NUM                       { $$ = $1; }
    | OPENPAREN exp CLOSEPAREN  { $$ = $2; }
    | exp DIV exp               { $$ = $1 / $3; }
    | exp MUL exp               { $$ = $1 * $3; }
    | exp ADD exp               { $$ = $1 + $3; }
    | exp SUB exp               { $$ = $1 - $3; }
    ;
str : /* Empty */       { isInStr = 1; str_clear(); } /* Always clear first */
    | str CHAR          { str_update($2); }
    | str WHITESPACE    { str_update_str($2); }
    | str NUM           { sprintf(num, "%d", $2); str_update_str(num); }
    | str ESCAPE QUOTE  { str_update('"'); }
    | str ADD           { str_update('+'); }
    | str SUB           { str_update('-'); }
    | str MUL           { str_update('*'); }
    | str DIV           { str_update('/'); }
    | str OPENPAREN     { str_update('('); }
    | str CLOSEPAREN    { str_update(')'); }
    | str ESCAPE ESCAPE { str_update('\\'); }
    | str APPEND        { str_update('@'); }
    | str PRINT         { str_update_str("print"); }
    ;
%%


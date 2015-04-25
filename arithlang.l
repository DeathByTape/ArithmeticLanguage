/**
 * arithlang.l
 *
 * Lexer definition for arithmetic language (toy language)
 *
 * Author: Dennis J. McWherter, Jr. <dennis@deathbytape.com>
 */
%{
#include "y.tab.h"
extern const int isInStr; /* Flag set in yacc to give us a little state information */
%}

%%
print           { return PRINT; };
[0-9]+          { yylval.iVal = atoi(yytext); return NUM; };
[@]             { return APPEND; };
[\"]            { return QUOTE; };
[\\]            { return ESCAPE; };
[+]             { return ADD; };
[-]             { return SUB; };
[*]             { return MUL; };
[/]             { return DIV; };
[(]             { return OPENPAREN; };
[)]             { return CLOSEPAREN; };
[\n|\r|\r\n]    { return NEWLINE; };
[ \t]+          {
                  yylval.sPtr = yytext;
                  /* Capture in string otherwise eat it */
                  if (isInStr) {
                    return WHITESPACE;
                  }
                }; 
.               { yylval.cVal = *yytext; return CHAR; };
%%

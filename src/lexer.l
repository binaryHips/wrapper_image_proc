%option noyywrap
%{
#include "parser.h"
#include <string.h>

char* strdup (const char* s)
{
  size_t slen = strlen(s);
  char* result = malloc(slen + 1);
  if(result == NULL)
  {
    return NULL;
  }

  memcpy(result, s, slen+1);
  return result;
}

char* strtrim_end(char* s, const int k){

  s[strlen(s)-k] = '\0';
  return s;
}



int block_count = 1;
int par_count = 1;

%}
%s fragment
%s argscatch

digit         [0-9]
letter        [a-zA-Z]

%%
"FRAGMENT"[\n \t]*\{ {BEGIN(fragment); ++block_count; return FRAGMENT;} 

"IN ".+                {yylval.input = strdup(yytext+3); return INPUT;} 
"OUT ".+                {yylval.output = strdup(yytext+4); return OUTPUT;}

"//".*$              {return COMM;}

<fragment>"{"     {++block_count;yylval.input = strdup(yytext); return CHAR;}
<fragment>"}"     {--block_count;
                    if (block_count == 1){
                      return FRAG_END;
                    }else{
                      yylval.input = strdup(yytext); return CHAR;
                    }
                  }
<fragment>"IN("    {BEGIN(argscatch); par_count = 1; return IN_ACCESS;}

<argscatch>"("    {++par_count;}
<argscatch>")"    {if (par_count <= 1){BEGIN(fragment);} else {--par_count;} ; yylval.input = strdup(yytext); return CHAR;}
<argscatch>.      {yylval.input = strdup(yytext); return CHAR;} 
<argscatch>\n     {yylval.input = strdup(yytext); return NEWLINE;}
<fragment>. {yylval.input = strdup(yytext); return CHAR;} 


<<EOF>>               return END;
\n            {yylval.input = strdup(yytext); return NEWLINE;}
[ \t\r]            
.                     {printf("Unknown character [%c]\n",yytext[0]); return UNKNOWN;}

%%

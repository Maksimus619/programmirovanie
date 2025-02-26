%{
#include "cool-parse.h"
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z]
WHITESPACE  [ \t\n]

%%

"class"     { printf("CLASS\n"); return CLASS; }
"inherits"  { printf("INHERITS\n"); return INHERITS; }
"if"        { printf("IF\n"); return IF; }
"then"      { printf("THEN\n"); return THEN; }
"else"      { printf("ELSE\n"); return ELSE; }
"fi"        { printf("FI\n"); return FI; }
"while"     { printf("WHILE\n"); return WHILE; }
"loop"      { printf("LOOP\n"); return LOOP; }
"pool"      { printf("POOL\n"); return POOL; }
"let"       { printf("LET\n"); return LET; }
"in"        { printf("IN\n"); return IN; }
"true"      { printf("TRUE\n"); return TRUE; }
"false"     { printf("FALSE\n"); return FALSE; }
"isvoid"    { printf("ISVOID\n"); return ISVOID; }
"new"       { printf("NEW\n"); return NEW; }
"not"       { printf("NOT\n"); return NOT; }
"out_string" { printf("OUT_STRING\n"); return OUT_STRING; }
"out_int"   { printf("OUT_INT\n"); return OUT_INT; }

{DIGIT}+    { printf("INT_CONST: %s\n", yytext); return INT_CONST; }
{LETTER}({LETTER}|{DIGIT}|_)* { printf("ID: %s\n", yytext); return ID; }
\"([^\"\n]|\\\")*\" { printf("STR_CONST: %s\n", yytext); return STR_CONST; }

"+"         { printf("PLUS\n"); return PLUS; }
"-"         { printf("MINUS\n"); return MINUS; }
"*"         { printf("MULT\n"); return MULT; }
"/"         { printf("DIV\n"); return DIV; }
"<-"        { printf("ASSIGN\n"); return ASSIGN; }
"<"         { printf("LT\n"); return LT; }
"<="        { printf("LE\n"); return LE; }
"="         { printf("EQ\n"); return EQ; }
";"         { printf("SEMI\n"); return SEMI; }
":"         { printf("COLON\n"); return COLON; }
","         { printf("COMMA\n"); return COMMA; }
"("         { printf("LPAREN\n"); return LPAREN; }
")"         { printf("RPAREN\n"); return RPAREN; }
"{"         { printf("LBRACE\n"); return LBRACE; }
"}"         { printf("RBRACE\n"); return RBRACE; }
"."         { printf("DOT\n"); return DOT; }
"@"         { printf("AT\n"); return AT; }

{WHITESPACE}+ { /* skip whitespace */ }

.           { printf("ERROR: %s\n", yytext); return ERROR; }

%%

int main(int argc, char** argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}

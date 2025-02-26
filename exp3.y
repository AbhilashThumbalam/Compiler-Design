%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex(void);  // Declare the lexical analyzer function

void yyerror(const char *s);
%}

%union {
    int num; // For numbers
}

%token <num> NUMBER
%token SQRT CQRT
%left '+' '-'
%left '*' '/'
%right SQRT CQRT

%type <num> calculation expression

%%

calculation:
    expression { printf("Result: %d\n", $1); }
    ;

expression:
      NUMBER               { $$ = $1; }
    | expression '+' expression  { $$ = $1 + $3; }
    | expression '-' expression  { $$ = $1 - $3; }
    | expression '*' expression  { $$ = $1 * $3; }
    | expression '/' expression  { $$ = $1 / $3; }
    | SQRT expression       { $$ = sqrt($2); }
    | CQRT expression       { $$ = cbrt($2); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Simple Calculator. Type 'exit' to quit.\n");
    while (1) {
        printf("> ");
        yyparse();  // Parse the input
    }
    return 0;
}

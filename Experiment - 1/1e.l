%{
#include <stdio.h>
%}

%%

[+\-*/=<>^]   { printf("Operator: %s\n", yytext); }  // Match and print operators
.              { /* Ignore other characters */ }       // Ignore other characters

%%

int yywrap() {
    return 1;  // End of input
}

int main() {
    yylex();  // Start lexical analysis
    return 0;
}

%{
#include <stdio.h>
int no_of_lines = 0; // Count the number of lines
int no_of_chars = 0; // Count the number of characters
%}

%%

\n      { ++no_of_lines; }   // Increment line count for every newline
.       { ++no_of_chars; }   // Increment character count for every character
%%

/*** User code section ***/
int yywrap() {
    return 1; // End of input handling
}

int main(int argc, char **argv) {
    yylex(); // Call the lexer
    printf("Number of lines = %d, Number of characters = %d\n", no_of_lines, no_of_chars);
    return 0;
}
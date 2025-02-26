#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Function to find the longest common prefix
void findLCP(char **prod, int count, char *prefix) {
    int len = strlen(prod[0]), i, j;
    for (i = 1; i < count; i++) {
        for (j = 0; j < len && prod[i][j] == prod[0][j]; j++);
        len = j;
    }
    strncpy(prefix, prod[0], len);
    prefix[len] = '\0';
}

int main() {
    char input[MAX], nonTerminal, prefix[MAX], *prod[MAX], *rem[MAX];
    int count = 0;

    printf("Enter the grammar production (A->α1|α2|... format): ");
    fgets(input, MAX, stdin);

    nonTerminal = input[0];
    char *ptr = strtok(input + 3, "|\n"); // Move past 'A->'
    
    while (ptr) {
        prod[count] = strdup(ptr);
        ptr = strtok(NULL, "|\n");
        count++;
    }

    if (count < 2) return printf("No left factoring needed.\n"), 0;

    findLCP(prod, count, prefix);
    if (!strlen(prefix)) return printf("The given grammar has no left factoring.\n"), 0;

    printf("\nGrammar after removing left factoring:\n");
    printf("%c -> %s%c'\n%c' -> ", nonTerminal, prefix, nonTerminal, nonTerminal);
    
    for (int i = 0; i < count; i++) {
        rem[i] = prod[i] + strlen(prefix);
        printf("%s%s", *rem[i] ? rem[i] : "ε", (i < count - 1) ? " | " : "\n");
        free(prod[i]); // Free allocated memory
    }
    return 0;
}
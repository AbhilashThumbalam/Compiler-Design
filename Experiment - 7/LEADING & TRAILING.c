#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
int vars, terms, i, j, k, m, rep, count, temp = -1;
char var[10], term[10], lead[10][10], trail[10][10];

// Structure to store grammar rules
struct grammar {
    int prodno;       // Number of productions for a variable
    char lhs;         // Left-hand side of the production
    char rhs[20][20]; // Right-hand side of the production
} gram[50];

// Function to get grammar details from the user
void get() {
    printf("\nLEADING AND TRAILING\n");
    
    // Input number of variables
    printf("\nEnter the number of variables: ");
    scanf("%d", &vars);
    
    // Input variable names
    printf("\nEnter the variables:\n");
    for (i = 0; i < vars; i++) {
        scanf(" %c", &gram[i].lhs);
        var[i] = gram[i].lhs;
    }
    
    // Input number of terminals
    printf("\nEnter the number of terminals: ");
    scanf("%d", &terms);
    
    // Input terminal names
    printf("\nEnter the terminals: ");
    for (j = 0; j < terms; j++)
        scanf(" %c", &term[j]);

    // Input production rules
    printf("\nPRODUCTION DETAILS\n");
    for (i = 0; i < vars; i++) {
        printf("\nEnter the number of productions for %c: ", gram[i].lhs);
        scanf("%d", &gram[i].prodno);
        for (j = 0; j < gram[i].prodno; j++) {
            printf("%c -> ", gram[i].lhs);
            scanf("%s", gram[i].rhs[j]);
        }
    }
}

// Function to compute LEADING sets
void leading() {
    // Initialize leading table
    memset(lead, 0, sizeof(lead));

    // Find leading terminals in productions
    for (i = 0; i < vars; i++) {
        for (j = 0; j < gram[i].prodno; j++) {
            for (k = 0; k < terms; k++) {
                // Check if the first symbol in RHS is a terminal
                if (gram[i].rhs[j][0] == term[k])
                    lead[i][k] = 1;
                else {
                    // Check if the second symbol is a terminal
                    if (gram[i].rhs[j][1] == term[k])
                        lead[i][k] = 1;
                }
            }
        }
    }

    // Propagate leading symbols across non-terminals
    for (rep = 0; rep < vars; rep++) {
        for (i = 0; i < vars; i++) {
            for (j = 0; j < gram[i].prodno; j++) {
                // Find the first variable in RHS
                for (m = 0; m < vars; m++) {
                    if (gram[i].rhs[j][0] == var[m]) {
                        temp = m;
                        break;
                    }
                }
                for (k = 0; k < terms; k++) {
                    if (lead[temp][k] == 1)
                        lead[i][k] = 1;
                }
            }
        }
    }
}

// Function to compute TRAILING sets
void trailing() {
    // Initialize trailing table
    memset(trail, 0, sizeof(trail));

    // Find trailing terminals in productions
    for (i = 0; i < vars; i++) {
        for (j = 0; j < gram[i].prodno; j++) {
            count = strlen(gram[i].rhs[j]);
            
            for (k = 0; k < terms; k++) {
                // Check if the last symbol is a terminal
                if (gram[i].rhs[j][count - 1] == term[k])
                    trail[i][k] = 1;
                else {
                    // Check if the second last symbol is a terminal
                    if (count > 1 && gram[i].rhs[j][count - 2] == term[k])
                        trail[i][k] = 1;
                }
            }
        }
    }

    // Propagate trailing symbols across non-terminals
    for (rep = 0; rep < vars; rep++) {
        for (i = 0; i < vars; i++) {
            for (j = 0; j < gram[i].prodno; j++) {
                count = strlen(gram[i].rhs[j]);

                // Find the last variable in RHS
                for (m = 0; m < vars; m++) {
                    if (gram[i].rhs[j][count - 1] == var[m])
                        temp = m;
                }

                for (k = 0; k < terms; k++) {
                    if (trail[temp][k] == 1)
                        trail[i][k] = 1;
                }
            }
        }
    }
}

// Function to display LEADING and TRAILING sets
void display() {
    // Display Leading sets
    for (i = 0; i < vars; i++) {
        printf("\nLEADING(%c) = { ", gram[i].lhs);
        for (j = 0; j < terms; j++) {
            if (lead[i][j] == 1)
                printf("%c ", term[j]);
        }
        printf("}");
    }
    printf("\n");

    // Display Trailing sets
    for (i = 0; i < vars; i++) {
        printf("\nTRAILING(%c) = { ", gram[i].lhs);
        for (j = 0; j < terms; j++) {
            if (trail[i][j] == 1)
                printf("%c ", term[j]);
        }
        printf("}");
    }
    printf("\n");
}

// Main function
int main() {
    get();       // Get input from the user
    leading();   // Compute leading sets
    trailing();  // Compute trailing sets
    display();   // Display the results
    return 0;
}
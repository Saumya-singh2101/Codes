#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char* keywords[] = {
    "int", "float", "char", "double", "return", "if", "else", "while", "for", "void"
};
int isKeyword(const char* word) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

// Check if character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>';
}

void lexicalAnalyze(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    char buffer[100];
    int i = 0;

    printf("Lexical Analysis Output:\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        // If letter or digit, build word
        if (isalnum(ch)) {
            buffer[i++] = ch;
        } else if (ch == ' ' || ch == '\n' || ch == ';' || ch == '(' || ch == ')') {
            buffer[i] = '\0';
            if (i != 0) {
                if (isKeyword(buffer))
                    printf("[Keyword]    -> %s\n", buffer);
                else
                    printf("[Identifier] -> %s\n", buffer);
                i = 0;
            }
        } else if (isOperator(ch)) {
            buffer[i] = '\0';
            if (i != 0) {
                if (isKeyword(buffer))
                    printf("[Keyword]    -> %s\n", buffer);
                else
                    printf("[Identifier] -> %s\n", buffer);
                i = 0;
            }
            printf("[Operator]   -> %c\n", ch);
        }
    }

    fclose(fp);
}
 
int main() {
    char filename[100];
    printf("Enter source file name (e.g., sample.c): ");
    scanf("%s", filename);
    lexicalAnalyze(filename);
    return 0;
}

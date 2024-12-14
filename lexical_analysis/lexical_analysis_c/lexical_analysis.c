#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Check if a word is a keyword
bool isKeyword(const char *word) {
    const char *keywords[] = {"if", "else", "int", "float", "return", "for", "while", "do", "switch", "case"};
    for (int i = 0; i < 10; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Classify a single character
void classifyChar(char ch, int *arithmetic, int *punctuation, int *parentheses) {
    if (strchr("+-*/=", ch)) {
        (*arithmetic)++;
        printf("Arithmetic Operator: %c\n", ch);
    } else if (strchr(";:,", ch)) {
        (*punctuation)++;
        printf("Punctuation: %c\n", ch);
    } else if (strchr("(){}[]", ch)) {
        (*parentheses)++;
        printf("Parenthesis: %c\n", ch);
    }
}

int main() {
    char input[256], token[64];
    int keywordCount = 0, identifierCount = 0, constantCount = 0;
    int arithmeticCount = 0, punctuationCount = 0, parenthesesCount = 0;

    printf("Enter a line of code: ");
    fgets(input, sizeof(input), stdin);

    int tokenIndex = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        // Build token for alphanumeric sequences
        if (isalnum(ch) || ch == '_') {
            token[tokenIndex++] = ch;
        } else {
            // Process completed token
            if (tokenIndex > 0) {
                token[tokenIndex] = '\0';
                if (isKeyword(token)) {
                    keywordCount++;
                    printf("Keyword: %s\n", token);
                } else if (isdigit(token[0])) {
                    constantCount++;
                    printf("Constant: %s\n", token);
                } else {
                    identifierCount++;
                    printf("Identifier: %s\n", token);
                }
                tokenIndex = 0;
            }

            // Classify non-alphanumeric characters
            classifyChar(ch, &arithmeticCount, &punctuationCount, &parenthesesCount);
        }
    }

    // Process any remaining token
    if (tokenIndex > 0) {
        token[tokenIndex] = '\0';
        if (isKeyword(token)) {
            keywordCount++;
            printf("Keyword: %s\n", token);
        } else if (isdigit(token[0])) {
            constantCount++;
            printf("Constant: %s\n", token);
        } else {
            identifierCount++;
            printf("Identifier: %s\n", token);
        }
    }

    printf("\nSummary:\n");
    printf("Keywords: %d\n", keywordCount);
    printf("Identifiers: %d\n", identifierCount);
    printf("Constants: %d\n", constantCount);
    printf("Arithmetic Operators: %d\n", arithmeticCount);
    printf("Punctuation: %d\n", punctuationCount);
    printf("Parentheses: %d\n", parenthesesCount);

    return 0;
}

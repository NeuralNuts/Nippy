#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

struct AstNode **_ast_node[MAP_SIZE];

char *extract_number(char *file_lines, int *index) {
    int start = *index;
    char *numeric_literal = (char*)malloc(*index - start + 1);

    while (isdigit(file_lines[*index])) {
        (*index)++;
    }

    if(numeric_literal != NULL) {
        strncpy(numeric_literal, file_lines + start, *index - start);

        numeric_literal[*index - start] = '\0';
    }
    return numeric_literal;

    free(numeric_literal);
}

char *extract_alpha(char *file_lines, int *i) {
    int start = *i;
    char *alpha_literal = (char*)malloc(*i - start + 1);

    while(isalpha((unsigned char)file_lines[*i])) {
        (*i)++;
    }
    
    if(alpha_literal == NULL) {
        printf("Error: alpha literal is null");
        free(alpha_literal);
    }
    else if(alpha_literal != NULL) {
        strncpy(alpha_literal, file_lines + start, *i - start);

        alpha_literal[*i - start] = '\0';
    }
    return alpha_literal;

    free(alpha_literal);
}

void tokenizer(char *file_lines) {
    for(int i = 0; file_lines[i] != '\0'; i++) {
        if(isdigit(file_lines[i])) {
            insert_token(_ast_node, extract_number(file_lines, &i), i, INTEGER);
        }
        else if(isalpha(file_lines[i])) {
            insert_token(_ast_node, extract_alpha(file_lines, &i), i, ALPHA);
        }

        switch(file_lines[i]) {
            case '\n':
                continue;
            case '+':
                insert_token(_ast_node, "+", i, ADDITION);
                break;
            case '-':
                insert_token(_ast_node, "-", i, MINUS);
                break;
            case '/':
                insert_token(_ast_node, "/", i, DIVIDE);
                break;
            case '*':
                insert_token(_ast_node, "*", i, MULTIPLY);
                break;
            case '(':
                insert_token(_ast_node, "(", i, LEFT_ROUND_BRACKET);
                break;
            case ')':
                insert_token(_ast_node, ")", i, RIGHT_ROUND_BRACKET);
                break;
            case '{':
                insert_token(_ast_node, "{", i, LEFT_SQUARE_BRACKET);
                break;
            case '}':
                insert_token(_ast_node, "}", i, RIGHT_SQUARE_BRACKET);
                break;
            case '&':
                insert_token(_ast_node, "&", i, AND);
                break;
            case ';':
                insert_token(_ast_node, ";", i, END_OF_LINE);
                break;
            case '=':
                insert_token(_ast_node, "=", i, ASSIGN);
                break;
            case '_':
                insert_token(_ast_node, "_", i, UNDERSCORE);
                break;
            default:
                printf("Unhandled character: [ %c ] (%d)\n", file_lines[i], file_lines[i]);
                break;
        }
    }
    in_order_traversal(*_ast_node);
}

#include <stdio.h>
#include <stdlib.h>

#include "token_map.h"

struct AstNode {
    int token_position;
    
    struct AstNode *left;
    struct AstNode *right;
};

void ast_init(struct AstNode ast_node) {
    ast_node.token_position = 0;
    ast_node.right = NULL;
    ast_node.left = NULL;
}

void insert_ast_node(struct AstNode **ast_node, struct TokenMap token_map[]) {
    struct ast_node *temp_node = NULL;

    if(*ast_node != NULL) {
        temp_node = (struct ast_node*)malloc(sizeof(ast_node));

        
    }
}

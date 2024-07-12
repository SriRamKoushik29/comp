#include <stdio.h>
#include "parser.h"  // Assuming parser.h defines Node structure and functions

void generateAssembly(Node *node, FILE *outputFile) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case NODE_ASSIGN:
            // Generate assembly code for assignment statement
            fprintf(outputFile, "MOV %s, %s\n", node->left->value, node->right->value);
            break;
        case NODE_IF:
            // Generate assembly code for if statement
            fprintf(outputFile, "CMP %s, 0\n", node->left->value);
            fprintf(outputFile, "JE ELSE_LABEL\n");
            // Generate assembly code for statements inside if body
            generateAssembly(node->right, outputFile);
            fprintf(outputFile, "ELSE_LABEL:\n");
            break;
        case NODE_CONSTANT:
            // Generate assembly code for constant value
            fprintf(outputFile, "DW %s\n", node->value);
            break;
        case NODE_VARIABLE:
            // Generate assembly code for variable usage
            fprintf(outputFile, "VAR %s\n", node->value);
            break;
        default:
            fprintf(stderr, "Error: Unknown node type\n");
            break;
    }
}

int main() {
    FILE *inputFile = fopen("input.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_ASSIGN,
    NODE_OPERATION,
    NODE_IF,
    NODE_CONSTANT,
    NODE_VARIABLE
} NodeType;

typedef struct Node {
    NodeType type;
    char value[20];  // Example size for storing variable names or numbers
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(NodeType type, const char *value) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node != NULL) {
        node->type = type;
        strcpy(node->value, value);
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

Node* parseStatement(FILE *file);
Node* parseExpression(FILE *file);
Node* parseTerm(FILE *file);
Node* parseFactor(FILE *file);

Node* parseStatement(FILE *file) {
    Token token;
    getNextToken(file, &token);

    if (token.type == TOKEN_INT) {
        // Handle variable declaration
        getNextToken(file, &token);  // Expecting an identifier
        Node *variable = createNode(NODE_VARIABLE, token.text);

        getNextToken(file, &token);  // Expecting a semicolon
        if (token.type != TOKEN_SEMICOLON) {
            fprintf(stderr, "Syntax error: Expected semicolon\n");
            exit(1);
        }
        return variable;
    } else if (token.type == TOKEN_IDENTIFIER) {
        // Handle assignment
        Node *variable = createNode(NODE_VARIABLE, token.text);

        getNextToken(file, &token);  // Expecting an assignment operator
        if (token.type != TOKEN_ASSIGN) {
            fprintf(stderr, "Syntax error: Expected assignment operator\n");
            exit(1);
        }

        Node *expression = parseExpression(file);

        getNextToken(file, &token);  // Expecting a semicolon
        if (token.type != TOKEN_SEMICOLON) {
            fprintf(stderr, "Syntax error: Expected semicolon\n");
            exit(1);
        }

        Node *assignment = createNode(NODE_ASSIGN, "");
        assignment->left = variable;
        assignment->right = expression;
        return assignment;
    } else if (token.type == TOKEN_IF) {
        // Handle if statement
        Node *ifNode = createNode(NODE_IF, "");

        // Handle condition
        getNextToken(file, &token);  // Expecting a left brace
        if (token.type != TOKEN_LBRACE) {
            fprintf(stderr, "Syntax error: Expected left brace\n");
            exit(1);
        }

        ifNode->left = parseExpression(file);  // Condition expression

        getNextToken(file, &token);  // Expecting a right brace
        if (token.type != TOKEN_RBRACE) {
            fprintf(stderr, "Syntax error: Expected right brace\n");
            exit(1);
        }

        // Handle if body
        getNextToken(file, &token);  // Expecting a left brace
        if (token.type != TOKEN_LBRACE) {
            fprintf(stderr, "Syntax error: Expected left brace\n");
            exit(1);
        }

        ifNode->right = parseStatement(file);  // Statement inside if body

        getNextToken(file, &token);  // Expecting a right brace
        if (token.type != TOKEN_RBRACE) {
            fprintf(stderr, "Syntax error: Expected right brace\n");
            exit(1);
        }

        return ifNode;
    }

    fprintf(stderr, "Syntax error: Unexpected token\n");
    exit(1);
}

Node* parseExpression(FILE *file) {
    // Example implementation for parsing expressions (simplified)
    return parseTerm(file);
}

Node* parseTerm(FILE *file) {
    // Example implementation for parsing terms (simplified)
    return parseFactor(file);
}

Node* parseFactor(FILE *file) {
    // Example implementation for parsing factors (simplified)
    Token token;
    getNextToken(file, &token);

    Node *node = createNode(NODE_CONSTANT, token.text);
    return node;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    Node *statement = parseStatement(file);

    // Code to traverse and process the AST (not included here)

    fclose(file);
    return 0;
}

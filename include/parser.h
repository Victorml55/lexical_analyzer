#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "list.h"

/*
 * Nodos del AST (Abstract Syntax Tree)
 * Cada tipo de nodo corresponde a una producción de la gramática.
 */
typedef enum NodeType {
    NODE_PROGRAM,
    NODE_ASSIGNMENT,
    NODE_IF_STATEMENT,
    NODE_CONDITION,
    NODE_EXPRESSION,
    NODE_TERM,
    NODE_FACTOR_ID,
    NODE_FACTOR_NUMBER,
    NODE_FACTOR_STRING,
    NODE_FACTOR_EXPR,
    NODE_BINOP,         /* operación binaria: +, -, *, /        */
} NodeType;

typedef struct ASTNode {
    NodeType type;

    /* Para NODE_FACTOR_ID, NODE_FACTOR_NUMBER, NODE_FACTOR_STRING,
       NODE_BINOP (operador), NODE_CONDITION (operador)           */
    char* value;

    /* Hijos genéricos                                             */
    struct ASTNode* left;
    struct ASTNode* right;

    /* Para NODE_IF_STATEMENT                                      */
    struct ASTNode* condition;
    struct ASTNode* then_branch;
    struct ASTNode* else_branch;

    /* Lista encadenada de sentencias (NODE_PROGRAM)               */
    struct ASTNode* next;
} ASTNode;

/* ----------------------------------------------------------------
 * Estado del parser: envuelve la lista de tokens y el cursor.
 * ---------------------------------------------------------------- */
typedef struct Parser {
    Token* current;   /* token que estamos mirando ahora           */
} Parser;

/* ----------------------------------------------------------------
 * API pública
 * ---------------------------------------------------------------- */

/* Crea un parser apuntando al primer token de la lista.           */
Parser* parser_init(List* token_list);

/* Libera el parser (NO libera la lista de tokens).                */
void    parser_free(Parser* p);

/* Punto de entrada: parsea toda la lista y devuelve el AST.
   Retorna NULL si hay error de sintaxis.                          */
ASTNode* parse_program(Parser* p);

/* Imprime el AST con indentación (útil para depuración).          */
void ast_print(ASTNode* node, int indent);

/* Libera recursivamente un nodo AST y sus hijos.                  */
void ast_free(ASTNode* node);

#endif /* PARSER_H */

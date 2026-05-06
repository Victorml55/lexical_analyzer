#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/token.h"
#include "../include/list.h"


static const char* keywords[] = {
    "if", "while", "for", "else", "then"
};

static const char* commands[] = {
    "ls", "mkdir", "touch", "edit", "rm", "help", "clear", "vim", "echo"
};

static int is_keyword(const char* str) {
    if (!str || *str == '\0') return 0;
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++)
        if (strcmp(str, keywords[i]) == 0) return 1;
    return 0;
}

static int is_command(const char* str) {
    if (!str || *str == '\0') return 0;
    int n = sizeof(commands) / sizeof(commands[0]);
    for (int i = 0; i < n; i++)
        if (strcmp(str, commands[i]) == 0) return 1;
    return 0;
}

static int is_operation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/'
        || c == '=' || c == '<' || c == '>';
}

static int is_paren(char c) {
    return c == '(' || c == ')';
}

Token* get_next_token(const char* input) {
    if (!input || *input == '\0') return NULL;

    Token* t = init_token();
    if (!t) return NULL;

    const char* str = input;

    if (isalpha(*str)) {
        const char* p = str;
        while (*p) {
            if (!isalpha(*p) && !isdigit(*p)) {
                t->lexeme = strdup(str);
                t->type   = UNKNOWN;
                return t;
            }
            p++;
        }
        t->lexeme = strdup(str);
        if (is_keyword(str))
            t->type = KEYWORD;
        else if (is_command(str))
            t->type = IDENTIFIER;
        else
            t->type = IDENTIFIER;
        return t;
    }

    if (isdigit(*str)) {
        const char* p = str;
        while (*p) {
            if (!isdigit(*p)) {
                t->lexeme = strdup(str);
                t->type   = UNKNOWN;
                return t;
            }
            p++;
        }
        t->lexeme = strdup(str);
        t->type   = NUMBER;
        return t;
    }

    if (is_operation(*str)) {
        if (*(str + 1) != '\0') {
            t->lexeme = strdup(str);
            t->type   = UNKNOWN;
            return t;
        }
        t->lexeme = strdup(str);
        t->type   = OPERATION;
        return t;
    }

    if (is_paren(*str)) {
        if (*(str + 1) != '\0') {
            t->lexeme = strdup(str);
            t->type   = UNKNOWN;
            return t;
        }
        t->lexeme = strdup(str);
        t->type   = SYMBOLS;
        return t;
    }

    if (*str == '\'') {
        const char* p = str + 1;
        while (*p && *p != '\'') p++;
        if (*p == '\'') {
            t->lexeme = strdup(str);
            t->type   = STRING;
        } else {
            t->lexeme = strdup(str);
            t->type   = UNKNOWN;
        }
        return t;
    }

    t->lexeme = strdup(str);
    t->type   = UNKNOWN;
    return t;
}


static void flush_buffer(List* l, char* buffer, int* i) {
    if (*i == 0) return;
    buffer[*i] = '\0';
    Token* t = get_next_token(buffer);
    if (t) push_token(l, t);
    memset(buffer, 0, *i + 1);
    *i = 0;
}


List* tokenize(const char* input) {
    if (!input) return NULL;

    List* l = init_list();
    if (!l) return NULL;

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int i = 0;

    const char* str = input;

    while (*str) {

        if (*str == ' ' || *str == '\n') {
            flush_buffer(l, buffer, &i);
            str++;
            continue;
        }

        if (is_paren(*str)) {
            flush_buffer(l, buffer, &i);
            char paren[2] = { *str, '\0' };
            Token* t = get_next_token(paren);
            if (t) push_token(l, t);
            str++;
            continue;
        }

        if (is_operation(*str)) {
            flush_buffer(l, buffer, &i);
            char op[2] = { *str, '\0' };
            Token* t = get_next_token(op);
            if (t) push_token(l, t);
            str++;
            continue;
        }

        if (*str == '\'') {
            flush_buffer(l, buffer, &i);
            buffer[i++] = *str++;
            while (*str && *str != '\'')
                buffer[i++] = *str++;
            if (*str == '\'')
                buffer[i++] = *str++;
            flush_buffer(l, buffer, &i);
            continue;
        }

         buffer[i++] = *str++;
    }

     flush_buffer(l, buffer, &i);

    return l;
}

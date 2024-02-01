#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defining KEYWORDS    */
const char *keywords[] = {
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "while"
};

int lexer(FILE* fp, token_t *tokens, int tklm) {
    int tp = 0;
    char filestr[MAX_TOKEN_VAL_LEN];
    for (int i = 0; i < tklm; i++) {
        if (fscanf(fp, "%*[ \n\t\r\v]")) {
            continue;
        } else if (fscanf(fp, "%[0-9] ", filestr)) {
            token_t nt;
            nt.tokentype = NUMERIC_CONSTANT;
            strcpy(nt.tokenval, filestr);
            tokens[tp++] = nt;
        } else if (fscanf(fp, "%[a-zA-Z0-9_] ", filestr)) {
            token_t nt;
            int kwval = iskeyword(filestr);

            strcpy(nt.tokenval, filestr);
            nt.tokentype = ((kwval >= 0) ? kwval : IDENTIFIER);
            /* Keywords are set to 0-29 same as indexes, so setting it
               to kwavl accomplishes the same thing */
            tokens[tp++] = nt;
        } else if (fscanf(fp, "%1[\\] ")) {
            token_t nt;
            int eschar = fgetc(fp);
            nt.tokentype = getescval(eschar);
            char esseq[3];
            esseq[0] = '\\';
            esseq[1] = eschar;
            esseq[2] = '\0';
            strcpy(nt.tokenval, esseq);
            tokens[tp++] = nt;
        } else if (fscanf(fp, "%1[\"\'] ", filestr)) {
            token_t nt;
            char literal[MAX_TOKEN_VAL_LEN];
            int c, i;
            char openchar = *filestr;
            for (i = 0; i < MAX_TOKEN_VAL_LEN && (c = fgetc(fp)) != openchar; i++) {
                literal[i] = c;
                if (c == '\\')
                    literal[++i] = fgetc(fp);
            }
            literal[i] = '\0';
            nt.tokentype = (openchar == '\"') ? STRING_LITERAL : CHAR_CONSTANT;
            strcpy(nt.tokenval, literal);
            tokens[tp++] = nt;
        } else if (fscanf(fp, "%1[](){},.;:#[] ", filestr)) {
            token_t nt;
            nt.tokentype = getsymbolval(*filestr);
            strcpy(nt.tokenval, filestr);
            tokens[tp++] = nt;
        } else if (fscanf(fp, "%2[+-/*%=<>&|!?] ", filestr)) {
            token_t nt;
            nt.tokentype = getoperatorval(filestr);
            strcpy(nt.tokenval, filestr);
            tokens[tp++] = nt;
        }
    }

    return tp;
}

int iskeyword(char *s) {
    for (int i = 0; i < 30; i++)
        if (strcmp(keywords[i], s) == 0)
            return i;
    return -1;
}

int getsymbolval(char c) {
    switch(c) {
    case '(':
        return SYMBOL_OPEN_PAREN;
    case ')':
        return SYMBOL_CLOSE_PAREN;
    case '{':
        return SYMBOL_OPEN_BRACE;
    case '}':
        return SYMBOL_CLOSE_BRACE;
    case '[':
        return SYMBOL_OPEN_SQUARE;
    case ']':
        return SYMBOL_CLOSE_SQUARE;
    case ';':
        return SYMBOL_SEMICOLON;
    case '#':
        return SYMBOL_HASHTAG;
    case ',':
        return SYMBOL_COMMA;
    case ':':
        return SYMBOL_COLON;
    case '\'':
        return SYMBOL_SNGL_QUOTE;
    case '\"':
        return SYMBOL_DBL_QUOTE;
    case '\\':
        return SYMBOL_BACKSLASH;
    case '.':
        return SYMBOL_PERIOD;
    default:
        return -1;
    }
}

int getoperatorval(char *s) {
    int len = strlen(s);
    if (len == 1) {
        switch(s[0]) {
        case '=':
            return OPERATOR_ASSIGN;
        case '>':
            return OPERATOR_COMPARE_GR;
        case '<':
            return OPERATOR_COMPARE_LS;
        case '+':
            return OPERATOR_ADD;
        case '-':
            return OPERATOR_SUBTRACT;
        case '*':
            return OPERATOR_MULTIPLY;
        case '/':
            return OPERATOR_DIVIDE;
        case '%':
            return OPERATOR_MODULUS;
        case '!':
            return OPERATOR_NOT;
        case '?':
            return OPERATOR_TERNARY_QU;
        case '&':
            return OPERATOR_AND;
        case '|':
            return OPERATOR_OR;
        default:
            return -1;
        }
    } else if (len == 2) {
        switch(s[0]+s[1]) {
        case '='+'=':
            return OPERATOR_COMPARE_EQ;
        case '>'+'=':
            return OPERATOR_COMPARE_GR_EQ;
        case '<'+'=':
            return OPERATOR_COMPARE_LS_EQ;
        case '!'+'=':
            return OPERATOR_COMPARE_NOT_EQ;
        case '&'+'&':
            return OPERATOR_COMPARE_AND;
        case '|'+'|':
            return OPERATOR_COMPARE_OR;
        case '+'+'=':
            return OPERATOR_ASSIGN_ADD;
        case '-'+'=':
            return OPERATOR_ASSIGN_SUBT;
        case '*'+'=':
            return OPERATOR_ASSIGN_MULT;
        case '/'+'=':
            return OPERATOR_ASSIGN_DIV;
        case '%'+'=':
            return OPERATOR_ASSIGN_MOD;
        case '&'+'=':
            return OPERATOR_ASSIGN_AND;
        case '|'+'=':
            return OPERATOR_ASSIGN_OR;
        case '+'+'+':
            return OPERATOR_ASSIGN_INCR;
        case '-'+'-':
            return OPERATOR_ASSIGN_DECR;
        case '<'+'<':
            return OPERATOR_LEFT_SHIFT;
        case '>'+'>':
            return OPERATOR_RIGHT_SHIFT;
        default:
            return -1;
        }
    } else
        return -1;
}

int getescval(int c) {
    switch(c) {
    case 'n':
        return ESC_NEWLINE;
    case 't':
        return ESC_TAB;
    case 'r':
        return ESC_RETURN;
    case 'v':
        return ESC_VTAB;
    case 'a':
        return ESC_ALERT;
    case 'b':
        return ESC_BACKSPACE;
    case 'f':
        return ESC_FORMFEED;
    case '\\':
        return ESC_BACKSLASH;
    case '?':
        return ESC_QUESTION_MARK;
    case '\'':
        return ESC_SINGLE_QUOTE;
    case '\"':
        return ESC_DOUBLE_QUOTE;
    case '0':
        return ESC_NULL;
    default:
        return -1;
    }
}

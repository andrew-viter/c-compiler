#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

/*  Creating TOKEN struct   */

#define MAX_TOKEN_VAL_LEN   256

struct token {
    int tokentype;
    char tokenval[MAX_TOKEN_VAL_LEN];
};

typedef struct token token_t;

/*  Defining KEYWORD Types  */

#define KEYWORD_BREAK       0x000
#define KEYWORD_CASE        0x001
#define KEYWORD_CHAR        0x002
#define KEYWORD_CONST       0x003
#define KEYWORD_CONTINUE    0x004
#define KEYWORD_DEFAULT     0x005
#define KEYWORD_DO          0x006
#define KEYWORD_DOUBLE      0x007
#define KEYWORD_ELSE        0x008
#define KEYWORD_ENUM        0x009
#define KEYWORD_EXTERN      0x00A
#define KEYWORD_FLOAT       0x00B
#define KEYWORD_FOR         0x00C
#define KEYWORD_GOTO        0x00D
#define KEYWORD_IF          0x00E
#define KEYWORD_INT         0x00F
#define KEYWORD_LONG        0x010
#define KEYWORD_REGISTER    0x011
#define KEYWORD_RETURN      0x012
#define KEYWORD_SHORT       0x013
#define KEYWORD_SIGNED      0x014
#define KEYWORD_SIZEOF      0x015
#define KEYWORD_STATIC      0x016
#define KEYWORD_STRUCT      0x017
#define KEYWORD_SWITCH      0x018
#define KEYWORD_TYPEDEF     0x019
#define KEYWORD_UNION       0x01A
#define KEYWORD_UNSIGNED    0x01B
#define KEYWORD_VOID        0x01C
#define KEYWORD_WHILE       0x01D

/*  Defining SYMBOL Types   */

#define SYMBOL_OPEN_PAREN   0x100
#define SYMBOL_CLOSE_PAREN  0x101
#define SYMBOL_OPEN_BRACE   0x102
#define SYMBOL_CLOSE_BRACE  0x103
#define SYMBOL_OPEN_SQUARE  0x104
#define SYMBOL_CLOSE_SQUARE 0x105
#define SYMBOL_SEMICOLON    0x106
#define SYMBOL_HASHTAG      0x107
#define SYMBOL_COMMA        0x108
#define SYMBOL_COLON        0x109
#define SYMBOL_SNGL_QUOTE   0x10A
#define SYMBOL_DBL_QUOTE    0x10B
#define SYMBOL_BACKSLASH    0x10C
#define SYMBOL_PERIOD       0x10D

/*  Defining OPERATOR Types */

#define OPERATOR_ASSIGN         0x200
#define OPERATOR_COMPARE_GR     0x201
#define OPERATOR_COMPARE_LS     0x202
#define OPERATOR_ADD            0x203
#define OPERATOR_SUBTRACT       0x204
#define OPERATOR_MULTIPLY       0x205
#define OPERATOR_DIVIDE         0x206
#define OPERATOR_MODULUS        0x207
#define OPERATOR_NOT            0x208
#define OPERATOR_TERNARY_QU     0x209
#define OPERATOR_AND            0x20A
#define OPERATOR_OR             0x20B
#define OPERATOR_STRUCT_POINTER "UNDEF"
#define OPERATOR_COMPARE_EQ     (OPERATOR_ASSIGN+OPERATOR_ASSIGN)
#define OPERATOR_COMPARE_GR_EQ  (OPERATOR_COMPARE_GR+OPERATOR_ASSIGN)
#define OPERATOR_COMPARE_LS_EQ  (OPERATOR_COMPARE_LS+OPERATOR_ASSIGN)
#define OPERATOR_COMPARE_NOT_EQ (OPERATOR_NOT+OPERATOR_ASSIGN)
#define OPERATOR_COMPARE_AND    (OPERATOR_AND+OPERATOR_AND)
#define OPERATOR_COMPARE_OR     (OPERATOR_OR+OPERATOR_OR)
#define OPERATOR_ASSIGN_ADD     (OPERATOR_ADD+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_SUBT    (OPERATOR_SUBTRACT+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_MULT    (OPERATOR_MULTIPLY+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_DIV     (OPERATOR_DIVIDE+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_MOD     (OPERATOR_MODULUS+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_AND     (OPERATOR_AND+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_OR      (OPERATOR_OR+OPERATOR_ASSIGN)
#define OPERATOR_ASSIGN_XOR     "UNDEF"
#define OPERATOR_ASSIGN_INCR    (OPERATOR_ADD+OPERATOR_ADD)
#define OPERATOR_ASSIGN_DECR    (OPERATOR_SUBTRACT+OPERATOR_SUBTRACT)
#define OPERATOR_LEFT_SHIFT     (OPERATOR_COMPARE_LS+OPERATOR_COMPARE_LS)
#define OPERATOR_RIGHT_SHIFT    (OPERATOR_COMPARE_GR+OPERATOR_COMPARE_GR)

/*  Defining ESC SEQUENCES  */

#define ESC_NEWLINE         0x300
#define ESC_TAB             0x301
#define ESC_RETURN          0x302
#define ESC_VTAB            0x303
#define ESC_ALERT           0x304
#define ESC_BACKSPACE       0x305
#define ESC_FORMFEED        0x306
#define ESC_BACKSLASH       0x307
#define ESC_QUESTION_MARK   0x308
#define ESC_SINGLE_QUOTE    0x309
#define ESC_DOUBLE_QUOTE    0x30A
#define ESC_NULL            0x30B

/*  Defining Other Types    */

#define NUMERIC_CONSTANT    0x400
#define STRING_LITERAL      0x401
#define CHAR_CONSTANT       0x402
#define IDENTIFIER          0x500

/*  Declaring FUNCTIONS     */

int lexer(FILE* fp, token_t *tokens, int tklm);
int iskeyword(char *s);
int getsymbolval(char c);
int getoperatorval(char *s);
int getescval(int c);

#endif

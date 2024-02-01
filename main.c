/*  A Lexer program for processing an 
    input file and generating
    Token Sequences, for a C program */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

#define MAX_TOKENS 2000

token_t tokens[MAX_TOKENS];

int main(int argc, char *argv[]) {
    FILE* fp = fopen("test.txt", "r");
    int tkncnt = lexer(fp, tokens, MAX_TOKENS);
    fclose(fp);
    for (int i = 0; i < tkncnt; i++)
        printf("%d\t\'%s\'\n", tokens[i].tokentype, tokens[i].tokenval);
    printf("Lexing phase completed. Processed %d tokens\n", tkncnt);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

const char ADDITION = '+';
const char SUBTRACTION = '-';
const char MULTIPLICATION = '*';
const char DIVISION = '/';
const char OPEN = '(';
const char CLOSE = ')';
const char EMPTY = EOF;

int la; // Lookahead
FILE* inp_file;

void parseExpr();
void parseExpr2();
void parseTerm();
void parseTerm2();
void parseFactor();

void consume() {
    la = fgetc(inp_file);
}
void printError(char* text) {
    printf("Error: %s\n", text);
    exit(0);
}
void expect(char c) {
    if (la == c) {
        consume();
    }
    else {
        printError("In Expect!");
    }
}

int isNumber(char c) {
    if (c >= 48 && c <= 57) return TRUE;
    return FALSE;
}

void parseExpr() {
    parseTerm();
    parseExpr2();
}

void parseExpr2() {
    if (la == ADDITION) {
        consume();
        parseTerm();
        parseExpr2();
    }
    else if (la == ADDITION) {
        consume();
        parseTerm();
        parseExpr2();
    }

    //FOLLOW
    if (la == CLOSE || la == EMPTY) {

    }
    else {
        printError("In parseExpr2");
    }
}

void parseTerm() {
    parseFactor();
    parseTerm2();
}

void parseTerm2() {
    if (la == MULTIPLICATION) {
        consume();
        parseFactor();
        parseTerm2();
    }
    else if (la == DIVISION) {
        consume();
        parseFactor();
        parseTerm2();
    }

    if (la == ADDITION || la == SUBTRACTION || la == CLOSE || la == EMPTY) {
        
    }
    else {
        printError("In parseTerm2");
    }
    
}

void parseFactor() {
    if (la == OPEN) {
        consume();
        parseExpr();
        consume();
    }
    else if (la == ADDITION) {
        consume();
        parseFactor();
    }
    else if (la == SUBTRACTION) {
        consume();
        parseFactor();
    }
    else if (isNumber(la)) {
        consume();
    }

    //FOLLOW
	if (la == MULTIPLICATION || la == DIVISION || la == CLOSE
		|| la == ADDITION || la == SUBTRACTION || la == EMPTY) {
		
	}
	else {
		printError("In parseFaktor");
	}
}


int main() {
    fopen_s(&inp_file, "Code.txt", "r");
    if (inp_file != NULL) {
        la = getc(inp_file);
        parseExpr();

        printf("FUCK SUCCESS\n");


        fclose(inp_file);
    }
    else {
        printf("Didn't work!");
    }
}

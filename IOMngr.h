#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int openFiles(char * sourceName, char * listingName);
void closeFiles();
char getNextSourceChar();
void writeIndicator(int column);
void writeMessage(char * message);
int getCurrentLineNum();
int getCurrentColumnNum();
int num_digits(int i);


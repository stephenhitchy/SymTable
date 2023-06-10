#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IOMngr.h"
#define MAXLINE 1024

char c, *IObuff, *ourBuf;
int print_line = 0;
int listing_file_used = 0;
int bufSize = 0;
FILE *sourceFile;
FILE *listingFile;
char buf[MAXLINE];
char c;
int cur_char = 0;
int curLine = 0;
int curCol = 0;


int openFiles(char *sourceName, char *listingName)
{
  sourceFile = fopen(sourceName, "r");
  if(sourceFile == NULL){
    return 0;
  }
  if (listingName != NULL)
  {
    listingFile = fopen(listingName, "w+");
  }
  return 1;
}

void closeFiles()
{
  if (listingFile != NULL)
  {
    fclose(listingFile);
  }
  fclose(sourceFile);
}

char getNextSourceChar()
{
  if (buf[cur_char] == '\0')
  {
    cur_char = 0;
    curLine++;
    bufSize = sizeof(buf);
    ourBuf = malloc(MAXLINE);
    for(int x = 0; x < sizeof(buf); x++){
      ourBuf[x] = buf[x];
    }
    memset(buf, 0, sizeof(buf));
    if (fgets(buf, MAXLINE, sourceFile) == NULL)
    { 
      return EOF;
    }
    else
    {
      fprintf(listingFile, "%d: ", curLine);
    }
  }
  fputc(buf[cur_char], listingFile);
  char return_val = buf[cur_char];
  cur_char++;
  return return_val;
}

void writeIndicator(int column)
{
  int i;
  if (listingFile != NULL)
  {
    for (i = 0; i < column + num_digits(getCurrentLineNum()) + 1; i++)
    {
      fprintf(listingFile, " ");
    }
    fprintf(listingFile, "%c\n", '^');
  }
  else
  {
    if (getCurrentLineNum() != print_line)
    {
      printf("%d. ", curLine);
        printf("%s", ourBuf);
        printf("%s", buf);
      print_line = getCurrentLineNum();
    }
    printf("\n");
    for (i = 0; i < column + num_digits(getCurrentLineNum()) + 1; i++)
    {
      printf(" ");
    }
    printf("%c\n", '^');
  }
}

int num_digits(int i)
{
  int count = 0;
  while (i != 0)
  {
    i = i / 10;
    count++;
  }
  return count;
}

void writeMessage(char *message)
{
  if (listingFile != NULL)
  {
    fprintf(listingFile, "%s\n", message);
  }
  else
  {
    fprintf(stderr, "%s\n", message);
  }
}

int getCurrentLineNum()
{
  return curLine;
}

int getCurrentColumnNum()
{
  return curCol;
}

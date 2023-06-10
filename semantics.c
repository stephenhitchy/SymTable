#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "semantics.h"

SymTab *table;

void printSymTab()
{
  int firstIteration = startIterator(table);
  int secondIteration;
  SymTab *sym;
  while (firstIteration == 1)
  {
    printf("%s: {", getCurrentName(table));
    sym = (SymTab *)getCurrentAttr(table);
    secondIteration = startIterator(sym);
    while (secondIteration == 1)
    {
      printf("%c", getCurrentName(sym)[0]);
      secondIteration = nextEntry(sym);
      if(secondIteration == 1){
        printf(", ");
      }
    }
    printf("}\n");
    firstIteration = nextEntry(table);
  }
  // destroySymTab(table);
}



SymTab *makeSet(char *set)
{
  SymTab *newTable = createSymTab(17);
  int i = 0;
  char *current = malloc(2 * sizeof(char));
  current[1] = '\0';
  for (i = 0; i < strlen(set); i++)
  {
    if (isalpha(set[i]) != 0)
    {
      current[0] = set[i];
      enterName(newTable, current);
      setCurrentAttr(newTable, (void *)&i);
    }
  }
  return newTable;
}



void storeVar(char *id, SymTab *tab)
{
  enterName(table, id);
  setCurrentAttr(table, (void *)tab);
}

SymTab *getVal(char *id)
{
  if (enterName(table, id))
  {
    setCurrentAttr(table, (void *)id);
  }

  SymTab *newTable = createSymTab(17);
  SymTab *sym = getCurrentAttr(table);
  int iteration = startIterator(sym);
  while (iteration == 1)
  {
    char *newEntry = getCurrentName(sym);
    enterName(newTable, newEntry);
    iteration = nextEntry(sym);
  }
  return newTable;
}



SymTab *doIntersection(SymTab *sym1, SymTab *sym2)
{
  SymTab *newTable = createSymTab(30);

  int firstIteration = startIterator(sym1);
  while (firstIteration == 1)
  {
    char *name1 = getCurrentName(sym1);
    int secondIteration = startIterator(sym2);
    if(secondIteration == 0){
      return newTable;
    }
    while (secondIteration == 1)
    {
      char *name2 = getCurrentName(sym2);
      if (strcmp(name1, name2) == 0)
      {
        enterName(newTable, name1);
      }
      secondIteration = nextEntry(sym2);
    }
    firstIteration = nextEntry(sym1);
  }

  // destroySymTab(sym1);
  // destroySymTab(sym2);
  return newTable;
}



SymTab *doUnion(SymTab *sym1, SymTab *sym2)
{
  SymTab *newTable = createSymTab(30);
  char *symName1;

  int firstIteration = startIterator(sym1);
  while (firstIteration == 1)
  {
    symName1 = getCurrentName(sym1);
    enterName(newTable, symName1);
    firstIteration = nextEntry(sym1);
  }

  int secondIteration = startIterator(sym2);
  while (secondIteration == 1)
  {
    char *symName2 = getCurrentName(sym2);
    if (strcmp(symName1, symName2) != 0)
    {
      enterName(newTable, symName2);
    }
    secondIteration = nextEntry(sym2);
  }

  // destroySymTab(sym1);
  // destroySymTab(sym2);
  return newTable;
}

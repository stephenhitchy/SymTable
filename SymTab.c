#include "SymTab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *listingFile;

SymTab *createSymTab(int size)
{
    SymTab *symTable = (SymTab *)malloc(sizeof(SymTab));
    symTable->size = size;
    symTable->contents = (SymEntry **)malloc(sizeof(SymEntry *) * size);

    for (int i = 0; i < size; i++)
    {
        SymEntry *firstEntry = (SymEntry *)malloc(sizeof(SymEntry));
        firstEntry->name = NULL;
        firstEntry->attributes = NULL;
        firstEntry->next = NULL;
        symTable->contents[i] = firstEntry;
    }
    return symTable;
}

int hash(char *key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i < strlen(key); i++)
    {
        hashVal = 37 + hashVal + key[i];
        hashVal %= tableSize;
        if (hashVal < 0)
        {
            hashVal += tableSize;
        }
        return hashVal;
    }
}

void destroySymTab(SymTab *table)
{
    int size = table->size;
    for (int i = 0; i < size; i++)
    {
        SymEntry *curRow = table->contents[i];
        while (curRow != NULL)
        {
            SymEntry *nextEntry = curRow->next;
            free(curRow->name);
            free(curRow->attributes);
            free(curRow);
            curRow = nextEntry;
        }
    }
    free(table->contents);
    free(table->current);
    free(table);
}

int enterName(SymTab *table, char *name)
{
    if (findName(table, name) == 0)
    {
        int hashVal = hash(name, table->size);
        SymEntry *curEntry = (SymEntry *)malloc(sizeof(SymEntry));
        curEntry->name = strdup(name);
        curEntry->attributes = (int*)1;
        curEntry->next = NULL;

        SymEntry *firstValueInTab = (table->contents)[hashVal];
        SymEntry *holder = firstValueInTab->next;
        if (firstValueInTab->next != NULL)
        {
            while (firstValueInTab->next != NULL)
            {
                firstValueInTab = firstValueInTab->next;
            }
            firstValueInTab->next = curEntry;
        }
        else
        {
            firstValueInTab->next = curEntry;
        }
        table->current = curEntry;
        return 1;
    }
    else
    {
        return 0;
    }
}

int findName(SymTab *table, char *name)
{
    int hashVal = hash(name, table->size);
    SymEntry *curEntry = table->contents[hashVal];

    if (curEntry->next == NULL)
    {
        return 0;
    }
    else
    {
        curEntry = curEntry->next;
        while (curEntry->name != NULL)
        {
            if (strcmp(curEntry->name, name) == 0)
            {
                table->current = curEntry;
                return 1;
            }
            if (curEntry->next != NULL)
            {
                curEntry = curEntry->next;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

int nextEntry(SymTab *table)
{
    SymEntry *currentEntry;
    if(hasCurrent(table) == 1){
        currentEntry = table->current;
    }else{
        return 0;
    }
    if (currentEntry->next != NULL)
    {
        table->current = currentEntry->next;
        return 1;
    }
    if (currentEntry->name == NULL)
    {
        printf("Error");
        return 0;
    }

    int currentRowNum = hash(currentEntry->name, table->size);
    int tblSize = table->size;
    if (currentRowNum == tblSize - 1)
    {
        return 0;
    }

    currentRowNum++;
    for (int i = currentRowNum; i < tblSize; i++)
    {
        SymEntry *currentRowEntry = table->contents[i];
        if (currentRowEntry->next != NULL)
        {
            table->current = currentRowEntry->next;
            return 1;
        }
    }
    return 0;
}

int hasCurrent(SymTab *table)
{
    if(table->current != NULL){
        return 1;
    }else{
        return 0;
    }
}

void setCurrentAttr(SymTab *table, void *attr)
{
    SymEntry *cur = table->current;
    cur->attributes = attr;
}

void *getCurrentAttr(SymTab *table)
{
    SymEntry *cur = table->current;
    return cur->attributes;
}

char *getCurrentName(SymTab *table)
{
    SymEntry *cur = table->current;
    return cur->name;
}

int startIterator(SymTab *table)
{
    int x = 0;
    if(hasCurrent(table) == 1){
        SymEntry *cur = table->contents[0];
        while(cur->next == NULL){
            x++;
            cur = table->contents[x];
        }
        table->current = cur->next;
        return 1;
    }
    return 0;
}
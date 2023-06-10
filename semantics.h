#include <stdbool.h>
#include "SymTab.h"
#include "IOMngr.h"

extern void printSymTab();
extern void storeVar(char * id, SymTab * tab);
extern SymTab * getVal(char * id);
extern SymTab * makeSet(char * set);
extern SymTab * doUnion(SymTab * sym1, SymTab * sym2);
extern SymTab * doIntersection(SymTab * sym1, SymTab * sym2);

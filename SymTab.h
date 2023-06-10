typedef struct SymEntry{ 
    char* name;
    void* attributes;
    struct SymEntry* next;
}SymEntry;

typedef struct {
    int size;
    SymEntry** contents;
    SymEntry* current;
} SymTab;

SymTab* createSymTab(int size);

void destroySymTab(SymTab* table);

int enterName(SymTab* table, char* name);

int findName(SymTab* table, char* name); 

int hasCurrent(SymTab* table);

void setCurrentAttr(SymTab* table, void * attr);

void * getCurrentAttr(SymTab* table); 

char * getCurrentName(SymTab* table); 

int nextEntry(SymTab* table); 

int hash(char* key, int tableSize);

int startIterator(SymTab* table);

int nextEntry(SymTab* table);
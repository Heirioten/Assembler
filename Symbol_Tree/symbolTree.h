#ifndef SYMBOL_TREE
#define SYMBOL_TREE

typedef struct Tree
{
    char* key;
    char* value;
    struct Tree* left;
    struct Tree* right;
    int size;
    
} Tree;

Tree* createRoot(char* key, char* value);
int addKey(Tree* tree, char* key, char* value);
char* getValueByKey(Tree* tree, char* key);
void deallocateTree(Tree* tree);
void printTree(Tree* tree);

int checkAndFill(Tree* tree, int direction, char* key, char* value);
Tree* createNewNode(char* key, char* value);
Tree* getNextNode(Tree* tree, int direction);
int getNextNodeDirection(Tree* tree, char* key);

#endif
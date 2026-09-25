#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct StringList
{
    struct StringNode* start;
    struct StringNode* end;
    int count;
} StringList;

typedef struct StringNode
{
    char* value;
    struct StringNode* previous;
    struct StringNode* next;
} StringNode;

StringList* createStringList();
char* getValueAtIndex(StringList* list, int index);
void deleteElementAtIndex(StringList* list, int index);
void addToStart(StringList* list, char* value);
void addToEnd(StringList* list, char* value);
char* popStart(StringList* list);
char* popEnd(StringList* list);
int size(StringList* list);
void deallocateStringList(StringList* list);
void printList(StringList* list);

#endif
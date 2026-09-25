#ifndef PARSER
#define PARSER

#include "../Linked_List/linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StringList* parseFile(char* fileName);
StringList* separateLines(char* text);
void removeComments(StringList* list);
void removeCommentsFromLine(char* line);
void removeWhitespace(StringList* list);
char* removeWhitespaceFromLine(char* line);
void removeUnnecessaryNodes(StringList* list);

#endif
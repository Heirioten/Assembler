#ifndef A_Instruction
#define A_Instruction

#include "../../Symbol_Tree/symbolTree.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct AInstructionMap
{
    struct Tree* variables;
    short nextNumber;
} AInstructionMap;

AInstructionMap* createAInstructionMap();
void deallocateAInstructionMap(AInstructionMap* map);
char* aInstructionToBinary(AInstructionMap* instructionMap, char* line);
void addLabel(AInstructionMap* map, char* label, short lineNumber);

void raiseBinary(char* binary);
char* parseNumber(char* line);
char* shortToBinary(short num);
char* findVariable(AInstructionMap* instructionMap, char* line);

#endif
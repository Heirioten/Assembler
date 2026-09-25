#ifndef C_Instruction
#define C_Instruction

#include "../../Symbol_Tree/symbolTree.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct CInstructionMaps
{
    struct Tree* comp;
    struct Tree* jump;
} CInstructionMaps;

CInstructionMaps* createCInstructionMaps();
void deallocateCInstructionMaps(CInstructionMaps* maps);
char* cInstructionToBinary(const CInstructionMaps* const maps, char* line);

char* createZeroBinaryString();
char* createBinaryString();
void compBinary(Tree* compMap, char* instruction, char* const binary);
void destBinary(char* instruction, char* const binary);
void jumpBinary(Tree* jumpMap, char* instruction, char* const binary);

#endif
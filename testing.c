#include <stdlib.h>
#include <stdio.h>
#include "Symbol_Tree/symbolTree.h"
#include "Parser/parser.h"
#include "Linked_List/linkedList.h"
#include "Instruction_Sets/A_Instructions/aInstructions.h"
#include "Instruction_Sets/C_Instructions/cInstructions.h"
#include <assert.h>
#include <string.h>

int main()
{
    AInstructionMap* map = createAInstructionMap();

    addLabel(map, "(LOOP)", 15);
    addLabel(map, "(END)", 12);
    addLabel(map, "(HELLO)", 0);
    addLabel(map, "(WORLD)", 7);

    char* binary = aInstructionToBinary(map, "(LOOP)");
    assert(strcmp(binary, "0000000000001111") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "(END)");
    assert(strcmp(binary, "0000000000001100") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "(HELLO)");
    assert(strcmp(binary, "0000000000000000") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "(WORLD)");
    assert(strcmp(binary, "0000000000000111") == 0);
    free(binary);

    deallocateAInstructionMap(map);

    return 0;
}

int cInstructionTests()
{
    CInstructionMaps* maps = createCInstructionMaps();

    char* binary = cInstructionToBinary(maps, "D=0;JMP");
    assert(strcmp(binary, "1110101010010111") == 0);
    free(binary);

    binary = cInstructionToBinary(maps, "D;JGT");
    assert(strcmp(binary, "1110001100000001") == 0);
    free(binary);

    binary = cInstructionToBinary(maps, "D=D+A");
    assert(strcmp(binary, "1110000010010000") == 0);
    free(binary);

    binary = cInstructionToBinary(maps, "MD=M-1");
    assert(strcmp(binary, "1111110010011000") == 0);
    free(binary);

    binary = cInstructionToBinary(maps, "M=D");
    assert(strcmp(binary, "1110001100001000") == 0);
    free(binary);

    deallocateCInstructionMaps(maps);
}

int jumpingBinaryTests()
{
    CInstructionMaps* maps = createCInstructionMaps();

    char* binary = createBinaryString();

    jumpBinary(maps->jump, "", binary);
    assert(strcmp(binary, "1110000000000000") == 0);

    jumpBinary(maps->jump, NULL, binary);
    assert(strcmp(binary, "1110000000000000") == 0);

    jumpBinary(maps->jump, "JGT", binary);
    assert(strcmp(binary, "1110000000000001") == 0);

    jumpBinary(maps->jump, "JEQ", binary);
    assert(strcmp(binary, "1110000000000010") == 0);

    jumpBinary(maps->jump, "JGE", binary);
    assert(strcmp(binary, "1110000000000011") == 0);

    jumpBinary(maps->jump, "JLT", binary);
    assert(strcmp(binary, "1110000000000100") == 0);

    jumpBinary(maps->jump, "JNE", binary);
    assert(strcmp(binary, "1110000000000101") == 0);

    jumpBinary(maps->jump, "JLE", binary);
    assert(strcmp(binary, "1110000000000110") == 0);

    jumpBinary(maps->jump, "JMP", binary);
    assert(strcmp(binary, "1110000000000111") == 0);

    free(binary);
    deallocateCInstructionMaps(maps);
    return 0;
}

int destinationBinaryTests()
{
    char* binary = createBinaryString();

    destBinary("M", binary);
    assert(strcmp(binary, "1110000000001000") == 0);

    destBinary("D", binary);
    assert(strcmp(binary, "1110000000010000") == 0);

    destBinary("A", binary);
    assert(strcmp(binary, "1110000000100000") == 0);

    destBinary("MD", binary);
    assert(strcmp(binary, "1110000000011000") == 0);

    destBinary("AD", binary);
    assert(strcmp(binary, "1110000000110000") == 0);

    destBinary("AM", binary);
    assert(strcmp(binary, "1110000000101000") == 0);

    destBinary("ADM", binary);
    assert(strcmp(binary, "1110000000111000") == 0);

    destBinary("AMD", binary);
    assert(strcmp(binary, "1110000000111000") == 0);

    destBinary("", binary);
    assert(strcmp(binary, "1110000000000000") == 0);

    destBinary(NULL, binary);
    assert(strcmp(binary, "1110000000000000") == 0);

    free(binary);

    return 0;
}

int computationBinaryTests()
{
    CInstructionMaps* maps = createCInstructionMaps();

    char* binary = createBinaryString();

    compBinary(maps->comp, "0", binary);
    assert(strcmp(binary, "1110101010000000") == 0);

    compBinary(maps->comp, "A+1", binary);
    assert(strcmp(binary, "1110110111000000") == 0);

    compBinary(maps->comp, "M+1", binary);
    assert(strcmp(binary, "1111110111000000") == 0);

    compBinary(maps->comp, "A-D", binary);
    assert(strcmp(binary, "1110000111000000") == 0);

    compBinary(maps->comp, "M-D", binary);
    assert(strcmp(binary, "1111000111000000") == 0);

    compBinary(maps->comp, "D&A", binary);
    assert(strcmp(binary, "1110000000000000") == 0);

    compBinary(maps->comp, "D&M", binary);
    assert(strcmp(binary, "1111000000000000") == 0);

    free(binary);
    deallocateCInstructionMaps(maps);
    return 0;
}

int aInstructionTests()
{
    AInstructionMap* map = createAInstructionMap();
    char* binary;

    binary = aInstructionToBinary(map, "@0");
    assert(strcmp(binary, "0000000000000000") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@R15");
    assert(strcmp(binary, "0000000000001111") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@R16");
    assert(strcmp(binary, "0000000000010000") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@R16");
    assert(strcmp(binary, "0000000000010000") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@i");
    assert(strcmp(binary, "0000000000010001") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@R16");
    assert(strcmp(binary, "0000000000010000") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@i");
    assert(strcmp(binary, "0000000000010001") == 0);
    free(binary);

    binary = aInstructionToBinary(map, "@LCL");
    assert(strcmp(binary, "0000000000000001") == 0);
    free(binary);

    deallocateAInstructionMap(map);

    return 0;
}

int createAInstructionMapTest()
{
    AInstructionMap* map = createAInstructionMap();
    printTree(map->variables);
    deallocateAInstructionMap(map);

    return 0;
}

int parseNumberTests()
{       
    char* binary = parseNumber("@0");
    assert(strcmp(binary, "0000000000000000") == 0);
    free(binary);

    binary = parseNumber("@1");
    assert(strcmp(binary, "0000000000000001") == 0);
    free(binary);

    binary = parseNumber("@2");
    assert(strcmp(binary, "0000000000000010") == 0);
    free(binary);

    binary = parseNumber("@15");
    assert(strcmp(binary, "0000000000001111") == 0);
    free(binary);

    return 0;
}

int shortToBinaryTests()
{
    char* expected = (char*)malloc(16 + 1);

    for(int i = 0; i < 16; i++)
    {
        expected[i] = '0';
    }

    expected[16] = '\0';

    char* binary;

    for(int i = 0; i < 32767; i++)
    {
        binary = shortToBinary(i);
        assert(strcmp(binary, expected) == 0);
        free(binary);
        raiseBinary(expected);
    }

    printf("All tests passed!");
    free(expected);

    return 0;
}

int parserComponentTests()
{
    StringList* list = separateLines("Hell//o\nWorld\nmy name //is...\nNicholas         John            Lyons //:)");
    printList(list);

    printf("\n=============================================\n");

    removeComments(list);
    printList(list);

    printf("\n=============================================\n");

    removeWhitespace(list);
    printList(list);

    deallocateStringList(list);
}

int listTests()
{
    StringList* list = createStringList();

    for(int i = 0; i < 10; i++)
    {
        addToStart(list, "Hello");
        addToEnd(list, "World");
    }

    for(int i = 0; i < 3; i++)
    {
        char* start = popStart(list);
        char* end = popEnd(list);
        printf("Start: %s\nEnd: %s\n========================\n", start, end);
        free(start);
        free(end);
    }

    char* intermediateValue = getValueAtIndex(list, 10);
    printf("IntermediateValue: %s\n", intermediateValue);
    free(intermediateValue);

    printList(list);
    deallocateStringList(list);
    return 0;
}

int parserTests()
{
    StringList* list = parseFile("Test_Files/Pong.asm");
    printList(list);
    deallocateStringList(list);
}

int treeTests() 
{
    Tree* tree = createRoot("I", "a");
    addKey(tree, "B", "b");
    addKey(tree, "J", "Hello");
    addKey(tree, "W", "World");
    addKey(tree, "Z", "My");
    addKey(tree, "P", "Name");
    addKey(tree, "Q", "Is");
    addKey(tree, "E", "Nicholas");
    addKey(tree, "A", "John");
    addKey(tree, "A", "Lyons");
    addKey(tree, "N", "The");
    addKey(tree, "V", "First");
    addKey(tree, "M", "Rawr");
    addKey(tree, "P", "Mother");
    addKey(tree, "R", "Truckers");

    char* res = getValueByKey(tree, "J");
    assert(strcmp(res, "Hello") == 0);
    free(res);

    res = getValueByKey(tree, "E");
    assert(strcmp(res, "Nicholas") == 0);
    free(res);

    res = getValueByKey(tree, "E");
    assert(strcmp(res, "Nicholas") == 0);
    free(res);

    res = getValueByKey(tree, "M");
    assert(strcmp(res, "Rawr") == 0);
    free(res);

    res = getValueByKey(tree, "WOW");
    assert(res == NULL);

    deallocateTree(tree);
    tree = NULL;

    printf("All tests passed successfully\n");

    return 0;
}
#include "Symbol_Tree/symbolTree.h"
#include "Parser/parser.h"
#include "Linked_List/linkedList.h"
#include "Instruction_Sets/A_Instructions/aInstructions.h"
#include "Instruction_Sets/C_Instructions/cInstructions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/// @brief Calculate the beginning of the accessed file name in a `filePath`
/// @param filePath 
/// @return Starting index of file name
int getFileNameStart(char* filePath)
{
    int start = 0;

    for(int i = 0; i < strlen(filePath); i++)
    {
        if(filePath[i] == '/')
        {
            start = i + 1;
        }
    }

    return start;
}

/// @brief Take the binary from `binaryList` and write it to a new 
///        text file with the `inFileName`, except with a .hack extension 
/// @param inFileName 
/// @param binaryList 
void writeToHackFile(char* inFileName, StringList* binaryList)
{
    int fileStart = getFileNameStart(inFileName);
    int outFileLength = strlen(inFileName) - fileStart + 2;
    char* outFileName = (char*)malloc(outFileLength);

    strcpy(outFileName, inFileName + fileStart);
    strncpy(outFileName + outFileLength - 6, ".hack", 5);
    outFileName[outFileLength - 1] = '\0';

    int filePathLength = strlen("./Output_Files/") + outFileLength;
    char* filePath = (char*)malloc(filePathLength);

    strcpy(filePath, "./Output_Files/");
    filePath[16] = '\0';

    strcat(filePath, outFileName);
    filePath[filePathLength - 1] = '\0';

    free(outFileName);

    FILE* fptr = fopen(filePath, "w");
    free(filePath);

    if (fptr == NULL) 
    {
        fprintf(stderr, "Error opening file: %s (errno = %d)\\n", strerror(errno), errno);
        return;
    }

    StringNode* currentNode = binaryList->start;

    while(currentNode != NULL)
    {
        fprintf(fptr, "%s", currentNode->value);
        currentNode = currentNode->next;

        if(currentNode != NULL)
        {
            fprintf(fptr, "\n");
        }
    }

    fclose(fptr);
}

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        perror("Too little arguments");
        return 0;
    }
    else if(argc > 2)
    {
        perror("Too many arguments");
        return 0;
    }

    char* fileName = argv[1];

    if(strlen(fileName) < 4)
    {
        perror("Must input a .asm file");
        return 0;
    }

    if(strncmp(".asm", fileName + (strlen(fileName) - 4), 4) != 0)
    {
        perror("Must input a .asm file");
        return 0;
    }

    StringList* instructionList = parseFile(fileName);

    if(instructionList == NULL)
    {
        perror("Invalid file path");
        return 0;
    }

    AInstructionMap* aMap = createAInstructionMap();
    CInstructionMaps* cMaps = createCInstructionMaps();

    StringNode* currentNode = instructionList->start;
    short currentLine = 0;

    while(currentNode != NULL)
    {
        if(currentNode->value[0] == '(')
        {
            addLabel(aMap, currentNode->value, currentLine);
            currentNode = currentNode->next;
            deleteElementAtIndex(instructionList, currentLine);
            continue;
        }

        currentNode = currentNode->next;
        currentLine++;
    }

    StringList* binaryList = createStringList();

    currentNode = instructionList->start;

    while(currentNode != NULL)
    {
        char* binary;

        if(currentNode->value[0] == '@')
        {
            binary = aInstructionToBinary(aMap, currentNode->value);
        }
        else
        {
            binary = cInstructionToBinary(cMaps, currentNode->value);
        }

        addToEnd(binaryList, binary);
        free(binary);
        currentNode = currentNode->next;
    }
    
    writeToHackFile(fileName, binaryList);

    deallocateAInstructionMap(aMap);
    deallocateCInstructionMaps(cMaps);
    deallocateStringList(instructionList);
    deallocateStringList(binaryList);

    return 0;
}
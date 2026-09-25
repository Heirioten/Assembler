#include "cInstructions.h"

/// @brief Constructs a map with all pre-defined computation binary codes
/// @return Reference to C Instruction Computation Mapping
CInstructionMaps* createCInstructionMaps()
{
    CInstructionMaps* maps = (CInstructionMaps*)malloc(sizeof(CInstructionMaps));
    
    Tree* comp = createRoot("0", "0101010");
    addKey(comp, "1", "0111111");
    addKey(comp, "-1", "0111010");
    addKey(comp, "D", "0001100");
    addKey(comp, "A", "0110000");
    addKey(comp, "M", "1110000");
    addKey(comp, "!D", "0001101");
    addKey(comp, "!A", "0110001");
    addKey(comp, "!M", "1110001");
    addKey(comp, "-D", "0001111");
    addKey(comp, "-A", "0110011");
    addKey(comp, "-M", "1110011");
    addKey(comp, "D+1", "0011111");
    addKey(comp, "A+1", "0110111");
    addKey(comp, "M+1", "1110111");
    addKey(comp, "D-1", "0001110");
    addKey(comp, "A-1", "0110010");
    addKey(comp, "M-1", "1110010");
    addKey(comp, "D+A", "0000010");
    addKey(comp, "D+M", "1000010");
    addKey(comp, "D-A", "0010011");
    addKey(comp, "D-M", "1010011");
    addKey(comp, "A-D", "0000111");
    addKey(comp, "M-D", "1000111");
    addKey(comp, "D&A", "0000000");
    addKey(comp, "D&M", "1000000");
    addKey(comp, "D|A", "0010101");
    addKey(comp, "D|M", "1010101");

    Tree* jump = createRoot("JGT", "001");
    addKey(jump, "JEQ", "010");
    addKey(jump, "JGE", "011");
    addKey(jump, "JLT", "100");
    addKey(jump, "JNE", "101");
    addKey(jump, "JLE", "110");
    addKey(jump, "JMP", "111");

    maps->comp = comp;
    maps->jump = jump;

    return maps;
}

/// @brief Frees map and all variables within the map. Will render map variable as garbage
/// @param map Map Pointer
void deallocateCInstructionMaps(CInstructionMaps* maps)
{
    deallocateTree(maps->comp);
    deallocateTree(maps->jump);
    free(maps);
}

/// @brief Creates a 16-bit binary string of all zeros: 0000000000000000
/// @return Binary String reference
char* createZeroBinaryString()
{
    char* binary = (char*)malloc(4);

    for(int i = 0; i < 3; i++)
    {
        binary[i] = '0';
    }

    binary[3] = '\0';

    return binary;;
}

/// @brief Converts a C-Instruction assembly line `line` to a Binary String
/// @param maps Reference to a C-Instruction mapping
/// @param line C-Instruction assembly line string
/// @return Binary String reference
char* cInstructionToBinary(const CInstructionMaps* const maps, char* line)
{
    char* binary = createBinaryString();
    int instructionLength = strlen(line);

    int equalIndex = -1;

    for(int i = 0; i < instructionLength; i++)
    {
        if(line[i] == '=')
        {
            char* instruction = (char*)malloc(i + 1);
            instruction[i] = '\0';

            strncpy(instruction, line, i);
            destBinary(instruction, binary);

            free(instruction);
            equalIndex = i;
            break;
        }
    }

    int numOfElements;
    int colanIndex = instructionLength;

    for(int i = colanIndex - 1; i >= 0; i--)
    {
        if(line[i] == ';')
        {
            int numOfElements = instructionLength - i;

            char* instruction = (char*)malloc(numOfElements);
            instruction[numOfElements - 1] = '\0';

            strncpy(instruction, line + i + 1, numOfElements - 1);
            jumpBinary(maps->jump, instruction, binary);

            free(instruction);
            colanIndex = i;
            break;
        }
    }

    numOfElements = colanIndex - equalIndex;
    char* compInstruction = (char*)malloc(numOfElements);
    compInstruction[numOfElements - 1] = '\0';

    strncpy(compInstruction, line + equalIndex + 1, numOfElements - 1);
    compBinary(maps->comp, compInstruction, binary);

    free(compInstruction);

    return binary;
}

/// @brief Creates the template of a computation binary string: 1110000000000000
/// @return Binary String reference
char* createBinaryString()
{
    char* binary = (char*)malloc(17);
    binary[16] = '\0';

    for(int i = 0; i < 3; i++)
    {
        binary[i] = '1';
    }

    for(int i = 3; i < 16; i++)
    {
        binary[i] = '0';
    }

    return binary;
}

/// @brief Adds binary code associated with computational instruction `instruction`
///        to the provided binary string `binary`
/// @param compMap Reference to a C-Instruction mapping
/// @param instruction C-Instruction Computation String
/// @param binary Binary String that will be edited in the computational section
void compBinary(Tree* compMap, char* instruction, char* const binary)
{
    assert(compMap != NULL);
    assert(instruction != NULL);
    assert(binary != NULL);

    assert(strlen(binary) == 16);

    char* computationBinary = getValueByKey(compMap, instruction);

    if(computationBinary == NULL)
    {
        perror("Computation instruction is invalid");
    }

    assert(strlen(computationBinary) == 7);

    for(int i = 0; i < 7; i++)
    {
        binary[i + 3] = computationBinary[i];
    }

    free(computationBinary);
}

/// @brief Adds binary code associated with destination instruction `instruction`
///        to the provided binary string `binary`
/// @param instruction C-Instruction Destination String
/// @param binary Binary String that will be edited in the destination section
void destBinary(char* instruction, char* const binary)
{
    assert(binary != NULL);

    assert(strlen(binary) == 16);

    if(instruction == NULL || strcmp(instruction, "") == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            binary[i + 10] = '0';
        }

        return;
    }

    char* destinationBinary = createZeroBinaryString();

    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < strlen(instruction); x++)
        {
            switch(instruction[x])
            {
                case 'A':
                    if(i == 0)
                    {
                        destinationBinary[i] = '1';
                    }

                    break;
                case 'D':
                    if(i == 1)
                    {
                        destinationBinary[i] = '1';
                    }

                    break;
                case 'M':
                    if(i == 2)
                    {
                        destinationBinary[i] = '1';
                    }

                    break;
                default:
                    free(destinationBinary);
                    perror("Invalid destination instruction");
                    return;
            }
        }
    }

    assert(strlen(destinationBinary) == 3);

    for(int i = 0; i < 3; i++)
    {
        binary[i + 10] = destinationBinary[i];
    }

    free(destinationBinary);
}

/// @brief Adds binary code associated with jump instruction `instruction`
///        to the provided binary string `binary`
/// @param instruction C-Instruction Jump String
/// @param binary Binary String that will be edited in the jump section
void jumpBinary(Tree* jumpMap, char* instruction, char* const binary)
{
    assert(jumpMap != NULL);
    assert(binary != NULL);

    assert(strlen(binary) == 16);

    if(instruction == NULL || strcmp(instruction, "") == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            binary[i + 10] = '0';
        }

        return;
    }

    char* jumpingBinary = getValueByKey(jumpMap, instruction);

    if(jumpingBinary == NULL)
    {
        perror("Jumping instruction is invalid");
    }

    assert(strlen(jumpingBinary) == 3);

    for(int i = 0; i < 3; i++)
    {
        binary[i + 13] = jumpingBinary[i];
    }

    free(jumpingBinary);
}
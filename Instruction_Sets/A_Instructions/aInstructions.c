#include "aInstructions.h"

/// @brief Constructs a map with all pre-defined address variables
/// @return Reference to A Instruction Variable Mapping
AInstructionMap* createAInstructionMap()
{
    char* binary = (char*)malloc(16 + 1);

    for(int i = 0; i < 16; i++)
    {
        binary[i] = '0';
    }

    binary[16] = '\0';

    AInstructionMap* map = (AInstructionMap*)malloc(sizeof(AInstructionMap));

    Tree* tree = createRoot("@R0", binary);
    addKey(tree, "@SP", binary);
    raiseBinary(binary);

    addKey(tree, "@R1", binary);
    addKey(tree, "@LCL", binary);
    raiseBinary(binary);

    addKey(tree, "@R2", binary);
    addKey(tree, "@ARG", binary);
    raiseBinary(binary);

    addKey(tree, "@R3", binary);
    addKey(tree, "@THIS", binary);
    raiseBinary(binary);

    addKey(tree, "@R4", binary);
    addKey(tree, "@THAT", binary);
    raiseBinary(binary);
    
    addKey(tree, "@R5", binary);
    raiseBinary(binary);

    addKey(tree, "@R6", binary);
    raiseBinary(binary);

    addKey(tree, "@R7", binary);
    raiseBinary(binary);

    addKey(tree, "@R8", binary);
    raiseBinary(binary);
    
    addKey(tree, "@R9", binary);
    raiseBinary(binary);

    addKey(tree, "@R10", binary);
    raiseBinary(binary);

    addKey(tree, "@R11", binary);
    raiseBinary(binary);

    addKey(tree, "@R12", binary);
    raiseBinary(binary);

    addKey(tree, "@R13", binary);
    raiseBinary(binary);

    addKey(tree, "@R14", binary);
    raiseBinary(binary);

    addKey(tree, "@R15", binary);

    free(binary);

    binary = shortToBinary(16384);
    addKey(tree, "@SCREEN", binary);
    free(binary);

    binary = shortToBinary(24576);
    addKey(tree, "@KBD", binary);
    free(binary);

    map->variables = tree;
    map->nextNumber = 16;

    return map;
}

/// @brief Frees map and all variables within the map. Will render map variable as garbage
/// @param map Map Pointer
void deallocateAInstructionMap(AInstructionMap* map)
{
    deallocateTree(map->variables);
    free(map);
}

/// @brief Increases the binary string by 1
/// @param bin Binary String
void raiseBinary(char* bin)
{
    for(int i = 15; i >= 0; i--)
    {
        if(bin[i] == '0')
        {
            bin[i] = '1';
            break;
        }

        bin[i] = '0';
    }
}

/// @brief Converts an A-Instruction assembly line to a Binary String 
/// @param instructionMap Reference to an A-Instruction mapping
/// @param line A-Instruction assembly line string
/// @return Binary String pointer
char* aInstructionToBinary(AInstructionMap* instructionMap, char* line)
{
    int nonNum = 0;

    for(int i = 1; i < strlen(line); i++)
    {
        if(line[i] < '0' || '9' < line[i])
        {
            nonNum++;
            break;
        }
    }

    return nonNum == 0 ? parseNumber(line) : findVariable(instructionMap, line);
}

/// @brief Append `map` with a `label` variable associated with a specific line number `line number`
/// @param map Reference to an A-Instruction mapping 
/// @param label Variable String
/// @param lineNumber Line Number of Label Variable
void addLabel(AInstructionMap* map, char* label, short lineNumber)
{
    int labelSize = strlen(label);
    char* key = (char*)malloc(labelSize);
    key[0] = '@';
    key[labelSize - 1] = '\0';

    strncpy(key + 1, label + 1, labelSize - 2);

    char* binary = shortToBinary(lineNumber);
    addKey(map->variables, key, binary);
    
    free(binary);
    free(key);
}

/// @brief Converts a number string `line` into a binary string
/// @param line A-Instruction assembly line string
/// @return Binary String reference
char* parseNumber(char* line)
{
    short num = 0;

    for(int i = 1; i < strlen(line); i++)
    {
        num *= 10;
        char c = line[i];
        num += (int)(c - '0');
    }

    return shortToBinary(num);
}

/// @brief Converts a 16-bit number `num` into a 16-bit binary string
/// @param num 
/// @return Binary String reference
char* shortToBinary(short num)
{
    char* binary = (char*)(malloc(16 + 1));
    binary[16] = '\0';

    for(int i = 0; i < 16; i++)
    {
        binary[i] = '0';
    }

    for(int i = 15; i >= 0; i--)
    {
        if(num <= 0)
        {
            break;
        }

        short remainder = num % 2;
        binary[i] = (char)(remainder + '0');
        num /= 2;
    }

    return binary;
}

/// @brief Attempts to find the variable string `line` in the A-Instruction map `instructionMap`,
///        returning the associated Binary String if found. If the string `line` cannot be found
///        within `instructionMap`, it will add a new entry into the map with the next memory
///        location available in the form of a binary number. This binary will be returned as a 
///        string
/// @param instructionMap A-Instruction assembly line string
/// @param line A or L Instruction assembly line string
/// @throw If instruction map is not initialized
/// @return Binary String reference
char* findVariable(AInstructionMap* instructionMap, char* line)
{
    if(instructionMap == NULL || instructionMap->variables == NULL)
    {
        perror("Map is null and cannot be referenced");
        return NULL;
    }

    char* binary = getValueByKey(instructionMap->variables, line);

    if(binary == NULL)
    {
        binary = shortToBinary(instructionMap->nextNumber);
        instructionMap->nextNumber++;
        addKey(instructionMap->variables, line, binary);
    }

    return binary;
}
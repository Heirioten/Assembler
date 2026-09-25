#include "parser.h"

/// @brief Parse and clean text file into separate lines with no whitespace or comments
/// @param fileName file path to .asm file
/// @return String List reference, where each element is a separate line in the .asm code
StringList* parseFile(char* fileName)
{   
    FILE* fptr = fopen(fileName, "r");
    long size = 0;

    if(fptr == NULL)
    {
        return NULL;
    }

    char c;

    fseek(fptr, 0, SEEK_END); // Seek to the end of the file
    size = ftell(fptr);       // Get the current file pointer position (size)
    rewind(fptr);

    int i = 0;
    char* text = (char*)malloc(size + 1);

    while((c = fgetc(fptr)) != EOF)
    {
        text[i] = c;
        i++;
    }

    text[size] = '\0';

    fclose(fptr);

    StringList* list = separateLines(text);
    free(text);

    removeComments(list);
    removeWhitespace(list);
    removeUnnecessaryNodes(list);

    return list;
}

/// @param text
/// @return String List reference that contains each line in `text` as a separate element in the list
StringList* separateLines(char* text)
{
    StringList* list = createStringList();
    int start = 0;

    int length = strlen(text);
    char* insertion;

    for(int i = 0; i < length; i++)
    {
        if(text[i] != '\n' && text[i] != '\r')
        {
            continue;
        }

        insertion = (char*)malloc((i - start + 1));
        strncpy(insertion, text + start, i - start);
        insertion[i - start] = '\0';
        addToEnd(list, insertion);
        free(insertion);
        start = i + 1;
    }

    insertion = (char*)malloc((length - start + 1));
    strncpy(insertion, text + start, length - start);
    insertion[length - start] = '\0';
    addToEnd(list, insertion);
    free(insertion);

    return list;
}

/// @brief Removes comments from each node in `list`
/// @param list 
void removeComments(StringList* list)
{
    StringNode* node = list->start;

    while(node != NULL)
    {
        removeCommentsFromLine(node->value);
        node = node->next;
    }
}

/// @brief Removes comments from a string `line`
/// @param line 
void removeCommentsFromLine(char* line)
{
    int comment = 0;
    
    for(int i = 0; i < strlen(line); i++)
    {
        if(line[i] == '/')
        {
            comment = 1;
        }

        if(comment > 0)
        {
            line[i] = ' ';
        }
    }
}

/// @brief Removes whitespace from each node in `list`
/// @param list 
void removeWhitespace(StringList* list)
{
    StringNode* node = list->start;

    while(node != NULL)
    {
        node->value = removeWhitespaceFromLine(node->value);
        node = node->next;
    }
}

/// @brief Removes whitespace from a string `line`
/// @param line 
/// @return A new string with no whitespace
char* removeWhitespaceFromLine(char* line)
{
    int numOfCharacters = 0;

    for(int i = 0; i < strlen(line); i++)
    {
        if(line[i] != ' ')
        {
            numOfCharacters++;
        }
    }

    char* result = (char*)malloc(numOfCharacters + 1);
    int index = 0;

    for(int i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ')
        {
            continue;
        }

        result[index] = line[i];
        index++;
    }

    result[numOfCharacters] = '\0';
    free(line);
    return result;
}

/// @brief Removes an elements from `list` that contain empty strings
/// @param list 
void removeUnnecessaryNodes(StringList* list)
{
    StringNode* node = list->start;
    int index = 0;

    while(node != NULL)
    {
        if(strcmp(node->value, "") == 0)
        {
            node = node->next;
            deleteElementAtIndex(list, index);
            continue;
        }

        node = node->next;
        index++;
    }
}
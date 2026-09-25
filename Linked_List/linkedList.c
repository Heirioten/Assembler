#include "linkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/// @brief Creates an empty string list
/// @return String List reference
StringList* createStringList()
{
    StringList* list = (StringList*)malloc(sizeof(StringList));

    list->start = NULL;
    list->end = NULL;
    list->count = 0;

    return list;
}

/// @brief Gets string value from `list` at `index`
/// @param list
/// @param index 
/// @return String at list[index]
char* getValueAtIndex(StringList* list, int index)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return NULL;
    }

    if(index < 0 || index >= list->count)
    {
        perror("Provided index is invalid");
        return NULL;
    }

    StringNode* node = list->start;

    for(int i = 0; i < index; i++)
    {
        node = node->next;
    }

    char* result = (char*)malloc(strlen(node->value) + 1);
    strcpy(result, node->value);
    return result;
}

/// @brief Deletes string value from `list` at `index`
/// @param list 
/// @param index
void deleteElementAtIndex(StringList* list, int index)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return;
    }

    if(index < 0 || index >= list->count)
    {
        perror("Provided index is invalid");
        return;
    }

    if(index == 0)
    {
        char* value = popStart(list);
        free(value);
        return;
    }

    if(index == list->count - 1)
    {
        char* value = popEnd(list);
        free(value);
        return;
    }

    list->count--;

    StringNode* node = list->start;

    for(int i = 0; i < index; i++)
    {
        node = node->next;
    }

    StringNode* previous = node->previous;
    StringNode* next = node->next;

    previous->next = next;
    next->previous = previous;

    free(node->value);
    free(node);
}

/// @brief Adds a string `value` to the beginning of a `list`
/// @param list 
/// @param value 
void addToStart(StringList* list, char* value)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return;
    }

    StringNode* node = (StringNode*)malloc(sizeof(StringNode));
    node->next = NULL;
    node->previous = NULL;
    node->value = (char*)malloc(strlen(value) + 1);
    strcpy(node->value, value);
    list->count++;

    if(list->start == NULL)
    {
        list->start = node;
        list->end = node;
        return;
    }

    StringNode* start = list->start;
    list->start = node;
    node->next = start;
    start->previous = node;
}

/// @brief Adds a string `value` to the end of a `list`
/// @param list 
/// @param value 
void addToEnd(StringList* list, char* value)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return;
    }

    StringNode* node = (StringNode*)malloc(sizeof(StringNode));
    node->next = NULL;
    node->previous = NULL;
    node->value = (char*)malloc(strlen(value) + 1);
    strcpy(node->value, value);
    list->count++;

    if(list->end == NULL)
    {
        list->start = node;
        list->end = node;
        return;
    }

    StringNode* end = list->end;
    list->end = node;
    node->previous = end;
    end->next = node;
}

/// @brief Removes, deletes, and returns the first element of a `list`
/// @param list 
/// @return String at list[0]
char* popStart(StringList* list)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return NULL;
    }

    if(list->start == NULL)
    {
        perror("List is empty");
        return NULL;
    }

    StringNode* node = list->start;
    char* result = node->value;
    list->count -= 1;

    if(list->start == list->end)
    {
        list->start = NULL;
        list->end = NULL;
        free(node);
        return result;
    }

    list->start = node->next;
    list->start->previous = NULL;
    free(node);
    return result;
}

/// @brief Removes, deletes, and returns the end element of a `list`
/// @param list 
/// @return String at list[size - 1]
char* popEnd(StringList* list)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return NULL;
    }

    if(list->end == NULL)
    {
        perror("List is empty");
        return NULL;
    }

    StringNode* node = list->end;
    char* result = node->value;
    list->count -= 1;

    if(list->start == list->end)
    {
        list->start = NULL;
        list->end = NULL;
        free(node);
        return result;
    }

    list->end = node->previous;
    list->end->next = NULL;
    free(node);
    return result;
}

/// @param list 
/// @return Integer size of `list`
int size(StringList* list)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return -1;
    }

    return list->count;
}

/// @brief Frees a string list `list` and all elements stored in the `list`
/// @param list A string list to be deallocated
void deallocateStringList(StringList* list)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return;
    }

    while(list->count > 0)
    {
        char* value = popStart(list);
        free(value);
    }

    free(list);
}

/// @brief Prints all elements of a `list` to the console 
/// @param list 
void printList(StringList *list)
{
    if(list == NULL)
    {
        perror("list is null and cannot be referenced");
        return;
    }

    StringNode* node = list->start;
    int i = 0;

    while(node != NULL)
    {
        printf("-------------------------------------\nIndex: %d\nValue: %s\n", i, node->value);
        node = node->next;
        i++;
    }
}

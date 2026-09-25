#include "symbolTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// @brief Creates a one node string tree with a root `key` and `value`
/// @param key 
/// @param value 
/// @return String Tree reference
Tree* createRoot(char* key, char* value)
{
    return createNewNode(key, value);
}

/// @brief Adds a `key` and `value` to a `tree`
/// @param tree 
/// @param key 
/// @param value 
/// @return Returns -1 for an error, 0 for no error but not added, and 1 for successful addition
int addKey(Tree* tree, char* key, char* value)
{
    if(tree == NULL || key == NULL)
    {
        perror("Tree and/or key is null and cannot be referenced");
        return -1;
    }

    tree->size++;

    int direction = getNextNodeDirection(tree, key);

    int res = checkAndFill(tree, direction, key, value);

    if(res != 0)
    {
        return res;
    }

    return addKey(getNextNode(tree, direction), key, value);
}

/// @brief
/// @param tree 
/// @param key 
/// @param value 
/// @return Returns -1 for an error, 0 for no error but not filled, and 1 for successful filling
int checkAndFill(Tree* tree, int direction, char* key, char* value)
{
    if(getNextNode(tree, direction) != NULL)
    {
        return 0;
    }

    Tree* addition = createNewNode(key, value);

    if(addition == NULL)
    {
        return -1;
    }

    if(direction < 0)
    {
        tree->left = addition;
    }
    else
    {
        tree->right = addition;
    }

    return 1;
}

/// @brief Creates a new one node subtree with a `key` and `value` 
/// @param key 
/// @param value 
/// @return String Tree reference
Tree* createNewNode(char* key, char* value)
{
    if(value == NULL)
    {
        perror("Value is null and cannot be referenced");
        return NULL;
    }

    Tree* node = (Tree*)malloc(sizeof(Tree));

    node->key = (char*)malloc(strlen(key) + 1);
    strcpy(node->key, key);

    node->value = (char*)malloc(strlen(value) + 1);
    strcpy(node->value, value);

    node->left = NULL;
    node->right = NULL;
    node->size = 0;

    return node;
}

/// @param tree 
/// @param key 
/// @return The value associated with a `key` in a `tree` 
char* getValueByKey(Tree* tree, char* key)
{
    if(key == NULL)
    {
        perror("Key is null and cannot be referenced");
        return NULL;
    }

    if(tree == NULL)
    {
        // There is no value associated with key in this tree
        return NULL;
    }

    if(strcmp(key, tree->key) == 0)
    {
        char* res = (char*)malloc(strlen(tree->value) + 1);
        strcpy(res, tree->value);
        return res;
    }

    Tree* nextNode = getNextNode(tree, getNextNodeDirection(tree, key));
    getValueByKey(nextNode, key);
}

/// @brief Calculate where the next direction of a `tree` should be given a `key`
/// @param tree 
/// @param key 
/// @return -1 for the left, 1 for the right, and 0 for equal keys
int getNextNodeDirection(Tree* tree, char* key)
{
    return strcmp(key, tree->key);
}

/// @param tree 
/// @param direction Integer value where x < 0 is left and x >= 0 is right 
/// @return Next node in a `tree` given a `direction`
Tree* getNextNode(Tree* tree, int direction)
{
    return direction < 0 ? tree->left : tree->right;
}

/// @brief Frees a string symbol tree `tree` and all elements stored in the `tree`
/// @param tree A tree to be deallocated
void deallocateTree(Tree* tree)
{
    if(tree == NULL)
    {
        return;
    }

    deallocateTree(tree->left);
    deallocateTree(tree->right);
    
    free(tree->key);
    free(tree->value);
    free(tree);
}

/// @brief Prints all elements of a `tree` to the console 
/// @param tree 
void printTree(Tree* tree)
{
    if(tree == NULL)
    {
        return;
    }

    printf("Key: %s\nValue: %s\n------------------\n", tree->key, tree->value);
    printTree(tree->left);
    printTree(tree->right);
}
#ifndef tree_H
#define tree_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>

typedef const char* tree_element; // ЕСЛИ МЕНЯЕШЬ ТИП, ТО НАДО ПОПРАВИТЬ АРГУМЕНТЫ AddNode и Label в TreeDumpDot

const size_t BUFFER_SIZE = 20000;

typedef struct BinaryTree
{
    tree_element value;
    struct BinaryTree *left;
    struct BinaryTree *right;
    int height;
} BinaryTree;

enum Type
{
    INT = 0x000001,
    STRING = 0x000002,
};


enum TreeErrors
{
    OK                    = 0x000000,
    ALLOC_ERROR           = 0x000001,
    NODE_NULL             = 0x000002,
    FILE_NOT_OPEN         = 0x000004,
};

const enum Type TREE_ELEMENT_TYPE = STRING; // как сделать по другому?

TreeErrors CreateNode(BinaryTree **Node, tree_element value);
TreeErrors FreeTree(BinaryTree **Node);
TreeErrors AddNode(BinaryTree **Root, tree_element value);
BinaryTree* FindNode(BinaryTree *Root, tree_element value);
TreeErrors TreeTraversal(BinaryTree *Node);
TreeErrors AddNodeLoop(BinaryTree **Root, tree_element value);
TreeErrors DeleteNode(BinaryTree **Root, tree_element value);
TreeErrors TreeDumpDot(BinaryTree *Root);
int GenerateGraph(BinaryTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE);
int CompareValue(tree_element a, tree_element b);

#endif // tree_H

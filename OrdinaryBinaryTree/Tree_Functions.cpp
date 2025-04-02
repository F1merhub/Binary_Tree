#include "tree.h"

/*
    Создает узел по указателю на указатель равный null
    используем в Addnode

*/
TreeErrors CreateNode(BinaryTree **Node, tree_element value)
{
    assert(*Node == NULL && Node != NULL);
    *Node = (BinaryTree*)calloc(1, sizeof(BinaryTree));

    if (*Node == NULL)
    {
        return ALLOC_ERROR;
    }

    (*Node)->value = value;
    (*Node)->left = NULL;
    (*Node)->right = NULL;

    return OK;
}


TreeErrors FreeTree(BinaryTree **Node)
{
    assert(Node); // нулевой указатель может передать сам программист

    if (*Node == NULL)
    {
        return OK;
    }

    FreeTree(&((*Node)->left));
    FreeTree(&((*Node)->right));

    free(*Node);
    *Node = NULL;

    return OK;
}

TreeErrors AddNode(BinaryTree **Root, tree_element value) // TODO если объекты равны
{
    assert(Root != NULL);

    if (*Root == NULL)
    {
        return CreateNode(Root, value);
    }

    TreeErrors error_buffer = OK;
    if (CompareValue(value, (*Root)->value) < 0)  // Использование CompareValue
    {
        return AddNode(&((*Root)->left), value);
    }
    else
    {
        return AddNode(&((*Root)->right), value);
    }

    return OK;
}

TreeErrors AddNodeLoop(BinaryTree **Root, tree_element value)
{
    if (*Root == NULL)
    {
        return CreateNode(Root, value);
    }

    BinaryTree *cur = *Root;

    while (cur != NULL)
    {
        if (CompareValue(value, cur->value) < 0)  // Использование CompareValue
        {
            if (cur->left != NULL)
            {
                cur = cur->left;
            }
            else
            {
                return CreateNode(&(cur->left), value);
            }
        }
        else
        {
            if (cur->right != NULL)
            {
                cur = cur->right;
            }
            else
            {
                return CreateNode(&(cur->right), value);
            }
        }
    }

    return OK;
}

BinaryTree* FindNode(BinaryTree *Root, tree_element value) // рекурсивный поиск
{
    if (Root == NULL)
    {
        return NULL;
    }

    if (CompareValue(Root->value, value) == 0)  // Использование CompareValue
        return Root;

    if (CompareValue(value, Root->value) < 0)  // Использование CompareValue
    {
        return FindNode(Root->left, value);
    }
    else
    {
        return FindNode(Root->right, value);
    }

    return NULL;
}

TreeErrors TreeTraversal(BinaryTree *Node)
{
    if (Node == NULL)
    {
        return NODE_NULL;
    }

    TreeTraversal(Node->left);
    printf("ELEMENT_SPECIFICATOR ", Node->value);
    TreeTraversal(Node->right);

    return OK;
}

TreeErrors DeleteNode(BinaryTree **Root, tree_element value)
{
    if (*Root == NULL)
    {
        return NODE_NULL;
    }

    if (CompareValue(value, (*Root)->value) < 0)  // Использование CompareValue
    {
        return DeleteNode(&((*Root)->left), value);
    }
    else if (CompareValue(value, (*Root)->value) > 0)  // Использование CompareValue
    {
        return DeleteNode(&((*Root)->right), value);
    }
    else
    {
        if ((*Root)->left == NULL)
        {
            BinaryTree *temp = *Root;
            *Root = (*Root)->right;
            free(temp);
            temp = NULL;
        }
        else if ((*Root)->right == NULL)
        {
            BinaryTree *temp = *Root;
            *Root = (*Root)->left;
            free(temp);
            temp = NULL;
        }
        else
        {
            BinaryTree *minNode = (*Root)->right;
            while (minNode->left != NULL)
            {
                minNode = minNode->left;
            }

            (*Root)->value = minNode->value;
            return DeleteNode(&((*Root)->right), minNode->value);
        }
    }

    return OK;
}

int CompareValue(tree_element a, tree_element b) {
    switch (TREE_ELEMENT_TYPE) {
        case (INT):
            return a - b;
        case (STRING):
            return strcmp(a, b);
        default:
            return 0;
    }
}

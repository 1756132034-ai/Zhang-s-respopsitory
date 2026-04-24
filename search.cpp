// Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct TreeNode
{
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;
} TreeNode, *Bitree;

void preOrder(Bitree T)
{
    if (T == NULL)
    {
        return;
    }
    printf("%d", T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
    return;
}

int search_bst(Bitree T, int value, Bitree parent, Bitree *pos)
{
    if (T == NULL)
    {
        *pos = parent;
        return 0;
    }
    if (T->data == value)
    {
        *pos = T;
        return 1;
    }

    if (T->data > value)
    {
        return search_bst(T->lchild, value, parent, pos);
    }
    else
    {
        return search_bst(T->rchild, value, parent, pos);
    }
}

int insert_bst(Bitree *T, int value)
{
    Bitree parent, pos;
    Bitree curr;

    int Status = search_bst(*T, value, NULL, &pos);
    if (Status == 0)
    {
        curr = (Bitree)malloc(sizeof(TreeNode));
        curr->data = value;
        curr->lchild = NULL;
        curr->rchild = NULL;

        if (pos == NULL)
        {
            *T = curr;
        }
        else if (value < pos->data)
        {
            pos->lchild = curr;
        }
        else
        {
            pos->rchild = curr;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    int i = 0;
    Bitree T = NULL;

    int treeArr[] = {70, 55, 49, 30, 53, 80, 75, 98, 95};

    for (int i = 0; i < 10; i++)
    {
        insert_bst(&T, treeArr[i]);
    }
    preOrder(T);
    printf("\n");

    insert_bst(&T, 99);

    preOrder(T);
    printf("\n");

    return 0;
}
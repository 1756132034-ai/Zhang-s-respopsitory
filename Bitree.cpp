#include <iostream>
#include <string>
using namespace std;
typedef int ElemType;
typedef int Statue;

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltags;
    int rtags;
} ThreadNode;

typedef ThreadNode *ThreadTree;
typedef char ElemType;
string str;
int idx = 0;
typedef struct TreeNode
{
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;
} TreeNode;

typedef TreeNode *Binarytree;

typedef struct Stack
{
    Binarytree data[MAXSIZE]; // 栈数组，元素为二叉树结点指针
    int top;                  // 栈顶指针，-1表示空栈
} Stack;

typedef char ElemType;

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag;
    int rtag;
} ThreadNode;

typedef struct
{
    ElemType data[MAXSIZE];
    int rear;
    int front;
} Queue;

typedef ThreadNode *ThreadTree;

int preOrder(Binarytree T)
{
    if (T == NULL)
    {
        return ERROR;
    }
    cout << T->data << endl;
    preOrder(T->lchild);
    preOrder(T->rchild);
}

void initStack(Stack *s)
{
    s->top = -1;
}

int pop(Stack *s, Binarytree *e)
{
    if (isEmpty(s))
        return 0; // 栈空
    *e = s->data[s->top--];
    return 1;
}

int push(Stack *s, Binarytree e)
{
    if (s->top == MAXSIZE - 1)
        return 0; // 栈满
    s->data[++s->top] = e;
    return 1;
}

void creatTree(Binarytree *T)
{
    ElemType ch;
    ch = str[idx++];
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (Binarytree)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        creatTree(&(*T)->lchild);
        creatTree(&(*T)->rchild);
    }
}

void initQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

int isEmpty(Stack *s)
{
    return s->top == -1 ? OK : ERROR;
}

int inOrder(Binarytree T)
{
    if (T == NULL)
    {
        return ERROR;
    }
    inOrder(T->lchild);
    cout << T->data << endl;
    inOrder(T->rchild);
}

int postOrder(Binarytree T)
{
    if (T == NULL)
    {
        return ERROR;
    }
    postOrder(T->lchild);
    postOrder(T->rchild);
    cout << T->data << endl;
}

int iterPreOrder(Stack *s, Binarytree T)
{
    while (T != NULL || isEmpty(s) != 0)
    {
        while (T != NULL)
        {
            printf("%c ", T->data);
            push(s, T);
            T = T->lchild;
        }
        pop(s, &T);
        T = T->rchild;
    }
}

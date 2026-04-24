#include <iostream>
#include <cstdlib> // malloc 所需
#include <cstdio>  // printf
#include <string>
using namespace std;

// 统一宏定义
#define OK 1
#define ERROR 0
#define MAXSIZE 100

// 统一元素类型
typedef char ElemType;
typedef int Status;

// ===================== 普通二叉树结点 =====================
typedef struct TreeNode
{
    ElemType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode, *Binarytree;

// ===================== 栈结构（用于非递归遍历） =====================
typedef struct Stack
{
    Binarytree data[MAXSIZE];
    int top;
} Stack;

// ===================== 队列结构（用于层序遍历） =====================
typedef struct
{
    Binarytree data[MAXSIZE];
    int rear;
    int front;
} Queue;

// ===================== 线索二叉树结点 =====================
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag; // 0=孩子 1=前驱线索
    int rtag; // 0=孩子 1=后继线索
} ThreadNode, *ThreadTree;

// 全局变量:用于建树 & 线索化
string str;
int idx = 0;
ThreadNode *pre = NULL; // 前驱指针（线索化必备）

// ===================== 栈操作函数 =====================
void initStack(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1 ? OK : ERROR;
}

int push(Stack *s, Binarytree e)
{
    if (s->top == MAXSIZE - 1)
        return ERROR;
    s->data[++s->top] = e;
    return OK;
}

int pop(Stack *s, Binarytree *e)
{
    if (isEmpty(s))
        return ERROR;
    *e = s->data[s->top--];
    return OK;
}

// ===================== 队列操作函数（补全） =====================
void initQueue(Queue *Q)
{
    Q->front = Q->rear = 0;
}

int isQueueEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}

int enQueue(Queue *Q, Binarytree e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

int deQueue(Queue *Q, Binarytree *e)
{
    if (isQueueEmpty(Q))
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

// ===================== 1. 创建普通二叉树（递归） =====================
void creatTree(Binarytree *T)
{
    ElemType ch = str[idx++];
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

// ===================== 2. 递归遍历 =====================
//前序遍历
void preOrder(Binarytree T)
{
    if (T)
    {
        cout << T->data << " ";
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

//中序遍历
void inOrder(Binarytree T)
{
    if (T)
    {
        inOrder(T->lchild);
        cout << T->data << " ";
        inOrder(T->rchild);
    }
}

//后序遍历
void postOrder(Binarytree T)
{
    if (T)
    {
        postOrder(T->lchild);
        postOrder(T->rchild);
        cout << T->data << " ";
    }
}

// ===================== 3. 非递归前序遍历（补全返回值） =====================
int iterPreOrder(Stack *s, Binarytree T)
{
    while (T != NULL || !isEmpty(s))
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
    return OK;
}

// ===================== 4. 层序遍历（补全功能） =====================
void levelOrder(Binarytree T, Queue *Q)
{
    if (!T)
        return;
    initQueue(Q);
    enQueue(Q, T);

    while (!isQueueEmpty(Q))
    {
        Binarytree node;
        deQueue(Q, &node);
        cout << node->data << " ";

        if (node->lchild)
            enQueue(Q, node->lchild);
        if (node->rchild)
            enQueue(Q, node->rchild);
    }
}

// ===================== 5. 普通二叉树 转 中序线索二叉树 =====================
// 把普通树复制成线索树
void copyTree(Binarytree t, ThreadTree &tt)
{
    if (!t)
    {
        tt = NULL;
        return;
    }
    tt = (ThreadTree)malloc(sizeof(ThreadNode));
    tt->data = t->data;
    tt->ltag = 0;
    tt->rtag = 0;
    copyTree(t->lchild, tt->lchild);
    copyTree(t->rchild, tt->rchild);
}

// 中序线索化递归
void InThread(ThreadTree T)
{
    if (T)
    {
        InThread(T->lchild);

        if (!T->lchild)
        {
            T->ltag = 1;
            T->lchild = pre;
        }
        if (pre && !pre->rchild)
        {
            pre->rtag = 1;
            pre->rchild = T;
        }
        pre = T;

        InThread(T->rchild);
    }
}

// 创建中序线索二叉树
void CreateInThread(ThreadTree T)
{
    pre = NULL;
    if (T)
    {
        InThread(T);
        if (!pre->rchild)
            pre->rtag = 1;
    }
}

// ===================== 6. 遍历中序线索二叉树（无需栈） =====================
void InOrderThread(ThreadTree T)
{
    ThreadNode *p = T;
    while (p)
    {
        while (p->ltag == 0)
            p = p->lchild;
        cout << p->data << " ";
        while (p->rtag == 1 && p->rchild)
        {
            p = p->rchild;
            cout << p->data << " ";
        }
        p = p->rchild;
    }
}

// ===================== 主函数测试 =====================
int main()
{
    Binarytree T;
    ThreadTree TT;
    Stack s;
    Queue q;

    // 测试用例:AB#D##C##
    cout << "请输入二叉树扩展序列（如 AB#D##C##):";
    cin >> str;
    idx = 0;

    // 创建普通二叉树
    creatTree(&T);

    cout << "\n递归先序:";
    preOrder(T);
    cout << "\n递归中序:";
    inOrder(T);
    cout << "\n递归后序:";
    postOrder(T);

    cout << "\n非递归先序:";
    initStack(&s);
    iterPreOrder(&s, T);
    cout << "\n层序遍历:";
    levelOrder(T, &q);

    // 转为线索二叉树
    copyTree(T, TT);
    CreateInThread(TT);
    cout << "\n线索二叉树中序:";
    InOrderThread(TT);

    cout << endl;
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef int VertextType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct
{
    VertextType vertext[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Graph;

typedef struct EdgeNode
{
    int edge_vex;
    struct EdgeNode *next;
}EdgeNode;

typedef struct VertextNode
{
    int in;
    VertextType data;
    EdgeNode *head;
}VertextNode;

typedef VertextNode Adj_List[MAXSIZE];

typedef struct
{
    Adj_List adj_list;
    int vertet_num;
    int edge_num;
}Adj_Graph;

typedef Adj_Graph *Adj_List_Graph;

int top = -1;
int stack[MAXSIZE];

void push(int e)
{
    if(top > MAXSIZE)
    {
        printf("满了\n");
        return ;
    }
    top++;
    stack[top] = e;
}

int pop()
{
    if (top == -1)
    {
        printf("栈空，无法出栈\n");
        return -1;
    }
    int e = stack[top];
    top--;
    return e;
}

int is_empty()
{
    if(top == -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
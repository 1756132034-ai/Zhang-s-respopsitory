#include <iostream>
#include <stdlib.h>
using namespace std;

// 你要求的宏定义
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef char VertextType; // 顶点数据类型（如 A、B、C）

// ====================== 1. 邻接表结构体定义 ======================
// 边结点
typedef struct EdgeNode
{
    int adjvex;            // 邻接点的下标
    int weight;            // 边的权值（关键路径需要）
    struct EdgeNode *next; // 下一条边
} EdgeNode;

// 顶点结点
typedef struct VNode
{
    VertextType data;    // 顶点数据
    int in;              // 入度
    EdgeNode *firstedge; // 边表头指针
} VNode;

// 图结构（邻接表）
typedef struct
{
    VNode adjList[MAXSIZE]; // 顶点数组
    int numVertexes;        // 顶点数
    int numEdges;           // 边数
} GraphAdjList;

// ====================== 2. 全局变量（拓扑排序用） ======================
int topo[MAXSIZE]; // 存储拓扑序列
int top = -1;      // 栈顶指针
int etv[MAXSIZE];  // 事件最早发生时间
int ltv[MAXSIZE];  // 事件最晚发生时间

// ====================== 3. 创建有向网（邻接表） ======================
void CreateGraph(GraphAdjList *G)
{
    int i, j, k;
    int weight;
    EdgeNode *e;

    cout << "请输入顶点数、边数：";
    cin >> G->numVertexes >> G->numEdges;

    // 初始化顶点
    for (i = 0; i < G->numVertexes; i++)
    {
        cout << "请输入顶点 " << i << " 的数据：";
        cin >> G->adjList[i].data;
        G->adjList[i].in = 0;
        G->adjList[i].firstedge = NULL;
    }

    // 初始化边
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "输入边 (vi, vj) 下标、权值：";
        cin >> i >> j >> weight;

        // 创建边结点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->weight = weight;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;

        G->adjList[j].in++; // 入度+1
    }
}

// ====================== 4. 拓扑排序（同时求 etv） ======================
int TopologicalSort(GraphAdjList *G)
{
    int i, k, gettop;
    int count = 0; // 统计输出顶点数
    EdgeNode *e;

    int *stack = (int *)malloc(G->numVertexes * sizeof(int));
    top = -1;

    // 入度为0的顶点入栈
    for (i = 0; i < G->numVertexes; i++)
    {
        if (G->adjList[i].in == 0)
            stack[++top] = i;
    }

    // 初始化最早开始时间
    for (i = 0; i < G->numVertexes; i++)
        etv[i] = 0;

    while (top != -1)
    {
        gettop = stack[top--];  // 出栈
        topo[count++] = gettop; // 存入拓扑序列

        // 遍历所有邻接点
        for (e = G->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;

            // 关键：更新 etv
            if (etv[k] < etv[gettop] + e->weight)
                etv[k] = etv[gettop] + e->weight;

            // 入度-1，为0则入栈
            if (!(--G->adjList[k].in))
                stack[++top] = k;
        }
    }

    // 判断是否有环
    if (count < G->numVertexes)
    {
        cout << "图中有环！" << endl;
        return ERROR;
    }
    return OK;
}

// ====================== 5. 关键路径 ======================
void CriticalPath(GraphAdjList *G)
{
    int i, k, j;
    int ete, lte; // 活动最早、最晚开始时间
    EdgeNode *e;

    // 先做拓扑排序
    TopologicalSort(G);

    // 初始化 ltv = 终点 etv
    for (i = 0; i < G->numVertexes; i++)
        ltv[i] = etv[G->numVertexes - 1];

    // 逆拓扑序求 ltv
    for (i = G->numVertexes - 1; i >= 0; i--)
    {
        k = topo[i];
        for (e = G->adjList[k].firstedge; e; e = e->next)
        {
            j = e->adjvex;
            if (ltv[k] > ltv[j] - e->weight)
                ltv[k] = ltv[j] - e->weight;
        }
    }

    // 求关键路径
    cout << "\n关键路径(活动):" << endl;
    for (i = 0; i < G->numVertexes; i++)
    {
        for (e = G->adjList[i].firstedge; e; e = e->next)
        {
            j = e->adjvex;
            ete = etv[i];
            lte = ltv[j] - e->weight;

            // 相等 = 关键活动
            if (ete == lte)
                cout << G->adjList[i].data << " -> " << G->adjList[j].data
                     << "  权值：" << e->weight << endl;
        }
    }
}

// ====================== 6. 主函数 ======================
int main()
{
    GraphAdjList G;
    CreateGraph(&G);

    cout << "\n拓扑序列:";
    TopologicalSort(&G);
    for (int i = 0; i < G.numVertexes; i++)
        cout << G.adjList[topo[i]].data << " ";
    cout << endl;

    CriticalPath(&G);

    return 0;
}
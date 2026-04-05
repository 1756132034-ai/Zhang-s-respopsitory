#include <iostream>
#include <stdlib.h>
using namespace std;
// 你要求的宏定义
#define OK 1
#define ERROR 0
#define MAXSIZE 100

// 二叉树结点结构
typedef struct TreeNode {
    int data;               // 结点数据
    struct TreeNode *lchild; // 左孩子
    struct TreeNode *rchild; // 右孩子
} TreeNode;

// 队列结构（层序遍历用）
typedef struct Queue {
    TreeNode* data[MAXSIZE]; // 存储树结点指针
    int front;               // 队头
    int rear;                // 队尾
} Queue;

// 初始化队列
Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = 0;
    return q;
}

// 判断队列是否为空
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// 获取队列当前元素个数
int queueSize(Queue* q) {
    return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}

// 入队
int enqueue(Queue* q, TreeNode* node) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        return ERROR; // 队满
    }
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % MAXSIZE;
    return OK;
}

// 出队
int dequeue(Queue* q, TreeNode** node) {
    if (isEmpty(q)) {
        return ERROR; // 队空
    }
    *node = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return OK;
}

// 层序遍历求二叉树最大深度
int maxDepth(TreeNode* root) {
    if (root == NULL) {
        return ERROR; // 空树深度为0，替换为ERROR
    }

    int depth = 0;
    Queue* q = initQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        int count = queueSize(q);
        while (count > 0) {
            TreeNode* curr;
            dequeue(q, &curr);

            if (curr->lchild != NULL) {
                enqueue(q, curr->lchild);
            }
            if (curr->rchild != NULL) {
                enqueue(q, curr->rchild);
            }
            count--;
        }
        depth++;
    }
    return depth;
}

// ------------------- 测试主函数 -------------------
int main() {
    // 构建一棵测试二叉树
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->lchild = (TreeNode*)malloc(sizeof(TreeNode));
    root->rchild = (TreeNode*)malloc(sizeof(TreeNode));
    root->lchild->data = 2;
    root->rchild->data = 3;
    root->lchild->lchild = NULL;
    root->lchild->rchild = NULL;
    root->rchild->lchild = NULL;
    root->rchild->rchild = NULL;

    int depth = maxDepth(root);
    printf("二叉树最大深度：%d\n", depth);

    return OK;
}
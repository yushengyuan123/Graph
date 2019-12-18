#include <stdio.h>
#include <stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define ERROR -1

typedef char VexType;
typedef int Status;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct AdjVexNode{
	int adjves;//邻接顶点在顶点数组中的位序
	struct AdjVexNode *nextArc;
	int info;//存储边(弧)相关信息
}AdjVexNode, *AdjVexNodeP;//邻接链表的结点类型

typedef struct VexNode {
	VexType data;//顶点值
	struct AdjVexNode *firstArc;//邻接表头指针
}VexNode;//顶点数组类型

typedef struct {
	VexNode *vexs;
	int n, e;
	int *tags;//标志数组
}ALGraph;//邻接表的类型

typedef struct {
	VexType v,w;//边弧信息
	int info;//权值
}ArcInfo;

//队列结点及指针类型
typedef struct LQNode {
    int data;
    struct LQNode *next;
} LQNode, *QueuePtr;

//队队列
typedef struct {
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
} LQueue;

/**
* function:初始化队列。
* params:队列
*/
Status InitQueue_LQ(LQueue *Q) {
    Q->front =(LQNode *)malloc(sizeof(LQNode));
    Q->rear = Q->front;
    if(Q->front == NULL && Q->rear == NULL) {
        return ERROR;
    }
    Q->front->next = Q->rear->next = NULL;
    return 1;
}

/**
* function:入队操作。
* params:队列，需要入队的函数
*/
Status EnQueue_LQ(LQueue *Q, VexType e) {
    LQNode *p;
    p = (LQNode *)malloc(sizeof(LQNode));

    if(p == NULL) {
        return ERROR;
    }

    p->data = e;
    p->next = NULL;
    if(Q->rear == Q->front) {
        Q->front->next = p;
        Q->rear = p;
    } else {
        Q->rear->next = p;
        Q->rear = p;
    }
    return 1;
}

/**
* function:出队操作。
* params:队列
*/
Status DeQueue_LQ(LQueue *Q, int *k) {
    LQNode *p = Q->front->next;
    if(Q->front == Q->rear) {
        return ERROR;
    } else if(p == Q->rear) {
        Q->front->next = NULL;
        Q->rear = Q->front;
        *k = p->data;
        free(p);
        return 1;
    }
    *k = p->data;
    Q->front->next = p->next;
    free(p);
    return 1;
}

/**
* function:队列的遍历。
* params:队列
*/
void TravelQueue(LQueue *Q) {
    LQNode *p = Q->front->next;

    while(p != NULL) {
        printf("%d", p->data);
        p = p->next;
    }
}


/**
*功能：查找数据域对应数据在图中的位序。
*参数说明：图，数据域数据
*/
int LocateVex_A(ALGraph *G, VexType v) {
	int i;
	for(i = 0; i < G->n; i++) {
		if(G->vexs[i].data == v) {
			return i;
		}
	}
	return -1;
};


/**
* function:创建有向图的邻接表存储结构
* params:邻接表，表的类型，顶点数组，顶点数，边的信息，边数
*/
Status CreateGraph_AL(ALGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e) {
	int i,j,k;
	VexType v,w;
	G->n = n;
	G->e = e;
	G->vexs = (VexNode *)malloc(n * sizeof(VexNode));
	G->tags = (int *)malloc(n * sizeof(int));
	AdjVexNode *p;

	for(i = 0; i < G->n; i++) {
		G->tags[i] = UNVISITED;
		G->vexs[i].data = vexs[i];
		G->vexs[i].firstArc = NULL;
	}

	for(k = 0; k < G->e; k++) {
		v = arcs[k].v;
		w = arcs[k].w;
		i = LocateVex_A(G, v);
		j = LocateVex_A(G, w);

		if(i < 0 || j < 0)
			return ERROR;
		p = (AdjVexNode *)malloc(sizeof(AdjVexNode));
		if(p == NULL)
			return ERROR;
		p->adjves = j;
		p->nextArc = G->vexs[i].firstArc;
		G->vexs[i].firstArc = p;
	}

	return 1;
};

/**
*功能：插入边或弧,在图中增加k顶点到m顶点的边或弧
*参数说明：图，顶点k，顶点m，顶点权值
*/
Status AddArc_AL(ALGraph *G, int k, int m, int info) {
	AdjVexNode *p;

	if(k < 0 || m < 0 || k >G->n || m > G->n) {
		return ERROR;
	}

	p = G->vexs[k].firstArc;

	if(p == NULL) {
		return ERROR;
	}
	//判断弧是否存在
	while(p != NULL) {
		if(m == p->adjves) {
			return ERROR;
		}
	}

	p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));

	if(p == NULL) {
		return ERROR;
	}

	p->adjves = m;
	p->info = info;
	p->nextArc = G->vexs[k].firstArc;
	G->vexs[k].firstArc = p;
	G->e++;

	return 1;
};

/**
* function:求某个顶点第一个邻接顶点
* params:图查找顶点数组中位序为k的顶点
*/
int FirstAdjVex_AL(ALGraph *G, int k, AdjVexNodeP *p) {
	if(k < 0 || k > G->n) {
		return ERROR;
	}

	*p = G->vexs[k].firstArc;

	if(*p != NULL) {
		return (*p)->adjves;
	} else {
		return ERROR;
	}
};

/**
*功能：求某个顶点下一个邻接顶点
*参数说明：图，查找顶点数组中位序为k的顶点
*/
int NextAdjVex_AL(ALGraph *G, int k, AdjVexNodeP *p) {
	if(k < 0 || k > G->n) {
		return -1;
	}
	if(*p == NULL) {
		return -1;
	} else {
		(*p) = (*p)->nextArc;
		if((*p) != NULL) {
			return (*p)->adjves;
		} else {
			return -1;
		}
	}
};

/**
* function:输入顶点之间边的信息，即数组arcs的信息
* params:顶点数组,边弧信息,边的数量。
*/
Status initEdge(VexType *vexs, ArcInfo *arcs, int e, int n) {
	int i, j, right, index = 0;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("请输入第%c个与%c之间的信息,如果连通则输入权值，如果不连通则输入0\n", vexs[i], vexs[j]);
			fflush(stdin);
			scanf("%d", &right);
			if(right > 0) {
				arcs[index].info = right;
				arcs[index].v = vexs[i];
				arcs[index].w = vexs[j];
				printf("%d,%c,%c\n", arcs[index].info,arcs[index].v,arcs[index].w);
				index++;//记录边的条数看是否匹配，不匹配则重新输入。
				if(index == e) {
                    return 1;
                }
			} else {
				continue;
			}
		}
	}
	return 1;
}

/**
* function：输入顶点信息
* params：
*/
Status initPoint(VexType *vexs, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("第%d个顶点的数值域信息:", i + 1);
		//清空输入缓冲区避免输入时候出现的bug
		fflush(stdin);
		vexs[i] = getchar();
		printf("%c\n", vexs[i]);
	}
	return 1;
}

/**
* function：连通图的遍历 (深度优先)
* params：图，从k顶点出发
*/
Status DFS_M(ALGraph *G, int k) {
	int i;
	G->tags[k] = VISITED;
	//记录第一个顶点所在位置指针
	printf("%c", G->vexs[k]);
	AdjVexNode *p;

    p = G->vexs[k].firstArc;
	while(p) {
        if(!G->tags[p->adjves]) {
            DFS_M(G, p->adjves);
        }
        p = p->nextArc;
	}
	return 1;
};

/**
* function：连通图的遍历 (广度优先)
* params：图
*/
Status BFSTraverse_AL(ALGraph *G) {
    int i,j,k;

    AdjVexNode *p;
    LQueue Q;
    InitQueue_LQ(&Q);

    for(i = 0; i < G->n; i++) {
        G->tags[i] = UNVISITED;
    }

    //外层的for循环是防止非连通图的出现
    for(i = 0; i < G->n; i++) {
        if(UNVISITED == G->tags[i]) {
            printf("%c ", G->vexs[i].data);
            EnQueue_LQ(&Q, i);
            //TravelQueue(&Q);
            printf("\n");
            while(DeQueue_LQ(&Q, &k) != ERROR) {
                for(j = FirstAdjVex_AL(G, k, &p); j >= 0; j = NextAdjVex_AL(G, k, &p)) {
                    if(UNVISITED == G->tags[j]) {
                        printf("%c ", G->vexs[j]);
                        G->tags[j] = VISITED;
                        EnQueue_LQ(&Q, j);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
	ALGraph	*p = (ALGraph *)malloc(sizeof(ALGraph));
	LQueue q;
	VexType *vexs;
	//存放顶点信息的数组
	ArcInfo *arcs;
	int i;
	//图结点的数量
	int n;
	//图的边的数目
	int e;

	printf("请输入节点数量\n");
	scanf("%d", &n);
	vexs = (VexType *)malloc(n * sizeof(VexType));
	printf("请输入图的边的数目\n");
	scanf("%d", &e);
	arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
	printf("请输入图顶点的数值域\n");
	if(initPoint(vexs, n)) {
		printf("输入成功\n");
		if(initEdge(vexs, arcs, e, n)) {
			CreateGraph_AL(p, vexs, n, arcs, e);
			printf("我真的是叼你了%d", p->vexs[0].firstArc->nextArc->adjves);
			printf("图创建成功\n");
			printf("深度遍历结果\n");
			//DFS_M(p , 0);
			BFSTraverse_AL(p);
		} else {
			printf("输入失败\n");
		}
	}
}

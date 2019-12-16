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
*功能：创建有向图的邻接表存储结构 
*参数说明：邻接表，表的类型，顶点数组，顶点数，边的信息，边数  
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
*功能：求某个顶点第一个邻接顶点 
*参数说明：图，查找顶点数组中位序为k的顶点 
*/
int FirstAdjVex_AL(ALGraph *G, int k, AdjVexNode *p) {
	if(k < 0 || k > G->n) {
		return ERROR;
	}
	
	p = G->vexs[k].firstArc;
	
	if(p != NULL) {
		return p->adjves;
	} else {
		return -1;
	}
};

/**
*功能：求某个顶点下一个邻接顶点 
*参数说明：图，查找顶点数组中位序为k的顶点 
*/
int NextAdjVex_AL(ALGraph *G, int k, AdjVexNode *p) {
	if(k < 0 || k > G->n) {
		return -1;
	}
	
	if(p == NULL) {
		return -1;
	} else {
		p = p->nextArc;
		if(p != NULL) {
			return p->adjves;
		} else {
			return -1;
		}
	}	
};

/**
*功能：连通图的遍历 (深度优先) 
*参数说明：图，从k顶点出发 
*/
Status DFS_M(ALGraph *G, int k) {
	int i;
	G->tags[k] = VISITED;
	//记录第一个顶点所在位置指针 
	AdjVexNodeP p;
	printf("%c", G->vexs[k]);
	if(G->vexs[k].firstArc == NULL) {
		return ERROR; 
	} 
 	
	for(i = FirstAdjVex_AL(G, k, p); i >= 0; i = NextAdjVex_AL(G, k, p)) {
		if(UNVISITED == G->tags[i]) {
			if(ERROR == DFS_M(G, i))
				return ERROR; 
		}
	}
	
	return 1;
	
};

/**
*功能：根据顶点的位序查出顶点的值 
*参数说明：
*/
Status PointValue(VexType *vexs, n, VexType *vexs, ArcInfo *arcs) {
	int i;
	for(i = 0; i < )
}

/**
*功能：输入顶点信息 
*参数说明：
*/
Status initGraph(VexType *vexs, n, VexType *vexs, ArcInfo *arcs) {
	int i, j, right;
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			printf("请输入第%c个与%c之间的信息,如果连通则输入权值，如果不连通则输入0\n", vexs[i], vexs[j]);
			scanf("%d", &right);
			if(right > 0) {
				
			}
		}
		printf("请输入第%d个顶点\n", vexs[i]);
		scanf("%c", &vexs[i]);
	}
	return 1;
}

/**
*功能：输入边信息 
*参数说明：
*/
Status initEdge(VexType *vexs, n, VexType *vexs) {
	int i;
	for(i = 0; i < n * (n - 1); i++) {
		printf("第%d个顶点\n", vexs[i]);
		scanf("%c", &vexs[i]);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	ALGraph	*p = (ALGraph *)malloc(sizeof(ALGraph));
	VexType *vexs = (VexType *)malloc(3 * sizeof(VexType));
	ArcInfo *arcs = (ArcInfo *)malloc(3 * sizeof(ArcInfo));
	int i;
	int n;//图结点的数量 
		
	//用3个结点来进行测试 
	vexs[0] = 'A';
	vexs[1] = 'B';
	vexs[2] = 'C';
	//第一条边起始结点A，终点B，权值3 
//	arcs[0].v = 'A';
//	arcs[0].w = 'B';
//	arcs[0].info = 3;
//	//第二条边起始结点B，终点C，权值1 	
//	arcs[1].v = 'B';
//	arcs[1].w = 'C';
//	arcs[1].info = 1;
//	//第三条边起始结点A，终点C，权值1	
//	arcs[2].v = 'A';
//	arcs[2].w = 'C';
//	arcs[2].info = 2;
	printf("请输入节点数量\n");
	scanf("%c", &n);
	printf("请输入结点数值信息\n");
	initGraph(vexs, n);
	printf("请输入边信息\n");
	
	if(CreateGraph_AL(p, vexs, 3, arcs, 3)) {
		printf("创建成功！图为:");
		for(i = 0; i < p->n; i++) {
			printf("%c", p->vexs[i].data);
		}
	} else {
		printf("创建失败");
	}
		
}

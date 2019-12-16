#include <stdio.h>
#include <stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define ERROR -1

typedef char VexType;
typedef int Status;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct AdjVexNode{
	int adjves;//�ڽӶ����ڶ��������е�λ��
	struct AdjVexNode *nextArc;
	int info;//�洢��(��)�����Ϣ	
}AdjVexNode, *AdjVexNodeP;//�ڽ�����Ľ������ 

typedef struct VexNode {
	VexType data;//����ֵ
	struct AdjVexNode *firstArc;//�ڽӱ�ͷָ�� 
}VexNode;//������������ 

typedef struct {
	VexNode *vexs;
	int n, e;
	int *tags;//��־���� 
}ALGraph;//�ڽӱ������ 

typedef struct {
	VexType v,w;//�߻���Ϣ
	int info;//Ȩֵ 
}ArcInfo;

/**
*���ܣ������������Ӧ������ͼ�е�λ�� 
*����˵����ͼ������������ 
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
*���ܣ���������ͼ���ڽӱ�洢�ṹ 
*����˵�����ڽӱ�������ͣ��������飬���������ߵ���Ϣ������  
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
*���ܣ�����߻�,��ͼ������k���㵽m����ı߻� 
*����˵����ͼ������k������m������Ȩֵ  
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
	//�жϻ��Ƿ���� 
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
*���ܣ���ĳ�������һ���ڽӶ��� 
*����˵����ͼ�����Ҷ���������λ��Ϊk�Ķ��� 
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
*���ܣ���ĳ��������һ���ڽӶ��� 
*����˵����ͼ�����Ҷ���������λ��Ϊk�Ķ��� 
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
*���ܣ���ͨͼ�ı��� (�������) 
*����˵����ͼ����k������� 
*/
Status DFS_M(ALGraph *G, int k) {
	int i;
	G->tags[k] = VISITED;
	//��¼��һ����������λ��ָ�� 
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
*���ܣ����ݶ����λ���������ֵ 
*����˵����
*/
Status PointValue(VexType *vexs, n, VexType *vexs, ArcInfo *arcs) {
	int i;
	for(i = 0; i < )
}

/**
*���ܣ����붥����Ϣ 
*����˵����
*/
Status initGraph(VexType *vexs, n, VexType *vexs, ArcInfo *arcs) {
	int i, j, right;
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			printf("�������%c����%c֮�����Ϣ,�����ͨ������Ȩֵ���������ͨ������0\n", vexs[i], vexs[j]);
			scanf("%d", &right);
			if(right > 0) {
				
			}
		}
		printf("�������%d������\n", vexs[i]);
		scanf("%c", &vexs[i]);
	}
	return 1;
}

/**
*���ܣ��������Ϣ 
*����˵����
*/
Status initEdge(VexType *vexs, n, VexType *vexs) {
	int i;
	for(i = 0; i < n * (n - 1); i++) {
		printf("��%d������\n", vexs[i]);
		scanf("%c", &vexs[i]);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	ALGraph	*p = (ALGraph *)malloc(sizeof(ALGraph));
	VexType *vexs = (VexType *)malloc(3 * sizeof(VexType));
	ArcInfo *arcs = (ArcInfo *)malloc(3 * sizeof(ArcInfo));
	int i;
	int n;//ͼ�������� 
		
	//��3����������в��� 
	vexs[0] = 'A';
	vexs[1] = 'B';
	vexs[2] = 'C';
	//��һ������ʼ���A���յ�B��Ȩֵ3 
//	arcs[0].v = 'A';
//	arcs[0].w = 'B';
//	arcs[0].info = 3;
//	//�ڶ�������ʼ���B���յ�C��Ȩֵ1 	
//	arcs[1].v = 'B';
//	arcs[1].w = 'C';
//	arcs[1].info = 1;
//	//����������ʼ���A���յ�C��Ȩֵ1	
//	arcs[2].v = 'A';
//	arcs[2].w = 'C';
//	arcs[2].info = 2;
	printf("������ڵ�����\n");
	scanf("%c", &n);
	printf("����������ֵ��Ϣ\n");
	initGraph(vexs, n);
	printf("���������Ϣ\n");
	
	if(CreateGraph_AL(p, vexs, 3, arcs, 3)) {
		printf("�����ɹ���ͼΪ:");
		for(i = 0; i < p->n; i++) {
			printf("%c", p->vexs[i].data);
		}
	} else {
		printf("����ʧ��");
	}
		
}

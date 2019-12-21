#include <stdio.h>
#include <stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define ERROR -1
#define NotInit -2

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

//���н�㼰ָ������
typedef struct LQNode {
    int data;
    struct LQNode *next;
} LQNode, *QueuePtr;

//�Ӷ���
typedef struct {
    QueuePtr front;//��ͷָ��
    QueuePtr rear;//��βָ��
} LQueue;

/**
* function:��ʼ�����С�
* params:����
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
* function:��Ӳ�����
* params:���У���Ҫ��ӵĺ���
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
* function:���Ӳ�����
* params:����
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
* function:���еı�����
* params:����
*/
void TravelQueue(LQueue *Q) {
    LQNode *p = Q->front->next;

    while(p != NULL) {
        printf("%d", p->data);
        p = p->next;
    }
}


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
* function:��������ͼ���ڽӱ�洢�ṹ
* params:�ڽӱ�������ͣ��������飬���������ߵ���Ϣ������
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
* function:��ĳ�������һ���ڽӶ���
* params:ͼ���Ҷ���������λ��Ϊk�Ķ���
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
*���ܣ���ĳ��������һ���ڽӶ���
*����˵����ͼ�����Ҷ���������λ��Ϊk�Ķ���
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
* function:���붥��֮��ߵ���Ϣ��������arcs����Ϣ
* params:��������,�߻���Ϣ,�ߵ�������
*/
Status initEdge(VexType *vexs, ArcInfo *arcs, int e, int n) {
	int i, j, right, index = 0;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("�������%c����%c֮�����Ϣ,�����ͨ������Ȩֵ���������ͨ������0\n", vexs[i], vexs[j]);
			fflush(stdin);
			scanf("%d", &right);
			if(right > 0) {
				arcs[index].info = right;
				arcs[index].v = vexs[i];
				arcs[index].w = vexs[j];
				printf("������ȨֵΪ%d,��%c->%c\n", arcs[index].info,arcs[index].v,arcs[index].w);
				index++;//��¼�ߵ��������Ƿ�ƥ�䣬��ƥ�����������롣
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
* function:���붥����Ϣ
* params:
*/
Status initPoint(VexType *vexs, int n) {
	int i;
	char m;
	printf("%d���������ֵ��,�������벻��Ҫ�ո����:", n);
	fflush(stdin);
	for(i = 0; i < n; i++) {
		scanf("%c", &vexs[i]);
	}
	printf("������������Ϊ:");
	for(i = 0; i < n;i++) {
        printf("%c ", vexs[i]);
	}
	return 1;
}

/**
* function:��ͼ��k��������m�������Ӷ���
* params:ͼ�����붥��k��λ�򣬲��붥��m��λ��
*/
Status AddArc_AL(ALGraph *G, int k, int m, int info, int *e) {
    if(k < 0 || k > G->n) {
        return ERROR;
    }
    AdjVexNodeP p = G->vexs[k].firstArc;
    //���ж�һ�¶���治����
    while(p != NULL) {
        if(m == p->adjves) {
            return ERROR;
        }
        p = p->nextArc;
    }
    p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));

    if(p == NULL) {
        return ERROR;
    }
    p->nextArc = G->vexs[k].firstArc;
    G->vexs[k].firstArc = p;
    p->adjves = m;
    p->info = info;
    *e++;

    return 1;
}

/**
* function:ɾ��k������m����
* params:ͼ��ɾ������k��λ��ɾ������m��λ��
*/
Status RemoveArc_AL(ALGraph *G, int k, int m, int *e) {
    if(k < 0 || k > G->n) {
         return ERROR;
    }

    if(G == NULL) {
        return NotInit;
    };
    AdjVexNodeP p, pre = G->vexs[k].firstArc;
    //���ж�һ�¶���治����
    if(pre->nextArc != NULL) {
        if(m != pre->adjves) {
            while(1) {
                printf("fuckaaa");
                printf("%d", pre->adjves);
                if(pre == NULL) {
                    return ERROR;
                }
                if(m == pre->nextArc->adjves) {
                    printf("%d", pre->adjves);
                    p = pre->nextArc;
                    break;
                }
                pre = pre->nextArc;
            }
            pre->nextArc = p->nextArc;
            free(p);
            *e--;
            return 1;
        } else {
            G->vexs[k].firstArc = pre->nextArc;
            free(pre);
            *e--;
            return 1;        }
    } else {
        free(pre);
        G->vexs[k].firstArc = NULL;
        *e--;
        return 1;
    }
}


/**
* function:��ͨͼ�ı��� (�������)
* params:ͼ����k�������
*/
Status DFS_M(ALGraph *G, int k) {
    if(G == NULL) {
        return NotInit;
    }
	int i;
	G->tags[k] = VISITED;
	//��¼��һ����������λ��ָ��
	printf("%c ", G->vexs[k]);
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
* function:��ͨͼ�ı��� (�������),��ͨͼ����ͨͼ������
* params:ͼ
*/
Status DFS_M_Other(ALGraph *G) {
    if(G == NULL) {
        return NotInit;
    }
	int i;

    for(i = 0; i < G->n; i++) {
        if(UNVISITED == G->tags[i]) {
            DFS_M(G, i);
        }
    }
    return 1;
};

/**
* function����ͨͼ�ı��� (�������)
* params��ͼ
*/
Status BFSTraverse_AL(ALGraph *G) {
    if(G == NULL) {
        return NotInit;
    }
    int i,j,k;

    AdjVexNode *p;
    LQueue Q;
    InitQueue_LQ(&Q);

    for(i = 0; i < G->n; i++) {
        G->tags[i] = UNVISITED;
    }

    //����forѭ���Ƿ�ֹ����ͨͼ�ĳ���
    for(i = 0; i < G->n; i++) {
        if(UNVISITED == G->tags[i]) {
            printf("%c ", G->vexs[i].data);
            EnQueue_LQ(&Q, i);
            //TravelQueue(&Q);
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

Status DestoryGraph_AL(ALGraph **G) {
    int i;
    AdjVexNode *p, *temp;

    if(*G == NULL) {
        return 0;
    }

    for(i = 0; i < (*G)->n; i++) {
        p = (*G)->vexs[i].firstArc;
        while(p != NULL) {
            temp = p;
            p = temp->nextArc;
            free(p);
        }
    }
    *G = NULL;
}

void Format() {
    printf("1.��ʼ������ͼ 2.��ͼ�в��뻡 3.ɾ���� 4.��ȱ��� 5.��ȱ��� 6.�ݻ�����ͼ 7.�˳�����\n");
}

int main(int argc, char *argv[]) {
	ALGraph	*p = NULL;
	LQueue q;
	VexType *vexs;
	//��Ŷ�����Ϣ������
	ArcInfo *arcs;
	//������������
	int index;
	//���ز���
	char returnBtn;
	int i;
	//ͼ��������
	int n;
	//ͼ�ıߵ���Ŀ
	int e;
	//���뵽��һ�������
	int insert;
	//����Ľ�㶥��λ��
	int insertAfter;
	//���붥���Ȩֵ
	int insertInfo;
	//�����������صĽ��
    int result = 0;
    //��ԭ��־��ָ��
    int clearIndex;

	while(1) {
        system("cls");
        Format();
        printf("��������Ҫִ�еĲ���:");
        scanf("%d", &index);
        if(index <=0 || index > 7) {
            printf("��������,����������\n");
        } else {
            if(index == 1) {
                p = (ALGraph *)malloc(sizeof(ALGraph));
                printf("��ʼ��ʼ��ͼ\n");
                printf("������������\n");
                scanf("%d", &n);
                vexs = (VexType *)malloc(n * sizeof(VexType));
                printf("������ͼ�ıߵ���Ŀ\n");
                scanf("%d", &e);
                arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
                printf("������ͼ�������ֵ��\n");
                if(initPoint(vexs, n)) {
                    printf("����ɹ�\n");
                    if(initEdge(vexs, arcs, e, n)) {
                        CreateGraph_AL(p, vexs, n, arcs, e);
                        printf("ͼ�����ɹ�\n");
                    } else {
                        printf("�����������\n");
                    }
                    printf("���������ȷ�Ϸ���\n");
                    fflush(stdin);
                    scanf("%c", &returnBtn);
                }

            }

            if(index == 2) {
                if(p == NULL) {
                    printf("�ȳ�ʼ������ͼ\n");
                } else {
                    printf("���������������һ�������,���붥��λ��:");
                    fflush(stdin);
                    scanf("%d", &insert);
                    printf("��������Ҫ����Ľ���λ��:");
                    fflush(stdin);
                    scanf("%d", &insertAfter);
                    printf("������û���Ȩֵ:");
                    fflush(stdin);
                    scanf("%d", &insertInfo);
                    if(AddArc_AL(p, insert, insertAfter, insertInfo, &e)) {
                        printf("����ɹ�\n");
                    } else {
                        printf("�����������\n");
                    }
                }
                printf("���������ȷ�Ϸ���\n");
                fflush(stdin);
                scanf("%c", &returnBtn);
            }

            if(index == 3) {
                if(p == NULL) {
                    printf("���ȳ�ʼ��\n");
                } else {
                    printf("��������ɾ����һ������֮������ӵ�,�����䶥��λ��:");
                    fflush(stdin);
                    scanf("%d", &insert);
                    printf("��������Ҫɾ���Ľ���λ��:");
                    fflush(stdin);
                    scanf("%d", &insertAfter);
                    if(RemoveArc_AL(p, insert, insertAfter, &e)) {
                        printf("ɾ���ɹ�\n");
                    } else {
                        printf("�����������\n");
                    }
                }
                printf("���������ȷ�Ϸ���\n");
                fflush(stdin);
                scanf("%c", &returnBtn);
            }

            if(index == 4) {
                if(p != NULL) {
                    printf("������ȱ������Ϊ: ");
                    result = BFSTraverse_AL(p);
                } else{
                    printf("���ȳ�ʼ��\n");
                }
                printf("���������ȷ�Ϸ���\n");
                fflush(stdin);
                scanf("%c", &returnBtn);
            }

            if(index == 5) {
                if(p != NULL) {
                    for(clearIndex = 0; clearIndex < p->n; clearIndex++) {
                        p->tags[clearIndex] = UNVISITED;
                    }
                    printf("������ȱ������Ϊ: ");
                    DFS_M_Other(p);
                } else {
                    printf("���ȳ�ʼ��");
                }
                printf("\n���������ȷ�Ϸ���");
                fflush(stdin);
                scanf("%c", &returnBtn);
            }

            if(index == 6) {
                if(p == NULL) {
                    printf("ͼ�Ѿ�Ϊ�գ��޷�����\n");
                } else {
                    DestoryGraph_AL(&p);
                    printf("���ٳɹ�\n");
                }
                printf("���������ȷ�Ϸ���");
                fflush(stdin);
                scanf("%c", &returnBtn);
            }

            if(index == 7) {
                fflush(stdin);
                return 0;
            }
        }
	}
}

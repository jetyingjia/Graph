#include <iostream>
#include <queue>
#define UNVISITED 0
#define VISITED 1
//#define INFINITE 9999
#define N 7         // ����ͼ�Ķ�����

#include "Graphm.h"
#include "MinHeap.h"
#include "ParTree.h"

//��С֧������Kruskal�㷨��
//����G��ͼ������MST�Ǳ�����С֧���������бߵ�����
void AddEdgetoMST(Edge e, Edge *&MST, int n)
{
	MST[n] = e;
}

void Kruskal(Graph& G, Edge* &MST)  {
	ParTree<int> A(G.verticesNum());           //�ȼ���
	minHeap<Edge> H(G.edgesNum());        //��Сֵ�ѣ�minheap��    
	MST=new Edge[G.verticesNum()-1];      //��С֧����
	int MSTtag=0;                         //��С֧�����ߵı��
	for(int i=0; i<G.verticesNum(); i++)  //��ͼ�����б߲�����Сֵ��H��
		for(Edge e= G. firstEdge(i); G.isEdge(e);e=G. nextEdge(e))
			if(G.fromVertex(e)< G.toVertex(e))  //��Ϊ������ͼ������Ӧ��ֹ�ظ�����
				H.insert(e);
	int EquNum=G.verticesNum();              //��ʼʱ��|V|���ȼ���
	while(EquNum>1)  {                     //�ϲ��ȼ���
		Edge e=H.removeMin();               //�����һ��Ȩ��С�ı�
		if(e.weight==INFINITE)  {
			std::cout << "��������С֧����." <<std::endl;
			delete [] MST;                     //�ͷſռ�
			MST=NULL;                   //MST�ǿ�����
			return;
		}
		int from=G.fromVertex(e);            //��¼�����ߵ���Ϣ
		int to= G.toVertex(e);
		if(A.Different(from,to))  {            //�����e���������㲻��һ���ȼ���
			A.Union(from,to);     //����e�������������ڵ������ȼ���ϲ�Ϊһ��
			AddEdgetoMST(e,MST,MSTtag++); //����e�ӵ�MST
			EquNum--;                     //���ȼ���ĸ�����1
		}
	}
}


int A[N][N] =  {
	//   v0  v1  v2  v3  v4  v5  v6     
	0, 20,  0,  0,  1,  0,  0,
	20,  0,  6,  4,  0,  0,  0,
	0,  6,  0,  0,  0,  0,  2,
	0,  4,  0,  0,  0, 12,  8,
	1,  0,  0,  0,  0, 15,  0,
	0,  0,  0, 12, 15,  0, 10,
	0,  0,  2,  8,  0, 10,  0,
};			                    	//ͼ7.24 ��Ȩͼ

void main()
{
	Graphm aGraphm(N); // ����ͼ
	aGraphm.initGraphm(&aGraphm, A); // ��ʼ��ͼ

	Edge *D;
	Kruskal(aGraphm, D); for (int i = 0; i < N - 1; i ++)
		std::cout << "V" << D[i].from << "->V" << D[i].to << "   Weight is : " << D[i].weight << std::endl;
	system("pause");
}
#ifndef _Graphm_hpp_
#define _Graphm_hpp_

#include "Graph.h"
#include <queue>
#include <iostream>

#define N 3  //����ͼ�Ķ�����

//ͼ�����ھ����ʾ��
class Graphm: public Graph {
private:
	int **matrix;

public:
	void initGraphm(Graphm *Graphm, int a[N][N]);
	void DFS(Graph &G, int v);
	void BFS(Graph &G, int v);
	void visit(Graph &G, int v);


public:
	Graphm(int numVertex): Graph(numVertex) {
		int i,j;
		matrix=(int **)new int*[numVertex];
		for(i=0;i<numVertex;i++) {
			matrix[i]=new int[numVertex];
		}
		for(i=0;i<numVertex;i++) {
			for(j=0;j<numVertex;j++) {
				matrix[i][j]=0;
			}
		}
	}
	~Graphm() {
		for(int i=0;i<numVertex;i++) {
			delete [] matrix[i];
		}
		delete [] matrix;
	}

	//���ض���oneVertex�ĵ�һ����
	Edge firstEdge(int oneVertex) {
		Edge myEdge;
		myEdge.from=oneVertex;
		//myEdge.to=-1;
		//����Ѱ�ҵ�һ��ʹ��matrix[oneVertex][i]��Ϊ0��iֵ����ô��(oneVertex,i)����
		//��<oneVertex,i>��Ϊ����oneVertex�ĵ�һ���ߣ�������i��Ϊ��myEdge���յ��myEdge
		//��ȨΪ����Ԫ��matrix[oneVertex][i]��ֵ
		for(int i=0;i<numVertex;i++) {
			if(matrix[oneVertex][i]!=0) {
				myEdge.to=i;
				myEdge.weight=matrix[oneVertex][i];
				break;
			}
		}
		//����ҵ��˶���oneVertex�ĵ�һ����,�򷵻ص�myEdgeȷʵ��һ���ߣ����û���ҵ�����oneVertex�ĵ�һ����,��myEdge�ĳ�Ա����toΪ-1��
		//����IsEdge�����жϿ�֪myEdge����һ����
		return myEdge;
	}

	//�������PreEdge����ͬ�����������һ����
	Edge nextEdge(Edge preEdge) {
		Edge myEdge;
		myEdge.from=preEdge.from;/*����myEdge��ʼ����Ϊ����һ����preEdge��ʼ����ͬ*/
		if(preEdge.to<numVertex) {
			//���preEdge.to+1>=numVertex,��ô�Ͳ�������һ������
			for(int i=preEdge.to+1;i<numVertex;i++) {
				//Ѱ����һ��ʹ��//matrix[preEdge.from][i]��Ϊ0��iֵ,��ô
				//(preEdge.from,i)����<preEdge.from,i>��Ϊ����preEdge.from����һ����
				if(matrix[preEdge.from][i]!=0) {
					myEdge.to=i;
					myEdge.weight=matrix[preEdge.from][i];
					break;
				}
			}
		}
		return myEdge;/*����ҵ��˶���preEdge.from����һ���ߣ��򷵻ص�myEdgeȷʵ��һ���ߣ�
					   ���û���ҵ�����preEdge.from����һ���ߣ���myEdge�ĳ�Ա����toΪ-1��
						����IsEdge�����жϿ�֪myEdge����һ����*/
	}

	//Ϊͼ�趨һ����
	void setEdge(int from, int to, int weight) {
		if(matrix[from][to]<=0) { /*���matrix[from][to]<=0�����(from,to) ����<from,to>
			                       ����������һ���ߣ�����ñ��Ѿ����ڣ�����ֻ�ǶԸñ߽����޸ģ�*/
			numEdge++;
			inDegree[to]++;
		}
		matrix[from][to]=weight;
	}

	//ɾ��ͼ��һ����
	void delEdge(int from, int to) {
		if(matrix[from][to]>0) { /*���matrix[from][to]>0�����(from,to)����<from,to>ȷʵ���ڣ�
			                      ����ñ�ʵ���ϲ������ڣ��Ӷ����ض�ͼ�ı����Ͷ���to����Ƚ����޸ģ�*/
			numEdge--;
			inDegree[to]--;
		}
		matrix[from][to]=0;
	}

};

//�������ܣ���ʼ��ͼ
void Graphm::initGraphm(Graphm *Graphm, int a[N][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(a[i][j]>0) {
				Graphm->setEdge(i,j,a[i][j]);
			}
		}
	}
}

//�������ܣ��������������DFS��
void Graphm::DFS(Graph &G, int v) {
	G.mark[v]=VISITED;
	visit(G,v);
	for(Edge e=G.firstEdge(v);G.isEdge(e);e=G.nextEdge(e)) {
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			DFS(G,G.toVertex(e));
		}
	}
}

//�������ܣ������������
void Graphm::BFS(Graph &G, int v) {
	std::queue<int> aQueue;
	visit(G,v);
	G.mark[v]=VISITED;
	aQueue.push(v);
	while(!aQueue.empty()) {
		int u=aQueue.front();
		aQueue.pop();
		// �ö����ڽӵ���ÿһ��δ���ʶ��㶼���
		for(Edge e=G.firstEdge(u);G.isEdge(e);e=G.nextEdge(e)) {
			if(G.mark[G.toVertex(e)]==UNVISITED) {
				visit(G,G.toVertex(e));
				G.mark[G.toVertex(e)]=VISITED;
				aQueue.push(G.toVertex(e));
			}
		}
	}
}


//�������ܣ���ʾ����
void Graphm::visit(Graph &G, int v) {
	std::cout<<"V"<<v<<" ";	
}


#endif
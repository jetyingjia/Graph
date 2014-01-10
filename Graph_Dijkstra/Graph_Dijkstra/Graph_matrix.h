#ifndef _Graph_matrix_hpp_
#define _Graph_matrix_hpp_

#include <iostream>
#include <queue>
//ͼ�Ļ���
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffffffff

//Edge��
class Edge {
public:
	int weight;   //weight�Ǳߵ�Ȩ
	int from;     //from�Ǳߵ�ʼ��
	int to;       //to�Ǳߵ��յ�
	Edge() {      //���캯��
		from=-1;
		to=-1;
		weight=0;
	}
	Edge(int f,int t,int w) {   //���캯��
		from=f;
		to=t;
		weight=w;
	}
	bool operator < (Edge &arg) {return (this->weight<arg.weight);};
	bool operator ==(Edge &arg) {return (this->weight==arg.weight);};
	bool operator > (Edge &arg) {return (this->weight>arg.weight); };
	bool operator <= (Edge &arg) {return (this->weight<=arg.weight); };
	bool operator >= (Edge &arg) {return (this->weight>=arg.weight); };

};

//ͼ����
class Graph: public Edge {
public:
	int numVertex;   //ͼ�Ķ���ĸ���
	int numEdge;      //ͼ�ıߵĸ���
	int *mark;       //markָ��ָ�򱣴���ͼ�Ķ���ı�־λ������,��־λ�������ĳ�����Ƿ񱻷��ʹ�
	int *inDegree;    //inDegreeָ��ָ�򱣴���ͼ�Ķ�����ȵ�����
	Graph(int numVert) {
		numVertex=numVert;
		numEdge=0;
		inDegree=new int[numVertex];
		mark=new int[numVertex];
		//ȷ��ͼ�Ķ���ı�־λ�����,�����ж���ı�־λ��ʼ��Ϊδ�����ʹ�,��ȳ�ʼ��Ϊ0
		for(int i=0;i<numVertex;i++) {
			mark[i]=UNVISITED;
			inDegree[i]=0;
		}
	}
	~Graph() {
		delete[] mark;
		delete[] inDegree;
	}

	virtual Edge firstEdge(int oneVertex) {// �����붥��oneVertex������ĵ�һ����
		Edge myEdge;
		myEdge.from=oneVertex;
		myEdge.to=-1;
		return myEdge;
	}

	virtual Edge nextEdge(Edge preEdge) {// �������PreEdge����ͬ�����������һ����
		return preEdge;
	}

	int verticesNum() { //����ͼ�Ķ������
		return numVertex;
	}

	int edgesNum() {   //����ͼ�ı���
		return numEdge;
	}

	int fromVertex(Edge oneEdge) { //����oneEdge��ʼ��
		return oneEdge.from;
	}

	int toVertex(Edge oneEdge) {   //����oneEdge���յ�
		return oneEdge.to;
	}

	int weightf(Edge oneEdge) {     // ����oneEdge��Ȩֵ
		return oneEdge.weight;
	}

	bool isEdge(Edge oneEdge) {    //���oneEdge�Ǳ��򷵻�TRUE�����򷵻�FALSE
		if(oneEdge.weight>0 && oneEdge.weight<=INFINITE && oneEdge.to>=0) {
			return true;
		}
		else {
			return false;
		}
	}

	virtual void setEdge(int from, int to, int weight)=0;
	virtual void delEdge(int from, int to)=0;
};

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
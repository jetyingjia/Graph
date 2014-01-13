#ifndef _Graph_hpp_
#define _Graph_hpp_
//ͼ�Ļ���
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0x7fffffff

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


#endif
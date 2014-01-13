#ifndef _Graph_hpp_
#define _Graph_hpp_
//图的基类
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0x7fffffff

//Edge类
class Edge {
public:
	int weight;   //weight是边的权
	int from;     //from是边的始点
	int to;       //to是边的终点
	Edge() {      //构造函数
		from=-1;
		to=-1;
		weight=0;
	}
	Edge(int f,int t,int w) {   //构造函数
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

//图基类
class Graph: public Edge {
public:
	int numVertex;   //图的顶点的个数
	int numEdge;      //图的边的个数
	int *mark;       //mark指针指向保存有图的顶点的标志位的数组,标志位用来标记某顶点是否被访问过
	int *inDegree;    //inDegree指针指向保存有图的顶点入度的数组
	Graph(int numVert) {
		numVertex=numVert;
		numEdge=0;
		inDegree=new int[numVertex];
		mark=new int[numVertex];
		//确定图的顶点的标志位和入度,即所有顶点的标志位初始化为未被访问过,入度初始化为0
		for(int i=0;i<numVertex;i++) {
			mark[i]=UNVISITED;
			inDegree[i]=0;
		}
	}
	~Graph() {
		delete[] mark;
		delete[] inDegree;
	}

	virtual Edge firstEdge(int oneVertex) {// 返回与顶点oneVertex相关联的第一条边
		Edge myEdge;
		myEdge.from=oneVertex;
		myEdge.to=-1;
		return myEdge;
	}

	virtual Edge nextEdge(Edge preEdge) {// 返回与边PreEdge有相同关联顶点的下一条边
		return preEdge;
	}

	int verticesNum() { //返回图的顶点个数
		return numVertex;
	}

	int edgesNum() {   //返回图的边数
		return numEdge;
	}

	int fromVertex(Edge oneEdge) { //返回oneEdge的始点
		return oneEdge.from;
	}

	int toVertex(Edge oneEdge) {   //返回oneEdge的终点
		return oneEdge.to;
	}

	int weightf(Edge oneEdge) {     // 返回oneEdge的权值
		return oneEdge.weight;
	}

	bool isEdge(Edge oneEdge) {    //如果oneEdge是边则返回TRUE，否则返回FALSE
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
#ifndef _Graph_matrix_hpp_
#define _Graph_matrix_hpp_

#include <iostream>
#include <queue>
//图的基类
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffff

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

//图的相邻矩阵表示法
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

	//返回顶点oneVertex的第一条边
	Edge firstEdge(int oneVertex) {
		Edge myEdge;
		myEdge.from=oneVertex;
		//myEdge.to=-1;
		//下面寻找第一个使得matrix[oneVertex][i]不为0的i值，那么边(oneVertex,i)或者
		//弧<oneVertex,i>即为顶点oneVertex的第一条边，将顶点i作为边myEdge的终点边myEdge
		//的权为矩阵元素matrix[oneVertex][i]的值
		for(int i=0;i<numVertex;i++) {
			if(matrix[oneVertex][i]!=0) {
				myEdge.to=i;
				myEdge.weight=matrix[oneVertex][i];
				break;
			}
		}
		//如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边；如果没有找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1，
		//根据IsEdge函数判断可知myEdge不是一条边
		return myEdge;
	}

	//返回与边PreEdge有相同关联顶点的下一条边
	Edge nextEdge(Edge preEdge) {
		Edge myEdge;
		myEdge.from=preEdge.from;/*将边myEdge的始点置为与上一条边preEdge的始点相同*/
		if(preEdge.to<numVertex) {
			//如果preEdge.to+1>=numVertex,那么就不存在下一条边了
			for(int i=preEdge.to+1;i<numVertex;i++) {
				//寻找下一个使得//matrix[preEdge.from][i]不为0的i值,那么
				//(preEdge.from,i)或者<preEdge.from,i>即为顶点preEdge.from的下一条边
				if(matrix[preEdge.from][i]!=0) {
					myEdge.to=i;
					myEdge.weight=matrix[preEdge.from][i];
					break;
				}
			}
		}
		return myEdge;/*如果找到了顶点preEdge.from的下一条边，则返回的myEdge确实是一条边；
					   如果没有找到顶点preEdge.from的下一条边，则myEdge的成员变量to为-1，
						根据IsEdge函数判断可知myEdge不是一条边*/
	}

	//为图设定一条边
	void setEdge(int from, int to, int weight) {
		if(matrix[from][to]<=0) { /*如果matrix[from][to]<=0，则边(from,to) 或者<from,to>
			                       将是新增的一条边，否则该边已经存在（现在只是对该边进行修改）*/
			numEdge++;
			inDegree[to]++;
		}
		matrix[from][to]=weight;
	}

	//删除图的一条边
	void delEdge(int from, int to) {
		if(matrix[from][to]>0) { /*如果matrix[from][to]>0，则边(from,to)或者<from,to>确实存在，
			                      否则该边实际上并不存在（从而不必对图的边数和顶点to的入度进行修改）*/
			numEdge--;
			inDegree[to]--;
		}
		matrix[from][to]=0;
	}

};

//函数功能：初始化图
void Graphm::initGraphm(Graphm *Graphm, int a[N][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(a[i][j]>0) {
				Graphm->setEdge(i,j,a[i][j]);
			}
		}
	}
}

//函数功能：深度优先搜索（DFS）
void Graphm::DFS(Graph &G, int v) {
	G.mark[v]=VISITED;
	visit(G,v);
	for(Edge e=G.firstEdge(v);G.isEdge(e);e=G.nextEdge(e)) {
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			DFS(G,G.toVertex(e));
		}
	}
}

//函数功能：广度优先搜索
void Graphm::BFS(Graph &G, int v) {
	std::queue<int> aQueue;
	visit(G,v);
	G.mark[v]=VISITED;
	aQueue.push(v);
	while(!aQueue.empty()) {
		int u=aQueue.front();
		aQueue.pop();
		// 该顶点邻接到的每一个未访问顶点都入队
		for(Edge e=G.firstEdge(u);G.isEdge(e);e=G.nextEdge(e)) {
			if(G.mark[G.toVertex(e)]==UNVISITED) {
				visit(G,G.toVertex(e));
				G.mark[G.toVertex(e)]=VISITED;
				aQueue.push(G.toVertex(e));
			}
		}
	}
}


//函数功能：显示顶点
void Graphm::visit(Graph &G, int v) {
	std::cout<<"V"<<v<<" ";	
}



#endif
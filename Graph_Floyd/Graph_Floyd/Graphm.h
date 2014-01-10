#ifndef _Graphm_hpp_
#define _Graphm_hpp_

#include "Graph.h"
#include <queue>
#include <iostream>

#define N 3  //定义图的顶点数

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
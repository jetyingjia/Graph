#include <iostream>
#include <queue>
#define UNVISITED 0
#define VISITED 1
#define INFINITE 9999
#define N 7         // 定义图的顶点数

#include "Graphm.h"


class Dist  {      //定义Dist类，下面的Prim算法要用到
public:
	int index;      //顶点的索引值，仅Dijkstra算法会用到
	int length;     //顶点之间的距离
	int pre;       //路径最后经过的顶点
	Dist() {};
	~Dist() {};
	void Dijkstra(Graphm & G,int s, Dist* &D);
	bool operator < (const Dist &arg)  {
		return (length < arg.length);
	}
	bool operator == (const Dist &arg)  {
		return (length==arg.length);
	}
	bool operator == (const int c)  {
		return (length==c);
	}
	bool operator > (const Dist &arg)  {
		return (length>arg.length);
	}
	bool operator <=(const Dist &arg)  {
		return (length<=arg.length);
	}
	bool operator >= (const Dist &arg)  {
		return (length>=arg.length);
	}
};



int minVertex(Graph& G, Dist* & D) { 			// 在Dist数组中找最小值
	int i, v;  
	for (i=0; i<G.verticesNum(); i++)
		if (G.mark[i] == UNVISITED) {
			v = i; 						// 让v为随意一个未访问的定义
			break; 
		}
		for (i=0; i<G.verticesNum(); i++)  		
			if ((G.mark[i] == UNVISITED) && (D[i] < D[v]))  //此时源点已是visited
				v = i;						// 保存目前发现的具有最小距离的顶点
		return v;
}


//最小支撑树的Prim算法，
//参数G是图，参数s是开始顶点，参数MST是保存最小支撑树中所有边的数组
void AddEdgetoMST(Edge e, Edge *&MST, int n)
{
	MST[n] = e;
}

void Prim(Graph& G, int s, Edge* &MST)  {
	int MSTtag = 0;                       // 最小生成树边的标号
	MST = new Edge[G.verticesNum()-1];	  //存放的是边，比顶点数少1
	Dist *D;
	D = new Dist[G. verticesNum()];          	// D数组
	for (int i = 0; i < G.verticesNum(); i++)  {  	// 初始化Mark数组、D数组
		G.mark[i] = UNVISITED;
		D[i].index = i;
		D[i].length = INFINITE;
		D[i].pre = s;
	}

	D[s].length = 0; 
	G.mark[s]= VISITED;	

	int v = s;
	for (int i = 0; i < G.verticesNum()-1; i++)  {

		if (D[v] == INFINITE) return;    	// 非连通，有不可达顶点，

		// 因为v的加入，需要刷新v邻接点的D值
		for (Edge e = G.firstEdge(v); G.isEdge(e);e = G.nextEdge(e))
			if (G.mark[G.toVertex(e)]!=VISITED && (D[G.toVertex(e)].length > e.weight)) {
				D[G.toVertex(e)].length = e.weight;
				D[G.toVertex(e)].pre = v;
			}

			v = minVertex(G, D);

			G.mark[v] = VISITED;
			Edge edge(D[v].pre, D[v].index, D[v].length);

			AddEdgetoMST(edge,MST,MSTtag++);  // 将边e加到MST中
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
};			                    	//图7.24 带权图

void main()
{
	Graphm aGraphm(N); // 建立图
	aGraphm.initGraphm(&aGraphm, A); // 初始化图

	Edge *D;
	Prim(aGraphm, 0, D);
	for (int i = 0; i < N - 1; i ++)
		std::cout<<"V"<<D[i].from<<"->V" << D[i].to << "   Weight is : " << D[i].weight <<std::endl;
	system("pause");
}
// 图的相邻矩阵表示方法,还要用到最小值堆

#define N 5 // 定义图的顶点数

#include "Graph_matrix.h"
#include "minHeap.h"


//[代码7.8] Dijkstra算法
class Dist  {      //定义Dist类，下面的Dijkstra算法和Floyd算法要用到
public:
	int index;      //顶点的索引值，仅Dijkstra算法会用到
	int length;     //顶点之间的距离
	int pre;       //路径最后经过的顶点
	Dist() {};
	~Dist() {};

	bool operator < (const Dist & arg)  {
		return (length < arg.length);
	}
	bool operator == (const Dist &arg)  {
		return (length==arg.length);
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

//Dijkstra算法，其中参数G是图，参数s是源顶点，D是保存最短距离及其路径的数组
void Dijkstra(Graph& G, int s, Dist* &D)  {
	D = new Dist[G.verticesNum()];          	    // D数组
	for (int i = 0; i < G.verticesNum(); i++) {   	// 初始化mark数组、D数组
		G.mark[i] = UNVISITED;
		D[i].index = i;
		D[i].length = INFINITE;
		D[i].pre = s;
	}
	D[s].length = 0; 
	minHeap<Dist> H(G.edgesNum()); 
	H.buildHeap();   // 最小值堆（minheap）
	H.insert(D[s]);
	for (int i = 0; i < G.verticesNum(); i++) {
		bool FOUND = false;
		Dist d;

		//std::cout<<std::endl<<i<<std::endl;
		
		while (!H.isEmpty())  {
			d=H.removeMin(); 

			//std::cout<<std::endl<<i<<std::endl;

			if(G.mark[d.index]==UNVISITED) {                //打印出路径信息
				std::cout<< "vertex index: " <<d.index<<"   ";
				std::cout<< "vertex pre  : " <<d.pre  <<"   ";
				std::cout<< "V"<<s<<"--V"<< d.index <<"  length    : " <<d.length<<std::endl;
			}
			if (G.mark[d.index] == UNVISITED) { //找到距离s最近的顶点
				FOUND = true;
				break;
			}
		}
		if (!FOUND)
			break;
		int v = d.index;
		G.mark[v] = VISITED;           		// 把该点加入已访问组
		// 因为v的加入，需要刷新v邻接点的D值
		for (Edge e = G.firstEdge(v); G.isEdge(e);e = G.nextEdge(e))
			if (D[G.toVertex(e)].length > (D[v].length+G.weightf(e))) {
				D[G.toVertex(e)].length = D[v].length+G.weightf(e);
				D[G.toVertex(e)].pre = v;
				H.insert(D[G.toVertex(e)]);
			}
	}
}



int A[N][N] =  {          //图7.20  单源最短路径的示例
	//  v0  v1  v2  v3  v4  
	0, 10,  0, 30, 100,
	0,  0, 50,  0,  0, 
	0,  0,  0,  0, 10, 
	0, 10, 20,  0, 60, 
	0,  0,  0,  0,  0, 
};

void main()
{
// 	int jet=0xffffffff;
// 	std::cout<<jet;
	Graphm aGraphm(N); // 建立图
	aGraphm.initGraphm(&aGraphm, A); // 初始化图
	Dist *D;
	Dijkstra(aGraphm, 0, D);
	system("pause");
}

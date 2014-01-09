// 图的相邻矩阵表示方法
#include "Graph.h"
#include "Graphm.h"


#define N 5 // 定义图的顶点数

int A[N][N] = {
	//        V0 V1 V2 V3 V4 
	/*V0*/    0, 0, 1, 1, 0,
	/*V1*/    0, 0, 0, 1, 1,
	/*V2*/    1, 0, 0, 1, 1,
	/*V3*/    1, 1, 1, 0, 0,
	/*V4*/    0, 1, 1, 0, 0,};      //图7.2中G1表示的无向图
	
	
void main()  {
	Graphm aGraphm(N);              // 建立图 
	aGraphm.initGraphm(&aGraphm, A); // 初始化图
	std::cout << "DFS: ";
	aGraphm.DFS(aGraphm, 0);
	std::cout << std::endl;
		
	for (int i = 0; i < aGraphm.verticesNum(); i ++) //把Mark改回UNVISITED
		aGraphm.mark[i] = UNVISITED; 
		
	std::cout << "BFS: ";
	aGraphm.BFS(aGraphm, 0);
	std::cout << std::endl;
	system("pause");
}

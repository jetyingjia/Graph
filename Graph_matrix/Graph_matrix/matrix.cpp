// ͼ�����ھ����ʾ����
#include "Graph.h"
#include "Graphm.h"


#define N 5 // ����ͼ�Ķ�����

int A[N][N] = {
	//        V0 V1 V2 V3 V4 
	/*V0*/    0, 0, 1, 1, 0,
	/*V1*/    0, 0, 0, 1, 1,
	/*V2*/    1, 0, 0, 1, 1,
	/*V3*/    1, 1, 1, 0, 0,
	/*V4*/    0, 1, 1, 0, 0,};      //ͼ7.2��G1��ʾ������ͼ
	
	
void main()  {
	Graphm aGraphm(N);              // ����ͼ 
	aGraphm.initGraphm(&aGraphm, A); // ��ʼ��ͼ
	std::cout << "DFS: ";
	aGraphm.DFS(aGraphm, 0);
	std::cout << std::endl;
		
	for (int i = 0; i < aGraphm.verticesNum(); i ++) //��Mark�Ļ�UNVISITED
		aGraphm.mark[i] = UNVISITED; 
		
	std::cout << "BFS: ";
	aGraphm.BFS(aGraphm, 0);
	std::cout << std::endl;
	system("pause");
}

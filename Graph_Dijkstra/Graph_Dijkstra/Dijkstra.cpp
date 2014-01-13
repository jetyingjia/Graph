// ͼ�����ھ����ʾ����,��Ҫ�õ���Сֵ��

#define N 5 // ����ͼ�Ķ�����

#include "Graph_matrix.h"
#include "minHeap.h"


//[����7.8] Dijkstra�㷨
class Dist  {      //����Dist�࣬�����Dijkstra�㷨��Floyd�㷨Ҫ�õ�
public:
	int index;      //���������ֵ����Dijkstra�㷨���õ�
	int length;     //����֮��ľ���
	int pre;       //·����󾭹��Ķ���
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

//Dijkstra�㷨�����в���G��ͼ������s��Դ���㣬D�Ǳ�����̾��뼰��·��������
void Dijkstra(Graph& G, int s, Dist* &D)  {
	D = new Dist[G.verticesNum()];          	    // D����
	for (int i = 0; i < G.verticesNum(); i++) {   	// ��ʼ��mark���顢D����
		G.mark[i] = UNVISITED;
		D[i].index = i;
		D[i].length = INFINITE;
		D[i].pre = s;
	}
	D[s].length = 0; 
	minHeap<Dist> H(G.edgesNum()); 
	H.buildHeap();   // ��Сֵ�ѣ�minheap��
	H.insert(D[s]);
	for (int i = 0; i < G.verticesNum(); i++) {
		bool FOUND = false;
		Dist d;

		//std::cout<<std::endl<<i<<std::endl;
		
		while (!H.isEmpty())  {
			d=H.removeMin(); 

			//std::cout<<std::endl<<i<<std::endl;

			if(G.mark[d.index]==UNVISITED) {                //��ӡ��·����Ϣ
				std::cout<< "vertex index: " <<d.index<<"   ";
				std::cout<< "vertex pre  : " <<d.pre  <<"   ";
				std::cout<< "V"<<s<<"--V"<< d.index <<"  length    : " <<d.length<<std::endl;
			}
			if (G.mark[d.index] == UNVISITED) { //�ҵ�����s����Ķ���
				FOUND = true;
				break;
			}
		}
		if (!FOUND)
			break;
		int v = d.index;
		G.mark[v] = VISITED;           		// �Ѹõ�����ѷ�����
		// ��Ϊv�ļ��룬��Ҫˢ��v�ڽӵ��Dֵ
		for (Edge e = G.firstEdge(v); G.isEdge(e);e = G.nextEdge(e))
			if (D[G.toVertex(e)].length > (D[v].length+G.weightf(e))) {
				D[G.toVertex(e)].length = D[v].length+G.weightf(e);
				D[G.toVertex(e)].pre = v;
				H.insert(D[G.toVertex(e)]);
			}
	}
}



int A[N][N] =  {          //ͼ7.20  ��Դ���·����ʾ��
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
	Graphm aGraphm(N); // ����ͼ
	aGraphm.initGraphm(&aGraphm, A); // ��ʼ��ͼ
	Dist *D;
	Dijkstra(aGraphm, 0, D);
	system("pause");
}

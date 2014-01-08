#ifndef _Graphl_hpp_
#define _Graphl_hpp_

#include "Graph.h"
#include <queue>
#include <iostream>


#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffffffff
#define N 5 // 定义图的顶点数

struct listUnit {   //邻接表表目中数据部分的结构定义
	int vertex;  //边的终点
	int weight;  //边的权
};

template <typename T>  //链表元素
class link {
public:
	T element;         //表目的数据
	link *next;        //表目指针，指向下一个表目
	link(T& elemval, link *nextval=NULL) { //构造函数
		element=elemval;
		next=nextval;
	}
	link(link *nextval=NULL) {    //构造函数
		next=nextval;
	}
	~link(){};

};


template <typename T> //链表
class lList {
public:
	link<T>* head;    //head指针并不储存任何实际元素，其存在只是为了操作方便
	lList() {         //构造函数
		head=new link<T>();
	}

	void removeAll() {  //释放边表所有表目占据的空间
		link<T> *fence;
		while(head!=NULL) {  //逐步释放每个表目占据的空间
			fence=head;
			head=head->next;
			delete fence;
		}
	}
	~lList() {
		removeAll();
	}
};

class Graphl: public Graph {
private:
	lList<listUnit> *graList;  //graList是保存所有边表的数组
public:
	Graphl(int numVert): Graph(numVert) {
		//为graList数组申请空间，图有numVertex个顶点，则有numVertex个边表
		graList=new lList<listUnit>[numVert];
	}
	~Graphl(){
		delete[] graList;  //释放空间
	}
	
	//返回顶点oneVertex的第一条边
	Edge firstEdge(int oneVertex) {
		Edge myEdge;
		myEdge.from=oneVertex;     //将顶点oneVertex作为边myEdge的始点

		//graList[oneVertex].head保存的是顶点oneVertex的边表，temp->next指向顶点oneVertex
		//的第一条边(如果temp->next不为null)
		link<listUnit>* temp=graList[oneVertex].head;
		if(temp->next!=NULL) {
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;
		}
		return myEdge;
	}

	// 返回与边PreEdge有相同关联顶点的下一条边
	Edge nextEdge(Edge preEdge) {
		Edge myEdge;						// myEdge的初始成员变量to为-1
		myEdge.from=preEdge.from;			// 将边的始点置为与上一条边的相同
		link<listUnit>* temp=graList[preEdge.from].head;// temp指向边表头一个
		while(temp->next!=NULL && temp->next->element.vertex<=preEdge.to) {
			temp=temp->next;				// 确定边preEdge的位置
		}
		if(temp->next!=NULL) {				// 边preEdge的下一条边存在
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;
		}
		return myEdge;						// 如果没有找到第一条边，myEdge.to=-1
	}

	//为图设定一条边
	void setEdge(int from,int to,int weight) {
		link<listUnit> *temp=graList[from].head;
		//graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边
		//(如果temp->next不为null)
		while(temp->next!=NULL && temp->next->element.vertex<to)
			temp=temp->next;
		//确定边(from,to)或<from,to>在边表中的位置,如果不存在,
		//则边(from,to)或<from,to>为新加的一条边
		if(temp->next==NULL) {
			temp->next=new link<listUnit>;
			temp->next->element.vertex=to;
			temp->next->element.weight=weight;
			numEdge++;
			inDegree[to]++;
			return ;
		}
			
		//边(from,to)或<from,to>在边表中已存在,故只需要改变边的权值
		if(temp->next->element.vertex==to) {
			temp->next->element.weight=weight;
			return ;
		}

		//边(from,to)或<from,to>在边表中不存在,但在边表中其后存在其它边,则在边表中插入这条边
		if(temp->next->element.vertex>to) {
			link<listUnit> *other=temp->next;
			temp->next=new link<listUnit>;
			temp->next->element.vertex=to;
			temp->next->element.weight=weight;
			temp->next->next=other;
			numEdge++;
			inDegree[to]++;
			return ;
		}
	

	}

	//删掉图的一条边
	void delEdge(int from, int to) {
		link<listUnit> *temp=graList[from].head;
		while(temp->next!=NULL && temp->next->element.vertex<to) {
			temp=temp->next; //确定边(from,to)或<from,to>在边表中的位置(如果该边存在)
			if(temp->next==NULL) {
				return ;//边(from,to)或<from,to>在边表中不存在,则不需要做任何操作
			}
			if(temp->next->element.vertex>to) {
				return ;//边(from,to)或<from,to>在边表中不存在,则不需要做任何操作
			}
			//边(from,to)或<from,to>在边表中存在且确定了该边在边表中的位置,
			//则从边表中将其删掉
			if(temp->next->element.vertex==to) {
				link<listUnit> *other=temp->next;
				delete temp->next;
				temp->next=other;
				numEdge--;
				inDegree[to]--;
				return ;
			}
		}
	}

	void initGraphl(Graphl *Graphl,int a[N][N]);
	void DFS(Graphl& G, int v);
	void BFS(Graphl& G, int v);
	void visit(Graphl& G, int v);

};

//函数功能：初始化图
void Graphl::initGraphl(Graphl *Graphl,int a[N][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(a[i][j]>0) {
				Graphl->setEdge(i,j,a[i][j]);
			}
		}
	}
}

//函数功能：深度优先搜索
void Graphl::DFS(Graphl& G, int v) {
	G.mark[v]=VISITED;
	visit(G,v);
	//访问V邻接到的未被访问过的顶点，并递归地按照深度优先的方式进行周游
	for(Edge e=G.firstEdge(v);G.isEdge(e);e=G.nextEdge(e)) {
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			DFS(G,G.toVertex(e));
		}
	}
}


//函数功能：广度优先搜索
void Graphl::BFS(Graphl& G, int v) {
	std::queue<int> aQueue;
	visit(G,v);
	G.mark[v]=VISITED;
	aQueue.push(v);
	while(!aQueue.empty()) {
		int u=aQueue.front();
		aQueue.pop();
		// 该顶点邻接到的每一个未访问顶点都入队
		for(Edge e=G.firstEdge(u);G.isEdge(e);e=G.nextEdge(e)) 
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			visit(G,G.toVertex(e));
			G.mark[G.toVertex(e)]=VISITED;
			aQueue.push(G.toVertex(e));
		}
		
		
	}
}

//函数功能：显示顶点
void Graphl::visit(Graphl& G, int v) {
	std::cout<<"V"<<v<<" ";
}



#endif
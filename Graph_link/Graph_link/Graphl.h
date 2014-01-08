#ifndef _Graphl_hpp_
#define _Graphl_hpp_

#include "Graph.h"
#include <queue>
#include <iostream>


#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffffffff
#define N 5 // ����ͼ�Ķ�����

struct listUnit {   //�ڽӱ��Ŀ�����ݲ��ֵĽṹ����
	int vertex;  //�ߵ��յ�
	int weight;  //�ߵ�Ȩ
};

template <typename T>  //����Ԫ��
class link {
public:
	T element;         //��Ŀ������
	link *next;        //��Ŀָ�룬ָ����һ����Ŀ
	link(T& elemval, link *nextval=NULL) { //���캯��
		element=elemval;
		next=nextval;
	}
	link(link *nextval=NULL) {    //���캯��
		next=nextval;
	}
	~link(){};

};


template <typename T> //����
class lList {
public:
	link<T>* head;    //headָ�벢�������κ�ʵ��Ԫ�أ������ֻ��Ϊ�˲�������
	lList() {         //���캯��
		head=new link<T>();
	}

	void removeAll() {  //�ͷű߱����б�Ŀռ�ݵĿռ�
		link<T> *fence;
		while(head!=NULL) {  //���ͷ�ÿ����Ŀռ�ݵĿռ�
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
	lList<listUnit> *graList;  //graList�Ǳ������б߱������
public:
	Graphl(int numVert): Graph(numVert) {
		//ΪgraList��������ռ䣬ͼ��numVertex�����㣬����numVertex���߱�
		graList=new lList<listUnit>[numVert];
	}
	~Graphl(){
		delete[] graList;  //�ͷſռ�
	}
	
	//���ض���oneVertex�ĵ�һ����
	Edge firstEdge(int oneVertex) {
		Edge myEdge;
		myEdge.from=oneVertex;     //������oneVertex��Ϊ��myEdge��ʼ��

		//graList[oneVertex].head������Ƕ���oneVertex�ı߱�temp->nextָ�򶥵�oneVertex
		//�ĵ�һ����(���temp->next��Ϊnull)
		link<listUnit>* temp=graList[oneVertex].head;
		if(temp->next!=NULL) {
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;
		}
		return myEdge;
	}

	// �������PreEdge����ͬ�����������һ����
	Edge nextEdge(Edge preEdge) {
		Edge myEdge;						// myEdge�ĳ�ʼ��Ա����toΪ-1
		myEdge.from=preEdge.from;			// ���ߵ�ʼ����Ϊ����һ���ߵ���ͬ
		link<listUnit>* temp=graList[preEdge.from].head;// tempָ��߱�ͷһ��
		while(temp->next!=NULL && temp->next->element.vertex<=preEdge.to) {
			temp=temp->next;				// ȷ����preEdge��λ��
		}
		if(temp->next!=NULL) {				// ��preEdge����һ���ߴ���
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;
		}
		return myEdge;						// ���û���ҵ���һ���ߣ�myEdge.to=-1
	}

	//Ϊͼ�趨һ����
	void setEdge(int from,int to,int weight) {
		link<listUnit> *temp=graList[from].head;
		//graList[from].head������Ƕ���from�ı߱�temp->nextָ�򶥵�from�ĵ�һ����
		//(���temp->next��Ϊnull)
		while(temp->next!=NULL && temp->next->element.vertex<to)
			temp=temp->next;
		//ȷ����(from,to)��<from,to>�ڱ߱��е�λ��,���������,
		//���(from,to)��<from,to>Ϊ�¼ӵ�һ����
		if(temp->next==NULL) {
			temp->next=new link<listUnit>;
			temp->next->element.vertex=to;
			temp->next->element.weight=weight;
			numEdge++;
			inDegree[to]++;
			return ;
		}
			
		//��(from,to)��<from,to>�ڱ߱����Ѵ���,��ֻ��Ҫ�ı�ߵ�Ȩֵ
		if(temp->next->element.vertex==to) {
			temp->next->element.weight=weight;
			return ;
		}

		//��(from,to)��<from,to>�ڱ߱��в�����,���ڱ߱���������������,���ڱ߱��в���������
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

	//ɾ��ͼ��һ����
	void delEdge(int from, int to) {
		link<listUnit> *temp=graList[from].head;
		while(temp->next!=NULL && temp->next->element.vertex<to) {
			temp=temp->next; //ȷ����(from,to)��<from,to>�ڱ߱��е�λ��(����ñߴ���)
			if(temp->next==NULL) {
				return ;//��(from,to)��<from,to>�ڱ߱��в�����,����Ҫ���κβ���
			}
			if(temp->next->element.vertex>to) {
				return ;//��(from,to)��<from,to>�ڱ߱��в�����,����Ҫ���κβ���
			}
			//��(from,to)��<from,to>�ڱ߱��д�����ȷ���˸ñ��ڱ߱��е�λ��,
			//��ӱ߱��н���ɾ��
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

//�������ܣ���ʼ��ͼ
void Graphl::initGraphl(Graphl *Graphl,int a[N][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(a[i][j]>0) {
				Graphl->setEdge(i,j,a[i][j]);
			}
		}
	}
}

//�������ܣ������������
void Graphl::DFS(Graphl& G, int v) {
	G.mark[v]=VISITED;
	visit(G,v);
	//����V�ڽӵ���δ�����ʹ��Ķ��㣬���ݹ�ذ���������ȵķ�ʽ��������
	for(Edge e=G.firstEdge(v);G.isEdge(e);e=G.nextEdge(e)) {
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			DFS(G,G.toVertex(e));
		}
	}
}


//�������ܣ������������
void Graphl::BFS(Graphl& G, int v) {
	std::queue<int> aQueue;
	visit(G,v);
	G.mark[v]=VISITED;
	aQueue.push(v);
	while(!aQueue.empty()) {
		int u=aQueue.front();
		aQueue.pop();
		// �ö����ڽӵ���ÿһ��δ���ʶ��㶼���
		for(Edge e=G.firstEdge(u);G.isEdge(e);e=G.nextEdge(e)) 
		if(G.mark[G.toVertex(e)]==UNVISITED) {
			visit(G,G.toVertex(e));
			G.mark[G.toVertex(e)]=VISITED;
			aQueue.push(G.toVertex(e));
		}
		
		
	}
}

//�������ܣ���ʾ����
void Graphl::visit(Graphl& G, int v) {
	std::cout<<"V"<<v<<" ";
}



#endif
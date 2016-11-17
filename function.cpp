//
// Created by Aaron on 2016/11/14.
//

#include "preDefine.h"

void ShowMenu() {
    cout << "============================" << endl;
    cout << "    ��ӭʹ�þ�������ϵͳ    " << endl;
    cout << "       **��ѡ��˵�**       " << endl;
    cout << "============================" << endl;
    cout << "1.������������ֲ�ͼ" << endl;
    cout << "2.�����������ֲ�ͼ" << endl;
    cout << "3.���������·ͼ" << endl;
    cout << "4.���������·ͼ�еĻ�·" << endl;
    cout << "5.��������������·������̾���" << endl;
    cout << "6.�����·�޽��滮ͼ" << endl;
    cout << "7.ͣ��������������Ϣ" << endl;
    cout << "8.�˳�ϵͳ" << endl;
}

//����ͼ�������Ϣ
void LoadGraph(Graph &graph) {
    //����ڵ���Ϣ
    string filename = "vertexes.txt";
    ifstream inf1(filename.c_str());
    string name, description;
    int popular_degree = 0, is_toilet = 0, is_rest = 0;
    int i = 0, j;
    while (inf1.good()) {
        //���ܹ�ֱ��ͨ������д�����ݣ�����
//        inf1>>graph.node_table[i++].name>>graph.node_table[i++].description>>graph.node_table[i++].popular_degree
//            >>graph.node_table[i++].is_toilet>>graph.node_table[i++].is_rest;

        inf1 >> name >> description >> popular_degree
             >> is_toilet >> is_rest;
        graph.node_table[i].name = name;
        graph.node_table[i].description = description;
        graph.node_table[i].popular_degree = popular_degree;
        graph.node_table[i].is_toilet = is_toilet;
        graph.node_table[i].is_rest = is_rest;
        i++;
    }
    inf1.close();

    /**
     * ���Խڵ���Ϣ�Ƿ������ȷ

    for(int j=0;j<i;j++)
        cout<<(graph.node_table[j].name)<<" "<<(graph.node_table[j].description)<<endl;
    */


    //����·����Ϣ
    filename = "routes.txt";
    ifstream inf2(filename.c_str());
    string from, to;
    int timeFee = 0, distance = 0;
    while (inf2.good()) {
        inf2 >> from >> to >> distance >> timeFee;
//        cout<<from<<"  "<<to<<"  "<<distance<<"  "<<timeFee<<endl;
        //���Ҷ������������е�λ��
        i = GetVertexPos(graph, from);
        j = GetVertexPos(graph, to);
        //��������Ϣ����ֵ
        Edge *P = new Edge(j, distance, timeFee);
        Edge *Q = new Edge(i, distance, timeFee);
        P->link = graph.node_table[i].adj;//��һ��P������ΪNULL�������漸�ξͻ᲻�ϵļӵ�������ǰ��
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }
//    cout<<"����Ϊ  "<<graph.num_edges<<endl;
    inf2.close();
    /**
      * ����·����Ϣ�Ƿ������ȷ--Ӧ������ȷ��-----һ��Ҫע����صı���Ҫͳһ��
        for(int m=0;m<graph.num_vertices;m++)
        cout<<(graph.node_table[m].adj->dest)<<" "<<(graph.node_table[m].adj->distance)<<endl;

    int num_vertices=graph.num_vertices;
    Edge *edge;
    for(i=0;i<num_vertices;i++){
        cout<<graph.node_table[i].name<<"  ";
        for(edge=graph.node_table[i].adj;edge;edge=edge->link){//����ĳһ���ڵ�������ڽӽڵ���Ϣ
            cout<<graph.node_table[edge->dest].name<<"  ";
        }
        cout<<endl;
    }
    cout<<"end"<<endl;
 */
}

int GetVertexPos(Graph &graph, string &name) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (name == graph.node_table[i].name)//�ҵ���Ҫ���ҵĶ���
            return i;
    return -1;//û�ҵ�������-1
}

void OutputAdjMatrix(Graph &graph) {
    int i, j, num_vertices = graph.num_vertices;
    //����һ����ά���������洢�ڽӾ������Ϣ
    double **a = new double *[num_vertices];
    for (i = 0; i < num_vertices; i++)
        a[i] = new double[num_vertices];


    //��ʼ��������Ϣ
    for (i = 0; i < num_vertices; i++)
        for (j = 0; j < num_vertices; j++)
            if (i != j)
                a[i][j] = INFINITY;
            else
                a[i][j] = 0;
//    cout<<"�����ʼ���ɹ�"<<endl;

    //���ڽ�����ת��Ϊ�ڽӾ���
    Edge *edge = new Edge;
    for (i = 0; i < num_vertices; i++)
        for (edge = graph.node_table[i].adj; edge; edge = edge->link) {//����ĳһ���ڵ�������ڽӽڵ���Ϣ
            j = edge->dest;
            a[i][j] = edge->distance;
//            cout<<i<<endl;
        }
    graph.adj_matrix = a;
//    cout<<"ת���ɹ�"<<endl;

    //����ڽӾ������Ϣ
    for (int i = 0; i < num_vertices; ++i)//��ӡ��һ��
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//��ӡ���ı�ͷ
        for (j = 0; j < num_vertices; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
    delete[]edge;
}

//�������·��ͼ
void CreateTourSortGraph(Graph &graph) {
    string *vex = DFSTraverse(graph);
    /**
     * ����������ȱ������
    for (int i = 0; i < graph.num_vertices; i++) {
        cout << vex[i] << "->";
    }
    cout << endl;
    cout<<"������ȱ�������"<<endl;
      */
    string tour_map[2 * graph.num_vertices];
//    cout<<"size ��СΪ"<<tour_map->size()<<endl;//size���صĵ�����ʲô
//    tour_map[0]="1";
//    tour_map[1]="2";
//    tour_map[2]="3";
//    tour_map[3]="4";
//    tour_map[4]="5";
//    tour_map[5]="6";
//    cout<<"size ��СΪ"<<tour_map->size()<<endl;

    int n = 0;

    //��������·��ͼ
    for(int i=0;i<graph.num_vertices-1;i++){
        cout<<"IsEdge(graph,"<<vex[i]<<","<<vex[i+1]<<") "<<IsEdge(graph,vex[i],vex[i+1])<<"  "<<"i=  "<<i<<endl;
        if(IsEdge(graph,vex[i],vex[i+1])){//�����������֮���бߣ���ôֱ�ӽ��������������·������ʼ��
            if(i!=10){
                tour_map[n++]=vex[i];

            }else{
                tour_map[n++]=vex[i];
                tour_map[n++]=vex[i+1];
                cout<<"vex[i+1]"<<vex[i+1]<<endl;

            }
        }else{
            int temp_i=i;
            //���������
            tour_map[n++]=vex[i];
            while(!IsEdge(graph,vex[--temp_i],vex[i+1])){//ֻҪ��������֮��û�б�
                tour_map[n++]=vex[temp_i];//��ǰһ��������뵽������·��ͼ��
                cout<<"temp_i  "<<temp_i<<"    "<<vex[temp_i]<<endl;
            }
            tour_map[n++]=vex[temp_i];
            cout<<"temp_i->"<<temp_i<<endl;
        }
}

    cout << "���н���,n=" <<n<< endl;
    for (int m = 0; m < n; m++) {
        cout<<tour_map[m]<<"->";
    }

}

//������ȱ����㷨-�ݹ����ں���---���˰�����󣬾�Ȼ��������Ϊroutes.txt�ļ�����һ�����С�����
string *DFSTraverse(Graph &graph) {
    //���������Ӧ�Ľڵ��Ƿ��Ѿ�������
    int *visited = new int[graph.num_vertices];
    string *vertex = new string[graph.num_vertices];
    int num = 0;
    //��ʼ�����нڵ�Ϊδ���ʵ�״̬
    for (int i = 0; i < graph.num_vertices; i++)
        visited[i] = 0;
    DFS(graph, 0, visited, vertex, num);
    //�ͷſռ�
    delete[]visited;
//    cout<<"num �Ĵ�СΪ"<<num<<endl;
    return vertex;
}

/**
 * ������ȱ����㷨--�ݹ�
 * @param graph
 * @param v �����ʵĽڵ�
 * @param visited ���������Щ�ڵ��Ѿ������ʵ�����
 */

void DFS(Graph &graph, int v, int visited[], string *vertex, int &num) {
    //���ʽڵ�v
//    cout<<graph.node_table[v].name<<"-->";
    vertex[num++] = graph.node_table[v].name;
//    cout<<vertex[num]<<"  "<<num<<endl;
//    num++;
    //��Ǹýڵ��Ѿ�������
    visited[v] = 1;
    //��ȡv�ĵ�һ���ڽӶ���
    int w = GetFirstNeighbor(graph, v);
    //���ڵ�w����
    while (w != -1) {
        //����û�б�����
        if (!visited[w])
            DFS(graph, w, visited, vertex, num);//���ʽڵ�w
        //��ȡ���ڽڵ�w�������һ���ڵ�
        w = GetNextNeighbor(graph, v, w);
    }
}

/**
 * ��ȡ�ڵ�v�ĵ�һ���ڽӶ���
 * @param graph
 * @param v
 * @return ���ڷ���λ�ã����򷵻�-1
 */
int GetFirstNeighbor(Graph &graph, int v) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        //ֻҪ�ڵ���ھͷ�����Ŀ�ĵ�
        if (p != NULL)
            return p->dest;
    }
    return -1;//�ڵ㲻�����򷵻�-1
}

/**
 * ��ȡgraph�нڵ�v����w�������һ���ڽӶ���
 * @param graph
 * @param v
 * @param w
 * @return ���ڷ���λ�ã����򷵻�-1
 */
int GetNextNeighbor(Graph &graph, int v, int w) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        while (p != NULL) {
            //�����ǰ�ڵ���w������һ���ڵ㲻Ϊ��
            if (p->dest == w && p->link != NULL)
                //������һ���ڽӽڵ����ڽӱ��е�λ��
                return p->link->dest;
            else
                //����Ѱ�ҽڵ�w
                p = p->link;
        }
    }
    return -1;//û���ҵ���һ���ڽӶ���---����-1
}

/**
 * �ж�graph�е�v1,v2��������֮���Ƿ���ֱ�����ڵı�
 * @param graph
 * @param v1
 * @param v2
 * @return
 */
bool IsEdge(Graph graph, string v1, string v2) {
    //��ȡ����v1���ڽӱ��е�����λ��
    int i = GetVertexPos(graph, v1);
    //��ȡ����v2���ڽӱ��е�����λ��
    int j = GetVertexPos(graph, v2);
    for (Edge *edge= graph.node_table[i].adj; edge; edge = edge->link) {
        if (j == edge->dest)
            return true;
//        else{
//            edge = edge->link;
//        }
    }
    return false;
}
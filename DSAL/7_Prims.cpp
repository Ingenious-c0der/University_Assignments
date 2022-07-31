#include <iostream>
using namespace std;
// you have a business with several offices , you want to lease phone lines to connect them up with each other and the phone company
// charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost
// solve problem by suggesting appropriate data structure
// graph => minimum spanning tree


class Graph
{

    int **matrix;
    int max_ver = 0;
    string *officeList;
    static int index;

public:
    Graph(int max_vertices)
    {

        matrix = new int *[max_vertices];
        for (int i = 0; i < max_vertices; i++)
        {
            matrix[i] = new int[max_vertices];
        }
        for (int i = 0; i < max_vertices; i++)
        {
            for (int j = 0; j < max_vertices; j++)
            {
                matrix[i][j] = 0;
            }
        }
        max_ver = max_vertices;
        officeList = new string[max_ver];
    }
    ~Graph()
    {

        for (int i = 0; i < max_ver; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void insertOffice(string name)
    {
        if (index < max_ver)
        {
            officeList[index++] = name;
        }
        else
        {
            cout << "No more offices can be added" << endl;
        }
    }
    int refValuefromName(string name)
    {
        for (int i = 0; i < max_ver; i++)
        {
            if (officeList[i] == name)
            {
                return i;
            }
        }
        return -1;
    }

    void addLine(string name1, string name2, int weight)
    {
        int index1 = refValuefromName(name1);
        int index2 = refValuefromName(name2);
        if (index1 == -1 || index2 == -1)
        {
            if (index1 == -1)
            {
                cout << "No office named " << name1 << " found" << endl;
                return;
            }
            cout << "No office named " << name2 << " found" << endl;
        }
        matrix[index1][index2] = weight;
        matrix[index2][index1] = weight;
    }

    int minKey(int key[], int mstSet[])
    {
        int min = INT_MAX, min_index;
        for (int i = 0; i < max_ver; i++)
        {
            if (mstSet[i] == 0 && key[i] < min)
            {
                min = key[i];
                min_index = i;
            }
        }
        return min_index;
    }
    //for smooth brainers like me 
    void simplifiedPrims()
    {   
        int mst[max_ver] = {0};
        int total = 0 ;
        int selected[max_ver]  = {0};
        selected[0] = 1 ;
        int edge_count = 0 ; 
        int y = 0 ; 
        int x  = 0;
        while(edge_count < max_ver-1)
        {

            int min = INT_MAX; 
            for( int i = 0 ; i< max_ver; i++)
            {
                if (selected[i] == 1)
                {

                    for(int j = 0; j<max_ver ;j++)

                    {
                        if(selected[j] == 0 && matrix[i][j])
                        {
                            if(min> matrix[i][j])
                            {
                                min = matrix[i][j];
                                x = i ; 
                                y = j ;
                            }
                        }

                    }

                }
            }
           
            cout << x << " - " << y << " :  " << matrix[x][y]<<endl;
            total+= matrix[x][y];
            selected[y] = 1; 
            edge_count++; 

        }
      
        cout<<"Total cost "<<total<<endl;



    }

    void PRIMS()
    {
        
        int parent[max_ver] = {0};
        int key[max_ver] = {0};
        int mstSet[max_ver] = {0};

        for (int i = 0; i < max_ver; i++)
        {
            key[i] = INT_MAX;
        }
        key[0] = 0;
        parent[0] = -1;
        for (int i = 0; i < max_ver - 1; i++)
        {
            int u = minKey(key, mstSet);
            mstSet[u] = 1;
            for (int v = 0; v < max_ver; v++)
            {

                if (matrix[u][v] && mstSet[v] == 0 && matrix[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = matrix[u][v];
                }
            }
        }
        printMST(parent);
    }

    void printMST(int parent[])
    {
        cout << "Adjecency Matrix : " << endl;
        for (int i = 0; i < max_ver; i++)
        {
            cout << officeList[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < max_ver; i++)
        {
            for (int j = 0; j < max_ver; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }

        cout << endl;
        cout << "Minimum Spanning Tree : " << endl;
        cout << "Line  \tCost" << endl;
        int tc = 0;
        for (int i = 1; i < max_ver; i++)
        {
            cout << officeList[parent[i]] << " - " << officeList[i] << "\t" << matrix[i][parent[i]] << endl;
            tc += matrix[i][parent[i]];
        }
        cout << "Total Cost : " << tc << endl;
    }
};
int Graph::index = 0;

int main()
{
    Graph g(7);
    // A is the phone line company /root
    g.insertOffice("A");
    g.insertOffice("B");
    g.insertOffice("C");
    g.insertOffice("D");
    g.insertOffice("E");
    g.insertOffice("F");
    g.insertOffice("G");

    /*

    The graph

            B        7       E
        1       8        11      10
    A       4        D       3       G
        5       6        9       12
            C        2      F
    */

    g.addLine("A", "B", 1);
    g.addLine("A", "C", 5);
    g.addLine("B", "C", 4);
    g.addLine("B", "D", 8);
    g.addLine("C", "D", 6);
    g.addLine("B", "E", 7);
    g.addLine("F", "E", 3);
    g.addLine("F", "G", 12);
    g.addLine("E", "G", 10);
    g.addLine("D", "F", 9);
    g.addLine("C", "F", 2);
    g.addLine("E", "F", 3);

    //g.PRIMS();
    g.simplifiedPrims();

    return 0;
}

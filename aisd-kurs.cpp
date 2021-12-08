#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
    
class DisjointSet {
    int* parent;
    int* size;
public:
    DisjointSet(int n) {//тут мы инициализируем пустое подмножество на число вершин
        parent = new int[n];//тут какая вершина к кому относится
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1;//изначально каждая вершина относится сама к себе т.е является началом своего подможества
            size[i] = 1;//размер подмножества, по умолчанию 1
        }
    }
    int find(int i) {//поиск начала подмножества, в котором находится i
        if (parent[i] == -1) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int x, int y) {//склеивает подмножества
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (size[s1] < size[s2]){//если подмножество s2 больше, то s1 присоединяется к нему
                parent[s1] = s2;
                size[s2] += size[s1];
            }
            else {//и наоборот
                parent[s2] = s1;
                size[s1] += size[s2];
            }
        }
    }
};


class Graph {
    vector<vector<int>> edgelist;
    int V;
    int caster = 0;
public:
    Graph(int V) {
        this->V = V;
    }
    void symboltest(int x) {
        if (x > 60 && x < 96) caster = 65; 
        else if (x > 96) caster = 97;
    }

    void addEdge(int x, int y, int w) {
        symboltest(x);
        edgelist.push_back({ w,x-caster,y-caster});
    }
    int kruskal() {
        //тут сортировка, самый простой алгоритм
        for (int i = 0; i < edgelist.size(); i++) {
            for (int j = i; j < (edgelist.size()); j++) {
                if (edgelist[i] > edgelist[j]) {
                    swap(edgelist[i], edgelist[j]);
                }
            }
        }

        DisjointSet s(V);
        int ans = 0;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            if (s.find(x) != s.find(y)) {//если две ноды не явлвяются частью одного поднможества, но могут быть
                if (caster != 0) {//то выводим обе ноды
                    int wa1 = (x + caster), wa2 = (y + caster);
                    cout << (static_cast<char>(wa1)) << " - " << (static_cast<char>(wa2)) << endl;
                }
                else cout << x << " - " << y << endl;//это на случай цифровых вершин
                s.unite(x, y);//и склеиваем
                ans += w;//увеличиваем вес дерева на вес 
            }
        }
        return ans;
    }
};

int fileRoutine() {
    ifstream File;
    File.open("D:\\podelki\\aisd-kurs\\data2.txt");
    if (!File.is_open())
    {
        cout << "File not found\n";
        return 0;
    }
    int y,count = 0;
    char x;//change to int for digital verticles
    while (!File.eof()) {
        File >> x;
        File >> x;
        File >> y;
        if (y > 1023) {
            cout << "too heavy verticle" << endl;
            return 0;
        }
        count++;
    }
    File.close();
    
    if (count < 51) return count;
    else {
        cout << "too big graph";
        return 0;
    }
}

int main()
{
    int w,q = fileRoutine();//тут проверяем файл
    if (q == 0) return 7;//0 возвращается если с файлом что-то не так, тогда конец
    Graph g(q); //создаётся граф
    ifstream f;
    f.open("D:\\podelki\\aisd-kurs\\data2.txt");
    char x, y;//для вершин описанных цифрами поменять char на int и убрать 1 у data
    while (!f.eof()) {//читаем файл отсечками по 3 и добавляем в граф
        f >> x;
        f >> y;
        f >> w;
        g.addEdge(x, y, w);
    }


   /* g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 11, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(8, 9, 4);
    g.addEdge(9, 10, 7);
    g.addEdge(10, 2, 9);//17
    g.addEdge(2, 11, 3);
    g.addEdge(11, 7, 1);//19
    g.addEdge(10, 11, 4);*/
    //A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8, J=9, L=10, M=11
    /*g.addEdge('A', 'B', 4);//для маленьких букв 65 заменить на 97
    g.addEdge('A', 'H', 8);
    g.addEdge('B', 'C', 8);
    g.addEdge('B', 'H', 11);
    g.addEdge('B', 'M', 7);
    g.addEdge('C', 'I', 2);
    g.addEdge('C', 'F', 4);
    g.addEdge('D', 'E', 9);
    g.addEdge('D', 'F', 14);
    g.addEdge('E', 'F', 10);
    g.addEdge('F', 'G', 2);
    g.addEdge('G', 'H', 1);
    g.addEdge('G', 'I', 6);
    g.addEdge('H', 'I', 7);
    g.addEdge('I', 'J', 4);
    g.addEdge('J', 'L', 7);
    g.addEdge('L', 'C', 9);//17
    g.addEdge('C', 'M', 3);
    g.addEdge('M', 'H', 1);//19
    g.addEdge('L', 'M', 4);*/
    
    /*g.addEdge('a', 'b', 4);//для маленьких букв 65 заменить на 97
    g.addEdge('a', 'h', 8);
    g.addEdge('b', 'c', 8);
    g.addEdge('b', 'h', 11);
    g.addEdge('b', 'm', 7);
    g.addEdge('c', 'i', 2);
    g.addEdge('c', 'f', 4);
    g.addEdge('d', 'e', 9);
    g.addEdge('d', 'f', 14);
    g.addEdge('e', 'f', 10);
    g.addEdge('f', 'g', 2);
    g.addEdge('g', 'h', 1);
    g.addEdge('g', 'i', 6);
    g.addEdge('h', 'i', 7);
    g.addEdge('i', 'j', 4);
    g.addEdge('j', 'l', 7);
    g.addEdge('l', 'c', 9);//17
    g.addEdge('c', 'm', 3);
    g.addEdge('m', 'h', 1);//19
    g.addEdge('l', 'm', 4);*/
    

    cout << g.kruskal();
    f.close();
}


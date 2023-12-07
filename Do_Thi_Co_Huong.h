#ifndef Do_thi_Co_Huong
#define Do_thi_Co_Huong

#include"Library.h"


//1 IN RA TAT CA CAC DINH CUA DO THI

void DFS(int x) {
    std::cout << x << '\t';
    visited[x] = 1;
    for (auto v : graph[x]) {
        if (!visited[v]) {
            DFS(v);
        }
    }
}

void printVertex(int x) {       
    for (int i = 1; i <= V; ++i)
        if (!visited[i]) {
            DFS(i);
        }
}



//2 TÌM TAT CA DUONG DI TU DIEM DAU VA DIEM DICH NHAP TU BAN PHIM
void timDuongDi(int start, int end, std::vector<int> path, std::vector<std::vector<int>>& Way) {

    visited[start] = true;
    path.push_back(start);


    if (start == end) {
        Way.push_back(path);
    }
    else {
        for (int v : graph[start]) {
            if (!visited[v]) {
                timDuongDi(v, end, path, Way);
            }
        }
    }

    visited[start] = false;
    path.pop_back();
}

void inTatCaDuongDi(int start, int end, std::vector<int> path) {
    std::vector<std::vector<int> > Way;
    timDuongDi(start, end, path, Way);
    if (Way.size() == 0) {
        std::cout << "Khong co duong di tu " << start << " den " << end << std::endl;
        return;
    }
    std::cout << "Tat Ca duong di bat dau tu " << start << " toi " << end << ":" << std::endl;
    for (std::vector<int> tamp : Way) {
        for (int x : tamp) {
            std::cout << x << '\t';
        }
        std::cout << '\n';
    }
}

void InduongdiDainhat(int start, int end)
{
    std::vector<int> longestPath;
    std::vector<std::vector<int>> max;
    std::vector<int> path;
    timDuongDi(start, end, path, max);
    if (max.size() == 0) return;
    int maxLength = 0;



    for (int i = 0; i < max.size(); i++) {
        if (max[i].size() > maxLength) {
            maxLength = max[i].size();
            longestPath = max[i];
        }
    }

    std::cout << "Duong di dai nhat la: ";
    for (int i = 0; i < longestPath.size(); i++) {
        std::cout << longestPath[i] << " ";
    }

    std::cout << "\n";
}

void InduongdiNgannhat(int start, int end)
{

    std::vector<int> shortestPath;
    std::vector<std::vector<int>> max;
    std::vector<int> path;
    timDuongDi(start, end, path, max);
    if (max.size() == 0) return;
    int minLength = INT_MAX;


    for (int i = 0; i < max.size(); i++) {
        if (max[i].size() < minLength) {
            minLength = max[i].size();
            shortestPath = max[i];
        }
    }

    std::cout << "Duong di ngan nhat la: ";
    for (int i = 0; i < shortestPath.size(); i++) {
        std::cout << shortestPath[i] << " ";
    }

    std::cout << "\n";
}




//3 KIEM TRA DO THI CO CHU TRINH HAY KHONG

int color[100]; // 0: mau trang, 1: mau xam, 2: mau den.

int isCycle(int child) {
    color[child] = 1;
    for (auto x : graph[child]) {
        if (color[x] == 0) {
            if (isCycle(x)) return true;
        }
        else {
            if (color[x] == 1) {                
                return true;
            }
        }
    }
    color[child] = 2;
    return false;
}

//4 TIM THANH PHAN LIEN THONG MANH CUA DO THI (Kosaraju) 

std::vector<std::vector<int> > graph1;// luu canh nguoc cua do thi graph
std::stack<int> tamp;// luu cac dinh da duyet xong

void dfs1(int u) {
    visited[u] = true;
    for (auto v : graph[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    tamp.push(u);
}

void reverse_graph() {
    for (int i = 1; i < graph.size(); i++) {
        for (auto x : graph[i]) {
            graph1[x].push_back(i);
        }
    }
}

void printConnectedComponent(int u) {
    visited[u] = true;    
    for (auto v : graph1[u]) {
        if (!visited[v]) {
            printConnectedComponent(v);
        }
    }
    std::cout << u << '\t';
}

void kosaraju() {
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    std::fill(visited.begin(),visited.end(),false);
    int dem = 0;
    while (!tamp.empty()) {        
        int u = tamp.top(); tamp.pop();
        if (!visited[u]) { 
            dem++;
            printConnectedComponent(u);
            std::cout << '\n';
        }        
    }
    std::cout << "So thanh phan lien thong manh cua do thi la: " << dem << std::endl;
}

void menu() {
    std::cout << "\n\n=================================Menu=====================================" << std::endl;
    std::cout << "* 1. In ra tat ca cac dinh cua do thi.                                   *" << std::endl;
    std::cout << "* 2. Tim Duong di giua 2 dinh trong do .                                 *" << std::endl;
    std::cout << "* 3. Kiem tra xem do thi co chu trinh hay khong.                         *" << std::endl;
    std::cout << "* 4. Tim thanh phan lien thong manh cua do thi.                          *" << std::endl;
    std::cout << "==========================================================================" << std::endl;
    std::cout << "Nhap lua chon cua ban: ";
}

void input(int& V, int& E) {
    do {
        std::cout << "Nhap so dinh (V): ";
        std::cin >> V;
        std::cout << "Nhap so canh (E >= 0): ";
        std::cin >> E;

        if (!(V > 0 && E >= 0)) {
            std::cout << "Du lieu dau vao khong hop le. Vui long nhap lai." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!(V > 0 && E >= 0));

    visited.resize(V + 1);
    graph.resize(V + 1);
    

    std::cout << "Nhap cac canh (u, v):" << std::endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u == v) continue;
        graph[u].push_back(v);        
    }
}

void readFile(std::string filename, int& V, int& E) {
    std::fstream myFile;
    myFile.open(filename.c_str(), std::ios::in);
    if (!myFile.is_open()) {
        std::cout << "Khong mo duoc File!!!" << std::endl;
        return;
    }

    myFile >> V >> E;
    visited.resize(V + 1);
    graph.resize(V + 1);
    
    for (int i = 1; i <= E; i++) {
        int x, y;
        myFile >> x >> y;
        graph[x].push_back(y);        
    }
    myFile.close();
}

void Main() {
    while (true) {
        menu();
        int lc; std::cin >> lc;
        switch (lc) {
        case 1:
        {           
            printVertex(1);
            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 2:
        {
            int start, end;

            std::cout << "Nhap dinh bat dau: "; std::cin >> start;
            std::cout << "Nhap dinh ket thuc: "; std::cin >> end;

                       
            std::vector<int> path; // vector luu tru duong di

                        
            InduongdiDainhat(start, end);

           
            InduongdiNgannhat(start, end);

            
            inTatCaDuongDi(start, end, path);
            
            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 3:
        {
            int Cycle = 0;
            for (int i = 1; i <= V; i++) {
                Cycle = isCycle(i);
                if (Cycle == 1) break;
            }
            if (Cycle == 1) {                
                std::cout << "Do thi ton tai chu trinh" << std::endl;
            }
            else {
                std::cout << "Do thi khong ton tai chu trinh" << std::endl;
            }

            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 4:
        {
            graph1.resize(V + 1);
            reverse_graph();
            kosaraju();
            std::fill(visited.begin(), visited.end(), false);
            break;
        }        
        default:
        {
            return;
        }
        }
    }
}


#endif // !Do_thi_Co_Huong

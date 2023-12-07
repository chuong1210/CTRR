#ifndef Do_Thi_Vo_Huong
#define Do_Thi_Vo_Huong

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

void printVertex() {   
    for (int i = 1; i <= V; i++)
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

void inTatCaDuongDi(int start, int end) {
    std::vector<int> path;
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

int isCycle(int child, int parent) {
    visited[child] = true;
    for (auto x : graph[child]) {
        if (!visited[x]) {
            if (isCycle(x, child)) return true;
        }
        else {
            if (x != parent) return true;
        }
    }
    return false;
}



//4 TIM CAY KHUNG CUA DO THI
std::vector<std::pair<int, int> > tamp; // luu cac canh cua cay khunng

void printSpanningtree() {
    for (auto x : tamp) {
        std::cout << x.first << '\t' << x.second << std::endl;
    }
}

void DFS1(int u) {
    visited[u] = true;
    for (auto v : graph[u]) {
        if (!visited[v]) {
            tamp.push_back({ u,v });
            DFS1(v);
        }
    }
}



//5 DEM SO THANH PHAN LIEN THONG CO TRONG DO THI

void printConnectivity(std::vector<std::vector<int> > All_cpp) {
    std::cout << "Cac thanh phan lien thong" << std::endl;
    for (int i = 0; i < All_cpp.size(); i++) {
        std::cout << "Thanh phan Lien thong thu " << i + 1 << ": ";
        for (auto x : All_cpp[i]) {
            std::cout << '\t' << x;
        }
        std::cout << '\n';
    }
}

void dfs(int u,std::vector<int> &cpp)
{
    visited[u] = true;
    cpp.push_back(u);

    for (int v : graph[u])
        if (!visited[v])
            dfs(v,cpp);
}

int countccp(int V, std::vector<std::vector<int> > &All_cpp)
{
    int ccp_amount = 0;    
    std::vector<int> cpp;

    for (int u = 1; u <= V; ++u)
        if (!visited[u])
        {            
            dfs(u,cpp);
            All_cpp.push_back(cpp);
            ++ccp_amount;
            cpp.clear();
        }
    return ccp_amount;
}

void menu() {
    std::cout << "\n\n=================================Menu=====================================" << std::endl;
    std::cout << "* 1. In ra tat ca cac dinh cua do thi.                                   *" << std::endl;
    std::cout << "* 2. Tim Duong di giua 2 dinh trong do .                                 *" << std::endl;
    std::cout << "* 3. Kiem tra xem do thi co chu trinh hay khong.                         *" << std::endl;
    std::cout << "* 4. Tim cay khung cua do thi.                                           *" << std::endl;
    std::cout << "* 5. Dem so thanh phan lien thong cua do thi.                            *" << std::endl;
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

    graph.resize(V + 1);
    visited.resize(V + 1);

    std::cout << "Nhap cac canh (u, v):" << std::endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u == v) continue;
        graph[u].push_back(v);
        graph[v].push_back(u); // Do thi vo huong
    }
}

void readFile(std::string filename,int &V,int &E) {
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
        graph[y].push_back(x);       
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
            printVertex();
            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 2:
        {
            int start, end;

            std::cout << "Nhap dinh bat dau: "; std::cin >> start;
            std::cout << "Nhap dinh ket thuc: "; std::cin >> end;           

            
            InduongdiDainhat(start, end);

            
            InduongdiNgannhat(start, end);

            
            inTatCaDuongDi(start, end);

            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 3:
        {
            int Cycle = 0;
            for (int i = 1; i < V; i++) {
                if (!visited[i]) {
                    Cycle = isCycle(i, 0);
                    if (Cycle == 1) break;
                }
            }
            if (Cycle==1) {
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
            std::vector<std::vector<int> > cpp;
            if (countccp(V,cpp) == 1) {
                std::fill(visited.begin(), visited.end(), false);
                DFS1(1);
                printSpanningtree();
                tamp.clear();
            }
            else {
                std::cout << "Do thi khong ton tai cay khung" << std::endl;
            }            
            std::fill(visited.begin(), visited.end(), false);
            break;
        }
        case 5:
        {
            std::vector<std::vector<int> > All_cpp;
            std::cout << "So thanh phan lien thong cua do thi: " << countccp(V, All_cpp) << std::endl;
            printConnectivity(All_cpp);
            std::fill(visited.begin(), visited.end(), false);
            All_cpp.clear();
            break;
        }
        default:
        {
            return;
        }
        }
    }
}


#endif // !Do_Thi_Vo_Huong
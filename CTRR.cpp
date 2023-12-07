
#include<iostream>
#include<vector>
#include<stack>
#include <climits>
#include <queue>
#include <bits/stl_algobase.h>
#include <fstream>


using namespace std;

 std::vector<std::vector<int>> graph; 
 std::vector<bool> visited; 
 int matrix[1000][1000]; 
ifstream inputFile("../inputfile.txt");
ofstream outputfile("../outputfile.txt"); 

//1 TÌM TAT CA DUONG DI TU DIEM DAU VA DIEM DICH NHAP TU BAN PHIM
void TimDuongDiDFS(int start, int end, vector<int>& path) {
    visited[start] = true; 
    path.push_back(start); 

   
    if (start == end) {
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
    else {
        for (int v : graph[start]) {
            if (!visited[v]) {
                TimDuongDiDFS(v, end, path);
            }
        }
    }


    visited[start] = false;
    path.pop_back();
}



////2 DEM SO THANH PHAN LIEN THONG CO TRONG DO THI

void dfs(int u, vector<int>& ccp) {
    visited[u] = true;
    ccp.push_back(u);

    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v, ccp);
        }
    }
}

int countccp(int n) {
    int ccp_amount = 0;
    vector<vector<int>> all_ccp;

    for (int u = 1; u <= n; ++u) {
        if (!visited[u]) {
            vector<int> ccp;
            dfs(u, ccp);
            all_ccp.push_back(ccp);
            ++ccp_amount;
        }
    }

    for (int i = 0; i < ccp_amount; ++i) {
        cout << "CCP " << i+1 << ": ";
        for (int v : all_ccp[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    return ccp_amount;
}









//3 TÌM TAT CA DUONG DI DAI VA NGAN NHAT TU DIEM DAU VA DIEM DICH NHAP TU BAN PHIM
void TimDuongDiDaivaNgannhat(int start, int end, std::vector<int>& path,std::vector<std::vector<int>>& max) {

    visited[start] = true; 
    path.push_back(start); 

   
    if (start == end) {
       max.push_back(path);
      
        cout << endl;
        
    }
    else {
        for (int v : graph[start]) {
            if (!visited[v]) {
                TimDuongDiDaivaNgannhat(v, end, path,max);
            }
        }
    }


    visited[start] = false;
    path.pop_back();
}

//3.A IN DUONG DI DAI NHAT
void InduongdiDainhat(int start ,int end )
{
std::vector<int> longestPath;
std::vector<std::vector<int>> max;
std::vector<int> path;
TimDuongDiDaivaNgannhat(start, end, path, max);
 int maxLength = 0; 
 	

    
    for(int i=0; i < max.size(); i++) {
        if(max[i].size() > maxLength) {
            maxLength = max[i].size();
            longestPath = max[i];
        }
    }

if(longestPath.size()!=0)
{
    for(int i=0; i < longestPath.size(); i++) {
        std::cout << longestPath[i] << " ";
    }
    
}
else
{
	cout << " Khong tim thay duong di dai nhat" ;
}
    cout << "\n" ;
}



//3.B IN DUONG DI NGAN NHAT
void InduongdiNgannhat(int start ,int end )
{
	
std::vector<int> shortestPath;
std::vector<std::vector<int>> max;
std::vector<int> path;
TimDuongDiDaivaNgannhat(start, end, path, max);
 int minLength = INT_MAX; 
 	

    
    for(int i=0; i < max.size(); i++) {
        if(max[i].size() < minLength) {
            minLength = max[i].size();
            shortestPath = max[i];
        }
    }
if(shortestPath.size()!=0)
{
    for(int i=0; i < shortestPath.size(); i++) {
        std::cout << shortestPath[i] << " ";
    }
}
else
{
	cout << " Khong tim thay duong di ngan nhat" ;
}
    
    cout << "\n" ;
}



void duyetdothiMatrrix(int i,int n, vector<int> &path) {
    for (int j = 1; j <= n; j++) {
        if (matrix[i][j] != 0 && visited[j] == false) {
            visited[j] = true;
            path.push_back(j);
            duyetdothiMatrrix(j,n,path);
        }
    }
}



void Nhapsocanh_Directed(int m)
{
	 cout << "Enter the edges for Directed: " << endl;
	    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
      
    }

}
void Nhapsocanh_Undirected(int m)
{
	  cout << "Enter the edges for Undirected:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v); // them canh u v vao do thi
    	graph[v].push_back(u);
    	

    }
    
}




void nhapsocanh_fileDirected(int m, std::ifstream& inputFile) {
    for (int i = 0; i < m; i++) {
        int u, v;
        inputFile >> u >> v;
        graph[u].push_back(v);
    }
}

void nhapsocanh_fileUndirected(int m, std::ifstream& inputFile) {
    for (int i = 0; i < m; i++) {
        int u, v;
        inputFile >> u >> v;
        cout << u << " va " << v ;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}
void nhapsocanhXuongfile_Directed(int m, std::ofstream& outputfile) {
    std::cout << "Enter the edges for directed:" << std::endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v); // Them canh u v vao do thi

        outputfile << u << " " << v << std::endl; 
        outputfile << v << " " << u << std::endl; 
    }
}

void nhapsocanhXuongfile_Undirected(int m, std::ofstream& outputfile) {
    std::cout << "Enter the edges for undirected:" << std::endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v); // Them canh u v vao do thi
        graph[v].push_back(u);

        outputfile << u << " " << v << std::endl; 
        outputfile << v << " " << u << std::endl; 
    }
}
void cleaGraph(int n)
{
	graph.clear();
	visited.clear();		
     graph.resize(n + 1); 
	   visited.resize(n + 1); 
}


// ham in do thi

void printGraph(int n)
{
	    for (int i = 1; i <= n; i++) {
        cout << i << ":";
        for (int v : graph[i]) {
            cout << " " << v;
        }
        cout << endl;
    }
}




void Menu()
{
	 int n, m; 
    int start, end;
    cout << "Nhap so luong dinh: ";
    cin >> n;
    cout << "Nhap so luong canh: ";
    cin >> m;
    graph.resize(n + 1); 
    visited.resize(n + 1); 
    int option;
do {
        cout << " -------------------------- Menu -------------------------- \n";
        cout << "| 1. Them Cac Canh                                         | \n";
        cout << "| 2. Them canh tu File                                     | \n";
        cout << "| 3. Nhap Cac Canh xuong File                              | \n";
        cout << "| 4. Duyet tim tat ca duong di DFS                         | \n";                      
        cout << "| 5. Tim Duong di dai nhat bang DFS                        | \n";
        cout << "| 6. Tim Duong di ngan nhat bang DFS                       | \n";
        cout << "| 7. Dem thanh phan lien thong bang DFS                    | \n";
        cout << "| 8. Clear                                                 | \n";
   		cout << "| 9. In do thi                                             | \n";
        cout << "| 0. Exit                                                  | \n ";
		cout << " ---------------------------------------------------------- \n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1: {
            	cout << "Chon cach Duyet Do thi" << "\n" ;
cout << "1.Duyet Directed" << "\n" ;
cout << "2.Duyet Undirected" << "\n"  ;

            	int num;
cin >> num;
switch(num){
    case 1:
Nhapsocanh_Directed(m);  
        break;
    case 2:
Nhapsocanh_Undirected(m);
        break;

    default:
        cout << "Invalid number";
}
                break;
    }
	
					
						
                           case 2:
	{
		cleaGraph(n);
		cout << "Chon cach Duyet Do thi" << "\n" ;
		cout << "1.Duyet Directed" << "\n" ;
		cout << "2.Duyet Undirected" << "\n"  ;
 			if (!inputFile.is_open()) 
				inputFile.open("../inputfile.txt");
 			if (inputFile.is_open()) 
		{
           	int num;
			cin >> num;
			switch(num){
 			   case 1:
					nhapsocanh_fileDirected(m,inputFile);
       					 break;
    		   case 2:
					nhapsocanh_fileUndirected(m,inputFile);
      					 break;

  			   default:
      			  cout << "Invalid number";
      			  break;
			}   
			     		inputFile.close();
    
    }

			else 
		{
       	 	cout << "Khong the mo file." << endl;
       		return ;
    				}

               			break;
					}
						
						
						case 3:
						{
	
		cleaGraph(n);
		cout << "Chon cach Duyet Do thi" << "\n" ;
		cout << "1.Duyet Directed" << "\n" ;
		cout << "2.Duyet Undirected" << "\n"  ;
 			if (!outputfile.is_open()) 
				outputfile.open("../outputfile.txt");
 			if (outputfile.is_open()) 
		{
           	int num;
			cin >> num;
			switch(num){
 			   case 1:
					nhapsocanhXuongfile_Directed(m,outputfile);
       					 break;
    		   case 2:
					nhapsocanhXuongfile_Undirected(m ,outputfile);
	      					 break;

  			   default:
      			  cout << "Invalid number";
      			  break;
			}   
			     		outputfile.close();
    
    }

			else 
		{
       	 	cout << "Khong the mo file." << endl;
       		return ;
    				}

               			break;
    }
					
						
                        case 4: 
					{            
  						cout << "Nhap dinh bat dau: ";
      					cin >> start;
      				    cout << "Nhap dinh ket thuc: ";
     				    cin >> end;
     					vector<int> path;
        				cout << "Tat Ca duong di bat dau tu " << start << " toi " << end << ":" << endl;
     					TimDuongDiDFS(start, end, path); 
            			break;
          		    }
          		          case 5:
            		{
            	          cout << "Nhap dinh bat dau: ";
    					  cin >> start;
  						  cout << "Nhap dinh ket thuc: ";
  						  cin >> end;
       					  cout << "Duong Di Ngan nhat la:" ;
  						 InduongdiNgannhat(start,end);
    						break;
					}
           				case 6:
					{
            			cout << "Nhap dinh bat dau: ";
   						cin >> start;
 					    cout << "Nhap dinh ket thuc: ";
  					    cin >> end;              
   						cout << "Duong Di dai nhat la:" ;
   						InduongdiDainhat(start,end);
              			break;
           			}
						
						case 7:
					{
				 	    cout << "Co tong cong: "<< countccp(n) << " thanh phan lien thong";
						break;
					}
						case 8:
					{
						cleaGraph(n);
						break;
					}
						
						case 9:
					{
						printGraph(n);
						break;
						}	
						
						
						case 10:
							{
								
								   	vector<int> path; int n1;
								   	path[0] = 1; 
								   	visited[1] = true;


								  	 cout<<"nhap so dinh: "; cin>>n1;
								   	  cout<<"Nhap ma tran do thi: \n";
								    for(int i=1;i<=n1;i++)
								    {
								    	 for(int j=1;j<=n1;j++)
								        {
								        	             cin>> matrix[i][j];
										}
									}
   
								duyetdothiMatrrix(1, n1,path);  
								    for(int num : path) {
       								 cout << num << " ";
   									 }
//								8
//								0 1 0 0 0 1 0 0
//								1 0 1 1 0 1 0 1
//								0 1 0 0 0 0 0 0
//								0 1 0 0 0 0 0 0
//								0 0 0 0 0 0 1 0
//								1 1 0 0 0 0 1 0
//								0 0 0 0 1 1 0 1
//								0 1 0 0 0 0 1 0
break;
							}
           
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }

        cout << endl;
    } while (option != 0);

}

int main() {

  Menu();



	return 0;
}

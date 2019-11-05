#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#define MAX 6000
using namespace std;
int Prev[MAX];//mang truy vet
int Free[MAX]={0};//bfs
queue<int> BFS;
ifstream inf;
ofstream ouf;
string ST;//dinh start
int st;//vi tri dinh start
string FN;//dinh finish
int fn;//vi tri dinh ket thuc
struct node
{
	string word;//nhan cua dinh
	vector<int> adj_peak;//cac dinh ke
};vector<node> peak;
int compare(string a,string b)//so sanh 2 tu
{
	int dem=0;
	for(int i=0;i<5;i++)
	{
		if(a[i]!=b[i])
			dem++;
	}
	if(dem==1)
		return 1;
	else return 0;
}
Creat_graph()
{
	node Node;
	inf.open("sgb-words.txt");
	while (!inf.eof())
	{
		inf>>Node.word;
		if(ST.compare(Node.word)==0)
			st=peak.size();//luu vi tri dinh bat dau
		else if(FN.compare(Node.word)==0)
			fn=peak.size();
		peak.push_back(Node);
		for(int i=1;i<peak.size();i++)
		{
			if(compare(peak.back().word,peak[i].word))
			{
				peak.back().adj_peak.push_back(i);
				peak[i].adj_peak.push_back(peak.size()-1);
			}
		}
	}
}
Input()
{
	cout<<"Tim kiem duong di giua 2 tu:\n";
	cout<<"Nhap tu bat dau: ";
	cin>>ST;
	cout<< "\nNhap dinh ket thuc: ";
	cin>>FN;
}
find_path(int u)
{
	Free[u]=1;
	BFS.pop();
	for(int i=0;i<peak[u].adj_peak.size();i++)
	{
		if(Free[peak[u].adj_peak.at(i)]==0)//dinh ke voi u chua tham
		{
			BFS.push(peak[u].adj_peak.at(i));//bfs
			Free[peak[u].adj_peak.at(i)]=1;
			Prev[peak[u].adj_peak.at(i)]=u;//truy vet
		}
	}
}
Print_path()
{
	while(fn!=st)
	{
		cout<< peak[fn].word<<"  <--  ";
		fn=Prev[fn];
	}
	cout<<peak[st].word;
}
int main()
{
	Input();
	Creat_graph();
	BFS.push(st);
	while(BFS.empty()==0)
	{
		find_path(BFS.front());//tim duong di bang cach bfs tu dinh start
	}
	int dem=1;//vua tim duoc 1 thanh phan lien thong
	for(int i=0;i<peak.size();i++)//dem so thanh phan lien thong bang bfs
	{
		if(Free[i]==0)
		{
			++dem;
			BFS.push(i);
			while(BFS.empty()==0)
			{
				find_path(BFS.front());
			}
		}
	}
	cout<<endl<<"Duong di nhu sau: \n";
	Print_path();
	cout<< "\nSo thanh phan lien thong la: "<<dem;
    return 0;
}

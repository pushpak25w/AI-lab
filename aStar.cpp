#include<bits/stdc++.h>
using namespace std;

int m,n;
vector<int>dx={0,0,1,-1};
vector<int>dy={1,-1,0,0};
set<pair<int,int>>trace;
map<pair<int,int>,pair<int,int>>parent;
set<pair<int,int>>obstacles;
void read(int m,int n){
	char tmp;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>tmp;
			if(tmp=='x')obstacles.insert({i,j});
		}
	}
}

void printGrid(vector<vector<int>>&grid){
	for(int i=0;i<m;i++){
		for(int i=0;i<2*n;i++)cout<<"-";
		cout<<endl;
		for(int j=0;j<n;j++){
			cout<<'|'<<grid[i][j];
		}
		cout<<'|'<<endl;
	}
	for(int i=0;i<2*n;i++)cout<<"-";
	cout<<endl;
}

void manhattan(vector<vector<int>>&grid,int stX,int stY,int desX,int desY,int dist){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			grid[i][j]=abs(i-stX)+abs(stY-j);
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			grid[i][j]*=abs(i-desX)+abs(desY-j);
	}
}
void path(int stX,int stY,int desX,int desY){
	pair<int,int>st={stX,stY};
	pair<int,int>des={desX,desY};
	pair<int,int>p=des;
	while(p!=st){
		trace.insert(p);
		p=parent[des];
		des=p;
	}
	trace.insert(st);
}

void findPath(vector<vector<int>>&grid,set<pair<int,int>>&obstacles,int stX,int stY,int desX,int desY){
	int x,y,X,Y;
	priority_queue<vector<int>>pq;
	vector<vector<int>>visited(m,vector<int>(n,false));
	pq.push({-grid[stX][stY],stX,stY});
	while(!pq.empty()){
		X=pq.top()[1];
		Y=pq.top()[2];
		visited[X][Y]=true;
		pq.pop();
		// cout<<X<<' '<<Y<<endl;
		if(X==desX && Y==desY){
			cout<<"reached"<<endl;
			path(stX,stY,desX,desY);
			return;
		}
		for(int i=0;i<4;i++){
			x=X+dx[i];
			y=Y+dy[i];
			if( x<m && y<n && x>=0 && y>=0 &&
				visited[x][y]==false &&
				obstacles.find({x,y})==obstacles.end()){
				pq.push({-grid[x][y],x,y});
				parent.insert({{x,y},{X,Y}});
			}
		}
	}

}

int main(){
	int x,y,N;
	cout<<"enter dimensions(m*n):"<<endl;
	cin>>m>>n;
	vector<vector<int>>grid(m+1,vector<int>(n+1,m*n+1));
	int stX=-1,stY=-1,desX=-1,desY=-1;
	while(stX>=m || stY>=n || stX<0 || stY<0){
		cout<<"enter valid start coordinates: ";
		cin>>stX>>stY;
	}
	while(desX>=m || desY>=n || desX<0 || desY<0){
		cout<<"enter valid destination coordinates: ";
		cin>>desX>>desY;
	}
	cout<<"enter grid"<<endl;
	read(m,n);
	while(N--){
		cin>>x>>y;
		if(x>=m || y>=n || x<0 || y<0 || (x==stX && y==stY) || (x==desX && y==desY)){
			N++;
			cout<<"invalid coordinates"<<endl;
		}
		else obstacles.insert({x,y});
	}
	manhattan(grid,desX,desY,stX,stY,0);
	// printGrid(grid);
	findPath(grid,obstacles,stX,stY,desX,desY);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(obstacles.find({i,j})!=obstacles.end()){
				cout<<"X"<<' ';
			}
			else if(trace.find({i,j})!=trace.end()){
				cout<<"="<<' ';
			}
			else cout<<"0"<<' ';
		}
		cout<<endl;
	}
}
/*
5 10
3 0
2 5
0 0 0 0 0 0 0 0 0 0
0 x 0 0 x x x x x 0
s x 0 0 0 d 0 0 x 0
0 0 x x x x x x x 0
0 0 0 0 0 0 0 0 0 0
*/
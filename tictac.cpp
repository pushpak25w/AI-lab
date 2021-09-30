#include<bits/stdc++.h>
using namespace std;

void printBoard(vector<vector<char>>&board,char machine,char human){
	for(int i=0;i<3;i++){
		cout<<"-------"<<endl;
		for(int j=0;j<3;j++){
			cout<<'|'<<board[i][j];
		}
		cout<<'|'<<endl;
	}
	cout<<"-------"<<endl;
}

vector<int> posswin(vector<vector<char>>&board,char mark,char machine,char human){
	vector<int>coordinates={-1,-1};
	vector<int>ans={-1,-1};
	int blank,countMark,countNotmark;
	for(int j=0;j<3;j++){
		blank=0;
		countMark=0;
		countNotmark=0;
		for(int i=0;i<3;i++){
			if(board[i][j]=='.'){
				blank++;
				coordinates[0]=i;
				coordinates[1]=j;
			}
			else if(board[i][j]==mark)countMark++;
			else countNotmark++;
		}
		if(countNotmark==3){
			cout<<"human won :("<<endl;
			printBoard(board,machine,human);
			exit(0);
		}
		if(countMark==2 && blank==1)ans=coordinates;
		blank=0;
		countMark=0;
		countNotmark=0;
		for(int i=0;i<3;i++){
			if(board[j][i]=='.'){
				blank++;
				coordinates[0]=j;
				coordinates[1]=i;
			}
			else if(board[j][i]==mark)countMark++;
			else countNotmark++;
		}
		if(countNotmark==3){
			cout<<"human won :("<<endl;
			printBoard(board,machine,human);
			exit(0);
		}
		if(countMark==2 && blank==1)ans=coordinates;
	}
	blank=0;
	countMark=0;
	countNotmark=0;
	for(int i=0;i<3;i++){
		if(board[i][i]=='.'){
			blank++;
			coordinates[0]=i;
			coordinates[1]=i;
		}
		else if(board[i][i]==mark)countMark++;
		else countNotmark++;
	}
	if(countNotmark==3){
		cout<<"human won :("<<endl;
		printBoard(board,machine,human);
		exit(0);
	}
	if(countMark==2 && blank==1)ans=coordinates;
	blank=0;
	countMark=0;
	countNotmark=0;
	for(int i=0;i<3;i++){
		if(board[i][2-i]=='.'){
			blank++;
			coordinates[0]=i;
			coordinates[1]=2-i;
		}
		else if(board[i][2-i]==mark)countMark++;
		else countNotmark++;
	}
	if(countNotmark==3){
		cout<<"human won :("<<endl;
		printBoard(board,machine,human);
		exit(0);
	}
	if(countMark==2 && blank==1)ans=coordinates;
	return ans;
}

void putx(vector<vector<char>>&board,char machine,char human){
	if(board[1][1]=='.'){
		board[1][1]=machine;
		return;
	}
	vector<int>win=posswin(board,machine,machine,human);
	if(win[0]!=-1){
		board[win[0]][win[1]]=machine;
		cout<<"human lost :)"<<endl;
		printBoard(board,machine,human);
		exit(0);
	}
	vector<int>lose=posswin(board,human,machine,human);
	if(lose[0]!=-1){
		board[lose[0]][lose[1]]=machine;
		return;
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='.'){
				board[i][j]=machine;
				return;
			}
		}
	}
}

int main(){
	vector<vector<char>>board(3,vector<char>(3,'.'));
	int x,y,n=4;
	string who;
	char human,machine;
	cout<<"you want X or O?"<<endl;
	cin>>human;
	if(human=='X')machine='O';
	else machine='X';
	cout<<"wanna play first?"<<endl;
	cin>>who;
	if(who=="no")
		board[1][1]=machine;
	else{
		n=5;
	}
	printBoard(board,machine,human);
	for(int i=0;i<n;i++){
		cin>>x>>y;
		if(x>=3|| y>=3 || board[x][y]!='.'){
			cout<<"invalid move"<<endl;
			exit(0);
		}
		board[x][y]=human;
		putx(board,machine,human);
		printBoard(board,machine,human);
	}

}
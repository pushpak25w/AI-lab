#include<bits/stdc++.h>
using namespace std;

char human,machine;

void printBoard(vector<vector<char>>&board){
	for(int i=0;i<3;i++){
		cout<<"-------"<<endl;
		for(int j=0;j<3;j++){
			cout<<'|'<<board[i][j];
		}
		cout<<'|'<<endl;
	}
	cout<<"-------"<<endl;
}

int boardIsFull(vector<vector<char>>&board){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(board[i][j]=='.')
				return false;
	return true;
}

int value(vector<vector<char>>&board){
	for(int i=0;i<3;i++){
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
			if(board[i][0]==machine)return 10;
			else if(board[i][0]==human)return -10;
		}
	}
	for(int j=0;j<3;j++){
		if(board[0][j]==board[1][j] && board[1][j]==board[2][j]){
			if(board[0][j]==machine)return 10;
			else if(board[0][j]==human)return -10;
		}
	}
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
		if(board[0][0]==machine)return 10;
		else if(board[0][0]==human)return -10;
	}
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
		if(board[0][2]==machine)return 10;
		else if(board[0][2]==human)return -10;
	}
	return 0;
}

int minmax(vector<vector<char>>&board,int depth,bool maxTurn,bool AI){
	int val=value(board);
	if(val==10)return 10-depth;
	if(val==-10)return -10+depth;
	if(boardIsFull(board))return 0;
	if(depth<=0){
		if(maxTurn)return INT_MIN;
		else return INT_MAX;
	}
	if(maxTurn){
		int opti=INT_MIN;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='.'){
					if(AI)board[i][j]=machine;
					else board[i][j]=human;
					opti=max(opti,minmax(board,depth-1,!maxTurn,AI));
					printBoard(board);
					cout<<opti<<endl;
					board[i][j]='.';
				}
			}
		}
		return opti;
	}
	else{
		int opti=INT_MAX;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='.'){
					if(AI)board[i][j]=machine;
					else board[i][j]=human;
					opti=min(opti,minmax(board,depth-1,!maxTurn,AI));
					printBoard(board);
					cout<<opti<<endl;
					board[i][j]='.';
				}
			}
		}
		return opti;
	}
}


void moveAi(vector<vector<char>>&board,int depth,bool maxTurn,bool AI){
	int optiVal=INT_MIN,x=-1,y=-1;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='.'){
				board[i][j]=machine;
				int val=minmax(board,depth,maxTurn,AI);
				board[i][j]='.';
				if(val>=optiVal){
					x=i;
					y=j;
					optiVal=val;
				}
			}
		}
	}
	board[x][y]=machine;
}

int main(){
	vector<vector<char>>board(3,vector<char>(3,'.'));
	int x,y,n=4,depth;
	string who;
	cout<<"you want X or O?"<<endl;
	cin>>human;
	cout<<"depth of minmax?"<<endl;
	cin>>depth;
	if(human=='X')machine='O';
	else machine='X';
	cout<<"wanna play first?"<<endl;
	cin>>who;
	bool AI=false;
	if(who=="no"){
		AI=true;
		moveAi(board,depth,false,AI);
	}
	else{
		n=5;
	}
	printBoard(board);
	for(int i=0;i<n;i++){
		cin>>x>>y;
		if(x>=3|| y>=3 || board[x][y]!='.'){
			cout<<"invalid move"<<endl;
			exit(0);
		}
		board[x][y]=human;
		moveAi(board,depth,AI,!AI);
		printBoard(board);
	}

}
/*
INPUT having 12 checkpoints
100 100
##................................................................................................##
#@@...........................................................................##..................##
#.###.........................................................................##..................##
#...@@........................................................................##..................##
#.##.@........................................................................##..................##
#.@#..........................................................................##.........@........##
#.@...........................................................................##..................##
#....@........................................................................##..................##
.........@....................................................................##..................##
.........G....S...............................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##............@.....##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##..................##
..............................................................................##............@.....##

OUTPUT would be 399
*/


#include<iomanip>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<map>
#include<limits.h>

using namespace std;
//graph containing checkpoints, source and goal
class graph{
	private:
		int cost[22][22];//to store the cost between two vertices
	//constructor to intialize the cost between any of two vertices with zero
	public:
	graph(int n){
		for(int i = 0;i<n;i++)
			for(int j = 0;j<n;j++)
				cost[i][j] = 0;
	}
	//return cost between vertex i and vertex j
	int findCost(int i,int j){
		return cost[i][j];
	}
	//function to update cost between any pair of two vertices
	void updateCost(int i,int j,int c){
		cost[i][j] = c;
	}
	//to check the existance of path for all vertices
	bool checkPath(int n){
		for(int i = 0;i<n;i++)
			for(int j =0;j<n;j++)
				if(cost[i][j] == -1)
					return false;
		return true;
	}
	//checks for adjacent vertex in the graph
	bool checkAdjacent(int i,int j){
		if(cost[i][j] == 0)
			return false;
		else
			return true;
	}
};
//assuming each element of input matrix as a node having two values x and y coordinates
struct node{
    int i;
    int j;
};

struct nodes{
    int i;
    int j;
    struct nodes* next;
};

struct nodes* queue=NULL;

bool allvisited(int *visited,int n){
	int i;
	for(i = 0;i<n;i++)
		if(visited[i] == 0)
			break;
	if(i == n)
		return true;
    return false;
}


bool isSafe(int i, int j, char arr[][100], int visited[][100], int row, int col){
    if(i>=row || j>=col || i<0 || j<0)
        return false;
    if(visited[i][j] || arr[i][j]=='#')
        return false;
    return true;
}

void enqueue(int i,int j, struct nodes** queue){
    struct nodes *newnode = new nodes;
    newnode->i = i;
    newnode->j= j;
    newnode->next = NULL;
    if(!*queue){
        *queue  =newnode;
        return;
    }
    struct nodes* temp = *queue;
    while(temp->next){
        temp = temp->next;
    }
    temp->next=newnode;
}

struct nodes* dequeue(struct nodes** queue){
    struct nodes* temp;
    if(!(*queue)->next){
        temp=*queue;
        *queue=NULL;
        return temp;
    }
    temp=*queue;
    *queue=(*queue)->next;
    return temp;
}
//to check whether the queue is empty or not
bool emptyqueue(struct nodes * queue){
    if(queue == NULL)
        return true;
    return false;
}

//to find the minimum possible distance between two nodes
bool bfs(struct node source,struct node goal, char arr[][100],int *mincost, int cost, int visited[][100], int row, int col){
    visited[source.i][source.j]=1;
    if(source.i==goal.i && source.j==goal.j){
        *mincost=cost;
        return true;
    }
    struct nodes * queue= NULL;
    enqueue(source.i,source.j,&queue);
    enqueue(-1,-1,&queue);
    struct nodes* temp;
    while(!emptyqueue(queue)){
        temp=dequeue(&queue);
        if(temp->i==-1){
            cost++;
            if(emptyqueue(queue))
                break;
            enqueue(-1,-1,&queue);
            continue;
        }
        if(isSafe(temp->i+1,temp->j,arr,visited, row, col)){
            visited[temp->i+1][temp->j]=1;
            if(temp->i + 1 == goal.i && temp->j == goal.j){
                *mincost=cost+1;
                return true;
            }
            else
                enqueue(temp->i +1, temp->j,&queue);
        }
        if(isSafe(temp->i-1,temp->j,arr,visited, row, col)){
            visited[temp->i-1][temp->j]=1;
            if(temp->i - 1 == goal.i && temp->j == goal.j){
                *mincost=cost+1;
                return true;
            }
            else
                enqueue(temp->i -1,temp->j,&queue);
        }
        if(isSafe(temp->i,temp->j +1,arr,visited, row, col)){
            visited[temp->i][temp->j +1]=1;
            if(temp->i == goal.i && temp->j +1 == goal.j){
                *mincost=cost+1;
                return true;
            }
            else
                enqueue(temp->i,temp->j + 1,&queue);
        }
        if(isSafe(temp->i,temp->j -1,arr,visited, row, col)){
            visited[temp->i][temp->j -1]=1;
            if(temp->i == goal.i && temp->j -1 == goal.j){
                *mincost=cost+1;
                return true;
            }
            else
                enqueue(temp->i,temp->j - 1,&queue);
        }
    }
    return false;
}

//to find the distance betweeen two nodes
int findDistance(struct node a, struct node b, char str[][100],int row, int col,int visited[][100]){
    int mincost=INT_MAX;
    if(!bfs(a, b, str,&mincost,0,visited,row,col))
        mincost=-1;
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            visited[i][j]=0;
    return mincost;
}

void findMinCost(graph G,int *visited,int n,int *minCost,int cost,int vertex){
	if(vertex == n-1 && !allvisited(visited,n)){
		visited[vertex] = 0;
		return;
	}
	if(allvisited(visited,n) && vertex == n-1){
		if(*minCost > cost)
			*minCost = cost;
		visited[vertex] = 0;
		return;
	}
	else if(allvisited(visited,n)){
		visited[vertex] =0;
		return;
	}

	for(int i = 0;i<n;i++){
		if(G.checkAdjacent(vertex,i) && visited[i] == 0){
			if(cost + G.findCost(vertex,i) > *minCost){
				visited[vertex] = 0;
				return;
			}
			cost = cost + G.findCost(vertex,i);
			visited[i] = 1;
			findMinCost(G,visited,n,minCost,cost,i);
			cost = cost - G.findCost(vertex,i);
		}
	}
	visited[vertex] = 0;
}


class Orienteering {
    public:
    void main();
};

void Orienteering::main() {
    int row,col,atTheRateCount=0;
    char str[100][100];
    cin>>col>>row;
    //scanning input into str 2D matrix
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            cin>>str[i][j];

    //node to store source, goal and checkpoints
    node atTheRate[20], source, goal;

    //loop to store the position of source, goal and checkpoints along with the number of checkpoints
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(str[i][j]=='S'){
                source.i = i;
                source.j = j;
            }
            else if(str[i][j]=='G'){
                goal.i = i;
                goal.j = j;
            }
            else if(str[i][j]=='@'){
                atTheRate[atTheRateCount].i=i;
                atTheRate[atTheRateCount].j=j;
                atTheRateCount++;
            }
        }
    }
    int visited[100][100];
    for(int i=0;i<atTheRateCount+2;i++)
        for(int j=0;j<atTheRateCount+2;j++)
            visited[i][j]=0;

    graph g(atTheRateCount+2);

    for(int i=0;i<atTheRateCount+2;i++){
        g.updateCost(i,i,0);
        for(int j=i+1;j<atTheRateCount+2;j++){
            if(!i){
                if(j==(atTheRateCount+1)){
                    g.updateCost(i,j,findDistance(source,goal,str,row,col,visited));
                    g.updateCost(j,i,g.findCost(i,j));
                }
                else{
                    g.updateCost(i,j,findDistance(source,atTheRate[j-1],str,row,col,visited));
                    g.updateCost(j,i,g.findCost(i,j));
                }
            }
            else if(i==atTheRateCount+1)
                break;
            else{
                if(j==(atTheRateCount+1)){
                    g.updateCost(i,j,findDistance(atTheRate[i-1],goal,str,row,col,visited));
                    g.updateCost(j,i,g.findCost(i,j));
                }
                else{
                    g.updateCost(i,j,findDistance(atTheRate[i-1],atTheRate[j-1],str,row,col,visited));
                    g.updateCost(j,i,g.findCost(i,j));
                }
            }
        }
    }
    int ans = INT_MAX;
    int visit[22];

    for(int i =0;i<22;i++)
        visit[i] = 0;

    visit[0] = 1;
    if(g.checkPath(atTheRateCount+2)){
        findMinCost(g,visit,atTheRateCount+2,&ans,0,0);
        cout<<ans<<endl;
    }
    else
        cout<<"-1"<<endl;
}


int main(int argc, char* argv[]) {
    Orienteering o;
    o.main();
    return 0;
}

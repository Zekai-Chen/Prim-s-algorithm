#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

const int maxn = 2001;        //According to Constraints, n<=2000 in all ten cases
const long INF = 2000000001;  //According to Constraints, M<=2×10^9 in all ten cases

//*********Some global variable needed************
int n;                        //The number of teams in this tournament
                              //We need to use it in the Prim function, so I set it as global variable
long Arr[maxn];               //Array to store the popularity of each team
long Distance[maxn];          //To store the distance from start point to other point
long g[maxn][maxn];           //Adjacency Matrix
bool If_Get_Longest[maxn];                //To judge whether it is in the longest path
//************************************************

//Largest spanning tree algorithm
long Prim(){
    memset(Distance,-INF,sizeof Distance); //Initialize the distance from start point to other point is minus infinity
                                           //We want the longest path
    memset(If_Get_Longest,false,sizeof If_Get_Longest);
                                           //Initialize the bool array as false
    long Answer = 0;
    
    for (int i=0;i<n;i++){  //We need to iterate n times to add n point into the path
        int temp = 0;       //temp to find the furthest point
        for (int j=1;j<=n;j++)
            if ((If_Get_Longest[j]==false) && ((Distance[j] > Distance[temp]) || (temp==0)))
                temp = j;

        If_Get_Longest[temp] = true;      //Update the furthest point in the If_Get_Longest 
        if (i>0) 
            Answer += Distance[temp];     //Update the longest length
        
        for (int k=1;k<=n;k++)            //Update the Distance array
            Distance[k] = max(g[temp][k],Distance[k]); //The longest path
    }
    return Answer;
}

int main(int argc,char *argv[]){
  long M; 
  long temp;

  scanf("%d%ld", &n, &M);  
  //The first line contains two integers n and M.
  for (int i=0;i<n;i++){
    scanf("%ld", &temp); 
    Arr[i]=temp;
  }
  //The second line contains n integers a1 , · · · , an .

  for (int i=1;i<(n+1);i++){
    for (int j=1;j<(n+1);j++){
        if (i == j){
            g[i][j] = g[j][i] = 0;
        }
        //Same team can not match, useless point and I set it as 0
        else{
            g[i][j] = g[j][i] = (Arr[i-1] * Arr[j-1]) % M;
        }
        //A match between i and j will gain ai × aj MOD M attractions.
    }
  }
  printf("%ld",Prim());
  return 0;
}
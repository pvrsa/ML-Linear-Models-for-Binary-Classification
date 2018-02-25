#include <bits/stdc++.h>

using namespace std;

void getInput(double X[][4] , int Y[] , int N);
void getPriors(double* pC1,double* pC0,int Y[],int N);

int main()
{
	int N=960;
	double X[N][4];
	int Y[N];

	getInput(X,Y,N);
	double pC1,pC0;

	getPriors(&pC1,&pC0,Y,N);

	cout << pC0 << " <- pC0   pC1 -> " << pC1 << endl; 
	return 0;
}



void getInput(double X[][4] , int Y[] , int N){

	ifstream file ( "train.txt" );
	int i = 0;
	string x;
	while ( i!=N )
	{
		for (int j = 0; j < 4; ++j)
		{
			getline ( file,x , ',' );
		    X[i][j] = stod(x); 
		}

	    getline ( file,x , '\n' ); 
	    Y[i] = stoi(x); 

	    i++;
	}

}

void getPriors(double* pC1,double* pC0,int Y[],int N){
	int x=0;
	int y=0;

	for (int i = 0; i < N; ++i)
	{
		if(Y[i])
			x++;
		else
			y++;
	}

	(*pC0) = (double)y / (double)N;
	(*pC1) = (double)x / (double)N;

}
#include <bits/stdc++.h>

using namespace std;

void getInput(double X[][4] , int Y[] , int N);

int main()
{
	int N=960;
	double X[N][4];
	int Y[N];

	getInput(X,Y,N);

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
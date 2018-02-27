#include <bits/stdc++.h>

using namespace std;

// For training data
const int N=960;
double X[N][4];
int Y[N];

// For testing data
const int Ntest=412;
double Xtest[Ntest][4];
int Ytest[Ntest];


// Main Functions
void getInput(double X[][4],int Y[],int N,string lala);

void LogReg();

int main()
{
	
	getInput(X,Y,N,"../train.txt");
	getInput(Xtest,Ytest,Ntest,"../test.txt");
	
	LogReg();

	return 0;
}



void getInput(double X[][4],int Y[],int N,string lala){

	ifstream file (lala);
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

void LogReg(){
	
}
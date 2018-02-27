#include <bits/stdc++.h>
#include "inverse.h"
#define pi 3.141592653

using namespace std;

const int N=960;
double X[N][4];
int Y[N];

void getInput(double X[][4],int Y[],int N,string lala);
void getPriors(double* pC1,double* pC0);
double PGM();
vector<double> calcMean(int y);
vector<vector<double> > calcVar(vector<double> mean,int y);
vector<vector<double> > addMatrix(vector<vector<double> > A,vector<vector<double> > B);

double findLikelihood(int y,vector<double> mean,double invCovar[4][4],double detCovar,int row);


const int Ntest=412;
double Xtest[Ntest][4];
int Ytest[Ntest];

int main()
{
	
	getInput(X,Y,N,"train.txt");
	getInput(Xtest,Ytest,Ntest,"test.txt");
	
	PGM();
	

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

double PGM(){
	
	double pC1,pC0;
	getPriors(&pC1,&pC0);

	vector<double> mean0 = calcMean(0);
	vector<double> mean1 = calcMean(1);

	vector<vector<double> > var0 = calcVar(mean0,0);
	vector<vector<double> > var1 = calcVar(mean1,1);
	vector<vector<double> > covar = addMatrix(var0,var1);
	double invCovar[D][D]; double covar2D[D][D];

 
	for(int i = 0;i<4;i++){
		for(int j=0;j<4;j++){
			covar2D[i][j] = covar[i][j];
		}
	}

	double detCovar = determinant(covar2D,4);


	inverse(covar2D,invCovar);
	

	

	double pXC0,pXC1,a,b,ans;
	int correst = 0;
	for(int i=0;i<Ntest;i++){

		

		pXC0 = findLikelihood(0,mean0,invCovar,detCovar,i);	
		pXC1 = findLikelihood(1,mean1,invCovar,detCovar,i);

		// cout << pXC0 << " " << pXC1 << endl;

		a = pXC0*pC0;
		b = pXC1*pC1;
		ans = a/(a+b);

		// cout << i << " " <<  ans << endl;

		if(ans <= 0.5 && Ytest[i]){
			correst++;
		}else if(ans > 0.5 && Ytest[i]==0){
			correst++;
		}

	}
	
	cout << "ACCURACY = " << (double)correst/(double)Ntest << endl;
	
	

}

void getPriors(double* pC1,double* pC0){
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

vector<double> calcMean(int y){

	double temp=0;
	vector<double> ans;

	for(int j=0;j<4;j++){
		temp = 0;

		for(int i=0;i<N;i++){
			if(Y[i] == y){
				temp = temp + X[i][j];
			}
		}

		ans.push_back(temp/(double)N);
	}

	return ans;
	
}

vector<vector<double> > calcVar(vector<double> mean,int y){
	vector<vector<double> > ans(4,vector<double> (4,0.0));
	double temp;
	vector<double> lala(4,0.0);

	for(int i=0;i<N;i++){
		if(Y[i] == y){
			for(int j = 0;j<4;j++){
				lala[j] = X[i][j] - mean[j];
			}

			for(int j = 0; j<4 ; j++){
				for(int k = 0; k<4; k++){
					ans[j][k] += lala[j]*lala[k];
				}
			}

		}
	}
	return ans;
}

double findLikelihood(int y,vector<double> mean,double invCovar[4][4],double detCovar,int row){
	vector<double> temp;
	double matrix[4] = {0,0,0,0};

	for(int i=0;i<4;i++){
		temp.push_back(Xtest[row][i] - mean[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matrix[i] += temp[j]*invCovar[j][i];
		}
	}

	double a = 0;
	for (int i = 0; i < 4; ++i)
	{
		a += matrix[i]*temp[i];
	}
	
	a /= 2;

	a = exp(a);
	double b = sqrt(detCovar);
	double c = 4*pi*pi;

	// cout << "a b c" << endl;
	// cout << a << " " << b << " " << c << endl;
	double ans = 1/(a*b*c);

	return ans;
}

vector<vector<double> > addMatrix(vector<vector<double> > A,vector<vector<double> > B){
	
	for(int i = 0;i<4;i++){
		for(int j=0;j<4;j++){
			A[i][j] += B[i][j];
			A[i][j] /= N;
		}
	}
return A;
}
#include <bits/stdc++.h>

#define pi 3.141592653

using namespace std;

const int N=960;
double X[N][4];
int Y[N];

void getInput(double X[][4],int Y[],int N,string lala);
void getPriors(double* pC1,double* pC0);
double PGM();
vector<double> calcMean(int y);
double calcVar(vector<double> mean,int y);
double findLikelihood(int y,vector<double> mean,double covar,int row);


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

	double var0 = calcVar(mean0,0)/(double)N;
	double var1 = calcVar(mean0,1)/(double)N;
	double covar = var0 + var1;

	double pXC0,pXC1,a,b,ans;
	int correst = 0;
	for(int i=0;i<Ntest;i++){

		cout << i << endl;

		pXC0 = findLikelihood(0,mean0,covar,i);	
		pXC1 = findLikelihood(1,mean1,covar,i);

		a = pXC0*pC0;
		b = pXC1*pC1;
		ans = a/(a+b);

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

double calcVar(vector<double> mean,int y){
	double ans=0;
	double temp;

	for(int i=0;i<N;i++){
		if(Y[i]==y){
			for(int j=0;j<4;j++){
				temp = X[i][j]-mean[j];
				temp*=temp;
				ans+=temp;
			}
		}
		
	}
	return ans;
}

double findLikelihood(int y,vector<double> mean,double covar,int row){
	double temp=0;
	for(int i=0;i<4;i++){

		temp+=(Xtest[row][i]-mean[i])*(Xtest[row][i]-mean[i]);
	}

	temp/=(2*covar);

	double a = 2*pi;
	a*=a;

	double b = sqrt(covar);

	double c = exp(temp);

	double ans = (1/(a*b*c));

	return ans;
}
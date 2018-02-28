#include <bits/stdc++.h>
#include <unistd.h>
#include <math.h>

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

//Helper Functions
vector<double> getGradient(double W[5]);
double y(double* X,double W[5]);
double sigmoid(double x);



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
	double alpha=0.00001;
	vector<double> gradient;
	double epsilon;
	int iterations = 15000;

	double W[5] = {1,1,1,1,1}; 
	do{
		gradient = getGradient(W);

		cout << "\n Iteration: " << iterations ;
	
		for(int i = 0;i<5;i++){
			// cout << gradient[i] << " " ;			
			W[i] -= alpha * gradient[i];

			// cout << W[i] << " " ;
		}

		cout << endl;

		// sleep(1);
	}while(iterations--);


	double ans;
	int tp = 0;  // True positives
	int tn = 0;	 // True negatives
	int fp = 0;  // False positives
	int fn = 0;  // False negatives

	for(int i=0;i<Ntest;i++){
	
		ans = y(Xtest[i],W);

		if(ans > 0.5)
			if(Ytest[i])
				tp++;
			else
				fp++;
		else
			if(Ytest[i] == 0)
				tn++;
			else
				fn++;
	}

	cout << "Confusion matrix \n" ;
	cout << "True positives " << tp << endl;
	cout << "True negatives " << tn << endl;
	cout << "False positives " << fp << endl;
	cout << "False negatives " << fn << endl;

}

vector<double> getGradient(double W[5]){

	vector<double> gradient(5,0.0);

	double temp;
	for(int i=0;i<N;i++){
		temp = y(X[i],W) - Y[i];
		gradient[0] += temp;

		for(int j =0;j<4;j++){
			gradient[j+1] += temp*X[i][j];
		}
	}

	return gradient;	
}

double y(double* X,double W[5]){
	double ans = W[0];

	for(int i =0;i<4;i++){
		ans += X[i]*W[i+1];
	}

	return sigmoid(ans);

}

double sigmoid(double x)
{
     double exp_value;
     double return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}

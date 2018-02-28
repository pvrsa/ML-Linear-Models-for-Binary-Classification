#include <bits/stdc++.h>
#include "inverse.h"

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
void FisherDA();

//Helper Functions
vector<double> calcMean(int y);

int main()
{
	
	getInput(X,Y,N,"../train.txt");
	getInput(Xtest,Ytest,Ntest,"../test.txt");
	
	FisherDA();

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

void FisherDA(){

    vector<double> mean0 = calcMean(0);
	vector<double> mean1 = calcMean(1);

    double Sw[4][4]; double invSw[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            Sw[i][j] = 0;
    
    vector<double> lala;

    // Make Sw matrix
    for(int i=0;i<N;i++){
        lala.clear();
        
        if(Y[i]==0){
            for(int j=0;j<4;j++){
                    lala.push_back(X[i][j] - mean0[j]);
            }
        }else{
            for(int j=0;j<4;j++){
                lala.push_back(X[i][j] - mean1[j]);
            }
        }

        for(int j=0;j<4;j++)
            for(int k=0;k<4;k++)
                Sw[j][k] += lala[k]*lala[j];

    }

    inverse(Sw,invSw);

    vector<double> difMeans;
    for(int i=0;i<4;i++)
        difMeans.push_back(mean0[i] - mean1[i]);

    double W[4] = {0};

    for(int i=0; i<4 ; i++){
        for(int j=0;j<4;j++){
            W[i]+=invSw[i][j]*difMeans[j];
        }
    }
    vector<pair<double,int> > R;
    double temp;

    for(int i=0;i<N;i++){
        temp=0;
        for(int j=0;j<4;j++){
            temp+=X[i][j]*W[j];
        }
        R.push_back(make_pair(temp,i));
    }

    sort(R.begin() , R.end());

   

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
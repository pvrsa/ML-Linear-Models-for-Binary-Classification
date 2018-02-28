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
double entrpy(int l0,int l1,int t0,int t1);

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

    int t0=0,t1=0;
    for(int i=0;i<N;i++){
        if(Y[i]==0)
            t0++;
    }
    t1=N-t0;

    int l0=0,l1=0;
    double minen = INT_MAX;
    double threshold = (R[0].first+R[1].first)/2;
    
    for(int i=0;i<N-1;i++){
        if(Y[R[i].second]==0)
            l0++;
        else
            l1++;
        double yi = (R[i].first+R[i+1].first)/2;
        double en = entrpy(l0,l1,t0,t1);
        if (en<minen){
            threshold=yi;
            minen = en;
        }
    }


    int tp = 0;  // True positives
	int tn = 0;	 // True negatives
	int fp = 0;  // False positives
	int fn = 0;  // False negatives

    for(int i=0;i<Ntest;i++){
        temp=0;
        for(int j=0;j<4;j++){
            temp+=Xtest[i][j]*W[j];
        }

        if(temp > threshold)
            if(Ytest[i])
                tp++;
            else
                fp++;
        else
            if(Ytest[i]==0)
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
double entrpy(int l0,int l1,int t0,int t1){
    double l = l0+l1;
    double r = N-l;
    double r0=t0-l0;
    double r1=t1-l1;

    double x = (l0/l)*(log(l0/l)) + (l1/l)*(log(l1/l));
    double y = (r0/r)*(log(r0/r)) + (r1/r)*(log(r1/r));
    
    x*=(l/l+r);
    y*=(r/l+r);
    
    double en=x+y;
    en=(-en);
    return en;
}
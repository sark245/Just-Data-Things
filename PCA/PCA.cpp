//Created by Kira

#include<bits/stdc++.h>
using namespace std;

#define IOS cin.sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pii pair<int,int> 
#define pb push_back
#define vi vector<int> 
using ll = long long;

const int mod = 1e9 + 7;
const double EPS = 1e-6;

vector<vector<double>> A;   //(n,2)-->shape


vector<double> add_vec(vector<double> v1, vector<double> v2){
    int sz1 = v1.size(), sz2 = v2.size();
    assert(sz1==sz2);
    vector<double>ret(sz1);
    for(int i = 0; i < sz1; i++){
        ret[i] = v1[i] + v2[i];
    }
    return ret;
}

vector<double> sub_vec(vector<double> v1, vector<double> v2){
    int sz1 = v1.size(), sz2 = v2.size();
    assert(sz1==sz2);
    vector<double>ret(sz1);
    for(int i = 0; i < sz1; i++){
        ret[i] = v1[i] - v2[i];
    }
    return ret;
}


vector<double> find_mean(int m, int n, const vector<vector<double>>& A){
    
    vector<double>mu(m, 0.0);
   for(int i = 0; i < n; i++){
       mu = add_vec(mu, A[i]);
   }

   for(int i = 0; i < m; i++)mu[i]/=n;
    
    return mu;
}

vector<vector<double>> gen_B(int m, int n, const vector<vector<double>>& A, vector<double>& mu){
    vector<vector<double>> B;
    for(int i = 0; i < n; i++){
        B.pb(sub_vec(A[i],mu));
    }
    return B;
}

vector<vector<double>> transpose(int m, int n, vector<vector<double>> B){
    vector<vector<double>> B_t(m,vector<double>(n,0.0));

    for(int i = 0; i < m; i++){
        for(int j = 0; j <n; j++){
            B_t[i][j] = B[j][i];
        }
    }
    return B_t;
}

vector<vector<double>> gen_S(int m, int n, vector<vector<double>> B, vector<vector<double>>& B_t){

    vector<vector<double>>S(m,vector<double>(m));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < n; k++){
                S[i][j] += B_t[i][k]*B[k][j];
            }
            S[i][j]/=(n-1);
        }
    }

    return S; 
}


bool check_ok(vector<vector<double>> & S){
    double a = S[0][0], b = S[0][1], c = S[1][0], d = S[1][1];

    return ((a+d)*(a+d) - 4 *(a*d-b*c)) > EPS;
}

vector<double> PCA(vector<vector<double>> &S){
    assert(check_ok(S));
    double a = S[0][0], b = S[0][1], c = S[1][0], d = S[1][1];

    double sq = (a+d)*(a+d);
    double lambda1 = ((a+d) + sqrt(sq - 4 * (a*d-b*c)))/2.0;
    double lambda2 = ((a+d) - sqrt(sq - 4 * (a*d-b*c)))/2.0;

    cout<<"The Eigen Values are as follows : lambda1 = "<<lambda1<<" , "<<"lambda2 = "<<lambda2<<"\n";

    double x = 1.0;
    double y = -(a-lambda1)/b;

    double perc = (lambda1*100)/(lambda1 + lambda2);

    cout<<"Lambda 1 explains about "<<perc <<" of the total variation\n\n";

    
    double k = (1.0/sqrt(1 + y*y));
    x *= k, y *= k;

    vector<double> reduced(2);
    reduced[0] = x, reduced[1] = y;
    return reduced;
    
}



int m, n; //m = Dimensions, n = number of samples


vector<double> tranform_data(vector<double> &c){
    
    vector<double> D(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            D[i] += A[i][j] * c[j];
        }
    }
    return D;
}



int main(){
   
   cout<<"PCA for 2 Dimensional Data\n"<<endl;

   cout<<"Enter number of Samples = "; cin>>n;
   m = 2;

    cout<<endl<<"Enter Data : \n";

    for(int i = 0; i < n; i++){
        cout<<"Enter vector "<<i+1<<" : ";
        vector<double>tmp;
        for(int j = 0; j < m; j++){
            double val; cin>>val;
            tmp.pb(val);            
        }
        A.pb(tmp);
    }

    cout<<fixed<<setprecision(6);

    cout<<"\n\nInitial data set is "<<endl;

     for(int i = 0; i < n; i++){
        cout<<"[\t";
        for(int j = 0; j < m-1; j++){
            cout<<A[i][j]<<"\t,\t"; 
        }
        cout<<A[i][m-1]<<"\t]\n";
    }



    vector<double> mu = find_mean(m, n, A);

    cout<<"\nMean = "<<endl;
    cout<<"[\t";
    for(int i = 0; i < m-1; i++)cout<<mu[i]<<"\t,\t"; 
    cout<<mu[m-1]<<"\t]\n";

    vector<vector<double>> B = gen_B(m, n, A, mu);

    cout<<"\nSubtracting mean from the data : "<<endl;
     for(int i = 0; i < n; i++){
        cout<<"[\t";
        for(int j = 0; j < m-1; j++){
            cout<<B[i][j]<<"\t,\t"; 
        }
        cout<<B[i][m-1]<<"\t]\n";
    }

    vector<vector<double>> B_t = transpose(m,n,B);

    vector<vector<double>> S = gen_S(m, n, B, B_t);

    cout<<"\nCovariance Matrix : "<<endl;

    for(int i = 0; i < m; i++){
        cout<<"[\t";
        for(int j = 0; j < m-1; j++){
            cout<<S[i][j]<<"\t,\t"; 
        }
        cout<<S[i][m-1]<<"\t]\n";
    }

    cout<<endl;


   vector<double> res = PCA(S);


    cout<<"Dominant Principle component is : [\t";
   cout<<res[0]<<" , "<<res[1]<<"\t]\n";

   cout<<"\nTransformed Dataset : "<<endl;

    vector<double> D = tranform_data(res);

    for(int i = 0; i < n; i++){
        cout<<"[\t"<<D[i]<<"\t]\n";
    }
}

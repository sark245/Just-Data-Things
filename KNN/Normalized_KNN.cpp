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
using ld = long double;
const int mod = 1e9 + 7;


ll pwr(ll a, ll b);

struct Point{
	int val; 
	ld x, y;
	ld distance;
	Point(){}
	Point(ld x, ld y) : x(x), y(y){}
};

bool comp(Point &p1, Point& p2){
	return p1.distance < p2.distance;
}

ld calculate_distance(Point p1, Point p2){
	ld dist = sqrt((p1.x - p2.x)* (p1.x-p2.x) + (p1.y - p2.y)* (p1.y - p2.y));
	return dist;
}

void Normalize(vector<Point> & X, int n){

    ld x_mean = 0.0, y_mean = 0.0, x_sd = 0.0, y_sd = 0.0;

    for(int i = 0; i < n; i++){
        x_mean += X[i].x, y_mean += X[i].y;
    }

    x_mean /= n, y_mean /= n;

    for(int i = 0; i < n; i++){
        x_sd += (X[i].x - x_mean) * (X[i].x - x_mean);
        y_sd += (X[i].y - y_mean) * (X[i].y - y_mean);
    }

    x_sd /= n, y_sd/= n;
    x_sd = sqrt(x_sd), y_sd = sqrt(y_sd);

    for(int i = 0; i < n; i++){
        X[i].x = (X[i].x - x_mean)/x_sd;
        X[i].y = (X[i].y - y_mean)/y_sd;
    }

}

int WeightedKNN(vector<Point> X, int n, int k, Point p){
	for(int i = 0; i < n; i++){
		X[i].distance = calculate_distance(X[i], p);
	}

	sort(all(X), comp);

	ld freq_1 = 0;
	ld freq_2 = 0;

	for(int i = 0; i < k; i++){
		if(X[i].val == 0)
			freq_1 += (ld)(1/X[i].distance);
		else 
			freq_2 += (ld)(1/X[i].distance);
	}

	return freq_1 < freq_2;
}





int main(){
  
	int n; 
    cout<<fixed<<setprecision(4);
	cout<<"\tNormalized and Weighted KNN"<<endl<<endl;
	cout<<"Enter Number of Data Points : ";
	cin>>n;

	vector<Point> X(n);
	cout<<"\n\n Start entering Data Points: "<<endl;

	for(auto &i : X){
		cin>>i.x>>i.y>>i.val;
	}

	cout<<"DataSet is: "<<endl;

	for(auto i : X){
		cout<<"[\t"<<i.x<<"\t,\t"<<i.y<<"\t,\t"<<i.val<<"\t]"<<endl;
	}

	cout<<"\n\n Enter the testing point : ";
	Point p; 
	cin>>p.x>>p.y;

	int k; 
	cout<<"\nEnter the value of K: ";
	cin>>k;

    Normalize(X, n);

    cout<<"Normalising the dataset...\n Normalised Dataset:"<<endl;

  

    for(auto i : X){
		cout<<"[\t"<<i.x<<"\t,\t"<<i.y<<"\t,\t"<<i.val<<"\t]"<<endl;
	}

	cout<<"Class of this Point is: "<<WeightedKNN(X, n, k, p)<<endl;


}

ll pwr(ll a, ll b){
   a %= mod;	//Remove mod if not required
   ll res = 1;
   while(b > 0){
	if(b&1)
		res = res * a % mod;
		a = a * a % mod;
	b >>= 1;
	}

	return res;
}


#include "functions.h"

//class point:functions
void point::setID(int p_id){
	id = p_id;
}

int point::getID(){
	return id;
}

void point::setCoordinates(vector<long double> p){
	coordinates.assign(p.begin(),p.end());
}

vector<long double> point::getCoordinates(){
	return coordinates;
}

//Read CSV and Store it in a vector of points

vector<point> read_n_store(string filename){
	ifstream myfile;
	string line;
	string::size_type sz; 
	vector<long double> p;
	vector<point> v;
	myfile.open(filename);
	while(getline(myfile,line,'\n')){
		stringstream ss ( line );
		point mypoint;
		getline(ss,line,',');
		mypoint.setID(atoi(line.c_str()));
		while(getline(ss,line,',')){
			p.push_back(stold(line,&sz));
		}
		mypoint.setCoordinates(p);
		p.clear();
		v.push_back(mypoint);
	}
	myfile.close();
	return v;
}

//Distances
long double euclidean(vector<long double> x,vector<long double> y){
	long double j=0.0,euclidean_distance=0.0,sum=0.0;
	for(int i=0; i<x.size(); i++){
		j = x[i] - y[i];
		sum += pow(j,2);
	}
	euclidean_distance = sqrt(sum);
	return euclidean_distance;
}

long double cosine(vector<long double> x,vector<long double> y){
	long double multiply=0.0,metro_x=0.0,metro_y=0.0,cosine=0.0;
	for(int i=0; i<x.size(); i++){
		multiply += x[i]*y[i];
		metro_x += pow(x[i],2);
		metro_y += pow(y[i],2);
	}

	metro_x = sqrt(metro_x);
	metro_y = sqrt(metro_y);
	cosine = 1 - (multiply/(metro_x*metro_y));
	return cosine ; 
}


//Initialization with random centroids

vector<point> random_init(int k_cluster,vector<point> v){
	vector<point> centroids;
	int temp=0;
	random_device rd; 
    mt19937 eng(rd()); 
    uniform_int_distribution<> distr(1,v.size());
	 for(int n=0; n<k_cluster; ++n){
	 	temp = 0;
	 	temp = distr(eng);
        for(int i=0; i<v.size(); i++){
  			if(v[i].getID() == temp){
  			  centroids.push_back(v[i]);
  			}
  		}
    }

    return centroids;
}


//Initialization with K-means

vector<point> kmeans_init(int k_cluster,vector<point> v){
	vector<point> centroids;
	vector<long double> D;
	int temp=0;
	random_device rd; 
    mt19937 eng(rd()); 
    uniform_int_distribution<> distr(1,v.size());
    temp = distr(eng);
    for(int i=0; i<v.size(); i++){
  		if(v[i].getID() == temp){
  			centroids.push_back(v[i]);
  		}
  	}

  	for (int i = 0; i < v.size(); ++i)
  	{   
  		cout << "MY ID: " << v[i].getID() << " and my euclidean_distance is: " ;
  		cout <<	cosine(v[i].getCoordinates(),centroids[0].getCoordinates()) << endl ;

  	}

  	cout << "centroids id: " << centroids[0].getID() << endl;

  	return centroids;

} 
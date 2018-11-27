#include "functions.h"

//class point:functions
void point::setID(int p_id){
	id = p_id;
}

int point::getID(){
	return id;
}

void point::setFlag(int F){
	flag = F;
}

int point::getFlag(){
	return flag;
}

void point::setassigned(int a){
	assigned = a;
}

int point::getassigned(){
	return assigned;
}

void point::setbelong(int b){
	belong = b;
}

int point::getbelong(){
	return belong;
}

void point::setCoordinates(vector<long double> p){
	coordinates.assign(p.begin(),p.end());
}

vector<long double> point::getCoordinates(){
	return coordinates;
}

//class cluster:functions
void cluster::setCentroid(point mypoint){
	centroid = mypoint;
}

point cluster::getCentroid(){
	return centroid;
}

void cluster::setCluster_points(vector<point> cp){
	cluster_points.assign(cp.begin(),cp.end());
}

vector<point> cluster::getCluster_points(){
	return cluster_points;
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
		mypoint.setFlag(0);
		mypoint.setassigned(0);
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
  				v[i].setFlag(1);
  				centroids.push_back(v[i]);
  			}
  		}
    }

    return centroids;
}


//Initialization with K-means

vector<point> kmeans_init(int k_cluster,vector<point> v,int metric_function){
	vector<point> centroids;
	vector<long double> min;
	vector<long double> D;
	long double distance = 0.0,pos = 0.0,sum = 0.0;
	int temp=0,counter=0;
	random_device rd;
 	mt19937 eng(rd());
  	uniform_int_distribution<> distr(1,v.size());
  	temp = distr(eng);
  	v[temp].setFlag(1);
  	centroids.push_back(v[temp]);
	srand((unsigned)time(NULL));
	for(int k=1; k<k_cluster; k++){
		for(int j=0; j<v.size(); j++){
			if (v[j].getFlag() != 1){
				for(int i=0; i<centroids.size(); i++){
					if(metric_function == 0){
						distance = pow(euclidean(centroids[i].getCoordinates(),v[j].getCoordinates()),2);
						min.push_back(distance);
					}else{
						distance = pow(cosine(centroids[i].getCoordinates(),v[j].getCoordinates()),2);
						min.push_back(distance);
					}
				}
				sort(min.begin(),min.end());
				sum += min[0];
				D.push_back(sum);
				min.clear();
			}
		}
		for(int i=0; i<D.size(); i++){
				D.at(i) = D[i]/D.back();
		}
		pos = ((double)rand()/(double) (RAND_MAX+1.0));
		for(int i=0; i<D.size(); i++){
			if(pos<D[i]){
				v[i].setFlag(1);
				centroids.push_back(v[i]);
				break;
			}
		}
		sum = 0.0;
		D.clear();
	}

  return centroids;

}


//Lloyd's assignement
vector<cluster> make_clusters(vector<point> centroids){
	vector<cluster> c;
	for(int i=0; i<centroids.size(); i++){
		cluster mycluster;
		mycluster.setCentroid(centroids[i]);
		c.push_back(mycluster);
	}
	return c;
}

void Lloyds(vector<point> v,vector<cluster> c,int metric_function){
	int id=0,x,counter=0;
	long double distance = 0.0 , min = 0.0;
	vector<long double> min_distance;
	vector<point> assignement;
	for(int i=0; i<v.size(); i++){
		if(v[i].getFlag() != 1){
			for(int j=0; j<c.size(); j++){
				if(metric_function == 0){
					distance = euclidean(v[i].getCoordinates(),c[j].getCentroid().getCoordinates());
					min_distance.push_back(distance);
				}else{
					distance = cosine(v[i].getCoordinates(),c[j].getCentroid().getCoordinates());
					min_distance.push_back(distance);
				}
			}
			min = min_distance[0];
			for(x=0; x<min_distance.size(); x++){
				if(min_distance[x] <= min){
					min = min_distance[x];
					id = x;
				}
			}
			v[i].setassigned(1);
			v[i].setbelong(id);
			min_distance.clear();
		}
	}

	for(int i=0; i<c.size(); i++){
		for(int j=0; j<v.size(); j++){
			if(v[j].getbelong() == i){
				assignement.push_back(v[j]);
			}
		}
		c[i].setCluster_points(assignement);
		assignement.clear();
	}

}


//Lloyd's update

void cluster_mean(vector<cluster> c){
	int counter=0;
	for(int i=0; i<c.size(); i++){
		for(int j=0; j<c[i].getCluster_points().size(); j++){
			for(int z=0; z<c[i].getCluster_points().getCoordinates().size(); z++){
				counter++;
			}
		}break;
	}
cout << counter ;

}
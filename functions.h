#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <random>
using namespace std;

class point{
	private:
		int id,flag,assigned,belong;
		vector<long double> coordinates;
	public:
		void setID(int p_id);
		int getID();
		void setFlag(int F);
		int getFlag();
		void setassigned(int a);
		int getassigned();
		void setbelong(int b);
		int getbelong();
		void setCoordinates(vector<long double> p);
		vector<long double> getCoordinates();
};

class cluster{
	private:
		point centroid;
		vector<point> cluster_points;
	public:
		void setCentroid(point mypoint);
		point getCentroid();
		void setCluster_points(vector<point> cp);
		vector<point> getCluster_points();

};

void setID(int p_id);

int getID();

void setFlag(int F);

int getFlag();

void setassigned(int a);

int getassigned();

void setbelong(int b);

int getbelong();

void setCoordinates(vector<long double> p);

vector<long double> getCoordinates();

void setCentroid(point mypoint);

point getCentroid();

void setCluster_points(vector<point> cp);

vector<point> getCluster_points();

vector<point> read_n_store(string filename);

long double euclidean(vector<long double> x,vector<long double> y);

long double cosine(vector<long double> x,vector<long double> y);

vector<point> random_init(int k_cluster,vector<point> v);

vector<point> kmeans_init(int k_cluster,vector<point> v,int metric_function);

vector<cluster> make_clusters(vector<point> centroids);

void Lloyds(vector<point> v,vector<cluster> c,int metric_function);

void cluster_mean(vector<cluster> c);
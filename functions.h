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
		int id,flag;
		vector<long double> coordinates;
	public:
		void setID(int p_id);
		int getID();
		void setFlag(int F);
		int getFlag();
		void setCoordinates(vector<long double> p);
		vector<long double> getCoordinates();
};

void setID(int p_id);

int getID();

void setFlag(int F);

int getFlag();

void setCoordinates(vector<long double> p);

vector<long double> getCoordinates();

vector<point> read_n_store(string filename);

long double euclidean(vector<long double> x,vector<long double> y);

long double cosine(vector<long double> x,vector<long double> y);

vector<point> random_init(int k_cluster,vector<point> v);

vector<point> kmeans_init(int k_cluster,vector<point> v,int metric_function);
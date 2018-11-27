#include "functions.h"

int main(){
	vector<point> v;
	vector<point> s;
	vector<cluster> k;
	v = read_n_store("twitter_dataset_small.csv");
	s = random_init(200,v); 
	k = make_clusters(s);
	Lloyds(v,k,1);
	cluster_mean(k);
	return 0;
}
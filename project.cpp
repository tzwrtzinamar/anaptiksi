#include "functions.h"

int main(){
vector<point> v;
vector<point> s;
v = read_n_store("twitter_dataset_small.csv");
s = kmeans_init(2,v,1);  
	return 0;
}
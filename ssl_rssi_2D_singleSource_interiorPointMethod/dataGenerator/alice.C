#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using namespace std;

int NumberAnchors_ = 20;
int NumberNodes_ = 1;

double minX = -100;
double maxX = 100;

double minY = -100;
double maxY = 100;

vector<double> As_x;
vector<double> As_y;
vector<double> Ns_x;
vector<double> Ns_y;

int main()
{
	cout<<"Hello "<<endl;

	default_random_engine e(time(nullptr));

	// anchors
	uniform_real_distribution<double> anchor_x(minX, maxX);
	uniform_real_distribution<double> anchor_y(minY, maxY);
	for(int i=0;i<NumberAnchors_;i++)
	{
		double a_x = anchor_x(e);
		double a_y = anchor_y(e);
		cout<<"Anchors ID "<<i<<", x "<<a_x<<", y "<<a_y<<endl;
		As_x.push_back(a_x);
		As_y.push_back(a_y);
	}

	// nodes
	uniform_real_distribution<double> nodes_x(minX, maxX);
	uniform_real_distribution<double> nodes_y(minY, maxY);
	for(int i=0;i<NumberNodes_;i++)
	{
		double x_x = nodes_x(e);
		double x_y = nodes_y(e);
		cout<<"Nodes ID "<<i<<", x "<<x_x<<", y "<<x_y<<endl;
		Ns_x.push_back(x_x);
		Ns_y.push_back(x_y);
	}

	// observations
	ofstream write("observations.txt");
	for(int i=0;i<NumberAnchors_;i++)
	for(int j=0;j<NumberNodes_;j++)
	{
		int AnchorID = i;
		int NodeID = j;

		double distanceSquared = 0;
		double ax = As_x[AnchorID];
		double ay = As_y[AnchorID];
		double xx = Ns_x[NodeID];
		double xy = Ns_y[NodeID];
		cout<<"Distance : Anchor ID "<<AnchorID<<", loc "<<ax<<", "<<ay<<"; Node ID "<<NodeID<<", loc "<<xx<<", "<<xy<<endl;
		distanceSquared = (ax-xx)*(ax-xx) + (ay-xy)*(ay-xy);
		cout<<"distanceSquared "<<distanceSquared<<endl;

		write<<AnchorID<<" "<<ax<<" "<<ay<<" "<<NodeID<<" "<<xx<<" "<<xy<<" "<<distanceSquared<<endl;
	}

	write.close();


	return 1;
}

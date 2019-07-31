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

double minZ = -100;
double maxZ = 100;

vector<double> As_x;
vector<double> As_y;
vector<double> As_z;
vector<double> Ns_x;
vector<double> Ns_y;
vector<double> Ns_z;

int main()
{
	cout<<"Hello "<<endl;

	default_random_engine e(time(nullptr));

	// anchors
	uniform_real_distribution<double> anchor_x(minX, maxX);
	uniform_real_distribution<double> anchor_y(minY, maxY);
	uniform_real_distribution<double> anchor_z(minZ, maxZ);
	for(int i=0;i<NumberAnchors_;i++)
	{
		double a_x = anchor_x(e);
		double a_y = anchor_y(e);
		double a_z = anchor_z(e);
		cout<<"Anchors ID "<<i<<", x "<<a_x<<", y "<<a_y<<", z "<<a_z<<endl;
		As_x.push_back(a_x);
		As_y.push_back(a_y);
		As_z.push_back(a_z);
	}

	// nodes
	uniform_real_distribution<double> nodes_x(minX, maxX);
	uniform_real_distribution<double> nodes_y(minY, maxY);
	uniform_real_distribution<double> nodes_z(minZ, maxZ);
	for(int i=0;i<NumberNodes_;i++)
	{
		double x_x = nodes_x(e);
		double x_y = nodes_y(e);
		double x_z = nodes_z(e);
		cout<<"Nodes ID "<<i<<", x "<<x_x<<", y "<<x_y<<", z "<<x_z<<endl;
		Ns_x.push_back(x_x);
		Ns_y.push_back(x_y);
		Ns_z.push_back(x_z);
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
		double az = As_z[AnchorID];
		double xx = Ns_x[NodeID];
		double xy = Ns_y[NodeID];
		double xz = Ns_z[NodeID];
		cout<<"Distance : Anchor ID "<<AnchorID<<", loc "<<ax<<", "<<ay<<", "<<az<<"; Node ID "<<NodeID<<", loc "<<xx<<", "<<xy<<", "<<xz<<endl;
		distanceSquared = (ax-xx)*(ax-xx) + (ay-xy)*(ay-xy) + (az-xz)*(az-xz);
		cout<<"distanceSquared "<<distanceSquared<<endl;

		write<<AnchorID<<" "<<ax<<" "<<ay<<" "<<az<<" "<<NodeID<<" "<<xx<<" "<<xy<<" "<<xz<<" "<<distanceSquared<<endl;
	}

	write.close();


	return 1;
}

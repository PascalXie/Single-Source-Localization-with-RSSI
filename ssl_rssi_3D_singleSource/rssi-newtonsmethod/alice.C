#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "UserCostFunction.hh"
#include "SteepestCostFunction.hh"
#include "NewtonsCostFunction.hh"

#include "UserResidualBlockFunction.hh"
#include "PolyResidualBlockFunction.hh"

#include "UserOptimizationManager.hh"
#include "SteepestOptimizationManager.hh"
#include "NewtonsOptimizationManager.hh"


using namespace std;

int RSSI();
void test3();
void test4();
double observation1(double ob1);
double observation2(double ob1);

int main()
{
	cout<<"Hello "<<endl;

	// steepest descent method
	//test3();

	// Newton's method
	//test4();

	// RSSI
	int isRSSIGood = RSSI();

	return 1;
}

int RSSI()
{
	string filename = "../observations.txt";
	ifstream file(filename.c_str());

	if(file.fail())
	{
		cout<<"Can not find the file \" "<<filename<<" \""<<endl;
		return 0;
	}

	int AnchorID = 0;
	int NodeID = 0;
	double distanceSquared = 0;
	double ax = 0; 
	double ay = 0; 
	double az = 0; 
	double xx = 0;
	double xy = 0;
	double xz = 0;

	vector<int> AnchorIDs;
	vector<int> NodeIDs;
	vector<double> distancesSquared;
	vector<double> axs, ays, azs, xxs, xys, xzs;

	while(!file.eof())
	{
		file>>AnchorID>>ax>>ay>>az>>NodeID>>xx>>xy>>xz>>distanceSquared;

		if(file.eof()) break;

		cout<<"Distance squared "<<distanceSquared<<": Anchor ID "<<AnchorID<<", loc "<<ax<<", "<<ay<<", "<<az<<"; Node ID "<<NodeID<<", loc "<<xx<<", "<<xy<<", "<<xz<<endl;

		AnchorIDs.push_back(AnchorID);
		NodeIDs.push_back(NodeID);
		distancesSquared.push_back(distanceSquared);
		axs.push_back(ax);
		ays.push_back(ay);
		azs.push_back(az);
		xxs.push_back(xx);
		xys.push_back(xy);
		xzs.push_back(xz);
	}

	file.close();

	//
	// Optimization 
	//
	int observationsSize = 4;
	int residualSize = 1;
	int varialbeSize = 3;

	UserOptimizationManager * manager = new NewtonsOptimizationManager("NewtonsMethod",observationsSize,varialbeSize,residualSize);

	// set variables
	vector<double> variables;
	variables.push_back(-100.);
	variables.push_back(-100.);
	variables.push_back(100.);
	manager->SetUserInitialization(variables);

	// set cost function
	UserCostFunction* costFunction = new NewtonsCostFunction("costFunction",observationsSize,varialbeSize,residualSize);

	// get observations
	for(int i=0;i<AnchorIDs.size();i++)
	{
		vector<double> observation_current;
		observation_current.push_back(distancesSquared[i]);
		observation_current.push_back(axs[i]);
		observation_current.push_back(ays[i]);
		observation_current.push_back(azs[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	//
	cout<<" "<<endl;
	cout<<"alice SetUserInitialization"<<endl;
	manager->SetUserInitialization(costFunction);

	//
	double UserReferencedLength = 70.;
	manager->SetUserReferencedLength(UserReferencedLength);

	//
	double UserEpsilon = 10.;
	manager->SetUserEpsilonForTerminating(UserEpsilon);

	// initialize
	cout<<" "<<endl;
	cout<<"Initialize "<<endl;
	manager->Initialize();

	return 1;
}

void test3()
{
	int observationsSize = 2;
	int residualSize = 1;
	int varialbeSize = 4;
	UserOptimizationManager * sd = new SteepestOptimizationManager("SteepestDecentMethod",observationsSize,varialbeSize,residualSize);

	// set variables
	vector<double> variables;
	variables.push_back(1.+101);
	variables.push_back(2.+101);
	variables.push_back(3.-101);
	variables.push_back(4.-101);
	sd->SetUserInitialization(variables);

	// set cost function
	UserCostFunction* costFunction = new SteepestCostFunction("costFunction",observationsSize,varialbeSize,residualSize);

	// get observations
	int LengthObservations = 5;
	double observation_xs[5];
	double observation_ys[5];
	for(int i=0;i<LengthObservations;i++)
	{
		double x = double(i)-2;
		double y = observation2(x);
		observation_xs[i] = x;
		observation_ys[i] = y;
		cout<<"Observation ID "<<i<<", x "<<observation_xs[i]<<", y "<<observation_ys[i]<<endl;
	}

	for(int i=0;i<LengthObservations;i++)
	{
		vector<double> observation_current;
		observation_current.push_back(observation_xs[i]);
		observation_current.push_back(observation_ys[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	//
	cout<<" "<<endl;
	cout<<"alice SetUserInitialization"<<endl;
	sd->SetUserInitialization(costFunction);


	// initialize
	cout<<" "<<endl;
	cout<<"Initialize "<<endl;
	sd->Initialize();
}

void test4()
{
	int observationsSize = 2;
	int residualSize = 1;
	int varialbeSize = 4;
	UserOptimizationManager * manager = new NewtonsOptimizationManager("NewtonsMethod",observationsSize,varialbeSize,residualSize);

	// set variables
	vector<double> variables;
	variables.push_back(1.+101.);
	variables.push_back(2.+101.);
	variables.push_back(3.-101.);
	variables.push_back(4.-101.);
	manager->SetUserInitialization(variables);

	// set cost function
	UserCostFunction* costFunction = new NewtonsCostFunction("costFunction",observationsSize,varialbeSize,residualSize);

	// get observations
	int LengthObservations = 5;
	double observation_xs[5];
	double observation_ys[5];
	for(int i=0;i<LengthObservations;i++)
	{
		double x = double(i)-2;
		double y = observation2(x);
		observation_xs[i] = x;
		observation_ys[i] = y;
		cout<<"Observation ID "<<i<<", x "<<observation_xs[i]<<", y "<<observation_ys[i]<<endl;
	}

	for(int i=0;i<LengthObservations;i++)
	{
		vector<double> observation_current;
		observation_current.push_back(observation_xs[i]);
		observation_current.push_back(observation_ys[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	//
	cout<<" "<<endl;
	cout<<"alice SetUserInitialization"<<endl;
	manager->SetUserInitialization(costFunction);


	// initialize
	cout<<" "<<endl;
	cout<<"Initialize "<<endl;
	manager->Initialize();
}

double observation1(double ob1)
{
	double as[3] = {1,2,3};
	double x = ob1;
	double y = (as[0] + as[1]*x + as[2]*x*x);

	return y;
}

double observation2(double ob1)
{
	double as[4] = {1,2,3,4};
	double x = ob1;
	double y = (as[0] + as[1]*x + as[2]*x*x + as[3]*x*x*x);

	return y;
}

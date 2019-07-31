#include "PolyResidualBlockFunction.hh"

//-------------------------
// Constructor
//-------------------------
PolyResidualBlockFunction::PolyResidualBlockFunction(string name, vector<double> observations, int SizeObservations, int SizeVariables, int SizeResiduals)
:	UserResidualBlockFunction(name+"_User"),
	name_(name),
	SizeObservations_(SizeObservations),
	SizeVariables_(SizeVariables), SizeResiduals_(SizeResiduals)
{
	observations_.clear();
	observations_ = observations;
}

//-------------------------
// Destructor
//-------------------------
PolyResidualBlockFunction::~PolyResidualBlockFunction()
{}

//-------------------------
// Public
//-------------------------
bool PolyResidualBlockFunction::ResidualFunction(vector<double> variables, vector<double> &residuals)
{
	//
	// step 0
	//
	if(variables.size()!=SizeVariables_) return false;

	// observations_[0] : distanceSquared 
	// observations_[1] : ax , anchor location x
	// observations_[2] : ay , anchor location y
	// observations_[3] : az , anchor location z

	// varialbles[0] : xx, node location x
	// varialbles[1] : xy, node location y
	// varialbles[2] : xz, node location z

	// residual = (ax-xx)*(ax-xx) + (ay-xy)*(ay-xy) + (az-xz)*(az-xz) - distanceSquared

	double distanceSquared = observations_[0];
	double ax = observations_[1];
	double ay = observations_[2];
	double az = observations_[3];

	double xx = variables[0];
	double xy = variables[1];
	double xz = variables[2];

	double residual_0 = (ax-xx)*(ax-xx) + (ay-xy)*(ay-xy) + (az-xz)*(az-xz) - distanceSquared;

	residuals.clear();
	residuals.push_back(residual_0);

	/*
	// debug
	cout<<"Debug class PolyResidualBlockFunction::ResidualFunction"<<endl;
	cout<<"Debug Residual : Observation "<<distanceSquared<<" "<<ax<<" "<<ay<<endl;
	cout<<"Debug Residual : varialbles "<<xx<<" "<<xy<<", residual "<<residual_0<<endl;
	*/

	return true;
}

int PolyResidualBlockFunction::GetObervationsSize()
{
	return SizeObservations_;
}

void PolyResidualBlockFunction::ShowResidualFunction()
{
	// debug
	cout<<"debug Class PolyResidualBlockFunction : "<<name_<<endl;
	cout<<"Observations : "<<endl;
	for(int i=0; i<observations_.size(); i++)
	{
		cout<<"    ID "<<i<<"; Observation "<<observations_[i]<<endl;
	}
}

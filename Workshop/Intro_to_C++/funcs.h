#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

void buffer(const double& input, 
            double& output){ 
    // Computes a polynomial from a given input, modifies the output accordingly
    output = pow(input, 3) - 3*pow(input, 2) + 9.2 * pow(input,1) + 4.3;
}

void simulation(const vector<double>& input, 
                vector<double>& output) 
 {
    // Simulation loops over inputs and modifies the output vector
	double temp_val;
	for (auto i: input){
		buffer(i, temp_val);
		output.push_back(temp_val);
	}
 }


void rnum(double& input){
    // Replaces input variable with a random number
    const double range_from  = -1000;
    const double range_to    = 1000;
    random_device                  rand_dev;
    mt19937                        gen(rand_dev());
    uniform_real_distribution<double>  distr(range_from, range_to);
    input = distr(gen);
}

void write_out_vec( const string& filename, 
                    const string& array_name, 
                    const vector<double>& output, 
                    bool initialise = true)
    // Writes out data in numpy form. If initialise == true, creates file from scratch and includes top lines needed

 {

 ofstream myfile;
 
 if (initialise){
	myfile.open (filename);
	myfile << "import numpy as np" << "\n" << "\n";}

 else{myfile.open (filename, std::ios_base::app);}
 myfile << array_name << " = np.array((" << "\n";

 for (auto i = 0; i < output.size(); ++i)
 { if (i != (output.size() - 1))
 {
	myfile << output.at(i) << ", " << "\n";
 }
 else
 { 
	myfile << output.at(i) << "\n";
 }
 }
 myfile << "))" << "\n";
 myfile.close();
 }
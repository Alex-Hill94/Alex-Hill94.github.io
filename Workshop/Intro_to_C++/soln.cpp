#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void f_x(const double& x, double& fx)
 {
	if (x == 0)
	{
		fx = 0;
	}
	else
	{
		fx = exp(-1/pow(x,2));
	}
 }

void f_master(const vector<double>& input, vector<double>& output)
 {
	double temp_val;
	for (auto i: input){
		f_x(i, temp_val);
		output.push_back(temp_val);
	}

 }

void write_out_vec(const string& filename, string& array_name , const vector<double>& output)
 {

 ofstream myfile;
 myfile.open (filename, std::ios_base::app); 
 
 myfile << array_name << " = np.array((" << "\n";

 for (auto i = 0; i < output.size(); ++i)
 {
 if (i != (output.size() - 1))
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




int main()

	{
	string filename = "data1.py";
	double k;
	cout << "n_vals = ?";
	cin >> k;
	double llim = -10;
	double ulim = 10;
	double seps = (ulim - llim)/(k - 1);
	vector<double> x_range(k);
	vector<double> fx_range;

	for (int i =0; i < k; ++i)
	{
		x_range.at(i) = llim + (seps * i);
	}

	f_master(x_range, fx_range);

	ofstream myfile;
	myfile.open (filename);

	myfile << "import numpy as np" << "\n" << "\n";
	myfile.close();

	string x_lab = "x_range";
	string fx_lab = "fx_range";

	write_out_vec(filename, x_lab , x_range);
	write_out_vec(filename, fx_lab , fx_range);

	return 0; 
	}

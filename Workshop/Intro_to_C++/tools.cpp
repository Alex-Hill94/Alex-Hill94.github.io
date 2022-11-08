#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



// Purpose: compute f(x), save the data, plot it.
//
// f_master: a function that handles input and output data
//
// f_x: does the actual computation of the exponential function
//
// WritePyData: a class that creates a python script for the 
// purpose of saving data in numpy arrays
//
// PlotData: a class that writes a plotting script and then
// runs it




// f_master and f_x combine to compute some function
// given an input vector
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


class WritePyData { // Class to save data in numpy format
    public: // Access specifier
        string filename = "m_temp.py"; // temporary name of data file


    WritePyData( // Constructor creates a data file if initialise is true
        const string& x, 
        bool initialise = true) // initialise is set to true as a default 
    { 
        filename = x; // Set filename attribute.
        ofstream myfile;
        if (initialise)
        {
        myfile.open (filename);
        myfile << "import numpy as np" << "\n" << "\n";
        }
        myfile.close();
    }

    void write_out_vector( // Method to save data to file created by constructor
        string& array_name , // Name of numpy array
        const vector<double>& array) // Vector to be saved
    {
    ofstream myfile;
    myfile.open(filename, std::ios_base::app); // Opens file without wiping it
    myfile << array_name << " = np.array((" << "\n";

    for (auto i = 0; i < array.size(); ++i) // Loops over vector and saves element by element
    {
        if (i != (array.size() - 1))
        {myfile << array.at(i) << ", " << "\n";}
    else
        {myfile << array.at(i) << "\n";}
    }
    myfile << "))" << "\n";
    myfile.close();
    }


};

class PlotData{ // Class to write plotting script and then run it
    public:
    string plot_filename = "m_temp.py";
    string data_filename = "m_temp.py";
    string fig_filename = "m_temp.png";
    PlotData( // Constructor sets some attributes
    const string& plot_f = "plot.py", 
    const string& data_f = "data.py", 
    const string& fig_f = "test.png")
    {
        plot_filename = plot_f;
        data_filename = data_f;
        fig_filename = fig_f;

    }

    void write_plot() // Method writes plotting script
    {
    // Below two lines removes the .py extension from the end of data_filename,
    // this is required by python syntax for the 'from data import *' line.
    size_t lastindex = data_filename.find_last_of("."); 
    string data_filename_short = data_filename.substr(0, lastindex); 

    ofstream python_file;
    python_file.open(plot_filename);
    python_file<<

    // Write out plotting script
    "import matplotlib\n"<<
    "import matplotlib.pyplot as plt\n"<<
    "from " << data_filename_short << " import *\n"<<
    "FS = 15\n"<<
    "matplotlib.rcParams.update({'font.size': FS})\n"<<
    "fig, axs = plt.subplots(1,1, figsize = [5,5])\n"<<
    "axs.plot(x_range, fx_range)\n"<<
    "axs.set_xlabel('$x$')\n"<<
    "axs.set_ylabel('$f(x)$')\n"<<
    "axs.xaxis.set_tick_params(direction= 'in', which='both', right =True, top = True)\n"<<
    "axs.yaxis.set_tick_params(direction= 'in', which='both', right =True, top = True)\n"<<
    "plt.savefig('" << fig_filename << "',bbox_inches = 'tight', pad_inches = 0.05)\n";

    python_file.close();
    }

    void do_plot() // Method runs plotting script.
    {
        string comando="ipython ";
        comando+=plot_filename;
        system(comando.c_str());

    }

}
;



int main()
{

// First lines of main() set up the data.

double k; // Choose the number of data points, k, to 
// fall betwee llim and ulim
cout << "n_vals = ?";
cin >> k;
double llim = -10;
double ulim = 10;
double seps = (ulim - llim)/(k - 1);

// x_range is a vector of length k, its
// elements are not yet determined
vector<double> x_range(k);

// fx_range is our output. It initially takes the form of 
// a blank vector. We will modify it inside our function.
vector<double> fx_range;


// This loop replaces the elements of x_range with values
// we actually want, namely a linearly separated array
// between llim and ulim
for (int i =0; i < k; ++i)
{
x_range.at(i) = llim + (seps * i);
}

// f_master computes the function of interest. It takes in 
// x_range and fx_range. Fx_range is initially blank, but
// f_master will modify it such that 
// fx_range = f_master(x_range)
f_master(x_range, fx_range);


// We now set up the names of the files of interest, relating
// to our data, our plotting script, and the output figure
string data_filename = "data.py";
string plot_filename = "plot.py";
string fig_filename = "test.png";


// MyData is an object of the WritePyData class template
// The constructor creates a data.py file.
WritePyData MyData(data_filename);


// In saving our x_range and fx_range data as numpy arrays,
// we first decide their names:
string x_lab = "x_range";
string fx_lab = "fx_range";

// The write_out_vector method of MyData saves the data to the file
// created by the constructor
MyData.write_out_vector(x_lab , x_range);
MyData.write_out_vector(fx_lab , fx_range);

// MyPlot is an object of the PlotData class template.
// This class writes a python plotting script and then runs the code.
// The constructor sets some attributes needed to run the code, the
// data filename, the name of the plotting script, and the filename of
// the figure.
PlotData MyPlot(plot_filename, data_filename, fig_filename);

// The write_plot method creates a plotting script of the name
// plot_filename.
MyPlot.write_plot();

// The do_plot method runs the plotting script.
MyPlot.do_plot();
return 0; 
}

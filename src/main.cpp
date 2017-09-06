#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>

#include <unistd.h>		//using getopt()

#define PI 3.140592
#define SIZE 128

using namespace std;

typedef struct _inputparam {
//y = A sin(Bx + C) +D
    double a;       //A
    double b;       //B
    double c;       //C
    double d;       //D
} INPUT;


template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss; 
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }   
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


int main(int argc, char **argv)
{
    int opt;
    string inputfilePath;
    while ((opt = getopt(argc,argv,"i:")) != EOF)
    switch (opt)
    {
        case 'i':
            cout << "Succeed to open inputfile. Path: "<< optarg <<endl ;
            inputfilePath = optarg;
            break;
        default:
            cout << "Usage: %s -i [Inputfile path]\n" << optarg << endl;
            abort();
    }

	INPUT input;

    ifstream openFile(inputfilePath.data());
    
	if( openFile.is_open() ){
        string line;
		
		while(getline(openFile, line)){
			vector<string> opt = split(line, ' ');
			if (!(opt[0].compare("a"))){
				input.a = stod(opt[1]);
				cout << " a is " << input.a << endl;
			} else if (!(opt[0].compare("b"))){
                input.b = stod(opt[1]);
                cout << " b is " << input.b << endl;
            } else if (!(opt[0].compare("c"))){
                input.c = stod(opt[1]);
                cout << " c is " << input.c << endl;
            } else if (!(opt[0].compare("d"))){
                input.d = stod(opt[1]);
                cout << " d is " << input.d << endl;
            } else {
				cout << "Error Invalid value name :: " << opt[0] << endl;
				abort();
			}
        }
        openFile.close();
    } else {
		 cout << "Failed to open input file\n" << endl;
		 abort();
	}


	system("rm -rf result");
	system("mkdir result");

	ofstream outFile("result/result.oneD");

	outFile << "#NumField: 1" << endl;
	outFile << "#LabelX: time, LabelY: a*sine(bx+c)+d " << endl;
	outFile << "#Field1: a=" << input.a << " b=" << input.b << " c=" << input.c << " d=" << input.d << ",NumPoint:" << SIZE << endl;

	double x, y;
	for(int t=0 ; t<SIZE ; t++ ){
		x = (4*PI * t)/SIZE -2*PI;
		y = input.a*(sin( input.b*x +input.c)) +input.d;
		outFile << x << " " << y << endl;
	}
	outFile.close();

    return 0;
}

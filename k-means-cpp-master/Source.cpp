#include <iostream>  //contains the functions of the program like cout, cin etc.
#include <fstream>   //create files, write information to files, and read information from files.
#include <vector>
#include <math.h>    //uses mathematical functions
#include <chrono>    //used for time calculation
#include <algorithm> //collection of functions especially designed to be used on ranges of elements

#define data_type float

using namespace std;
using namespace chrono;  //used to calculate time


//pointer of nizx is centroid x 
//pointer of nizy is centroid y 
//pointer of input x(sem3) is dot x 
//pointer of input y(sem4) is dot y 
void Euclidian_dist(vector<data_type> &centroid_x, vector<data_type> &centroid_y, vector<data_type> &dot_x, vector<data_type> &dot_y){	
	
	vector<data_type> dist,result,arr;
	data_type distance, result_x, result_y;

	for (data_type i = 0; i < dot_x.size(); i++) //it will run for total number of entries
		{ 

		    for (data_type j = 0; j < centroid_x.size(); j++)  //it will run k times
			{

                //calculating the Euclidian distance
				distance = sqrt(pow((dot_x[i] - centroid_x[j]), 2) + pow((dot_y[i] - centroid_y[j]), 2));
				dist.push_back(distance);

			}
            //automatically deciding datatype of result
			//storing of minimum value of distance in result

			auto result = min_element(dist.begin(), dist.end()) - dist.begin();
			arr.push_back(result); //storing cluster value for each particular row value
			
			//cout << "C" << result << " " << dot_x[i] << " " << dot_y[i] << endl;

			dist.clear(); 
		}
	
	    /*for (vector<data_type>::iterator it = arr.begin(); it != arr.end(); ++it)
		cout << *it << endl;*/

	for (data_type k = 0; k < centroid_x.size(); k++)
	{
		result_x = 0, result_y = 0;
		data_type counter = 0;

		for (data_type z = 0; z < dot_x.size(); z++) 
		{

			if (arr[z] == k) //checking each row belongs to which cluster
			{
				result_x += dot_x[z]; 
				result_y += dot_y[z];
				counter++;
			}

		}
		//calculating mean value for each column
		result_x = result_x / counter;
		result_y = result_y / counter;
		
		cout << "Updated centroid " << k << " is:" << endl;
		cout << "Centroid[" << k << "] " << result_x << " " << result_y << endl;

	}
	
}

int main(){
	
	srand(time(NULL));	//this line assures random number combination every time compiling the program
	
	ifstream inputFile("input.txt");	//reading of .txt input file with random dots

	vector<data_type> input_x, input_y;
	
	data_type x,y;
	data_type k = 0;

	while(inputFile >> x >> y)	//read random dots from input file and save them to vectors
	{
		input_x.push_back(x);
		input_y.push_back(y);
			
		cout << input_x[k] << " " << input_y[k] << endl;
		k++;
	}
	
	data_type n_centr,n_centrx, n_centry;
	
	vector <data_type> nizx, nizy;

	cout << "Input value of K:";
	cin >> n_centr;
	
	auto started = high_resolution_clock::now(); //start time measure
	
	for (int i = 0; i < n_centr; i++)
	{	
	    n_centrx = rand() % 10 + 1;	//random X coordinate in range 1 to 10
		nizx.push_back(n_centrx);	//fill vector with X coordinates

		n_centry = rand() % 10 + 1;	//random Y coordinate in range 1 to 10
		nizy.push_back(n_centry);	//fill vector with Y coordinates
		
		cout << "Centroid[" << i << "] = " << nizx[i] << " " << nizy[i] << endl;	
	}
	
	/*for (int j = 0; j < n_centr; j++)
	{
		cout <<"X["<<j<<"] is "<< nizx[j] << endl;
		cout << "Y[" << j << "] is " << nizy[j] << endl;
	}*/

	Euclidian_dist(nizx, nizy, input_x, input_y);
		
	ofstream outputFile("output.txt");	//writing .txt output files with new dots
	
	//outputFile << Euclidian_dist(nizx, nizy, input_x, input_y) << " " << endl; //writing to output.txt in case function return
	//A stream buffer is an object in charge of performing the reading and writing operations
	// of the stream object it is associated with: the stream 
	//delegates all such operations to its associated stream buffer object, 
	//which is an intermediary between the stream and its controlled input and output sequences.
	
	streambuf *oldbuf = cout.rdbuf(); //assign streambuf to cout
	cout.rdbuf(outputFile.rdbuf());  //start writing the data to the file

	Euclidian_dist(nizx, nizy, input_x, input_y);  //contents to cout will be written to output.txt
			 
	cout.rdbuf(oldbuf); //restore original streambuf 
	
	outputFile.close(); //closes the file written
	
	auto done = high_resolution_clock::now();	//end time measure
	
	cout << "Running time: " << duration_cast<milliseconds>(done - started).count() << "ms" << endl;	//running time in milliseconds
}
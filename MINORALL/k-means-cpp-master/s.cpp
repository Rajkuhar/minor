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

void Euclidian_dist(vector<data_type> &centroid_x, vector<data_type> &centroid_y, vector<data_type> &dot_x, vector<data_type> &dot_y ,int n, vector<float>& l)
{	
    if(n==1)
	{
        for (int k = 0; k < centroid_x.size(); k++)
		{
            l.push_back(centroid_x[k]);
            l.push_back(centroid_y[k]);
        }
		return;
    }

	vector<data_type> dist,result,arr;
	data_type distance, result_x, result_y;

	for (int i = 0; i < dot_x.size(); i++) //it will run for total number of entries
		{ 
		    for (int j = 0; j < centroid_x.size(); j++)  //it will run k times
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

//    yahan pe bhi vapas se temporary array create karne padhege vapas se nizx and //nizy k liye yahan pe recursive function create karne k liye 

    
    vector <float> p;
    vector <float> q;
	for (int k = 0; k < centroid_x.size(); k++)
	{
		result_x = 0, result_y = 0;
		int counter = 0;

		for (int z = 0; z < dot_x.size(); z++) 
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

        p.push_back(result_x);
        q.push_back(result_y);

        
		//cout << "Updated centroid " << k << " is:" << endl;
		//cout << "Centroid[" << k << "] " << result_x << " " << result_y << endl;

	}

    return Euclidian_dist(p,q,dot_x,dot_y,n-1, l);
}




void sol(vector<data_type> &centroid_x, vector<data_type> &centroid_y, vector<data_type> &dot_x, vector<data_type> &dot_y ,vector<float>& lst)
{	
	
	vector<data_type> dist,result;
	data_type distance, result_x, result_y;

	for (int i = 0; i < dot_x.size(); i++) //it will run for total number of entries
		{ 

		    for (int j = 0; j < centroid_x.size(); j++)  //it will run k times
			{

                //calculating the Euclidian distance
				distance = sqrt(pow((dot_x[i] - centroid_x[j]), 2) + pow((dot_y[i] - centroid_y[j]), 2));
				dist.push_back(distance);

			}
            //automatically deciding datatype of result
			//storing of minimum value of distance in result

			auto result = min_element(dist.begin(), dist.end()) - dist.begin();
			lst.push_back(result); //storing cluster value for each particular row value
			
			//cout << "C" << result << " " << dot_x[i] << " " << dot_y[i] << endl;

			dist.clear(); 
		}
	
	    /*for (vector<data_type>::iterator it = arr.begin(); it != arr.end(); ++it)
		cout << *it << endl;*/

//yahan pe bhi vapas se temporary array create karne padhege vapas se nizx and //nizy k liye yahan pe recursive function create karne k liye 

    return; 
}

int main()
{
	
	//srand(time(NULL));	//this line assures random number combination every time compiling the program
	
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
	
	float n_centr,n_centrx, n_centry;

    cout << endl;
	
	vector <data_type> nizx, nizy;
    int n;
    cout<<"input no. of iterations:";
    cin >> n;
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
	
    //yahan code likh , for number of iterations
    //n=int(input())
    
	/*for (int j = 0; j < n_centr; j++)
	{
		cout <<"X["<<j<<"] is "<< nizx[j] << endl;
		cout << "Y[" << j << "] is " << nizy[j] << endl;
	}*/

    //yahan pe changes kar
    //x,y karke 2 array ya vector create kar or unme jo function return kare unhe store kara , jaise

    vector<float> l;
	Euclidian_dist(nizx, nizy, input_x, input_y ,n, l);
	
	vector<float> yy;
	vector<float> xx;
    int a=l.size();
    int i=0;
    int j=1;
    while(i!=a){
        cout<<"updated cordinates "<<j <<" : ";
        cout<<l[i]<<" "<<l[i+1]<<endl;
		xx.push_back(l[i]);
		yy.push_back(l[i+1]);
        i=i+2;
        j=j+1;
    }

	vector <float>lst;
	sol(xx, yy, input_x, input_y , lst);
    vector <float>students;
	for (int k = 0; k < xx.size(); k++)
	{
		int counter = 0;

		for (int z = 0; z < input_x.size(); z++) 
		{

			if (lst[z] == k) //checking each row belongs to which cluster
			{
				counter++;
			}

		}
		students.push_back(counter);
		cout<<"Number of students in centroid "<<k<<" : "<<counter<<endl;
	}

	ifstream inputFile1("input2.txt");	//reading of .txt input file with random dots

	vector<data_type> vaccinated, joining_campus;
	
	data_type x1,y1;
	data_type k1 = 0;

	while(inputFile1 >> x1 >> y1)	//read random dots from input file and save them to vectors
	{
		vaccinated.push_back(x1);
		joining_campus.push_back(y1);
		k1++;
	}

	int total=0;
	for (int k = 0; k < xx.size(); k++)
	{
		int counter = 0;

		for (int z = 0; z < vaccinated.size(); z++) 
		{

			if (lst[z] == k && vaccinated[z]==1 && joining_campus[z]==1) //checking each row belongs to which cluster
			{
				counter++;
			}

		}
		total=total+counter;
	}

	cout<<"Number of students being vaccinated and will be joining campus :" <<" "<<total<<endl;
	cout<<"Number of students joining in online mode :" <<" "<<input_x.size() - total<<endl;
	
	auto done = high_resolution_clock::now();	//end time measure
	
	cout << "Running time: " << duration_cast<milliseconds>(done - started).count() << "ms" << endl;	//running time in milliseconds

}

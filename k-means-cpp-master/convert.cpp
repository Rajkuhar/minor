#include<bits/stdc++.h>
#include <fstream>  
#include<vector>

using namespace std;
int main(){

    ifstream inputFile("studat55.txt");	

	vector<string> input_x;
	vector<float> aa,bb;
	vector<int> cc,dd;
	string x;
	float a,b;
	int c,d;
	double k = 0;

	while(inputFile >> x>> a>> b>> c>> d)	
	{
		input_x.push_back(x);
		aa.push_back(a);
		bb.push_back(b);
		cc.push_back(c);
		dd.push_back(d);
			
		cout << input_x[k] <<" "<<aa[k]<<" "<<bb[k]<<" "<<cc[k]<<" "<<dd[k]<<" "<< endl;
		k++;
	}

    ofstream outputFile("out.txt");
    streambuf *oldbuf = cout.rdbuf(); 
	cout.rdbuf(outputFile.rdbuf());  
	for(int i=0;i<aa.size();i++){
		cout<<aa[i]<<" "<<bb[i]<<endl;
	}
	cout.rdbuf(oldbuf);
	outputFile.close();
}
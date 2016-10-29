#include <iostream>
#include <vector> 
#include <queue>
#include <map> 
#include <set>
#include <utility> //Pair
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <bitset>
#include <limits>
#include <string>
#include <fstream>
#include <limits.h>
#define pb push_back
#define mp make_pair
#define mod 1000000007
using namespace std;

void computePrefix(string pattern, int *array)
{
	int m = pattern.length();
	array[0]=0;
	int k = 0;
	for(int q=1; q<m; q++)
	{
		while(k>0 && pattern[k]!=pattern[q])
			k = array[k-1];
		if(pattern[k]==pattern[q])
			k++;
		pattern[q]=k;
	}
}

void kmp(string text, string pattern)
{
	int n = text.length();
	int m = pattern.length();
	int * array = (int*)malloc(sizeof(int)*m);
	for(int i=0; i<m; i++)
		array[i]=0;
	computePrefix(pattern,array);
	int q = 0;
	int count = 0;
	for(int i=0; i<n; i++)
	{
		while(q>0 && pattern[q]!=text[i])
			q = array[q-1];
		if(pattern[q]==text[i])
			q++;
		if(q==m)
		{
			count++;
			q = array[q-1];
    	}
	}
	free(array);
	cout<<count;
}
int main()
{
	ifstream file("AESOP TALES (with random URLs).txt");
	string str;
	string txt="";	
	while (getline(file, str)){
		txt += str;
	 	txt.push_back('\n');
	} 
    string pat = "wolf";
    kmp(txt,pat);
	return 0;
}

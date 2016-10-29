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

#include<iostream>
#include<string>
#define d 127

using namespace std;

void rabinKarp(string text, string pattern)
{
	int count = 0;
    int M = pattern.length();
    int N = text.length();
    int q = 104729;
    int i, j;
    int p = 0; 
    int t = 0; 
    
	int h = 1;
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    for (i = 0; i < M; i++)
    {
        p = (d*p + pattern[i])%q;
        t = (d*t + text[i])%q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if ( p == t )
        {
            for (j = 0; j < M; j++)
            {
                if (text[i+j] != pattern[j])
                    break;
            }
 
            if (j == M)
                count++;
        }
        
        if ( i < N-M )
        {
            t = (d*(t - text[i]*h) + text[i+M])%q;
            if (t < 0)
            	t = (t + q);
        }
    }
    cout << count;
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
    rabinKarp(txt, "wolf");
    return 0;
}

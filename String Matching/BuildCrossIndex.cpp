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
#include <limits.h>
#include <string>
#include <fstream>
#define pb push_back
#define mp make_pair
#define mod 1000000007
using namespace std;

string txt="";

int* suffixArr;
int* lcp;

// Structure to store information of a suffix
typedef struct{
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
}suffix;
 
// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(suffix a, suffix b){
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
               (a.rank[0] < b.rank[0] ?1: 0);
}
 
// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
void buildSuffixArray(int n){
    // A structure to store suffixes and their indexes
    suffix suffixes[n];
 
    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabatically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }
 
    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);
 
    // At his point, all suffixes are sorted according to first
    // 2 characters.  Let us sort suffixes according to first 4
    // characters, then first 8 and so on
    int ind[n];  // This array is needed to get the index in suffixes[]
                 // from original index.  This mapping is needed to get
                 // next suffix.
    for (int k = 4; k < 2*n; k = k*2){
        // Assigning rank and index values to first suffix
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;
 
        // Assigning rank to suffixes
        for (int i = 1; i < n; i++){
            // If first rank and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else // Otherwise increment rank and assign
			{
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
 
        // Assign next rank to every suffix
        for (int i = 0; i < n; i++){
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                  suffixes[ind[nextindex]].rank[0]: -1;
        }
 
        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+n, cmp);
    }
 
    // Store indexes of all sorted suffixes in the suffix array
	suffixArr=new int[n];
 
    for (int i = 0; i < n; i++)
        suffixArr[i] = (suffixes[i].index);
 
}
 
void buildLCPkasai(int n){
    int k=0;
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[suffixArr[i]]=i;

	lcp = new int[n];
    for(int i=0; i<n; i++, k?k--:0){
        if(rank[i]==n-1) {k=0; continue;}
        int j=suffixArr[rank[i]+1];
        while(i+k<n && j+k<n && txt[i+k]==txt[j+k]) k++;
        lcp[rank[i]]=k;
    }
}

int noOfOccurences(string pattern,string a,string b){
	string txt1=txt.substr(txt.find(a),txt.find(b));
	int n=txt1.length();
	int l=0;
	int r=n-1;
	int count=0;
	int lenp=pattern.length();
	int till=n-1;
	
	//Process pattern
	string pat1="";
	for(int i=0;i<lenp;i++){
		char curr=pattern[i];
		if(curr>=65 && curr<91){
			pat1+=(char)(curr+32);
		}
		else pat1+=curr;
	}
	pattern=pat1;

	int mid=(l+r)/2;
	string curr=txt1.substr(suffixArr[mid]);
	int l1=curr.length();
	int offset=0;
	while(offset<l1 && offset<lenp && curr.at(offset)==pattern.at(offset)){
		offset++;
	}		
	if(offset==lenp){
		count+=1;
		int temp=mid;
		while(lcp[temp]>=lenp){
			count+=1;temp+=1;
		}
		temp=mid-1;
		while(lcp[temp]>=lenp){
			count+=1;temp-=1;
		}
//		cout<<"here1"<<endl;
		return count;
	}
	if(curr<pattern)l=mid+1;
	else r=mid-1;
	int prevlcp=offset;
	while(l<=r){
			int prevmid=mid;
			mid=(l+r)/2;
			int start=prevmid<mid?prevmid:mid;
			int end=prevmid<mid?mid:prevmid;
			int min =INT_MAX;
			for(int i=start;i<end;i++){
				if(lcp[i]<min)min=lcp[i];
			}
//			cout<<"min: "<<min<<" "<<mid<<" "<<prevmid<<" "<<txt.substr(mid)<<endl;
			if(min>prevlcp){
				if(l>prevmid)l=mid+1;
				else r=mid-1;
			}
			else if(min<prevlcp){
				if(l<prevmid)l=mid+1;
				else r=mid-1;
				prevlcp=min;
			}
			else{
				curr=txt.substr(suffixArr[mid]);
				int currl=curr.length();
				offset=min;
				while(offset<currl && offset<lenp && curr.at(offset)==pattern.at(offset)){
					offset++;
				}
				prevlcp=offset;
				if(offset==lenp){
					count+=1;
					int temp=mid;
					while(lcp[temp]>=lenp){
					count+=1;temp+=1;
					}
					temp=mid-1;
					while(lcp[temp]>=lenp){
						count+=1;temp-=1;
					}
//					cout<<curr<<endl;
					return count;
				}
				if(offset<currl){
					if(curr.at(offset)>pattern.at(offset))r=mid-1;
					else l=mid+1;
				}
				else{
					l=mid+1;
				}
			}
	}
	return count;
}
void processtxt(){
	int n=txt.length();
	string txt1="";
	for(int i=0;i<n;i++){
		char curr=txt[i];
//		cout<<curr<<" "<<(curr>=97)<<" "<<txt1<<endl;
/*		if(curr>=97 && curr<123)txt1+=curr;
		else*/ if(curr>=65 && curr<91){
			txt1+=(char)(curr+32);
		}
		else txt1+=curr;
	}
	txt=txt1;	
//	cout<<txt1<<endl;
}

int Find_Pattern(string txt,string pattern,int start,int end,int algo){
	txt=txt.substr(start,end);	
	if(algo==2){
		txt=processtxt(txt);
    	buildSuffixArray(txt);
		buildLCPkasai(txt);	
		return noOfOccurences(txt,pattern);
	}
} 

int Find_Pattern(string txt,string pattern,string start,string end,int algo){
	Find_Pattern(txt,pattern,txt.find(start),txt.find(end),algo);
}

int main(){
	ifstream file("AESOP TALES (with random URLs).txt");
	string str;
	while (getline(file, str)){
		txt += str;
	 	txt.push_back('\n');
	} 
	vector<string> titles;	
	int count=0;
	int len=txt.length();
	for(int i=0;i<len;i++){
		if((int)(txt[i])==10){
			i++;
			while((int)(txt[i])==13 || (int)(txt[i])==32)i++;
			if((int)(txt[i])==10){
				i++;
				while((int)(txt[i])==13 || (int)(txt[i])==32)i++;
				if((int)(txt[i])==10){
					string title="";i+=1;
					while(txt[i]!='\n'){
						title+=txt[i];i++;
					}
					titles.pb(title);
				}
			}
		} 
	}
	set<string> words; 
	for(int i=0;i<len;i++){
		string word="";
		while(i<len && (txt[i]!=' ' && txt[i]!='\n')){
			if(txt[i]>=65 && txt[i]<91)word+=(char)(txt[i]+32);
			else if(txt[i]>=97 && txt[i]<123)word+=txt[i];
			else break;
			i++;
		}
		if(word.length()>0)words.insert(word);
//		cout<<"WORD: "<<word<<endl;
	}
	int notitles=titles.size();
	int total=0;
	for(string currWord: words){
		cout<<currWord<<endl;
		for(int i=0;i<notitles-1;i++){
			int occ=Find_Pattern(txt,currWord,titles[i],titles[i+1],algo);
			if(occ>0){
				cout<<titles[i]<<" "<<occ<<endl;
			}
			total+=occ;
		}	
		cout<<"Total occurences: "<<total<<endl<<endl;
	}
}

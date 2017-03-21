#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
using namespace std;

//getfirst and getlast retrieve the first and last words of any given phrase
string getfirst(string phrase)
{
	int i=0;
	while(true)
	{
		if(phrase.at(i)==' ')
			break;
		i++;
	}
	return phrase.substr(0, i);
}

string getlast(string phrase)
{
	int i = phrase.length()-1;
	while(true)
	{
		if(phrase.at(i)==' ')
			break;
		i--;
	}
	return phrase.substr(i+1);
}

/* this function gets the longest path starting from node n by adding one to the maximum of
 * the longest paths starting from all of its children, and if that amount has not been found
 * yet, this function will call itself to retrieve that value. base case: leaves return 1 */
int longest(unordered_map<string, unordered_set<int>>& edges, int index, int* longs, string* tree)
{
	if(longs[index]!=-1)
		return longs[index];
	if(!edges.count(getlast(tree[index])))
	{
		longs[index] = 1;
		return 1;
	}
	int maxchild = 0;
	for(int x:edges.at(getlast(tree[index])))
	{
		if(longs[x]==-1)
		{
			longest(edges, x, longs, tree);
		}
		maxchild = max(maxchild, longs[x]);
	}
	longs[index] = maxchild+1;
	return longs[index];
}

int main()
{
	int cases;
	cin>>cases;
	for(int state=1;state<=cases;state++)
	{
		int size;
		string nothing;
		cin>>size; getline(cin, nothing);
		// we store the nodes in a simple array and refer to them by their index
		string tree[size];
		// this map will return a set of all nodes that start with a given word
		unordered_map<string, unordered_set<int>> edges;
		for(int i=0;i<size;i++)
		{
			getline(cin, tree[i]);
			if(!edges.count(getfirst(tree[i])))
			{
				unordered_set<int> temp;
				temp.emplace(i);
				edges.emplace(getfirst(tree[i]), temp);
			}
			else
			{
				edges.at(getfirst(tree[i])).emplace(i);
			}
		}
		int longs[size];
		for(int i=0;i<size;i++)
		{
			longs[i] = -1;
		}
		// here we call the longest function on all nodes, and output the maximum value
		int maxlen = 0;
		for(int i=0;i<size;i++)
		{
			maxlen = max(maxlen, longest(edges, i, longs, tree));
		}
		cout<<"Puzzle #"<<state<<": "<<maxlen<<endl;
	}
	
	return 0;
}

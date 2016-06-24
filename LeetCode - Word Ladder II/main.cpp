#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {

public:
	vector<vector<string>> path;

    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList)
	{
		vector<string> p;

		p.push_back(beginWord);
		wordList.insert(endWord);
		_findLadders(endWord, beginWord, p, wordList);

		return path;   
    }

	void make_candidates(vector<string> &candidates, string &word, vector<string> &p, unordered_set<string> &wordList)
	{
		for(int i=0; i<word.size(); i++)
		{
			for(char ch='a'; ch<'z'; ch++)
			{
				if(ch == word[i]) continue;

				string w = word;
				w[i] = ch;

				if(wordList.find(w) != wordList.end() && find(p.begin(), p.end(), w) == p.end())
					candidates.push_back(w);
			}
		}
	}

	void _findLadders(string &endWord, string &word, vector<string> &p, unordered_set<string> &wordList)
	{
		if(word == endWord)
		{
			path.push_back(p);
			return;
		}
		else
		{
			vector<string> candidates;
			make_candidates(candidates, word, p, wordList);

			for(auto &c : candidates)
			{
				p.push_back(c);
				_findLadders(endWord, c, p, wordList);
				p.pop_back();
			}
		}
	}
};

int main(void)
{
	string beginWord = "hit";
	string endWord = "cog";
	unordered_set<string> wordList;

	wordList.insert("hot");
	wordList.insert("dot");
	wordList.insert("dog");
	wordList.insert("lot");
	wordList.insert("log");

	Solution s;

	vector<vector<string>> res = s.findLadders(beginWord, endWord, wordList);

	return 0;
}

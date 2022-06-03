#ifndef __MIN_HASH_H__
#define __MIN_HASH_H__

#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include<bitset>
#include<set>
#include<algorithm>

#include<stdlib.h>
#include<time.h>
#include <stdio.h>

#define REP_TIMES 30
#define DOC_NUM 1000
//#include "Jaccard.h"

using namespace std;

template<unsigned int ROW_NUM = UINT_MAX, unsigned int COL_NUM = DOC_NUM>
class MinHash
{
public:
	MinHash(const string& strShingPath = "./Shingles/") :
		m_strShinglePath(strShingPath),
		m_vecShingle(DOC_NUM, set<unsigned int>()),
		m_vecMinHash(REP_TIMES, vector<unsigned int>(COL_NUM, UINT_MAX)),
		m_vecJaccard(DOC_NUM, vector<float>(DOC_NUM, 0.0))
	{
		Initialize();
	}

	bool CalMinHash()
	{
		unsigned long long randomAB[30][2];
		for(int i = 0; i < 30; i++){
			unsigned long long a = rand();
			unsigned long long b = rand();
			randomAB[i][0] = a;
			randomAB[i][1] = b;
		}
		for (int i = 0; i < DOC_NUM; ++i)
		{
			_CalSingleColMinHash(m_vecShingle[i], i, randomAB);
			cout << "minhash of doc "<<i<<endl;
		}//end of 1000 documents	

		return true;
	}


	bool Initialize()
	{
		srand((unsigned int)time(NULL));

		for (int i = 1; i <= DOC_NUM; ++i)
		{
			string strFile = m_strShinglePath + "shingle_" + to_string(i) + ".bin";
			FILE* fp;
			fp = fopen(strFile.c_str(), "rb");
			if (fp == NULL) {
				std::cout << "File create error, FileName: " << strFile << std::endl;
				return false;
			}

			fread(m_Shingle, sizeof(unsigned int), 493, fp);
			cout << "read shingle, DocNum: " << i << "iIndex"
				<< endl;
			for (int iIndex = 0; iIndex < 493; ++iIndex)
			{
				m_vecShingle[i - 1].insert(m_Shingle[iIndex]);
			}
			fclose(fp);
		}

		return true;
	}


	void _CalSingleColMinHash(set<unsigned int> setShingle, int uCol, unsigned long long randomAB[30][2])
	{
		for (int iCount = 0; iCount < REP_TIMES; ++iCount)
		{
			for (auto& ite : setShingle)
			{
				unsigned int uHashVal = _UniversalHash(ite, randomAB[iCount][0], randomAB[iCount][1]);
				if (uHashVal < m_vecMinHash[iCount][uCol])
				{
					m_vecMinHash[iCount][uCol] = uHashVal;
					//cout << iCount << ", uCol: " << uCol << ", Row: " << ite << ", uHashVal: " << uHashVal << endl;
				}
			} // end of setShingle 
		}// end of 30 Count
		
	}


	void CalJaccardSimilarity() {
		cout << "CalJaccardSimilarity: " << endl;
		for (int i = 0; i < DOC_NUM; i++) {
			cout << "calculate JaccardSimilarity of document "<<i << endl;
			for (int j = i + 1; j < DOC_NUM; j++) {
				const set<unsigned int>& a = m_vecShingle[i];
				const set<unsigned int>& b = m_vecShingle[j];

				set<unsigned int> inter_, union_;
				set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(inter_, inter_.begin()));
				set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(union_, union_.begin()));
				m_vecJaccard[i][j] = (float)inter_.size() / union_.size();
				//cout << inter_.size() << " inter " << union_.size() << " union " << m_vecJaccard[i][j] << endl;
			} //end of j

			//cout<< i << " " << m_vecJaccard[i][i+1] <<endl;
		} // end of i 

	}

	void ResetMinHash()
	{
		m_vecMinHash.clear();
		m_vecMinHash = std::move(vector<vector<unsigned int > >(REP_TIMES, vector<unsigned int>(COL_NUM, UINT_MAX)));
	}

	~MinHash()
	{
	}

private:
	//	define universal hashing function
	/*
	unsigned int _UniversalHash_old(unsigned int X)
	{
		//unsigned long long a = rand();
		//unsigned long long b = rand();
		//cout << "a: " << a << ", b: " << b << endl;
		return (((a * X) % m_ullP + b) % m_ullP) % UINT_MAX;
	}
	*/
	unsigned int _UniversalHash(unsigned int X, unsigned int a, unsigned int b)
	{
		//unsigned long long a = rand();
		//unsigned long long b = rand();
		//cout << "a: " << a << ", b: " << b << endl;
		return (((a * X) % m_ullP + b) % m_ullP) % UINT_MAX;
	}


private:
	std::string m_strShinglePath;

	unsigned long long m_ullP = 4294967311;

	unsigned int m_Shingle[493];

	vector<set<unsigned int> > m_vecShingle;

public:
	vector<vector<unsigned int> > m_vecMinHash;

	vector< vector<float> > m_vecJaccard;
};


#endif

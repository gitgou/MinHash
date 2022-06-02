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
	MinHash(const string& strShingPath="./Shingles/"):
	m_strShinglePath(strShingPath),
	m_vecShingle(DOC_NUM, set<unsigned int>()),
	m_vecMinHash(REP_TIMES, vector<unsigned int>(COL_NUM, UINT_MAX)),
	m_vecJaccard(DOC_NUM, vector<float>(DOC_NUM, 0.0))
	{
		Initialize();
	}
	
	bool CalMinHash()
	{
		for(int i = 0; i < DOC_NUM; ++i)
		{

			// 计算第i列（第i个文档）的重排
			_CalSingleColMinHash(m_vecShingle[i], i);
		}//end of 1000 documents	
		
		return true;
	}


	bool Initialize()
	{
		srand((unsigned int )time(NULL));
		
		for(int i = 1; i <= DOC_NUM; ++i)
		{
			string strFile = m_strShinglePath + "shingle_" + to_string(i) + ".bin"; 
			FILE* fp;
			fp = fopen(strFile.c_str(), "rb");
			if (fp == NULL) {
				std::cout << "File create error, FileName: " << strFile << std::endl;
				return false;
			}
			
			//读取 Shingle 文件
			fread(m_Shingle, sizeof(unsigned int), 493, fp);
			//使用set 去重, setShingle 保存文档的 Shingle
			for(int iIndex = 0; iIndex < 493; ++iIndex)
			{
				m_vecShingle[i - 1].insert(m_Shingle[iIndex]);
				cout << "read shingle, DocNum: " << i << "iIndex"
					<< endl;
			}
			fclose(fp);
		}
		
		return true;
	}
	
	
	void _CalSingleColMinHash(set<unsigned int> setShingle, int uCol)
	{
		// 对一列运行30 次
		for(int iCount = 0; iCount < REP_TIMES; ++iCount)
		{
				for(auto &ite : setShingle)
				{
					unsigned int uHashVal = _UniversalHash(ite);
					if(uHashVal < m_vecMinHash[iCount][uCol])
					{
						m_vecMinHash[iCount][uCol] = uHashVal;
						//cout << iCount << ", uCol: " << uCol << ", Row: " << ite << ", uHashVal: " << uHashVal << endl;
					}
				} // end of setShingle 
		}// end of 30 Count
	}
	
	
	//计算文档 Jaccard Similarity
	void CalJaccardSimilarity(){
		//文档i和文档j的相似度
		cout<<"CalJaccardSimilarity: "<<endl;
		for(int i = 0; i < DOC_NUM; i++){	
			for(int j = i + 1; j < DOC_NUM; j++){
				const set<unsigned int>& a = m_vecShingle[i];  
				const set<unsigned int>& b = m_vecShingle[j];  
				  
				set<unsigned int> inter_, union_;
				set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(inter_ , inter_.begin()));
				set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(union_ , union_.begin()));
				m_vecJaccard[i][j] = (float)inter_.size() / union_.size();
				cout<<inter_.size()<<" inter "<<union_.size()<<" union "<< m_vecJaccard[i][j]<<endl;
			} //end of j
			
			//cout<< i << " " << m_vecJaccard[i][i+1] <<endl;
		} // end of i 
	
	}
	
    void ResetMinHash()
    {
        m_vecMinHash.clear();
        m_vecMinHash = std::move(vector<vector<unsigned int > > (REP_TIMES, vector<unsigned int>(COL_NUM, UINT_MAX)));
    }
	
	~MinHash()
	{
	}

private:
	//	define universal hashing function
	//  𝑥是 shingling 中输出的整数（即特征矩阵中的行号）
	unsigned int _UniversalHash(unsigned int X)
	{
		unsigned long long a = rand();
		unsigned long long b = rand();
		//cout << "a: " << a << ", b: " << b << endl;
		//优化一下，可能越界
		return (((a * X) % m_ullP + b) % m_ullP) % UINT_MAX;
	}
	

	//获取所有 Shingle 文件描述符
private:
	//Shlingle 文件存放的目录
	std::string m_strShinglePath;
		
	//定义通用哈希函数的 P 值，P是大于N 的素数
	unsigned long long m_ullP = 4294967311;
	
	//用来读取所有 Shingle 文件内容, 500-8+1=493
	unsigned int m_Shingle[493];
	
	//记录 Shingle 文件，使用 set去重
	vector<set<unsigned int> > m_vecShingle;

public:
	//定义一个 30 * 1000 的矩阵记录 1000 篇文档 Shingles 经过 30 次排序的 MinHash 值, 初始化为 UINT_MAX
	vector<vector<unsigned int> > m_vecMinHash;

	//定义矩阵保存 Jaccard Similarity
	vector< vector<float> > m_vecJaccard;
};


#endif

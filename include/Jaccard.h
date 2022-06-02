#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include<iostream>
#include<bitset>


//用于计算 Jaccard 相似度 和 Hamming Distance
class Jaccard 
{
public:
	Jaccard()
	{}
	
	void Calcurate(unsigned int lsh, unsigned int rsh);

	void PrintResult();

	void Clear();
	
	float GetJaccardSimilarity()
	{
		return (double)_iInterset /(double)_iAndSet;
	}
private:
	int _iInterset = 0; //两个向量数据 1 交集
	int _iAndSet = 0;   //两个向量数据 1 并集 
	int _iHammingDistance = 0;// 记录 Hamming Distance 
};
#endif

#include <iostream>
#include <random>
#include <utility>
#include <math.h>
#include<climits>

#include "resultHandling.h"
#include "LocalSensitiveHash.h"
#include "MinHash.h"
#include "ArticleGenerator.h"

#define iJacSimRow 1000
#define iJacSimColumn 1000
#define iLocSensHashRow 1000
#define iLocSensHashColumn 1000
#define iMinHash 1000
#define iSignNum 30
#define iDocNum 1000

void GenerateArticle()
{
	ArticleGenerator oArtGenerator;
	//生成文件,默认存放路径为 ./Articles & ./Shingles
	oArtGenerator.fnArticleGeneration();
	oArtGenerator.fnShingling();
}


int main()
{
	clock_t start, end;
	start = clock();
	//生成字符文档 & Shingle 文档    
	GenerateArticle();

	//matrix [6,2]
	std::vector< pairBandRadius> vecBandRadius = { pairBandRadius(5,4)} ;//,
		//////////////////pairBandRadius(2,3),pairBandRadius(3,5),pairBandRadius(4,6),pairBandRadius(5,8) };

	//存放 1000次 MinHash Value [1000,30,1000]
	std::vector<std::vector< std::vector<unsigned int> > > vecMinHash(iMinHash, std::vector<
		std::vector<unsigned int> >(20, std::vector<unsigned int>(iDocNum, 0)));


	//存放 Local Senstive Hash [6,1000,1000]
	std::vector<std::vector<std::vector<float> > >vecLocSensHash(vecBandRadius.size(),
		std::vector<std::vector<float>>(iLocSensHashRow, std::vector<float>(iLocSensHashColumn, 0)));

	/* data initialization  */
	/*
	float fInterval = 1. / (1000 * 999 / 2.);
	for (int i = 0; i < iJacSimRow; i++) {
		for (int j = i; j < iJacSimColumn; j++) {
			oMinHash.m_vecJaccard[i][j] = fXaxis;
			fXaxis += fInterval;
		}
	}
	for (int k = 0; k < vecBandRadius.size(); k++)
	{
		fXaxis = 0.;
		for (int i = 0; i < iLocSensHashRow; i++) {
			for (int j = i; j < iLocSensHashColumn; j++) {
				vecLocSensHash[k][i][j] = fXaxis;
				fXaxis += fInterval;
			}
		}
	}
	*/

	//Part2: Cal  MinHash & JaccardSimilarity
	//Get 1000 signature matrix:[1000,30,1000]
	MinHash<UINT_MAX, DOC_NUM> oMinHash;
	
	oMinHash.CalJaccardSimilarity();
	//for (int i = 0; i < 1; i++) {
	//for (int i = 0; i < 30; i++) {
	for (int i = 0; i < iMinHash; i++) {
		cout << "finish minhash of doc "<<i<<endl;
		//计算 MinHash
		oMinHash.CalMinHash();
		vecMinHash[i]=oMinHash.m_vecMinHash;
		//重置 m_vecMinHash.
		oMinHash.ResetMinHash();
	}
	

	/*
	test vecMinHash
	*/
	//for (int i = 0; i < iDocNum; i++) {
		//cout << "jaccard similary of the first document to docum " << i <<": ";
		//cout << oMinHash.m_vecJaccard[0][i]<<endl;
	//	cout << "minhash of the first value(/30) to docum(/1000) " << i <<": ";
	//	cout << vecMinHash[0][0][i]<<" ";
	//	cout << oMinHash.m_vecMinHash[0][i] << endl;
	//}
	//for (int j = 0; j < 30; j++) {
	//	cout<< "minhash of the "<<j<<" value(/30) to docum(/1000) " << 0 << ": "<< vecMinHash[0][j][0]<<"; docum(/1000) " << 1 << ": " << vecMinHash[0][j][1]<<endl;
	//}
	

	//Part3: LSH
	
	for (int i = 0; i < vecBandRadius.size(); i++) {
		vecLocSensHash[i] = Locality_Sensitive_Hashing(vecMinHash,
			vecBandRadius[i].first, vecBandRadius[i].second);
	}
	end = clock();
	

	/*
	Part3: Results Handling
	*/
	ResultHandling id = ResultHandling();
	id.fnResultOutput(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);
	cout << "Run Time of LSH: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
	id.fnImageDrawing(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);
	id.fnResultMergeImageDrawing(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);

	//system("pause");
	return 0;

}

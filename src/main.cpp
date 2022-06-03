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
    //生成字符文档 & Shingle 文档    
    GenerateArticle();    

	clock_t start, end;
	
    //matrix [6,2]
	std::vector< pairBandRadius> vecBandRadius={ pairBandRadius(2,15),pairBandRadius(3,10),
		pairBandRadius(5,6),pairBandRadius(6,5),pairBandRadius(10,3),pairBandRadius(15,2)};
	
    //存放 1000次 MinHash Value [1000,30,1000]
	std::vector<std::vector< std::vector<unsigned int> > > vecMinHash(iMinHash, std::vector< 
		std::vector<unsigned int> >(iSignNum,std::vector<unsigned int>(iDocNum,0)));
	    
	    
    //存放 Local Senstive Hash [6,1000,1000]
	std::vector<std::vector<std::vector<float> > >vecLocSensHash(vecBandRadius.size(),
		std::vector< std::vector<float>>(iLocSensHashRow,std::vector<float>(iLocSensHashColumn, 0)));

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
	 
	for (int i = 0; i < iMinHash; i++) {
        //计算 MinHash
		oMinHash.CalMinHash();
		vecMinHash[i] = oMinHash.m_vecMinHash;
        //重置 m_vecMinHash.
        oMinHash.ResetMinHash();
	}

	//Part3: LSH
	start = clock();
	for (int i = 0; i < vecBandRadius.size(); i++) {
		vecLocSensHash[i] = Locality_Sensitive_Hashing(vecMinHash,
			vecBandRadius[i].first, vecBandRadius[i].second);
	}		
	end = clock();
	cout << "Run Time of LSH: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

	/*
	Part3: Results Handling
	*/
	ResultHandling id = ResultHandling();
	id.fnImageDrawing(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);
	//id.fnResultMergeImageDrawing(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);
	id.fnResultOutput(vecBandRadius, vecLocSensHash, oMinHash.m_vecJaccard);

	return 0;

}

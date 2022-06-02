#include <iostream>
#include <random>
#include <utility>
#include <math.h>
#include "resultHandling.h"
#include "LocalSensitiveHash.h"
//#include "MinHash.h"
//#include "lsh.h"

#define iJacSimRow 1000
#define iJacSimColumn 1000
#define iLocSensHashRow 1000
#define iLocSensHashColumn 1000
#define iMinHash 1000
#define iSignNum 30
#define iDocNum 1000

int main() {
	clock_t start, end;
	/*
	[6,2]
	*/
	std::vector< pairBandRadius> vecBandRadius={ pairBandRadius(2,15),pairBandRadius(3,10),
		pairBandRadius(5,6),pairBandRadius(6,5),pairBandRadius(10,3),pairBandRadius(15,2)};
	/*
	[1000,30,1000]
	*/
	std::vector<std::vector< std::vector<unsigned int> > > vecMinHash(iMinHash, std::vector< 
		std::vector<unsigned int> >(iSignNum,std::vector<unsigned int>(iDocNum,0)));
	/*
	[1000,1000]
	*/
	std::vector< std::vector<float>> vecJacSim(iJacSimRow, 
		std::vector<float>(iJacSimColumn, 0));
	/*
	[6,1000,1000]
	*/
	std::vector<std::vector<std::vector<float> > >vecLocSensHash(vecBandRadius.size(),
		std::vector< std::vector<float>>(iLocSensHashRow,std::vector<float>(iLocSensHashColumn, 0)));

	/*
	data initialization
	*/
	float fXaxis = 0.;
	float fInterval = 1. / (1000 * 999 / 2.);
	for (int i = 0; i < iJacSimRow; i++) {
		for (int j = i; j < iJacSimColumn; j++) {
			vecJacSim[i][j] = fXaxis;
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

	/*
	Part2: min hash
	*/
	//std::vector<std::vector<std::vector<unsigned int> > > vecMinHash;
	/*
	Get 1000 signature matrix:[1000,30,1000]
	*/
	//for (int i = 0; i < iMinHash; i++) {
	//	MinHash<UINT_MAX, doc_num> oMinHash;
	//	oMinHash.CalMinHash();
	//	oMinHash.CalJaccardSimilarity();
	//	vecMinHash.push_back(oMinHash.m_vecMinHash);
	//}

	/*
	Part3: LSH
	*/
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
	id.fnImageDrawing(vecBandRadius, vecLocSensHash, vecJacSim);
	id.fnResultMergeImageDrawing(vecBandRadius, vecLocSensHash, vecJacSim);
	id.fnResultOutput(vecBandRadius, vecLocSensHash, vecJacSim);
	
	getchar();
	return 0;

}
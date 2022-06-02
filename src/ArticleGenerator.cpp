#include "ArticleGenerator.h"

int ArticleGenerator::fnRandom(int start, int end) {
	//Generation of random number
	int dis = end - start;
	return rand() % dis + start;
}

int ArticleGenerator::fnNumToAscii(int num) {
	/*
	Since the ASCII interval itself is not continuous, 
	It is processed according to the size of the random number generated here.
	*/
	if (num >= 91)
		num += 6;
	return num;
}

void ArticleGenerator::fnArticleGeneration() {

	char aArticleBuffer[500]; // The buffer contains random words of one article
	int iCount = 1; //Article number Conutor
	srand((unsigned)time(NULL));

	//Generate article_1.txt
	for (int i = 0; i < 500; i++) {
		aArticleBuffer[i] = this->fnNumToAscii(this->fnRandom(iMinIndex, iMaxIndex));
	}
	for (; iCount <= 1000; iCount++) {
		FILE* fp;
		fp = fopen((this->m_ArticleFilePath + std::to_string(iCount) + ".txt").c_str(), "w");
		if (fp == NULL) {
			std::cout << "File create error" << std::endl;
		}
		else {
			if (iCount == 1) {
			}
			else {
				/*
				Since each article is different from the previous article by only one character,
				A random number is generated as the address of the changed symbol each time it is updated. 
				The address of each change may be the same, 
				but the changed characters must be different.
				*/
				int iIndex = this->fnRandom(1, 500) - 1;  //Changed Index
				char cTemp = this->fnNumToAscii(this->fnRandom(iMinIndex, iMaxIndex));
				while (aArticleBuffer[iIndex] == cTemp) {
					cTemp = this->fnNumToAscii(this->fnRandom(iMinIndex, iMaxIndex));
				}
				aArticleBuffer[iIndex] = cTemp; //charater changed and write into article
			}
			fwrite(&aArticleBuffer, sizeof(aArticleBuffer), 1, fp);
			fclose(fp);
		}
	}
	std::cout << "File Create successfully" << std::endl;
}

void ArticleGenerator::fnShingling() {
	FILE* fp1;   //file pointer to article 
	FILE* fp2;   //file pointer to shingle
	int iCount = 1;
	for (; iCount <= 1000; iCount++) {
		fp1 = fopen((this->m_ArticleFilePath + std::to_string(iCount) + ".txt").c_str(), "r");
		//Shingles documents are bin file,each cost memeroy 493 * 32bit = 1972Kb
		fp2 = fopen((this->m_ShinglesFilePath + std::to_string(iCount) + ".bin").c_str(), "wb+");
		if (fp1 == NULL || fp2 == NULL) {
			std::cout << "File open error" << std::endl;
		}
		else {
			char aBuffer[500];
			//Read all word in article
			while (!feof(fp1)) {
				fread(aBuffer, sizeof(aBuffer), 1, fp1);
			}
			//Generate shingles
			for (int i = 0; i <= sizeof(aBuffer) - 8; i++) {
				char aTemp[8];
				for (int j = 0; j < 8; j++) {
					aTemp[j] = aBuffer[i + j];
				}
				//CRC32
				unsigned int hash_num = CRC32(aTemp, 8);
				std::bitset<32> bst(hash_num);
				//std::cout << hash_num << std::endl;
				fwrite(&hash_num, sizeof(hash_num), 1, fp2);
			}
			fclose(fp1);
			fclose(fp2);
		}
	}
	std::cout << "Shingles Generate over" << std::endl;
}

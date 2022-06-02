#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <time.h>
#include "CRC32.h"

/*
The address of English characters in ASCII code
Characters A--Z  == 65--90
Characters a--z  == 97--122 
*/
const int iMaxIndex = 122-6;
const int iMinIndex = 65;

/*
Class ArticleGenerator:
      Used to generate random articles and corresponding shinggle documents
Member Variables:
      Type:string      Name: m_ArticleFilePath;
	  Type:string      Name: m_ShinglesFilePath;
Member Functions:
      Return Type:int      Name:fnRandom
	  Return Type:int      Name:fnNumToAscii
	  Return Type:void     Name:fnArticleGeneration
	  Return Type:void     Name:fnShingling
*/
class ArticleGenerator{
public:
	std::string m_ArticleFilePath;      //The path contains articles
	std::string m_ShinglesFilePath;     //The path contains shingles

	int fnRandom(int start, int end);  
	/* 
	Generate a random integers in interval
	*/
	int fnNumToAscii(int num);
	/*
	To continuate the  range of ASCII characters
	*/
	void fnArticleGeneration();
	/*
	Generate 1000 random articles,each contains 500 words
	*/
	void fnShingling();
	/*
	Generate  corresponding shinggle documents
	*/

	ArticleGenerator(std::string artfilepath = "./Articles/article_",std::string shingfilepath= "./Shingles/shingle_") :
	    m_ArticleFilePath(artfilepath) , m_ShinglesFilePath(shingfilepath){
	}
private:

};


#pragma once
#include <iostream>
#include <vector>
#include <string>
#define SEED 31
#define Max 10050
using namespace std;

vector<vector<float> > Locality_Sensitive_Hashing(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r);
/*
considering compare the integer vector but not the concated string
*/
vector<vector<float> > Locality_Sensitive_Hashing_2(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r);
/*
considering using hashing method to convert long string to hash code
*/
vector<vector<float> > Locality_Sensitive_Hashing_3(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r);
bool fnVecComp(std::vector<unsigned int> vecRadius1, std::vector<unsigned int> vecRadius2);
int H(string s);
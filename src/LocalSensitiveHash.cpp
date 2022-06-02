#include "LocalSensitiveHash.h"


//Input: 30*1000 singnature matrix
//#Output: (999+1)/2*1000 vector of collision about the fies in order
vector<vector<float> > Locality_Sensitive_Hashing(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r) {
    int MinHashRow = m_vecMinHash[0].size();
    int MinHashCol = m_vecMinHash[0][0].size();

    /*
    change Collision to 2-d vector
    */
    vector<vector<float> > Collision(MinHashCol, std::vector<float>(MinHashCol, 0));
    vector<vector<string>> Str;
    vector<string> localstr;
    /*
    A total of 1000 signature matrix iterations
    */
    clock_t start_oneSignMatrix, end_oneSignMatrix;
    for (int iSignNum = 0; iSignNum < m_vecMinHash.size(); iSignNum++) {
        //start_oneSignMatrix = clock();
        Str.clear();
        int i, j, col = 0;
        string CombineBand = "";

        for (i = 0; i < bands; i++) {
            localstr.clear();
            for (col = 0; col < MinHashCol; col++) {
                CombineBand = "";
                for (j = 0; j < r; j++) {
                    CombineBand += to_string(m_vecMinHash[iSignNum][i * r + j][col]);
                }
                localstr.push_back(CombineBand);
            }
            Str.push_back(localstr);
        }

        int index = 0;
        int ic, jc, kc = 0;
        bool ifCollision;
        //caculate collision
        for (ic = 0; ic < MinHashCol - 1; ic++) {
            for (jc = ic + 1; jc < MinHashCol; jc++) {
                ifCollision = false;
                for (kc = 0; kc < bands; kc++) {
                    if (Str[kc][jc] == Str[kc][ic]) {
                        ifCollision = true;
                    }
                }
                if (ifCollision) {
                    Collision[ic][jc] += 1;
                }
                else {
                    Collision[ic][jc] += 0;
                }
            }
        }
        //end_oneSignMatrix = clock();
        //cout << "Run Time of LSH: " << (double)(end_oneSignMatrix - start_oneSignMatrix) / CLOCKS_PER_SEC << "s" << endl;
    }

    /*
    calculate the Collision probability
    */
    for (int ic = 0; ic < MinHashCol - 1; ic++) {
        for (int jc = ic + 1; jc < MinHashCol; jc++) {
            Collision[ic][jc] /= m_vecMinHash.size();
        }
    }
	
    return Collision;
}

/*
considering compare the integer vector but not the concated string
*/
vector<vector<float> > Locality_Sensitive_Hashing_2(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r) {
    int MinHashRow = m_vecMinHash[0].size();
    int MinHashCol = m_vecMinHash[0][0].size();

    /*
    change Collision to 2-d vector
    */
    vector<vector<float> > Collision(MinHashCol, std::vector<float>(MinHashCol, 0));
    /*
    */
    std::vector<std::vector<std::vector<unsigned int> > > vecBandRadius;
    std::vector<std::vector<unsigned int> > vecBand;
    std::vector<unsigned int> vecRadius;

    vector<vector<string>> Str;
    vector<string> localstr;
    /*
    A total of 1000 signature matrix iterations
    */
    clock_t start_oneSignMatrix, end_oneSignMatrix;
    for (int iSignNum = 0; iSignNum < m_vecMinHash.size(); iSignNum++) {
        //start_oneSignMatrix = clock();
        vecBandRadius.clear();
        Str.clear();
        int i, j, col = 0;
        string CombineBand = "";

        for (i = 0; i < bands; i++) {
            localstr.clear();
            vecBand.clear();
            for (col = 0; col < MinHashCol; col++) {
                vecRadius.clear();
                CombineBand = "";
                for (j = 0; j < r; j++) {
                    //CombineBand += to_string(m_vecMinHash[iSignNum][i * r + j][col]);
                    vecRadius.push_back(m_vecMinHash[iSignNum][i * r + j][col]);
                }
                localstr.push_back(CombineBand);
                vecBand.push_back(vecRadius);
            }
            Str.push_back(localstr);
            vecBandRadius.push_back(vecBand);
        }

        int index = 0;
        int ic, jc, kc = 0;
        bool ifCollision;
        //caculate collision
        for (ic = 0; ic < MinHashCol - 1; ic++) {
            for (jc = ic + 1; jc < MinHashCol; jc++) {
                ifCollision = false;
                for (kc = 0; kc < bands; kc++) {
                    if (fnVecComp(vecBandRadius[kc][jc],vecBandRadius[kc][ic])) {
                        ifCollision = true;
                    }
                }
                if (ifCollision) {
                    Collision[ic][jc] += 1;
                }
                else {
                    Collision[ic][jc] += 0;
                }
            }
        }
        //end_oneSignMatrix = clock();
        //cout << "Run Time of LSH: " << (double)(end_oneSignMatrix - start_oneSignMatrix) / CLOCKS_PER_SEC << "s" << endl;
    }

    /*
    calculate the Collision probability
    */
    for (int ic = 0; ic < MinHashCol - 1; ic++) {
        for (int jc = ic + 1; jc < MinHashCol; jc++) {
            Collision[ic][jc] /= m_vecMinHash.size();
        }
    }

    return Collision;
}

bool fnVecComp(std::vector<unsigned int> vecRadius1, std::vector<unsigned int> vecRadius2) {
    bool flgVecEql = true;
    for (int i = 0; i < vecRadius1.size(); i++) {
        if (vecRadius1[i] != vecRadius2[i]) {
            flgVecEql = false;
            break;
        }
    }
    return flgVecEql;
}

/*
considering using hashing method to convert long string to hash code
*/
vector<vector<float> > Locality_Sensitive_Hashing_3(std::vector<std::vector<std::vector<unsigned int> > > m_vecMinHash, int bands, int r) {
    int MinHashRow = m_vecMinHash[0].size();
    int MinHashCol = m_vecMinHash[0][0].size();

    /*
    change Collision to 2-d vector
    */
    vector<vector<float> > Collision(MinHashCol, std::vector<float>(MinHashCol, 0));
    vector<vector<string>> Str;
    vector<string> localstr;
    /*
    A total of 1000 signature matrix iterations
    */
    clock_t start_oneSignMatrix, end_oneSignMatrix;
    for (int iSignNum = 0; iSignNum < m_vecMinHash.size(); iSignNum++) {
        start_oneSignMatrix = clock();
        Str.clear();
        int i, j, col = 0;
        string CombineBand = "";

        for (i = 0; i < bands; i++) {
            localstr.clear();
            for (col = 0; col < MinHashCol; col++) {
                CombineBand = "";
                for (j = 0; j < r; j++) {
                    CombineBand += to_string(H(to_string(m_vecMinHash[iSignNum][i * r + j][col]))% Max);
                }
                localstr.push_back(CombineBand);
            }
            Str.push_back(localstr);
        }

        int index = 0;
        int ic, jc, kc = 0;
        bool ifCollision;
        //caculate collision
        for (ic = 0; ic < MinHashCol - 1; ic++) {
            for (jc = ic + 1; jc < MinHashCol; jc++) {
                ifCollision = false;
                for (kc = 0; kc < bands; kc++) {
                    if (Str[kc][jc] == Str[kc][ic]) {
                        ifCollision = true;
                    }
                }
                if (ifCollision) {
                    Collision[ic][jc] += 1;
                }
                else {
                    Collision[ic][jc] += 0;
                }
            }
        }
        end_oneSignMatrix = clock();
        cout << "Run Time of LSH: " << (double)(end_oneSignMatrix - start_oneSignMatrix) / CLOCKS_PER_SEC << "s" << endl;
    }

    /*
    calculate the Collision probability
    */
    for (int ic = 0; ic < MinHashCol - 1; ic++) {
        for (int jc = ic + 1; jc < MinHashCol; jc++) {
            Collision[ic][jc] /= m_vecMinHash.size();
        }
    }

    return Collision;
}

int H(string s) {
    int key = 0;
    for (int i = 0; i < s.size(); i++) {
        key = key * SEED + s[i];
    }
    return key & 0x7ffffff;
}
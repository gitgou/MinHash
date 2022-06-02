#pragma once
#include<iostream>
#include<vector>

typedef std::pair<int, int> pairBandRadius;
/*
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
*/
class ResultHandling{
public:
	/*
	:param:
		vecBandRaduis: the pairs of Band and Raduis.
		vecLocSensHash: the LSH matrix to save Experimental Collision Probability of every two
			document.
		vecJacSim: the jaccard similarity of every two document.
	:function:
		output Theoretical Collision Probability, Jaccard Similarity and Experimental Collision
			Probability in every two documents of different pairs of Band and Raduis.
	:output:
		null
	*/
	void fnResultOutput(std::vector< pairBandRadius> vecBandRaduis, std::vector<std::vector<
		std::vector<float> > > vecLocSensHash, std::vector< std::vector<float>> vecJacSim);
	/*
	:param:
		vecBandRaduis: the pairs of Band and Raduis.
		vecLocSensHash: the LSH matrix to save Experimental Collision Probability of every two
			document.
		vecJacSim: the jaccard similarity of every two document.
	:function:
		Draw legends of relationship of jaccard similarity in x-axis and Experimental Collision
			Probability in y-axis in different pairs of Band and Raduis.
	:output:
		null
	*/
	void fnImageDrawing(std::vector< pairBandRadius> vecBandRaduis, std::vector<std::vector<
		std::vector<float> > >vecLocSensHash, std::vector< std::vector<float>> vecJacSim);
	/*
	:param:
		vecBandRaduis: the pairs of Band and Raduis.
		vecLocSensHash: the LSH matrix to save Experimental Collision Probability of every two
			document.
		vecJacSim: the jaccard similarity of every two document.
	:function:
		Draw the merged legend of relationship of jaccard similarity in x-axis and Experimental
		Collision Probability in y-axis in different pairs of Band and Raduis.
	:output:
		null
	*/
	void fnResultMergeImageDrawing(std::vector< pairBandRadius> vecBandRaduis, std::vector<
		std::vector<std::vector<float> > > vecLocSensHash, std::vector< std::vector<float>> 
		vecJacSim);
	ResultHandling();
	~ResultHandling();
};

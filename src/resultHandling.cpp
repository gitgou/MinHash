#include "resultHandling.h"
#include "matplotlibcpp.h"
#include <string>
#include <cmath>
namespace plt = matplotlibcpp;

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
void ResultHandling::fnImageDrawing(std::vector< pairBandRadius> vecBandRaduis, 
	std::vector<std::vector<std::vector<float> > >vecLocSensHash, std::vector< std::vector<float>>
	vecJacSim) {
	/*
	capture the size of the vectors
	*/
	int iJacSimRow = vecJacSim.size();
	int iJacSimColumn = vecJacSim[0].size();

	int iRow = iJacSimRow;
	int jiolumn = iJacSimColumn;
	
	/*
	instantiate vector of x-axis and y-axis to draw the legends
	*/
	std::vector<float> vecJacSimXaxis;
	std::vector<float> vecExpCollProbYaxis;
	std::vector<float> vecTheoCollProbYaxis;

	/*
	Clear previous plot
	*/
	//plt::clf();
	/*
	Set figure size
	*/
	plt::figure_size(1500, 900);

	/*
	For different pairs of Band and Raduis.
	*/
	for (int k = 0; k < vecBandRaduis.size(); k++) {
		/*
		Data initialization
		*/
		float fTheoYaxis = 0.;
		vecJacSimXaxis.clear();
		vecExpCollProbYaxis.clear();
		vecTheoCollProbYaxis.clear();
		/*
		get data of x-axis and y-axis
		*/
		for (int i = 0; i < iJacSimRow; i++) {
			//for (int j = i; j < iJacSimColumn; j++) {
				int j = 0;
				/*
				get Jaccard Similarity
				*/
				vecJacSimXaxis.push_back(vecJacSim[i][j]);
				/*
				get Experimental Collision Probability
				*/
				vecExpCollProbYaxis.push_back(vecLocSensHash[k][i][j]);
				/*
				get Theoretical Collision Probability
				*/
				fTheoYaxis = 1 - pow(1 - pow(vecJacSim[i][j], vecBandRaduis[k].second), 
					vecBandRaduis[k].first);
				vecTheoCollProbYaxis.push_back(fTheoYaxis);
			//}
		}

		/*
		Set canvas
		*/
		plt::subplot(2, 3, k + 1);
		/*
		* Plot a line whose name will show up as "Experimental" in the legend.
		*/
		plt::scatter("r",vecJacSimXaxis, vecExpCollProbYaxis, 35);
		//plt::named_plot("Experimental",vecJacSimXaxis, vecExpCollProbYaxis);
		//plt::plot(vecJacSimXaxis, vecExpCollProbYaxis);
		/*
		* Plot a line whose name will show up as "Theoretical" in the legend.
		*/
		plt::named_plot("Theoretical", "g",vecJacSimXaxis, vecTheoCollProbYaxis);
		//plt::plot(vecJacSimXaxis, vecTheoCollProbYaxis);
		/*
		* Set x-axis to interval [0,1]
		*/
		plt::xlim(0, 1);
		/*
		* Add graph title
		*/
		plt::title("Result:b=" + std::to_string(vecBandRaduis[k].first) + std::string(",r=") + 
			std::to_string(vecBandRaduis[k].second));
		/*
		Enable legend.
		*/
		plt::legend();
		/*
		Show xlabeland ylabel
		*/
		plt::xlabel("Jaccard Similarity");
		plt::ylabel("Experimental Collision Probability");
	}

	/*
	Master Title
	*/
	plt::suptitle("Min-Hash Results Curves");
	/*
	Show Image
	*/
	plt::show();
}

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
void ResultHandling::fnResultOutput(std::vector< pairBandRadius> vecBandRaduis, 
	std::vector<std::vector< std::vector<float> > >
	vecLocSensHash, std::vector< std::vector<float>> vecJacSim) {
	/*
	capture the size of the vectors
	*/
	int iJacSimRow = vecJacSim.size();
	int iJacSimColumn = vecJacSim[0].size();

	int iRow = iJacSimRow;
	int jiolumn = iJacSimColumn;

	/*
	For different pairs of Band and Raduis.
	*/
	for (int k = 0; k < vecBandRaduis.size(); k++) {
		float fTheoYaxis = 0.;
		std::cout << "Result:b=" + std::to_string(vecBandRaduis[k].first) + std::string(",r=") + 
			std::to_string(vecBandRaduis[k].second) << std::endl;
		for (int i = 0; i < iJacSimRow; i++) {
			//for (int j = i + 1; j < iJacSimColumn; j++) {
				int j = 0;
				fTheoYaxis = 1 - pow(1 - pow(vecJacSim[i][j], vecBandRaduis[k].second),
					vecBandRaduis[k].first);
				std::cout << "(" << i << "," << j << "):" << "Theoretical Collision Probability:" 
					<< fTheoYaxis << "\tJaccard Similarity:" << vecJacSim[i][j]
					<< "\tExperimental Collision Probability:" << vecLocSensHash[k][i][j] 
					<< std::endl;
			//}
		}
	}
}

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
void ResultHandling::fnResultMergeImageDrawing(std::vector< pairBandRadius> vecBandRaduis, 
	std::vector<std::vector<std::vector<float> > > vecLocSensHash, std::vector< std::vector
	<float> > vecJacSim) {
	/*
	capture the size of the vectors
	*/
	int iJacSimRow = vecJacSim.size();
	int iJacSimColumn = vecJacSim[0].size();
	int iLocSensHashRow = vecLocSensHash.size();
	int iLocSensHashColumn = vecLocSensHash[0].size();

	int iRow = iJacSimRow;
	int jiolumn = iJacSimColumn;

	/*
	instantiate vector of x-axis and y-axis to draw the legends
	*/
	std::vector<float> vecJacSimXaxis;
	std::vector<float> vecExpCollProbYaxis;
	std::vector<float> vecTheoCollProbYaxis;

	/*
	Clear previous plot
	*/
	plt::clf();

	/*
	For different pairs of Band and Raduis.
	*/
	for (int k = 0; k < vecBandRaduis.size(); k++) {
		/*
		Data initialization
		*/
		float fTheoYaxis = 0.;
		vecJacSimXaxis.clear();
		vecExpCollProbYaxis.clear();
		vecTheoCollProbYaxis.clear();
		/*
		get data of x-axis and y-axis
		*/
		for (int i = 0; i < iJacSimRow; i++) {
			//for (int j = i; j < iJacSimColumn; j++) {
				int j = 0;
				/*
				get Jaccard Similarity
				*/
				vecJacSimXaxis.push_back(vecJacSim[i][j]);
				/*
				get Experimental Collision Probability
				*/
				vecExpCollProbYaxis.push_back(vecLocSensHash[k][i][j]);
				/*
				get Theoretical Collision Probability
				*/
				fTheoYaxis = 1 - pow(1 - pow(vecJacSim[i][j], vecBandRaduis[k].second),
					vecBandRaduis[k].first);
				vecTheoCollProbYaxis.push_back(fTheoYaxis);
			//}
		}

		/*
		Plot a line whose name will show up as "Experimental" in the legend.
		*/
		plt::scatter(vecJacSimXaxis, vecExpCollProbYaxis, 35);
		/*
		Plot a line whose name will show up as "Theoretical" in the legend.
		*/
		plt::named_plot("b=" + std::to_string(vecBandRaduis[k].first) + std::string(",r=") +
			std::to_string(vecBandRaduis[k].second), vecJacSimXaxis, vecTheoCollProbYaxis);
	}

	/*
	Set x - axis to interval[0, 1]
	*/
	plt::xlim(0., 1.);
	/*
	Add graph title
	*/
	plt::title("Results");
	/*
	Enable legend.
	*/
	plt::legend();
	/*
	Show xlabel and ylabel
	*/
	plt::xlabel("Jaccard Similarity");
	plt::ylabel("Experimental Collision Probability");
	/*
	Show Image
	*/
	plt::show();
}

ResultHandling::ResultHandling() {

}
ResultHandling::~ResultHandling() {

}
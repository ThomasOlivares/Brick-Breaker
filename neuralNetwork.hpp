#pragma once

#include <vector>
#include <string>

class NeuralNetwork{
	
	public :
		NeuralNetwork(int nbLayers_, std::vector<int> neuronPerLayer_);
		NeuralNetwork(int nbLayers_, std::vector<int> neuronPerLayer_, 
			std::vector<std::vector<std::vector<double> > > weight_);
		NeuralNetwork(int nbLayers_, std::vector<int> neuronPerLayer_, 
			char* pathname);
		void initStructure();
		double getPoids(int numLayer, int i, int j);
		void setPoids(int numTheta, int i, int j, double modif);
		void setImput(std::vector<double> tab);
		void initPoids();
		void initPoids(std::vector<std::vector<std::vector<double> > > weight_);
		void computeLayers();
		std::vector<double> output();
		void afficherPoids();
		int getNbNeurons(int num);
		void sauvegarde(std::string name);

	protected :
		int nbLayers;
		std::vector<int> neuronPerLayer;

		std::vector<std::vector<double> > couches;
		std::vector<std::vector<std::vector<double> > > weight;
};

double sigmoid(double z);

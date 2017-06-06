#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include "neuralNetwork.hpp"

using namespace std;

NeuralNetwork::NeuralNetwork(int nbLayers_, vector<int> neuronPerLayer_) 
: nbLayers(nbLayers_)
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(neuronPerLayer_[i]);
	}
	initStructure();
	initPoids();
}

NeuralNetwork::NeuralNetwork(int nbLayers_, vector<int> neuronPerLayer_, 
		vector<vector<vector<double> > > weight_) 
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(neuronPerLayer_[i]);
	}
	initStructure();
	initPoids(weight_);
}

NeuralNetwork::NeuralNetwork(int nbLayers_, vector<int> neuronPerLayer_, 
		char* pathname)
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(neuronPerLayer_[i]);
	}
	initStructure();
	FILE* f = fopen(pathname, "r");
	for (int i = 0; i < nbLayers-1; i++){
		fread(&(weight[i]), sizeof(double)*neuronPerLayer[i]*neuronPerLayer[i+1], 1, f);
	}
	fclose(f);
}

double NeuralNetwork::getPoids(int numLayer, int i, int j){
	return weight[numLayer][i][j];
}

void NeuralNetwork::setPoids(int numTheta, int i, int j, double modif){
	weight[numTheta][i][j] = modif;
}

void NeuralNetwork::initStructure(){
	for(int i = 0; i<nbLayers; i++){
		int nbNeurons = neuronPerLayer[i];
		vector<double> couche;
		for (int j = 0; j<nbNeurons; j++){
			couche.push_back(0);
		}

		// We push the constant neuron, except for the output layer
		if (i != nbLayers - 1){
			couche.push_back(1); // Constant neuron
		}
		
		couches.push_back(couche);
	}	
}
/* Initialisation of the input layer using the data from the game
*/
void NeuralNetwork::setImput(vector<double> tab){
	for (int i = 0; i<tab.size(); i++){
		couches[0][i] = tab[i];
	}
	couches[0].push_back(1);
}

/* Random initialisation of all the weight of the neural network
*/
void NeuralNetwork::initPoids(){
	for (int numCouche = 0; numCouche < nbLayers - 1; numCouche++){
		// Here we have all the weight beetween two layers
		vector<vector<double> > theta;
		for(int i = 0; i<neuronPerLayer[numCouche]; i++){
			// Here we have all the weight of the connexions send by one neural
			vector<double> neuralWeight;
			for (int j = 0; j < neuronPerLayer[numCouche+1]; j++){
				neuralWeight.push_back((double)(rand()%10000)/10000);
			}
			theta.push_back(neuralWeight);
		}
		weight.push_back(theta);
	}
}

/* Initialisation of the weight of the neural network using the data in argument
*/
void NeuralNetwork::initPoids(vector<vector<vector<double> > > weight_){
	weight = weight_;
}

/* We calculate all the values of neurons using the fisrt layer and the weight
*/
void NeuralNetwork::computeLayers(){
	// We begin at 1 because layer 0 is already completed
	for (int numLayer = 1; numLayer<nbLayers; numLayer++){
		vector<double> previous = couches[couches.size()-1];

		// If we are not on the last layer we don't compute the last neural (constant)
		int max;
		if (numLayer == nbLayers-1){
			max = neuronPerLayer[numLayer];
		}
		else{
			max = neuronPerLayer[numLayer]-1;
		}

		for (int i = 0; i<max; i++){
			double value = 0;  //value of one neuron
			for (int j = 0; j<neuronPerLayer[numLayer-1]; j++){
				value += (double)((previous)[j]) * weight[numLayer-1][j][i];
			}
			value = sigmoid(value);
			couches[numLayer][i] = value;
		}
	}
}

/* Return the last layer (output layer)
*/
vector<double> NeuralNetwork::output(){
	return couches[nbLayers-1];
}

void NeuralNetwork::afficherPoids(){
	for (int numLayer = 0; numLayer<weight.size(); numLayer++){
		cout << "theta : " << numLayer << endl;
		for (int i= 0; i<neuronPerLayer[numLayer]; i++){
			for (int j = 0 ; j<neuronPerLayer[numLayer+1]; j++){
				cout << weight[numLayer][i][j] << " / ";
			}
		}
	cout << endl;
	}
}

int NeuralNetwork::getNbNeurons(int num){
	return neuronPerLayer[num];
}

void NeuralNetwork::sauvegarde(string name){
	FILE* f = fopen(name.c_str(), "w");
	fwrite(&nbLayers, sizeof(int), 1, f);
	for (int numLayer; numLayer < nbLayers; numLayer++){
		fwrite(&(neuronPerLayer[numLayer]), sizeof(int), 1, f);
	}
	for (int numLayer = 0; numLayer<weight.size(); numLayer++){
		for (int i= 0; i<neuronPerLayer[numLayer]; i++){
			for (int j = 0 ; j<neuronPerLayer[numLayer+1]; j++){
				fwrite(&(weight[numLayer][i][j]), sizeof(double), 1, f);
			}
		}
	}
	fclose(f);
}


double sigmoid(double z){
	return 1/(1+exp(-z));
}

/********************************************
 * 
 *  NeuralNetwork.h
 * 
 *  neural network class
 * 
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

#include "Layer.h"
#include "NeuronLayer.h"

class NeuralNetwork
{
    public:
        NeuralNetwork(int input_size, int output_size)
            : _input_size(input_size),
              _output_size(output_size)
              {}
              
        void printInfo()
        {
            std::cout << "Input size: " << _input_size << std::endl;

            std::cout << "Output size: " << _output_size << std::endl;
        }

        void addLayer(Layer * new_layer, int position);
        void generateLayer(layer_t layer_type, int input_count = -1, int output_count = -1,
                           int node_count = -1, int position = -1);

        const Layer * getLayer(int layer);
    protected:
        int _input_size;
        int _output_size;
        std::vector<Layer> _layers;

    private:
};

#endif
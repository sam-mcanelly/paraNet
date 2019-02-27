/********************************************
 * 
 *  NeuronLayer.h
 * 
 *  Classic fully connected layer
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include <assert.h>
#include <iostream>
#include <vector>

#include "Distribution.h"
#include "Layer.h"
#include "Types.h"

class NeuronLayer: public Layer
{
    public:
        NeuronLayer() { Layer(); }
        NeuronLayer(int input_length, int neuron_count, layer_t activation=_relu,
                    distrib_t distribution = _normal, 
                    float mean = 0.0f, float stdev = 1.0f
                    );
        ~NeuronLayer();

        void setInput(float const* input, int new_input_length);

        void printParams(); // input, output, weights, biases
        void printNeuronInfo(int neuron); // weights, biases

        float * getWeights();
        void printWeights();    

        float * getBiases();
        void printBiases();

        void printInfo();

        #ifdef __NO_OPEN_CL__
            void compute();
            void sumNeuron(int neuron);
            void softmax(std::vector<float> output_vec);
        #endif

    private:
        std::vector<float> _weights; //flattened weights representation
        std::vector<float> _biases;

        Activation _activation;

        void resizeWeights(int neuron_count, int input_length);
        void generateWeightsAndBiases(distrib_t distribution, float mean, float var2);
};

#endif
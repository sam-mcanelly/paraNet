/********************************************
 * 
 *  NeuronLayer.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include <vector>

#include "Layer.h"
#include "Types.h"

class NeuronLayer: public Layer
{
    public:
        void setInput(float* input);

    private:
        activation_t _activation;
        std::vector<float*> * _weights; //each row is a neuron
        float*  _biases;

        void initWeights(int neuron_count, int input_length, 
                          distrib_t distribution,
                          float mean, float var2);
        void deleteWeights();
};

#endif
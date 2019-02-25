/********************************************
 * 
 *  NeuronLayer.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include <assert.h>
#include <vector>

#include "Distribution.h"
#include "Layer.h"
#include "Types.h"

class NeuronLayer: public Layer
{
    public:
        NeuronLayer(int neuron_count, int input_length,
                    distrib_t distribution = _normal, 
                    float mean = 0.0f, float stdev = 1.0f);
        ~NeuronLayer();

        void setInput(float* input, int new_input_length);

    private:
        std::vector<std::vector<float>> _weights; //each row is a neuron
        std::vector<float> _biases;

        void initWeights(int neuron_count, int input_length);
        void generateRandomWB(distrib_t distribution, float mean, float var2);
};

#endif
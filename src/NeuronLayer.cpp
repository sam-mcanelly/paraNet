/********************************************
 * 
 *  NeuronLayer.cpp
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#include "NeuronLayer.h"

/********************
 * Public functions
 * *****************/
NeuronLayer::NeuronLayer(int neuron_count, int input_length,
                              distrib_t distribution = _normal, 
                              float mean, float stdev)
{
    assert(neuron_count > 0); 
    
    _biases.resize(neuron_count);

    initWeights(neuron_count, input_length);
    generateRandomWB(distribution, mean, stdev);

    _input_size = input_length;
    _node_count = neuron_count;
}

NeuronLayer::~NeuronLayer()
{
    
}


/********************
 * Private functions
 * *****************/
void NeuronLayer::initWeights(int neuron_count, int input_length)
{
    _weights.resize(neuron_count);
    for(int i = 0; i < neuron_count; i++)
    {
        _weights[i].resize(input_length);
    }
}

//generating random weights will be done on the cpu because it only has to be done once
void NeuronLayer::generateRandomWB(distrib_t distribution, float mean, float var2)
{
    Distribution dist(distribution, mean, var2);

    for(int i = 0; i < _node_count; i++)
    {
        _biases[i] = dist.generate();

        for(int j = 0; j < _input_size; j++)
        {
            _weights[i][j] = dist.generate();
        }
    }   
}


//TODO: Implement dynamic expansion of the weights array
void NeuronLayer::setInput(float* input, int new_input_length)
{
    assert(new_input_length == _input_size);

    _in = input;
    _input_size = new_input_length;
}



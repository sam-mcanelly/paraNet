/********************************************
 * 
 *  NeuronLayer.cpp
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#include "NeuronLayer.h"

//Utility function



/********************
 * Public functions
 * *****************/
NeuronLayer::NeuronLayer(int neuron_count, int input_length,
                              distrib_t distribution, 
                              float mean, float stdev)
{
    assert(neuron_count > 0); 
    
    _biases.resize(neuron_count);

    resizeWeights(neuron_count, input_length);
    generateWeightsAndBiases(distribution, mean, stdev);

    _input_size = input_length;
    _node_count = neuron_count;
}

NeuronLayer::~NeuronLayer()
{
    
}

float * NeuronLayer::getWeights()
{
    return _weights.data();
}

void NeuronLayer::printWeights()
{
    std::cout << "{ ";
    for(int i = 0; i < _weights.size(); i++)
    {
        std::cout << _weights[i] << ", ";
        

    }
}

float * NeuronLayer::getBiases()
{
    return _biases.data();
}


/********************
 * Private functions
 * *****************/
void NeuronLayer::resizeWeights(int neuron_count, int input_length)
{
    _weights.resize(neuron_count * input_length);
}

//generating random weights will be done on the cpu because it only has to be done once
void NeuronLayer::generateWeightsAndBiases(distrib_t distribution, float mean, float var2)
{
    Distribution dist(distribution, mean, var2);

    for(int i = 0; i < _biases.size(); i++)
    {
        _biases[i] = dist.generate();
    }   

    for(int i = 0; i < _weights.size(); i++)
    {
        _weights[i] = dist.generate();
    } 
}

//TODO: Implement dynamic expansion of the weights array
void NeuronLayer::setInput(float* input, int new_input_length)
{
    assert(new_input_length == _input_size);

    _in = input;
    _input_size = new_input_length;
}



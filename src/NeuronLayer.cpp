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
void NeuronLayer::NeuronLayer(int neuron_count, int input_length,
                              distrib_t distribution = _normal, 
                              float mean = 0.0, float stdev = 1.0,
                              activation_t activation = _relu)
{
    assert(neuron_count > 0); 
    
    initWeights(neuron_count, input_length, distribution, mean, stdev);
    _biases = new float[neuron_count];
    _input_count = input_length;
    _node_count = neuron_count;
    _activation = activation;
}

void NeuronLayer::~NeuronLayer()
{
    delete _biases[];
    deleteWeights();
}


/********************
 * Private functions
 * *****************/
void NeuronLayer::initWeights(int neuron_count, int input_length, 
                               distrib_t distribution, 
                               float mean, float var2)
{
    std::default_random_engine generator;

    switch(distribution)
    {
        case _uniform:
            std::uniform_real_distribution<float> distribution(mean, var2); //stdev used for width
            break;
        case _normal:
            std::normal_distribution<float> distribution(mean, var2);
            break;
        case _log_normal:
            std::lognormal_distribution<float> distribution(mean, var2);
            break;
        case _binomial:
            std::binomial_distribution<float> distribution(mean, var2);
            break;
        default:
            std::normal_distribution<float> distribution(0.0, 1.0);
    }

    weights = new std::vector<float*>(neuron_count);

    for(int i = 0; i < neuron_count; i++)
    {
        if(NULL != _weights[i]) delete _weights[i];
        _weights[i] = new float[input_length];

        for(int j = 0; j < input_length; j++)
        {
            _weights[i][j] = distribution(generator);
        }
    }   
}

void NeuronLayer::deleteWeights()
{
    for(int i = 0; i < _weights.size(); i++)
    {
        delete _weights[i];
    }

    delete _weights;
}

void NeuronLayer::setInput(float* input)
{
    _input = input;
}



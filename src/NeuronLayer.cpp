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
                              distrib_t distribution, 
                              float mean, float stdev,
                              layer_t activation)
{
    Layer();
    assert(neuron_count > 0); 
    _type = _neuron;

    _biases.resize(neuron_count);

    resizeWeights(neuron_count, input_length);
    generateWeightsAndBiases(distribution, mean, stdev);

    _input_size = input_length;
    _node_count = neuron_count;
    _out.resize(_node_count);
}

NeuronLayer::~NeuronLayer()
{
    
}

//TODO: Implement dynamic expansion of the weights array
void NeuronLayer::setInput(float const* input, int new_input_length)
{
    assert(new_input_length == _input_size);

    _in = input;
    _input_size = new_input_length;
}

void NeuronLayer::printNeuronInfo(int neuron)
{
    int start_idx = neuron * _input_size;
    std::cout << "Weight count: " << _input_size << std::endl;
    std::cout << "Weights: {" << std::endl;

    for(int i = start_idx; i < start_idx + _input_size; i++)
    {
        std::cout << _weights[i] << ",";
    }
    std::cout << "\n}" << "\n\n";

    std::cout << "Bias: {" << _biases[neuron] << "}" << std::endl;
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
        if(i % _node_count == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << "} " << "\n\n";
} 

float * NeuronLayer::getBiases()
{
    return _biases.data();
}

void NeuronLayer::printInfo()
{
    Layer::printInfo();
    std::cout << "Input size: " << _input_size << std::endl;
    std::cout << "Node count(and output size): " << _node_count << std::endl;

    std::cout << "Number of weight parameters: " << _weights.size() << std::endl;
    std::cout << "Number of bias parameters (Node count): " << _biases.size() << std::endl;
}

#ifdef __NO_OPEN_CL__
    void NeuronLayer::compute()
    {
        assert(_input != NULL);
        
        int i = 0;
        int localcounter = 0;
        float currentBias = 0.0f;

        std::cout << "Summing neurons" << std::endl;

        // Sum of Wx + b
        for(int i = 0; i < _node_count; i++)
        {
            std::cout << "Summing neuron: " << i << std::endl;
            sumNeuron(i);
        }

        std::cout << "Activating neurons" << std::endl;
        _activation.activate(_out.data(), _out.size(), _node_count);
        std::cout << "Compute finished" << std::endl;
    }

    void NeuronLayer::sumNeuron(int neuron)
    {
        _out[neuron] = 0.0f;
        int start_idx = neuron * _input_size;

        for(int i = start_idx; i < start_idx + _input_size; i++)
        {
            _out[neuron] += _weights[i] * _in[i - start_idx] + _biases[neuron];
        }
    }
#endif


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



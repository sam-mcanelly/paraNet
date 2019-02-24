/********************************************
 * 
 *  NeuronLayer.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Layer.h"
#include "Types.h"

template <size_t S>
class NeuronLayer: public Layer<S, float>
{
    public:
        NeuronLayer(int input_length, distrib_t distribution = _normal)
        {

        }
    private:
        Neuron[S] neurons;
        float*[S] weights;
};

#endif
/********************************************
 * 
 *  Neuron.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NEURON_H
#define NEURON_H

#include <random>

template <size_t S>
class Neuron {
    public:
        Neuron(){}

        void setWeights(const float* new_weights);
        const float * getWeights();

        void setBias(float bias);
        float getBias();
    private:
        int _io_size;
        const float* _input;

        float* _weights;
        float _bias;
};

#endif
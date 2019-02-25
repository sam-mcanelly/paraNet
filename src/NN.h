/********************************************
 * 
 *  NN.h
 * 
 *  Abstract neural network class
 * 
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef NN_H
#define NN_H

#include <vector>

#include "Layer.h"

class NN
{
    public:
        NN(int input_size, int output_size)
            : _input_size(input_size),
              _output_size(output_size)
              {}

        void addLayer();
    protected:
        int _input_size;
        int _output_size;
        std::vector<Layer> _layers;

    private:
};

#endif
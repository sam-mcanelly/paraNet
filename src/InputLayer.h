/********************************************
 * 
 *  InputLayer.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#include "Layer.h"

template <size_t S>
class InputLayer: public Layer<S, float>
{
    public:
        InputLayer(int io_length, float* input = NULL) 
        {
            _io_length = io_length;
            if(NULL != input)
            {
                _input = input
            }

            _output=_input;
        }

    private:
        const float* _output;
};

#endif
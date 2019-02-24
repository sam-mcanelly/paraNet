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
#include "Types.h"

class InputLayer: public Layer
{
    public:
        InputLayer(int io_length, float* input = NULL) 
        {
            _input_count, _node_count = io_length;
            _input = input; 
            _output=_input;
        }

    private:
};

#endif
/********************************************
 * 
 *  Layer.h
 * 
 *  Abstract class definition for layers of 
 *  the neural network
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef LAYER_H
#define LAYER_H

#include "Types.h"

class Layer {
    public:
        Layer() : _node_count(0), _input_count(0)
        {
            _type = _unknown; 
        }
        ~Layer() 
        {

        }

        virtual void setInput(float* input) = 0;

        int size() { return _node_count; }
        layer_t type() { return _type; }

        const float* getOutput() { return _output; }
        const float* getInput() { return _input; }

        int inputSize() { return _input_count; }

    protected:
        layer_t _type;
        int _node_count;
        int _input_count;
        float* _input;
        float* _output;

        void setType(layer_t type) { _type = type; }

    private:
};

#endif
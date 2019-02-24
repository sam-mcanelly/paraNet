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

#include "Neuron.h"

template <size_t S, typename T>
class Layer {
    public:
        Layer(int io_length = 0) : _io_length(io_length)
        {
            input = NULL;
            _type = _unknown; 
        }
        ~Layer() 
        {

        }

        virtual void setInput(T* new_input) = 0;

        int size() { return _io_length; }
        layer_t type() { return _type; }

    protected:
        void setType(layer_t type) { _type = type; }

    private:
        layer_t _type;
        int _io_length;

        T* input;
};

#endif
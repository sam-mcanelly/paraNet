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

#include <assert.h>
#include <fstream>

#include "Types.h"

class Layer {
    public:
        int size() { return _node_count; }
        layer_t type() { return _type; }

        virtual void setNext(Layer * new_next)
        {
            //TODO: make this assert unnecessary
            //update layers to fit mismatched inputs
            assert(new_next->getInputLength() == _node_count);
            
            _next = new_next;
            _next->setInput(_out, _node_count);
        }
        virtual void setPrev(Layer * new_prev)
        {
            if(_type == _input) return;

            //See TODO in setNext
            assert(new_prev->getOutputLength() == _input_size);

            _prev = new_prev;
            setInput(_prev->getOutput(), _prev->getOutputLength());
        }

        virtual float const* const getOutput() { return _out; }
        int getOutputLength() { return size(); }

        virtual void setInput(float const* input, int new_input_size)
        {
            assert(new_input_size == _input_size);

            _input_size = new_input_size;
            _in = input;
        }
        const float* getInput() { return _in; }
        int getInputLength() { return 0; }

    protected:
        Layer * _prev;
        Layer * _next;
        layer_t _type;
        int _node_count;
        int _input_size;
        float const * _in;
        float * _out;

        void setType(layer_t type) { _type = type; }

    private:
};

/*************************
 * 
 * Trivial layers that don't need their own header
 * 
 * **********************/

class BasicInputLayer: public Layer
{
    public:
        BasicInputLayer(int io_length, float* input = null) 
        {
            _prev = null;
            _input_size, _node_count = io_length;
            _in = input; 
            _out = _in;
        }

    private:
        float const* _out;
};

class ActivationLayer: public Layer
{  
    public:
        ActivationLayer(layer_t type)
        {
            assert(type == _relu 
                    || type == _tanh
                    || type == _sigmoid);
            
            setType(type);
            
            loadKernelCode();
        }
    private:

        void loadKernelCode()
        {
            std::ifstream file(clKernelPrefix + clKernels[_type]);
            assert(file.is_open());
            std::string kernel(
                std::istreambuf_iterator<char>(file),
                (std::istreambuf_iterator<char>()));
        }
        
};

#endif
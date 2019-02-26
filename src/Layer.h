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
#include <iostream>
#include <fstream>
#include <vector>

#include "Types.h"

#ifdef __NO_OPEN_CL__
    #include <cmath>
#endif

class Layer {
    public:
        Layer()
        {
            _prev = null;
            _next = null;
        }
        int size() { return _node_count; }
        layer_t type() { return _type; }

        virtual void setNext(Layer * new_next)
        {
            //TODO: make this assert unnecessary
            //update layers to fit mismatched inputs
            assert(new_next->getInputLength() == _node_count);
            
            _next = new_next;
            _next->setInput(_out.data(), _node_count);
        }
        virtual void setPrev(Layer * new_prev)
        {
            if(_type == _input) return;

            //See TODO in setNext
            assert(new_prev->getOutputLength() == _input_size);

            _prev = new_prev;
            setInput(_prev->getOutput(), _prev->getOutputLength());
        }

        virtual float const* const getOutput() { return _out.data(); }
        int getOutputLength() { return size(); }

        virtual void setInput(float const* input, int new_input_size)
        {
            //std::cout << "Input size: " << _input_size << "New input size: " << new_input_size << std::endl;
            assert(new_input_size == _input_size);

            _input_size = new_input_size;
            _in = input;
        }
        float const* getInput() { return _in; }
        int getInputLength() { return _input_size; }

        //TODO - refactor this for JSON output
        virtual void printInfo()
        {
            std::cout << "Layer type: " << layerNames[_type] << std::endl;
        }

    protected:
        Layer * _prev;
        Layer * _next;
        layer_t _type;
        int _node_count;
        int _input_size;
        float const * _in;
        std::vector<float> _out;

        static const std::string layerNames[];

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
        BasicInputLayer(int io_length) 
        {
            Layer();
            _input_size = io_length;
            _node_count = _input_size;
            _in = null;
            _type = _input;
        }

        float const* const getOutput()
        { 
            return _out;
        }

        void setInput(float const* input, int new_input_size)
        {
            //std::cout << "Input size: " << _input_size << "New input size: " << new_input_size << std::endl;
            assert(new_input_size == _input_size);

            _input_size = new_input_size;
            _in = input;
            _out = _in;
        }

        //TODO - refactor for JSON output
        void printInfo()
        {
            Layer::printInfo();
            std::cout << "Input/Output size: " << _node_count << std::endl;
        }

    private:
        float const* _out;

        
};

class Activation
{  
    public:
        Activation() { _type = _relu; }
        Activation(layer_t type)
        {
            assert(type == _relu 
                    || type == _tanh
                    || type == _sigmoid);
            
            _type = type;
            
            //loadKernelCode();
        }


        std::string getKernelCode() { return kernel_code; }

        #ifdef __NO_OPEN_CL__
            void activate(float *input, int input_count, int output_count)
            {
                assert(input_count == output_count);
                switch(_type)
                {
                    case _relu:
                        for(int i = 0; i < input_count; i++)
                        {
                            input[i] = std::max(0.0f, input[i]);
                        }
                        break;
                    case _tanh:
                        for(int i = 0; i < input_count; i++)
                        {
                            input[i] = tanh(input[i]);
                        }
                        break;
                    case _sigmoid:
                        for(int i = 0; i < input_count; i++)
                        {
                            input[i] = sigmoid(input[i]);
                        }
                        break;
                }
            }
        #endif
    private:
        int _output_size;
        layer_t _type;
        std::string kernel_code;
        void loadKernelCode()
        {
            std::ifstream file(clKernelPrefix + clKernels[_type]);
            assert(file.is_open());
            kernel_code = std::string(
                std::istreambuf_iterator<char>(file),
                (std::istreambuf_iterator<char>()));
        }

        #ifdef __NO_OPEN_CL__
            float sigmoid(float input)
            {
                return input / (1 + abs((double)(input)));
            }
        #endif
        
};

#endif
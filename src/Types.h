/********************************************
 * 
 *  Types.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef TYPES_H
#define TYPES_H

#define null nullptr
#define __NO_OPEN_CL__

#include <string>

enum distrib_t 
{
    _uniform,
    _normal,
    _log_normal,
    _binomial
};

enum loss_function_t
{
    _mean_squared,
    _mean_squared_log,
    _absolute_mean,
    _abssolute_percentage,
    _cross_entropy,
};

enum layer_t
{
    /*weighted sum and reduction layers*/
    _conv2d,
    _batch_norm2d,
    _max_pool,
    _neuron,

    /*activation layers*/
    _relu,
    _sigmoid,
    _tanh,

    /*final layers*/
    _softmax,
    _argmax,

    /*io*/
    _input
};

const std::string clKernelPrefix = "../kernel/";
//mapped to enum layer_t
const std::string clKernels[] = {"conv2d.cl", "batch_norm2d.cl",
                           "max_pool.cl", "neuron.cl",
                           "relu.cl", "sigmoid.cl", "tanh.cl", 
                           "softmax.cl", "argmax.cl"};

#endif


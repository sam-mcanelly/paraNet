/********************************************
 * 
 *  Types.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef TYPES_H
#define TYPES_H

#define NULL nullptr

enum distrib_t 
{
    _uniform,
    _normal,
    _log_normal,
    _binomial
};

enum layer_t
{
    _input,
    _conv2d,
    _max_pool,
    _neuron,
    _unknown
};

enum activation_t 
{
    _relu,
    _sigmoid,
    _tanh,
};

#endif


/********************************************
 * 
 *  Types.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef TYPES_H
#define TYPES_H

enum distrib_t {
    _uniform,
    _normal,
    _log_normal,
    _binomial
};

enum layer_t {
    _input,
    _conv,
    _max_pool,
    _activation,
    _unknown
};

#endif


/********************************************
 * 
 *  Distribution.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <random>

#include "Types.h"

class Distribution
{
    public:
        Distribution(distrib_t distribution, float mean, float var2) 
        {
            _type = distribution;

            switch(distribution)
            {
                case _uniform:
                    uni = new std::uniform_real_distribution<float>(mean, var2); //stdev used for width
                    break;
                case _normal:
                    normal = new std::normal_distribution<float>(mean, var2);
                    break;
                case _log_normal:
                    log_normal = new std::lognormal_distribution<float>(mean, var2);
                    break;
                case _binomial:
                    binomial = new std::binomial_distribution<>(mean, var2);
                    break;
            }
        }  

        ~Distribution()
        {   
            switch(_type)
            {
                case _uniform:
                    delete uni;
                    break;
                case _normal:
                    delete normal;
                    break;
                case _log_normal:
                    delete log_normal;
                    break;
                case _binomial:
                    delete binomial;
                    break;
            }
        }

        float generate()
        {
            switch(_type)
            {
                case _uniform:
                    return (float)(*uni)(generator);
                case _normal:
                    return (float)(*normal)(generator);
                case _log_normal:
                    return (float)(*log_normal)(generator);
                case _binomial:
                    return (float)(*binomial)(generator);
                default:
                    return -1.0f;
            }
        }

    private:
        //std::random_device rd;
        std::default_random_engine generator;

        std::uniform_real_distribution<float> * uni;
        std::normal_distribution<float> * normal;
        std::lognormal_distribution<float> * log_normal;
        std::binomial_distribution<> * binomial;

        distrib_t _type;

};

#endif
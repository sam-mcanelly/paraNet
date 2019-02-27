/********************************************
 * 
 *  GradientDescentTrainer.h
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef GRADIENTDESCENTTRAINER_H
#define GRADIENTDESCENTTRAINER_H

#include <math.h>

#include "Layer.h"
#include "NeuralNetwork.h"
#include "TrainingInput.h"
#include "Types.h"


class GradientDescentTrainer
{
    public:
        GradientDescentTrainer()
        {
            _training_rate = 0.01f;
        }
    private:
        void (GradientDescentTrainer::*_compute_loss)(void);
        NeuralNetwork *_network;

        float _training_rate;
        int _batch_size;

        loss_function_t _loss_function;

        const float *_net_output;
        const float *_expected_values;

        bp_out_t backprop(Layer *layer);

        // binary cross entropy
        float bce()
        {
            float sum = 0.0f;
            //hard coded to 10 for mnist test
            for(int i = 0; i < 10; i++)
            {
                sum += 
                _expected_values[i]*log(_net_output[i]) + (1.0f - _expected_values[i])*log(1-_net_output[i]);
            }

            //change to neuralnet.getoutputsize
            sum *= (-1.0f/10);

            return sum;
        }

        float testError(float expected, float actual)
        {
            return (expected - actual) * sigmoid_d(actual);
        }

        float sigmoid(float in)
        {
            return 1.0 / (1 + exp(-in));
        }

        //sigmoid derivative
        float sigmoid_d(float in)
        {
            return sigmoid(in) * (1.0f - sigmoid(in));
        }

};

#endif


//backprop
//dz2 = output[n] - Y
//dw2 = (1/m)*dz*output[n-1]
//db2 = (1/m)*sum(dz2)
//dz1 = w2T*dz2 _*_ act'*z1

// dz - a - y_actual     -> for logistic regression cost fuction
// dw_1 = x_1dz
// w_1 := w_1 - alpha * dw_1
/********************************************
 * 
 *  TrainingInput.h
 * 
 *  Class to hold data that will be used for 
 *  training the neural network
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef TRAINIGINPUT_H
#define TRAININGINPUT_H

template <typename X, typename Y>
class TrainingInput
{
    public:
        TrainingInput() {}
    private:
        std::vector<X> x;
        std::vector<Y> y;

};

#endif
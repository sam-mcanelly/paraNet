/********************************************
 * 
 *  Session.h
 * 
 *  Session object for running forwards and 
 *  backwards passes on the neural network
 *  objects
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef SESSION_H
#define SESSION_H

#include "../extlibs/include/CLBlast/include/clblast.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "InputBuffer.h"
#include "NeuralNetwork.h"
#include "Types.h"

class Session
{
    public:
        Session(bool configure = false);

        NeuralNetwork * getNN() { return _nn; }
        void setNN(NeuralNetwork * nn) { _nn = nn; }

        void configureOpenCL();
        void run();

    private:
        std::vector<cl_platform_id> _platforms;
        cl_platform_id _chosen_platform;
        cl_uint _num_platforms;

        std::vector<cl_uint> _devices_per_platform;
        std::vector<std::vector<cl_device_id>> _platform_devices;

        cl_context _context;
        cl_command_queue _queue;

        cl_int _cl_status;
        size_t work_units_per_kernel, program_size, log_size;

        std::vector<cl_mem> network_buffers;

        NeuralNetwork * _nn;
        InputBuffer _input_buffer;

        void countPlatforms();
        void loadPlatformIDs();
        void loadPlatformDevices();
        void createContext();
        void createCommandQueue();

        void printStatus(cl_int const* status);
        std::string getCLStatusName(cl_int const* status);


};

#endif
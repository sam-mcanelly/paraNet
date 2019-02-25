/********************************************
 * 
 *  Session.cpp
 * 
 *  Session object for running forwards and 
 *  backwards passes on the neural network
 *  objects
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#include "Session.h"

/********************
 * Public functions
 * *****************/

Session::Session(bool configure)
{
    if(configure)
    {
        configureOpenCL();
    }
}

void Session::configureOpenCL()
{
    countPlatforms();
    loadPlatformIDs();
    loadPlatformDevices();
}

/********************
 * Private functions
 * *****************/

void Session::countPlatforms()
{
    std::cout << "\n\n" << "Platforms" << std::endl;
    std::cout << "---------------------" << std::endl;
    _cl_status = clGetPlatformIDs(0, NULL, &_num_platforms);
    std::cout << "Number of available platforms: " << _num_platforms << std::endl;
    printStatus(&_cl_status);
}

void Session::loadPlatformIDs()
{
    std::cout << "Platforms IDs" << std::endl;
    std::cout << "-----------------------" << std::endl;
    _platforms.resize(_num_platforms);
    _cl_status = clGetPlatformIDs(_num_platforms, _platforms.data(), NULL);
    for(int i = 0; i < _num_platforms; i++)
    {
        std::cout << "Platform[" << i << "] ID: " << _platforms[i] << std::endl;
    }
    printStatus(&_cl_status);
}

void Session::loadPlatformDevices()
{
    _devices_per_platform.resize(_num_platforms);
    _platform_devices.resize(_num_platforms);
    cl_uint _num_devices = 0;

    for(int i = 0; i < _num_platforms; i++)
    {
        std::cout << "Devices for Platform [" << _platforms.at(i) << "]" << std::endl;
        std::cout << "-----------------------" << std::endl;
        
        _cl_status = clGetDeviceIDs(_platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &_num_devices);
        std::cout << "Devices on this platform: " << _num_devices << std::endl;
        _devices_per_platform[i] = _num_devices;
        std::vector<cl_device_id> new_ids(_num_devices);

        _cl_status = clGetDeviceIDs(_platforms[i], CL_DEVICE_TYPE_ALL, _num_devices, new_ids.data(), NULL);
        _platform_devices[i] = new_ids;
        for(int j = 0; j < _num_devices; j++)
        {
            std::cout << "Device[" << j << "] ID: " << _platform_devices[i][j] << std::endl;
        }
        printStatus(&_cl_status);
    }
}

//TODO - refactor
void Session::createContext()
{
    std::cout << "Creating Context" << std::endl;
    std::cout << "-----------------------" << std::endl;
    //context = clCreateContext(NULL, num_devices, device_list.data(), NULL, NULL, &cl_status);
    std::cout << "Context: " << _context << std::endl;
    printStatus(&_cl_status);

}

//TODO - refactor
void Session::createCommandQueue()
{
    std::cout << "Creating Command Queue" << std::endl;
    std::cout << "-----------------------" << std::endl;
    //queue = clCreateCommandQueueWithProperties(context, device_list[0], NULL, &cl_status);
    //cl_event event = cl_event{nullptr};
}

void Session::printStatus(cl_int const* status)
{
    std::cout << "Status: " << getCLStatusName(status) << std::endl;
    std::cout << "\n\n";
}

std::string Session::getCLStatusName(cl_int const* status)
{
    switch(*status)
    {
        case CL_SUCCESS:
            return "Success";
        case CL_INVALID_VALUE:
            return "Invalid Value";
        case CL_OUT_OF_HOST_MEMORY:
            return "Host out of Memory";
        case CL_PLATFORM_NOT_FOUND_KHR:
            "khr enabled and no platforms found";
        default:
            return "uknown status";
    }
}
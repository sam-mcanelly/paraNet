/********************************************
 * 
 *  MnistLoader.h
 * 
 *  Loads the MNIST dataset from a file
 *  in the current directory
 * 
 *  TODO - check if images exist and download if not
 * 
 *  Author - Sam McAnelly
 * 
 *********************************************/

#ifndef MNISTLOADER_H
#define MNISTLOADER_H

class MnistLoader
{
    public:
        MnistLoader() {}


    private:
        static const int MAGIC_OFFSET = 0;
        static const int OFFSET_SIZE = 4; //in bytes

        static const int LABEL_MAGIC = 2049;
        static const int IMAGE_MAGIC = 2051;

        static const int NUMBER_ITEMS_OFFSET = 4;
        static const int ITEMS_SIZE = 4;

        static const int NUMBER_OF_ROWS_OFFSET = 8;
        static const int ROWS_SIZE = 4;
        static const int ROWS = 28;

        static const int NUMBER_OF_COLUMNS_OFFSET = 12;
        static const int COLUMNS_SIZE = 4;
        static const int COLUMNS = 28;

        static const int IMAGE_OFFSET = 16;
        static const int IMAGE_SIZE = ROWS * COLUMNS;
};

#endif
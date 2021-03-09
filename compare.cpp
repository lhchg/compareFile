/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//@file compare.cpp
//@brief Use for compare two input files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>

enum Flag{
    INVILAD = 1,
    SAME_FILE,
    DIFFERENT_FILE,
    MAX_FLAG
};

/*
 *readDataFile
 *
 * @beief Read content from raw file
 *
 * @param fileName     path for raw file
 * @param input        buffer for raw file
 * @param input_size   buffer size size for input file
 *
 * @return Whether the file is read successed
 *
 */
template<class T>
bool readDataFile(const std::string fileName, T* input, size_t input_size)
{
	std::ifstream in(fileName, std::ifstream::binary);
	if (!in.is_open() || !in.good())
	{
		printf("File open failed for %s\n", fileName.c_str());
		return false;
	}

	if (!in.read((char*)input, input_size))
	{
		printf("Failed to read content for %s\n", fileName.c_str());
		return false;
	}
	return true;
}

/*
 *getFileSize
 *
 * @brief   calculate size for input file
 *
 * @param   file  file name for input file
 *
 * @reutrn  size for input file
 *
 */
size_t getFileSize(const std::string file)
{
    std::ifstream in(file, std::ifstream::binary); 
    if (!in.is_open() || !in.good()) {
        printf("input open failed for %s\n", file.c_str());
        return 0;
    }

    in.seekg(0, in.end);
    size_t length = in.tellg();
    in.seekg(0, in.beg);
    return length;

}

/*
 *compareFile
 *
 *@brief Wompare whether the two input file is the same
 *
 *@param buffer1      buffer for one input file 
 *@param buffer2      buffer for another input file
 *@param buffer_size  compare size between two input file 
 *
 *@return Whether the two input file is the same
 *
 */
bool compareFile(void* buffer1, void* buffer2, size_t buffer_size)
{
	for (unsigned int i = 0; i < buffer_size; i++)
	{
            uint8_t u1 = *((uint8_t*)buffer1 + i);
            uint8_t u2 = *((uint8_t*)buffer2 + i);
            
            if (u1 != u2)
            {
            	return false;
            }
	 }
         return true;
}


int main(int argc, char** argv)
{
	size_t buf_size1, buf_size2;
	void* inputFile1;
	void* inputFile2;
	
	if(argc != 3)
	{
	    printf("input was wrong, need two arguments\n");
	    return -1;
	}
	std::string file1 = argv[1];
	std::string file2 = argv[2];

	//read file1
	buf_size1 = getFileSize(file1);
	if(buf_size1 == 0)
	{
	    printf("File %s size get error\n", argv[1]);
	    return -1;
	}
	inputFile1 = malloc(buf_size1);
	if (inputFile1 == nullptr)
	{
	    printf("buffer for file %s malloc failed\n", argv[1]);
	    return -1;
	}
	if(!readDataFile(file1, inputFile1, buf_size1))
	{
	    return -1;
	}

	//read file2
	buf_size2 = getFileSize(file2);
	if(buf_size2 == 0)
	{
	    printf("File %s size get error\n", argv[2]);
	    return -1;
	}
	inputFile2 = malloc(buf_size2);
	if (inputFile2 == nullptr)
	{
	    printf("buffer for file %s malloc failed\n", argv[2]);
	    return -1;
	}
        if(!readDataFile(file2, inputFile2, buf_size2))
	{
	    return -1;
	}

	//compare two file, buf_size depending on the smaller file
	if (compareFile(inputFile1, inputFile2, ((buf_size1 <= buf_size2 ) ? buf_size1 : buf_size2)))
	{
	    //the two file is the same
	    return SAME_FILE;
	}
	else
	{
	    //the two file is different
	    return DIFFERENT_FILE;
	}

	return 0;
}

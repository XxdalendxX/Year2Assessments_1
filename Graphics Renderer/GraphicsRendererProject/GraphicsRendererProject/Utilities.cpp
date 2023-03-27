#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(std::string filename)
{
    std::stringstream fileSoFar;
    std::ifstream file(filename);

    //Will check if the file exists in the working folder of the project and can be opened.
    if (file.is_open())
    {
        //Checks to see if the end of the file has been reached.
        while (!file.eof())
        {
            //reads the line and collects it
            std::string thisLine;
            std::getline(file, thisLine);
            fileSoFar << thisLine << std::endl;
        }
        //returns string of all lines in the file
        std::cout << "Successfully loaded file: " << filename << std::endl;
        return fileSoFar.str();
    }
    else
    {
        //returns the string stating that the file was not found.
        std::cout << "Error loading file: " << filename << std::endl;
        return "";
    }
}

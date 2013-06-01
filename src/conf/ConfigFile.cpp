/*
 * ConfigFile.cpp
 *
 *  Created on: 18/ott/2012
 *      Author: Administrator
 */

#include "ConfigFile.h"


ConfigFile::ConfigFile() {



}



ConfigFile::~ConfigFile() {


}



void ConfigFile::load(std::string fileName)
{
	std::ifstream* ifs = new std::ifstream(const_cast<char*>(fileName.c_str()));

	std::string line, key, value;

	while(!ifs->eof())
	{
		getline(*ifs,line);

		if (!line.empty())
		{
			std::istringstream iss(line);

			iss >> key;
			iss >> value;
			std::pair<std::string, std::string> param (key, value);
			this->_confParameters.insert(param);

		}
	}

	ifs->close();
}




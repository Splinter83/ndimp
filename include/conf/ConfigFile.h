/*
 * ConfigFile.h
 *
 *  Created on: 18/ott/2012
 *      Author: Administrator
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include <sstream>
#include <fstream>
#include <string>
#include <map>

enum ConversionType
{
	hexadecimal,
	octal,
	decimal,
	none
};

class ConfigFile {
public:
	ConfigFile();
	virtual ~ConfigFile();
	void load(std::string fileName);
	template <typename T> T getParameter(const std::string& key, ConversionType type) const;


private:
	std::map<std::string, std::string> _confParameters;
};

template <typename T>
T ConfigFile::getParameter(const std::string& key, ConversionType type) const
{

	std::string tmp;
	T param;

	tmp = this->_confParameters.find(key)->second;

	std::stringstream ss;
	ss << tmp;

	switch(type)
	{
		case hexadecimal:
			ss >> std::hex;
			break;
		case octal:
			ss >> std::oct;
			break;
		case decimal:
			ss >> std::dec;
			break;
		case none:
		default:
			break;
	}

	ss >> param;

	return param;
}

#endif /* CONFIGFILE_H_ */

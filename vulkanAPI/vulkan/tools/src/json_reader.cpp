#include "pch.h"
#include "tools\include\json_reader.h"

#include <nlohmann/json.hpp>
#include <fstream>

JsonReader::JsonReader() = default;

JsonReader::JsonReader(const std::filesystem::path& json)
{
	_file.open(json); 
	if (!_file.is_open())
	{
		std::cerr << "Failed to open file: " << json << std::endl;
	}

	_path = json; 

	try
	{
		_file >> _json;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to parse json file: " << e.what() << std::endl;
	}
}

nlohmann::json::iterator JsonReader::begin()
{
	return _json.begin();
}

nlohmann::json::iterator JsonReader::end()
{
	return _json.end();
}


JsonReader::~JsonReader()
{
	_file.close(); 
}
#include "stdafx.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <map>
#include <regex>

std::map<std::string, std::string> parse(const std::string val) {
	std::map<std::string, std::string> retval;
	std::regex pattern("([\\w+%]+)=([^&]*)");

	auto begin = std::sregex_iterator(val.begin(), val.end(), pattern);
	auto end = std::sregex_iterator();

	for (std::sregex_iterator i = begin; i != end; i++) {
		std::string key = (*i)[1].str();
		std::string value = (*i)[2].str();
		retval[key] = value;
	}
	return retval;
}

void main(int argc, char* argv[])
{

	std::string reqmethod = getenv("REQUEST_METHOD");
	std::string q_string = getenv("QUERY_STRING");
	std::string postInputString;

	std::map<std::string, std::string> gtParams;

	if (reqmethod == "GET") // GET zahtev
	{
		if (!q_string.empty())
			gtParams = parse(q_string);
	}

	int result = 0;

	if (gtParams["op"] == "add") {
		result = stoi(gtParams["br1"]) + stoi(gtParams["br2"]);
	}
	else if (gtParams["op"] == "sbb") {
		result = stoi(gtParams["br1"]) - stoi(gtParams["br2"]);
	}
	else if (gtParams["op"] == "mul") {
		result = stoi(gtParams["br1"]) * stoi(gtParams["br2"]);
	}

	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<title>File Upload in CGI</title>\n";
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	std::cout << "<p>Your numbers are: <br>1) " << stoi(gtParams["br1"]) << " <br>2) " << stoi(gtParams["br2"]) << " <br>Operation is " << gtParams["op"];
	std::cout << "</p>\n";
	std::cout << "<p>Your result is " << result;
	std::cout << "</p>\n</body>\n";
	std::cout << "</html>\n";
}

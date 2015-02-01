//
//  File.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 5/9/14.
//  Copyright (c) 2014 Andreia Gaita. All rights reserved.
//

#include "File.h"

#include <iostream>
#include <fstream>

std::string File::ExecDir;
char File::PathSeparator;

void File::SetExecDir(const char* path) {
	std::string::size_type n;
	std::string s(path);
	PathSeparator = '/';
	n = s.rfind(PathSeparator);
	if (n == std::string::npos) {
		PathSeparator = '\\';
		n = s.rfind(PathSeparator);
	}
	if (n < s.length())
		ExecDir = s.substr(0, s.length());
	//if (n == std::string::npos)
		//ExecDir = std::move(s);
	else
		ExecDir = s.substr(0, n);
}

std::string File::Read(const char* const filename) {
	auto t = ExecDir + PathSeparator + filename;
	//std::ifstream file(ExecDir + PathSeparator + filename);
	std::ifstream file(t.c_str());
	if (file) {
		// get length of file:
		file.seekg(0, file.end);
		auto length = file.tellg();
		file.seekg(0, file.beg);

		std::string str;
		str.resize(length, ' '); // reserve space
		char* begin = &*str.begin();

		file.read(begin, length);
		file.close();
		
		return str;
	}
	return std::string();
}

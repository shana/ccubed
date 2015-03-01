//
//  File.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 5/9/14.
//  Copyright (c) 2014 Andreia Gaita. All rights reserved.
//

#ifndef __FILE_H__
#define __FILE_H__

#include <string>

class File {
public:
	static std::string Read(const char* const filename);

	static void SetExecDir(const char* path);
    
    static std::string GetExecDir() { return ExecDir; }
private:
	static std::string ExecDir;
	static char PathSeparator;
};

#endif /* defined(__FILE_H__) */

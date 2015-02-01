//
//  UrlParser.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 2/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__UrlParser__
#define __ccubed_sample__UrlParser__

#include <string>

class Url {
public:
	std::string GetPath() { return path; }
	void SetPath(const std::string p) { path = p; }
	std::string GetFile() { return file; }
	void SetFile(const std::string f) { file = f; }


private:
	std::string path;
	std::string file;
};

class UrlParser {
public:
	static Url* ParseUrl(std::string url) {
		std::string::size_type hostidx, pathidx, fileidx;
		
		hostidx = url.find("://");
		std::string scheme = url.substr(0, hostidx);
		hostidx+=3;
		pathidx = url.find('/', hostidx);
		std::string host = url.substr(hostidx, pathidx-hostidx);
		++pathidx;
		std::string path = url.substr(pathidx);
		std::string file;
		fileidx = url.rfind('/');
		if (fileidx > pathidx) {
			path = url.substr(pathidx, fileidx-pathidx);
			++fileidx;
			file = url.substr(fileidx);
		} else {
			file = path;
			path = "";
		}
		Url* u = new Url();
		u->SetPath(path);
		u->SetFile(file);
		return u;
	}
};

#endif /* defined(__ccubed_sample__UrlParser__) */

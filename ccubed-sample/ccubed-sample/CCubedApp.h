//
//  CCubedApp.h
//  ccubed-sample
//
//  Created by Shawn White on 31/01/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__CCubedApp__
#define __ccubed_sample__CCubedApp__

#include <include/cef_app.h>
#include <include/cef_application_mac.h>

#include "CCubedCefApp.h"

class CCubedApp {
public:
    CCubedApp() : app(new CCubedCefApp()) {}
    
    void Initialize(int argc, char* argv[]);
    bool Run();
    void Shutdown();
    
    CefRefPtr<CCubedCefApp> GetCef() { return app; }
private:
    CefRefPtr<CCubedCefApp> app;
};


#endif /* defined(__ccubed_sample__CCubedApp__) */

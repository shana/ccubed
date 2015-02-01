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

class CCubedApp : public CefApp,
                  public CefBrowserProcessHandler {
public:
    CCubedApp();
    
    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
    OVERRIDE { return this; }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

	virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) OVERRIDE;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CCubedApp);
};

#endif /* defined(__ccubed_sample__CCubedApp__) */

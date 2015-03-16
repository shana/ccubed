//
//  CCubedApp.h
//  ccubed-sample
//
//  Created by Shawn White on 31/01/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__CCubedCefApp__
#define __ccubed_sample__CCubedCefApp__

#include <include/cef_app.h>
#include <include/cef_application_mac.h>
#include <include/cef_v8.h>

#include <set>

#include "JSBridge.h"

class CCubedCefApp : public CefApp,
                     public CefBrowserProcessHandler,
                     public CefRenderProcessHandler
{
public:
    
    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
        return this;
    }
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {
        return this;
    }


    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;
    virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) OVERRIDE;
    virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) OVERRIDE;
    virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

    virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) OVERRIDE;

private:

CefRefPtr<JSBridge> bridge;

// Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(CCubedCefApp);
};


#endif /* defined(__ccubed_sample__CCubedCefApp__) */

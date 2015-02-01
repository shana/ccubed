//
//  CCubedApp.cpp
//  ccubed-sample
//
//  Created by Shawn White on 31/01/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CCubedApp.h"

#include "CallbackHandler.h"
#include "File.h"

#include <include/cef_browser.h>
#include <include/cef_command_line.h>

CCubedApp::CCubedApp() {
}

void CCubedApp::OnContextInitialized() {
    // Information used when creating the native window.
    CefWindowInfo window_info;
    
#if defined(OS_WIN)
    // On Windows we need to specify certain flags that will be passed to
    // CreateWindowEx().
    window_info.SetAsPopup(NULL, "CCubed Sample");
#endif
    
    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<CallbackHandler> handler(new CallbackHandler());
    
    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;
	
    std::string url;
    
    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    CefRefPtr<CefCommandLine> command_line =
    CefCommandLine::GetGlobalCommandLine();
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "client://ccubed/index.html";
    
    // Create the first browser window.
    CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url,
                                      browser_settings, NULL);
}

void
CCubedApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
	// Default schemes that support cookies.
	registrar->AddCustomScheme("client", true, false, false);
}

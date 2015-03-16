//
//  CCubedCefApp.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 3/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CCubedCefApp.h"

#include "CallbackHandler.h"
#include "File.h"

#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/cef_v8.h>


void CCubedCefApp::OnContextInitialized() {
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
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                      browser_settings, NULL);
}

void
CCubedCefApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
    // Default schemes that support cookies.
    registrar->AddCustomScheme("client", true, false, false);
}

void
CCubedCefApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) {
    int a = 0;
    a++;
}

void
CCubedCefApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {
    int a = 0;
    a++;
}

void
CCubedCefApp::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) {
    
    if (!bridge)
        bridge = new JSBridge();
    
    std::string js = File::Read("test.js");
    
    
    CefRegisterExtension("extensionTest",
                         js,
                         bridge);
}
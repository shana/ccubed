//
//  CCubedCefApp.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 3/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CCubedCefApp.h"

#include "CallbackHandler.h"
#include "Utils/File.h"

#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/cef_v8.h>
#include <include/wrapper/cef_helpers.h>


void CCubedCefApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();

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
    
    std::string url = "client://ccubed/index.html";
    
    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                      browser_settings, NULL);
}

void
CCubedCefApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) {
	CEF_REQUIRE_RENDERER_THREAD();
}

void
CCubedCefApp::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) {
	CEF_REQUIRE_RENDERER_THREAD();
}

void
CCubedCefApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
	// Default schemes that support cookies.
	registrar->AddCustomScheme("client", true, false, false);
}

void
CCubedCefApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {
    int a = 0;
    a++;
}

void
CCubedCefApp::OnWebKitInitialized() {
	CEF_REQUIRE_RENDERER_THREAD();

	if (!bridge)
		bridge = new JSBridge();

	std::string js = File::Read("test.js");


	CefRegisterExtension("extensionTest", js, bridge);
}

//
//  CallbackHandler.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CallbackHandler.h"
#include <cef_app.h>
#include <wrapper/cef_closure_task.h>
#include <wrapper/cef_helpers.h>
#include <base/cef_bind.h>

namespace {

CallbackHandler* g_instance = NULL;
    
}

CallbackHandler::CallbackHandler()
{
    g_instance = this;
}

CallbackHandler::~CallbackHandler()
{
    g_instance = NULL;
}

CallbackHandler* CallbackHandler::GetInstance() {
    return g_instance;
}

void
CallbackHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title)
{
	CEF_REQUIRE_UI_THREAD();
}

void
CallbackHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	m_Browser = browser;
}

void
CallbackHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
    m_Browser = NULL;

    // Quit the application message loop.
    CefQuitMessageLoop();
}

// CefLoadHandler methods:
void
CallbackHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	// Display a load error message.
	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		  "<h2>Failed to load URL " << std::string(failedUrl) <<
		  " with error " << std::string(errorText) << " (" << errorCode <<
		  ").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

bool
CallbackHandler::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();

	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
}

void
CallbackHandler::Close()
{
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI,
			base::Bind(&CallbackHandler::Close, this));
		return;
	}

	m_Browser->GetHost()->CloseBrowser(false);
}

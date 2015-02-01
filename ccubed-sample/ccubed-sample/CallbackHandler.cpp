//
//  CallbackHandler.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CallbackHandler.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"

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
}

void
CallbackHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	m_Browser = browser;
}

void
CallbackHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
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

void
CallbackHandler::Close()
{
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI, NewCefRunnableMethod(this, &CallbackHandler::Close));
		return;
	}

	if (m_Browser != NULL)
		return;

	m_Browser->GetHost()->CloseBrowser(true);
}

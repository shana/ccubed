//
//  CallbackHandler.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CallbackHandler.h"

CallbackHandler::CallbackHandler()
{
}

CallbackHandler::~CallbackHandler()
{
}

void
CallbackHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title)
{
}

void
CallbackHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
}

bool
CallbackHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	return true;
}

void
CallbackHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
}

// CefLoadHandler methods:
void
CallbackHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl)

{
}

//
//  RequestHandler.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 2/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "RequestHandler.h"

#include <include/wrapper/cef_helpers.h>

CefRefPtr<CefResourceHandler>
ClientSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
									const CefString& scheme_name, CefRefPtr<CefRequest> request)
{
    CEF_REQUIRE_IO_THREAD();
    return new ClientSchemeHandler();
}



bool
ClientSchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
{
    CEF_REQUIRE_IO_THREAD();

	bool handled = false;

	data_ = "<html><head><title>Client Scheme Handler</title></head>"
			"<body bgcolor=\"white\">"
			"This contents of this page page are served by the "
			"ClientSchemeHandler class handling the client:// protocol."
			"</body>"
			"</html>";

	handled = true;

    if (handled) {
      // Indicate the headers are available.
      callback->Continue();
      return true;
    }

	return false;
}

void
ClientSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
										int64& response_length,
										CefString& redirectUrl)
{
	CEF_REQUIRE_IO_THREAD();
	
	response->SetMimeType("text/html");
	response->SetStatus(200);
	response_length = data_.length();
}

void
ClientSchemeHandler::Cancel()
{
	CEF_REQUIRE_IO_THREAD();
}

bool
ClientSchemeHandler::ReadResponse(void* data_out,
					int bytes_to_read,
					int& bytes_read,
					CefRefPtr<CefCallback> callback)
{
	CEF_REQUIRE_IO_THREAD();
	
	bool has_data = false;
	bytes_read = 0;
	
	if (offset_ < data_.length()) {
		int transfer_size = std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
		memcpy(data_out, data_.c_str() + offset_, transfer_size);
		offset_ += transfer_size;
		bytes_read = transfer_size;
		has_data = true;
	}
	return has_data;
}
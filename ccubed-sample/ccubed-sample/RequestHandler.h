//
//  RequestHandler.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 2/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__RequestHandler__
#define __ccubed_sample__RequestHandler__

#include <include/cef_base.h>
#include <include/cef_scheme.h>

// Implementation of the factory for for creating schema handlers.
class ClientSchemeHandlerFactory : public CefSchemeHandlerFactory {
public:
	// Return a new scheme handler instance to handle the request.
	virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
												CefRefPtr<CefFrame> frame,
												const CefString& scheme_name,
												CefRefPtr<CefRequest> request)
												OVERRIDE;

	IMPLEMENT_REFCOUNTING(ClientSchemeHandlerFactory);
};


class ClientSchemeHandler : public CefResourceHandler {

public:
	virtual bool ProcessRequest(CefRefPtr<CefRequest> request,
								CefRefPtr<CefCallback> callback)
								OVERRIDE;

	virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
									int64& response_length,
									CefString& redirectUrl) OVERRIDE;
	void Cancel() OVERRIDE;

	bool ReadResponse(void* data_out,
					int bytes_to_read,
					int& bytes_read,
					CefRefPtr<CefCallback> callback) OVERRIDE;


private:
	std::string data_;
	size_t offset_;


	IMPLEMENT_REFCOUNTING(ClientSchemeHandler);
};

#endif /* defined(__ccubed_sample__RequestHandler__) */

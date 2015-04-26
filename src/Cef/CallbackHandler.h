//
//  CallbackHandler.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__CallbackHandler__
#define __ccubed_sample__CallbackHandler__

#include <cef_client.h>

class CallbackHandler : public CefClient,
                        public CefDisplayHandler,
                        public CefLifeSpanHandler,
                        public CefLoadHandler {
public:
    CallbackHandler();
    ~CallbackHandler();

    // Provide access to the single global instance of this object.
    static CallbackHandler* GetInstance();
 
    // CefClient methods:
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
        return this;
    }
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
        return this;
    }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
        return this;
    }

    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) OVERRIDE;

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
                             const CefString& failedUrl) OVERRIDE;

    void Close();

private:
    CefRefPtr<CefBrowser> m_Browser;

    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CallbackHandler);
};

#endif /* defined(__ccubed_sample__CallbackHandler__) */

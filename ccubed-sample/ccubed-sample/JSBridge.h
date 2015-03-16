//
//  JSBridge.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 3/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#ifndef __ccubed_sample__JSBridge__
#define __ccubed_sample__JSBridge__

#include <stdio.h>
#include <include/cef_v8.h>

class JSBridge : public CefV8Handler
{
public:
    
    virtual bool Execute(const CefString& name,
                         CefRefPtr<CefV8Value> object,
                         const CefV8ValueList& arguments,
                         CefRefPtr<CefV8Value>& retval,
                         CefString& exception) OVERRIDE;
    
private:
    IMPLEMENT_REFCOUNTING(JSBridge);
};


#endif /* defined(__ccubed_sample__JSBridge__) */

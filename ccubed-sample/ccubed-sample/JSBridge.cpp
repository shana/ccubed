//
//  JSBridge.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 3/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "JSBridge.h"
#include "File.h"
#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>

bool
JSBridge::Execute(const CefString& name,
                  CefRefPtr<CefV8Value> object,
                  const CefV8ValueList& arguments,
                  CefRefPtr<CefV8Value>& retval,
                  CefString& exception)
{
    
    std::string dll = File::GetExecDir() + "/Managed/test.dll";
    MonoAssembly* assembly = mono_domain_assembly_open(mono_domain_get(), dll.c_str());
    MonoImage* image = mono_assembly_get_image (assembly);
    MonoClass* klass = mono_class_from_name (image, "Embed", "Test");
    MonoObject* obj = mono_object_new (mono_domain_get(), klass);
    mono_runtime_object_init (obj);

    
    return true;
}
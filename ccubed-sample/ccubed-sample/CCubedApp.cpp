//
//  CCubedApp.cpp
//  ccubed-sample
//
//  Created by Shawn White on 31/01/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CCubedApp.h"
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>

#include "File.h"
#include "RequestHandler.h"

void
CCubedApp::Initialize(int argc, char* argv[])
{
    // Provide CEF with command-line arguments.
    CefMainArgs main_args(argc, argv);
    
    // SimpleApp implements application-level callbacks. It will create the first
    // browser instance in OnContextInitialized() after CEF has initialized.

    // Specify CEF global settings here.
    CefSettings settings;
    
    // Initialize CEF for the browser process.
    CefInitialize(main_args, settings, GetCef().get(), NULL);
    
    CefRegisterSchemeHandlerFactory("client", "ccubed", new ClientSchemeHandlerFactory());

    std::vector<std::string> monoPaths;
    std::string libmonoDir = File::GetExecDir() + "/mono/lib";
    std::string dllDir = File::GetExecDir() + "/Managed";
    std::string etcmonoDir = File::GetExecDir() + "/mono/etc";
    monoPaths.push_back(libmonoDir.c_str());
    monoPaths.push_back(dllDir.c_str());
    mono_set_dirs(libmonoDir.c_str(), etcmonoDir.c_str());
    mono_set_assemblies_path(dllDir.c_str());
    
    mono_config_parse (NULL);
    domain = mono_jit_init_version ("CCubed Root Domain", "v4.0.30319");
    
    // soft debugger needs this
    mono_thread_set_main (mono_thread_current ());
    
}

bool
CCubedApp::Run()
{
    std::string dll = File::GetExecDir() + "/Managed/test.dll";
    MonoAssembly* assembly = mono_domain_assembly_open(mono_domain_get(), dll.c_str());
    MonoImage* image = mono_assembly_get_image (assembly);
    MonoClass* klass = mono_class_from_name (image, "Embed", "Test");
    MonoObject* obj = mono_object_new (domain, klass);
    mono_runtime_object_init (obj);
    
    
    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    // called.
    CefRunMessageLoop();

    return true;
}

void
CCubedApp::Shutdown()
{
    mono_jit_cleanup (domain);
    
    // Shut down CEF.
    CefShutdown();
}
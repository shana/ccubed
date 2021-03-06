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
    // SimpleApp implements application-level callbacks. It will create the first
    // browser instance in OnContextInitialized() after CEF has initialized.
    app = new CCubedCefApp();

    // Provide CEF with command-line arguments.
    CefMainArgs main_args(argc, argv);
    

    // Specify CEF global settings here.
    CefSettings settings;
    
    
    // Initialize CEF for the browser process.
    CefInitialize(main_args, settings, app.get(), NULL);
    
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
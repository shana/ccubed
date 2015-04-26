//
//  JSBridge.cpp
//  ccubed-sample
//
//  Created by Andreia Gaita on 3/1/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "JSBridge.h"
#include "Utils\File.h"

#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>

MonoMethod* find_method(MonoClass* klass, const char* name)
{
	MonoMethod* method = mono_class_get_method_from_name(klass, name, -1);
	if (!method) return NULL;

	return method;
}

bool
JSBridge::Execute(const CefString& name,
CefRefPtr<CefV8Value> object,
const CefV8ValueList& arguments,
CefRefPtr<CefV8Value>& retval,
CefString& exception)
{

	if (!domain) {
		std::vector<std::string> monoPaths;
		std::string libmonoDir = File::BuildPath(File::GetExecDir(), "mono", "lib", '\0');
		std::string dllDir = File::BuildPath(File::GetExecDir(), "Managed", '\0');
		std::string etcmonoDir = File::BuildPath(File::GetExecDir(), "mono", "etc", '\0');
		monoPaths.push_back(libmonoDir.c_str());
		monoPaths.push_back(dllDir.c_str());
		mono_set_dirs(libmonoDir.c_str(), etcmonoDir.c_str());
		mono_set_assemblies_path(dllDir.c_str());

		mono_config_parse(NULL);
		domain = mono_jit_init_version("CCubed Root Domain", "v4.0.30319");

		// soft debugger needs this
		mono_thread_set_main(mono_thread_current());

		std::string dll = File::BuildPath(File::GetExecDir(), "Managed", "test.dll", '\0');
		MonoAssembly* assembly = mono_domain_assembly_open(mono_domain_get(), dll.c_str());
		image = mono_assembly_get_image(assembly);
		MonoClass* klass = mono_class_from_name(image, "Embed", "Test");
		MonoObject* obj = mono_object_new(mono_domain_get(), klass);
		mono_runtime_object_init(obj);
	}

	MonoClass* klass = mono_class_from_name(image, "Embed", "Test");
	auto method = find_method(klass, "Get");
	auto result = mono_runtime_invoke(method, NULL, NULL, NULL);
	int val = *(int*)mono_object_unbox(result);
	retval = CefV8Value::CreateInt(val);

	return true;
}
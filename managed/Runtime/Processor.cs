using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.IO;

namespace CCubed.Runtime
{
	public class Processor
	{
		const string namespaceReg = @"
if (!{{0}})
	{{0}} = {};
";
		const string typeRegStart = @"
if (!{{0}})
	{{0}} = {};
(function() {
";

		const string typeRegEnd = @"
})();
";

		const string methodReg = @"
	{{0}}.{{1}}= function() {
		native function {{2}}();
		return {{2}}();
	};
";

		const string propertyRegGetter = @"
	{{0}}.__defineGetter__('{{1}}', function() {
		native function Get{{2}}();
		return Get{{2}}();
	});
";

		const string propertyRegSetter = @"
	{{0}}.__defineSetter__('{{1}}', function(b) {
		native function Set{{2}}();
		if(b) Set{{2}}(b);
	});
";

		StringWriter sw = new StringWriter();

		List<string> registeredNamespaces = new List<string>();

		List<Type> typesWeWant = new List<Type>();

		Dictionary<Type, List<Thing>> things = new Dictionary<Type, List<Thing>>();

		public void Run(Assembly asm)
		{
			var types = asm.GetTypes();
			foreach (var type in types) {
				if (!typesWeWant.Contains(type) && IsTypeExposed(type)) {
					typesWeWant.Add(type);
				}
			}

			foreach (var type in typesWeWant) {
				var parts = type.FullName.Split('.');
				string acc = "";
				for (int i = 0; i < parts.Length - 2; i++) {
					acc += "." + parts[i];
					if (!registeredNamespaces.Contains(acc)) {
						sw.Write(namespaceReg, acc);
						registeredNamespaces.Add(acc);
					}
				}
			}

			foreach (var type in typesWeWant) {
				ProcessType(type);
			}

			foreach (var type in things.Keys) {
				sw.Write(typeRegStart, type.FullName);

				foreach (var thing in things[type]) {
					if (thing.IsProperty) {
						sw.Write(propertyRegGetter, type.FullName, thing.JSName, thing.CSName);
					} else if (thing.IsMethod) {
						sw.Write(propertyRegGetter, type.FullName, thing.JSName, thing.CSName);
					}
				}
			}
		}

		bool IsTypeExposed(Type type)
		{
			if (typeof(ISerializeIt).IsAssignableFrom(type)) {
				return true;
			}
			var props = type.GetProperties(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
			var methods = type.GetMethods(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);

			return props.Any(x => x.GetCustomAttribute<SerializeItAttribute>() != null) ||
				methods.Any(x => x.GetCustomAttribute<SerializeItAttribute>() != null);
		}

		void ProcessType(Type type)
		{
			var props = new List<PropertyInfo>();
			var methods = new List<MethodInfo>();
			if (typeof(ISerializeIt).IsAssignableFrom(type)) {
				props.AddRange(type.GetProperties(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic));
				methods.AddRange(type.GetMethods(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic));
			} else {
				foreach (var prop in type.GetProperties(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)) {
					if (prop.GetCustomAttribute<SerializeItAttribute>() != null) {
						props.Add(prop);
					}
				}
				foreach (var method in type.GetMethods(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)) {
					if (method.GetCustomAttribute<SerializeItAttribute>() != null) {
						methods.Add(method);
					}
				}
			}

			var list = new List<Thing>();
			foreach (var prop in props) {
				var thing = new Thing() { CSName = prop.Name, JSName = prop.Name, IsProperty = true };
				thing.HasSetter = prop.GetSetMethod() != null;
				list.Add(thing);
			}

			foreach (var method in methods) {
				list.Add(new Thing() { IsMethod = true, CSName = method.Name, JSName = method.Name });
			}
		}

		void ProcessMethod(MethodInfo method)
		{

		}

		void ProcessProperty(PropertyInfo property)
		{

		}

		void ProcessField(FieldInfo field)
		{

		}
	}


	class Thing
	{
		public bool IsProperty;
		public bool IsMethod;
		public bool HasSetter;
		public string JSName;
		public string CSName;
	}
}

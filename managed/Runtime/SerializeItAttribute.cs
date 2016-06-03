using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CCubed.Runtime
{
	[AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
	public class SerializeItAttribute : Attribute
	{
	}
}

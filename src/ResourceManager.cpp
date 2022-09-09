#include "ResourceManager.h"

using namespace Resource;

Foo::string Resource::ResourceManager::resolvePath(Foo::string file)
{
	path p = path("./assets") / file;
	return Foo::string(p.string());
}

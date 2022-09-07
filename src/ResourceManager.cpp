#include "ResourceManager.h"

using namespace Resource;

Foo::string Resource::ResourceManager::resolvePath(Foo::string path)
{
	return path;//std::filesystem::path::path(file).string(); //FIXME: is this correct?
}

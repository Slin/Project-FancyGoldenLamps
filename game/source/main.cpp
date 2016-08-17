#if __APPLE__
#if TARGET_OS_IPHONE
#include <SFML/Main.hpp>
#endif
#endif

#include "World.h"

int main(int argc, char* argv[])
{
	FGL::World::GetInstance()->Loop();
	return 0;
}


#include "stdafx.h"


int main(int argc, char* argv[])
{
	theWorld.Initialize(1024, 768, "Test", false, false, false);
	theWorld.Add(new GridActor(), -1);
	theWorld.StartGame();

	theWorld.Destroy();
	return 0;
}

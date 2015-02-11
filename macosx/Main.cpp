
#include "stdafx.h"


int main(int argc, char* argv[])
{
	theWorld.Initialize(1024, 768, "Test", false, false, false);
	theWorld.Add(new GridActor(), -1);
	theWorld.StartGame();
	Actor *a = new Actor();
	a->SetPosition(-3.0f, 4.0f);
	a->SetColor(1.0f, 0.0f, 0.0f);
	a->SetDrawShape(ADS_Circle);
	a->SetSize(3.0f);
	theWorld.Add(a);
	theWorld.Destroy();
	a->Render();
	return 0;
}

#include "ApplicationRenderer.h"

int main()
{
	ApplicationRenderer application;
	application.WindowInitialize(1920, 1080);
	application.Render();
	return 0;
}
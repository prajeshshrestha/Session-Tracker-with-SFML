#include "SessionApp.h"

int main()
{
	SessionApp App;
	while (App.isRunning())
	{
		App.Update();
		App.Render();
	}
	return EXIT_SUCCESS;
}
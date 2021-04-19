#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "application.h"
#include "instruction.h"
#include <FL/Fl.H>

void idle(void* data)
{
	Application *app = static_cast<Application*>(data);
}

int main(int argc, char **argv)
{
	Application *app = new Application();

	Fl::lock();
	app->SetupGUI()->show();
	Fl::add_idle(idle, app);
	while (Fl::wait());
}


#include <Windows.h> // include Windows.h only if using WinMain
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>
#include <string>
#include "application.h";

struct FileOpenResult{
	boolean success;
	std::string path;
	Fl_Text_Display* text_display;
};

void open_file_callback(Fl_Widget *w, void* file_result)
{
	Fl_Native_File_Chooser fnfc;
	fnfc.title("Pick a file");
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.filter("Text\t*.txt\n"
		"C Files\t*.{cxx,h,c}");
	fnfc.directory("/var/tmp");           // default directory to use
	switch (fnfc.show()) {
	case -1: 
		printf("ERROR: %s\n", fnfc.errmsg());    
		static_cast<FileOpenResult*>(file_result)->success = false;
		break;  // ERROR
	case  1: 
		printf("CANCEL\n");                
		static_cast<FileOpenResult*>(file_result)->success = false;
		break;  // CANCEL
	default: 
		printf("PICKED: %s\n", fnfc.filename()); 
		static_cast<FileOpenResult*>(file_result)->success = true;
		static_cast<FileOpenResult*>(file_result)->path = fnfc.filename();
		Fl_Text_Buffer *buff = new Fl_Text_Buffer();
		buff->append(fnfc.filename());
		static_cast<FileOpenResult*>(file_result)->text_display->buffer(buff);
		break;  // FILE CHOSEN
	}
}

void start_sim_callback(Fl_Widget *w, void* data)
{
	FileOpenResult *file_result = static_cast<FileOpenResult*>(data);
	if (file_result->success)
	{
		//StartSim();
	}
}

int __stdcall WinMain(
	__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in LPSTR lpCmdLine,
	__in int nShowCmd
	)
{
	Fl_Window window(800, 600, "Register Renaming Statistics Simulation");
	//Fl_Box box(0, 50, 200, 20, "Hello");
	Fl_Text_Display *text = new Fl_Text_Display(100, 50, 250, 25, "Log file");
	Fl_Button *browse_button = new Fl_Button(360, 50, 60, 30, "Browse");
	FileOpenResult *file_result = new FileOpenResult();
	file_result->success = false;
	file_result->text_display = text;
	browse_button->callback(open_file_callback, file_result);


	Fl_Button *sim_button = new Fl_Button(360, 150, 60, 30, "Start Sim");
	sim_button->callback(start_sim, file_result);
	window.show();


	return Fl::run();
}

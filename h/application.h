#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#define WIN32
#include <string>
#include "textparser.h"
#include "batchparser.h"
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>
#include <concurrent_queue.h>
#include <FL/Fl_Chart.H>
#include <mutex>

struct FileOpenResult{
	bool success;
	std::string path;
	Fl_Text_Display* text_display;
};

struct SimulationStruct {
	int batch_size;
	//concurrency::concurrent_queue<int>* result_queue;
	std::vector<int>* result_vector;
	std::vector<double>* result_vector_percentage;
	double average = 0;
	long long sum = 0;
	long double sum_percentage = 0;
	int sim_count = 0;
	int min = 0;
	int max = 0;
	bool finished = false;

	Fl_Text_Display* td_batch, * td_minimum, * td_maximum, * td_average;
	Fl_Button* btn_show_graph;

	SimulationStruct(int _batch_size): batch_size(_batch_size)
	{
	}
};

class Application
{
private:
	static std::string file_name;
	static int total_instruction_count;
	TextParser *text_parser;
	BatchParser *batch_parser;

	std::vector<SimulationStruct*> simulationsGlobal;
	std::vector<SimulationStruct*> simulationsFinalSubmit;
	std::vector<SimulationStruct*> simulationsArgments;
	std::vector<SimulationStruct*> simulationsEAX;
	std::vector<SimulationStruct*> simulationsEBX;
	std::vector<SimulationStruct*> simulationsECX;
	std::vector<SimulationStruct*> simulationsEDX;
	std::vector<SimulationStruct*> simulationsEBP;
	std::vector<SimulationStruct*> simulationsEDI;
	std::vector<SimulationStruct*> simulationsESI;
	

	void GetInstructionCount();
	void DisableButtons();

	static void OpenFileCallback(Fl_Widget *w, void* file_result);
	static void StartSimCallback(Fl_Widget *w, void* file_result);
	static void ShowGraphCallback(Fl_Widget* w, void* simulation);
public:
	Fl_Window *window;
	std::mutex mutex;

	Application();
	Fl_Window *SetupGUI();
	void StartSim();
};

#endif
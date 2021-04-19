#include "application.h"
#include <sstream>
#include "util.h"
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Tabs.H>
#include <thread>
#include <FL/Fl_chart.H>
#include <cstring>
#include <matplotlibcpp.h>
#include "batchparserfinalsubmit.h"
#include "batchparserarguments.h"


namespace plt = matplotlibcpp;

std::string Application::file_name = "";
int Application::total_instruction_count = 0;

Application::Application()
{
	simulationsGlobal.push_back(new SimulationStruct(2));
	simulationsGlobal.push_back(new SimulationStruct(3));
	simulationsGlobal.push_back(new SimulationStruct(4));
	simulationsGlobal.push_back(new SimulationStruct(6));
	simulationsGlobal.push_back(new SimulationStruct(8));
	simulationsGlobal.push_back(new SimulationStruct(16));
	simulationsGlobal.push_back(new SimulationStruct(32));

	simulationsFinalSubmit.push_back(new SimulationStruct(2));
	simulationsFinalSubmit.push_back(new SimulationStruct(3));
	simulationsFinalSubmit.push_back(new SimulationStruct(4));
	simulationsFinalSubmit.push_back(new SimulationStruct(6));
	simulationsFinalSubmit.push_back(new SimulationStruct(8));
	simulationsFinalSubmit.push_back(new SimulationStruct(16));
	simulationsFinalSubmit.push_back(new SimulationStruct(32));

	simulationsArgments.push_back(new SimulationStruct(2));
	simulationsArgments.push_back(new SimulationStruct(3));
	simulationsArgments.push_back(new SimulationStruct(4));
	simulationsArgments.push_back(new SimulationStruct(6));
	simulationsArgments.push_back(new SimulationStruct(8));
	simulationsArgments.push_back(new SimulationStruct(16));
	simulationsArgments.push_back(new SimulationStruct(32));

	simulationsEAX.push_back(new SimulationStruct(2));
	simulationsEAX.push_back(new SimulationStruct(3));
	simulationsEAX.push_back(new SimulationStruct(4));
	simulationsEAX.push_back(new SimulationStruct(6));
	simulationsEAX.push_back(new SimulationStruct(8));
	simulationsEAX.push_back(new SimulationStruct(16));
	simulationsEAX.push_back(new SimulationStruct(32));

	simulationsEBX.push_back(new SimulationStruct(2));
	simulationsEBX.push_back(new SimulationStruct(3));
	simulationsEBX.push_back(new SimulationStruct(4));
	simulationsEBX.push_back(new SimulationStruct(6));
	simulationsEBX.push_back(new SimulationStruct(8));
	simulationsEBX.push_back(new SimulationStruct(16));
	simulationsEBX.push_back(new SimulationStruct(32));

	simulationsECX.push_back(new SimulationStruct(2));
	simulationsECX.push_back(new SimulationStruct(3));
	simulationsECX.push_back(new SimulationStruct(4));
	simulationsECX.push_back(new SimulationStruct(6));
	simulationsECX.push_back(new SimulationStruct(8));
	simulationsECX.push_back(new SimulationStruct(16));
	simulationsECX.push_back(new SimulationStruct(32));

	simulationsEDX.push_back(new SimulationStruct(2));
	simulationsEDX.push_back(new SimulationStruct(3));
	simulationsEDX.push_back(new SimulationStruct(4));
	simulationsEDX.push_back(new SimulationStruct(6));
	simulationsEDX.push_back(new SimulationStruct(8));
	simulationsEDX.push_back(new SimulationStruct(16));
	simulationsEDX.push_back(new SimulationStruct(32));

	simulationsEBP.push_back(new SimulationStruct(2));
	simulationsEBP.push_back(new SimulationStruct(3));
	simulationsEBP.push_back(new SimulationStruct(4));
	simulationsEBP.push_back(new SimulationStruct(6));
	simulationsEBP.push_back(new SimulationStruct(8));
	simulationsEBP.push_back(new SimulationStruct(16));
	simulationsEBP.push_back(new SimulationStruct(32));

	simulationsEDI.push_back(new SimulationStruct(2));
	simulationsEDI.push_back(new SimulationStruct(3));
	simulationsEDI.push_back(new SimulationStruct(4));
	simulationsEDI.push_back(new SimulationStruct(6));
	simulationsEDI.push_back(new SimulationStruct(8));
	simulationsEDI.push_back(new SimulationStruct(16));
	simulationsEDI.push_back(new SimulationStruct(32));

	simulationsESI.push_back(new SimulationStruct(2));
	simulationsESI.push_back(new SimulationStruct(3));
	simulationsESI.push_back(new SimulationStruct(4));
	simulationsESI.push_back(new SimulationStruct(6));
	simulationsESI.push_back(new SimulationStruct(8));
	simulationsESI.push_back(new SimulationStruct(16));
	simulationsESI.push_back(new SimulationStruct(32));

}

void Application::GetInstructionCount()
{
	if (Application::file_name == "")
		return;

	Application::total_instruction_count = 0;

	delete text_parser;
	text_parser = new TextParser(Application::file_name);
	while (text_parser->IsValid())
	{
		std::string line = text_parser->GetNextLine();
		if (BatchParser::CheckIfInstruction(line))
			Application::total_instruction_count++;
	}
}

void Application::DisableButtons()
{
	for (SimulationStruct* sim : simulationsGlobal)
		sim->btn_show_graph->hide();

	for (SimulationStruct* sim : simulationsFinalSubmit)
		sim->btn_show_graph->hide();
}

void Application::StartSim()
{
	GetInstructionCount();
	DisableButtons();


	for (SimulationStruct* sim : simulationsGlobal)
	{
		int batch_count = Application::total_instruction_count / sim->batch_size;
		Util::LogToSTDOUT("INSTRUCTION COUNT IS " + std::to_string(Application::total_instruction_count));
		sim->sim_count = 0;
		sim->average = 0;
		sim->sum = 0;

		delete text_parser;
		text_parser = new TextParser(file_name);
		batch_parser = new BatchParser(sim->batch_size);
		sim->result_vector = new std::vector<int>();

		for (int i = 0; i < batch_count; i++)
		{
			std::string line = text_parser->GetNextLine();
			//Feed the batch parser with enough instructions
			while (!batch_parser->Feed(line))
				line = text_parser->GetNextLine();

			int result = batch_parser->CollectResult();
			Util::LogToSTDOUT("REMAP file accessed " + std::to_string(result) + " times in the last batch.");

			sim->min = min(result, sim->min);
			sim->max = max(result, sim->max);
			sim->result_vector->push_back(result);
			sim->sim_count++;
			sim->sum += result;
			sim->average = sim->sum / (double)sim->sim_count;


			Fl::lock();
			Fl_Text_Buffer* buff1 = new Fl_Text_Buffer();
			Fl_Text_Buffer* buff2 = new Fl_Text_Buffer();
			Fl_Text_Buffer* buff3 = new Fl_Text_Buffer();
			buff1->append(std::to_string(sim->min).c_str());
			buff2->append(std::to_string(sim->max).c_str());
			buff3->append(std::to_string(sim->average).c_str());
			sim->td_minimum->buffer(buff1);
			sim->td_maximum->buffer(buff2);
			sim->td_average->buffer(buff3);
			Fl::unlock();
			Util::LogToSTDOUT("AVERAGE IS " + std::to_string(sim->average));
		}
		Util::LogToSTDOUT("FINISHED SIM FOR GLOBAL");
		sim->btn_show_graph->show();
	}

	int index = 0;
	for (SimulationStruct* sim : simulationsFinalSubmit)
	{
		int batch_count = Application::total_instruction_count / sim->batch_size;
		Util::LogToSTDOUT("INSTRUCTION COUNT IS " + std::to_string(Application::total_instruction_count));
		sim->sim_count = 0;
		sim->average = 0;
		sim->sum = 0;

		delete text_parser;
		text_parser = new TextParser(file_name);
		batch_parser = new BatchParserFinalSubmit(sim->batch_size);
		sim->result_vector = new std::vector<int>();
		simulationsEAX[index]->result_vector = new std::vector<int>();
		simulationsEBX[index]->result_vector = new std::vector<int>();
		simulationsECX[index]->result_vector = new std::vector<int>();
		simulationsEDX[index]->result_vector = new std::vector<int>();
		simulationsEBP[index]->result_vector = new std::vector<int>();
		simulationsEDI[index]->result_vector = new std::vector<int>();
		simulationsESI[index]->result_vector = new std::vector<int>();

		for (int i = 0; i < batch_count; i++)
		{
			std::string line = text_parser->GetNextLine();
			//Feed the batch parser with enough instructions
			while (!batch_parser->Feed(line))
				line = text_parser->GetNextLine();


			//collect result for separate registers
			int eax = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("EAX") ? 1 : 0);
			simulationsEAX[index]->sum += eax;
			simulationsEAX[index]->sim_count++;
			simulationsEAX[index]->average = (double)simulationsEAX[index]->sum / simulationsEAX[index]->sim_count;
			simulationsEAX[index]->result_vector->push_back(eax);
			int ebx = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("EBX") ? 1 : 0);
			simulationsEBX[index]->sum += ebx;
			simulationsEBX[index]->sim_count++;
			simulationsEBX[index]->average = (double)simulationsEBX[index]->sum / simulationsEBX[index]->sim_count;
			simulationsEBX[index]->result_vector->push_back(ebx);
			int ecx = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("ECX") ? 1 : 0);
			simulationsECX[index]->sum += ecx;
			simulationsECX[index]->sim_count++;
			simulationsECX[index]->average = (double)simulationsECX[index]->sum / simulationsECX[index]->sim_count;
			simulationsECX[index]->result_vector->push_back(ecx);
			int edx = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("EDX") ? 1 : 0);
			simulationsEDX[index]->sum += edx;
			simulationsEDX[index]->sim_count++;
			simulationsEDX[index]->average = (double)simulationsEDX[index]->sum / simulationsEDX[index]->sim_count;
			simulationsEDX[index]->result_vector->push_back(edx);
			int ebp = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("EBP") ? 1 : 0);
			simulationsEBP[index]->sum += ebp;
			simulationsEBP[index]->sim_count++;
			simulationsEBP[index]->average = (double)simulationsEBP[index]->sum / simulationsEBP[index]->sim_count;
			simulationsEBP[index]->result_vector->push_back(ebp);
			int edi = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("EDI") ? 1 : 0);
			simulationsEDI[index]->sum += edi;
			simulationsEDI[index]->sim_count++;
			simulationsEDI[index]->average = (double)simulationsEDI[index]->sum / simulationsEDI[index]->sim_count;
			simulationsEDI[index]->result_vector->push_back(edi);
			int esi = (dynamic_cast<BatchParserFinalSubmit*>(batch_parser)->CollectRegisterRenamed("ESI") ? 1 : 0);
			simulationsESI[index]->sum += esi;
			simulationsESI[index]->sim_count++;
			simulationsESI[index]->average = (double)simulationsESI[index]->sum / simulationsESI[index]->sim_count;
			simulationsESI[index]->result_vector->push_back(esi);


			int result = batch_parser->CollectResult();
			Util::LogToSTDOUT("REMAP file accessed " + std::to_string(result) + " times in the last batch.");

			sim->min = min(result, sim->min);
			sim->max = max(result, sim->max);
			sim->result_vector->push_back(result);
			sim->sim_count++;
			sim->sum += result;
			sim->average = sim->sum / (double)sim->sim_count;


			Fl::lock();
			Fl_Text_Buffer* buff1 = new Fl_Text_Buffer();
			Fl_Text_Buffer* buff2 = new Fl_Text_Buffer();
			Fl_Text_Buffer* buff3 = new Fl_Text_Buffer();
			buff1->append(std::to_string(sim->min).c_str());
			buff2->append(std::to_string(sim->max).c_str());
			buff3->append(std::to_string(sim->average).c_str());
			sim->td_minimum->buffer(buff1);
			sim->td_maximum->buffer(buff2);
			sim->td_average->buffer(buff3);
			Fl::unlock();
			Util::LogToSTDOUT("AVERAGE IS " + std::to_string(sim->average));
		}

		Fl::lock();
		Fl_Text_Buffer* buff1 = new Fl_Text_Buffer();
		buff1->append(std::to_string(simulationsEAX[index]->average).c_str());
		simulationsEAX[index]->td_average->buffer(buff1);
		simulationsEAX[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff2 = new Fl_Text_Buffer();
		buff2->append(std::to_string(simulationsEBX[index]->average).c_str());
		simulationsEBX[index]->td_average->buffer(buff2);
		simulationsEBX[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff3 = new Fl_Text_Buffer();
		buff3->append(std::to_string(simulationsECX[index]->average).c_str());
		simulationsECX[index]->td_average->buffer(buff3);
		simulationsECX[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff4 = new Fl_Text_Buffer();
		buff4->append(std::to_string(simulationsEDX[index]->average).c_str());
		simulationsEDX[index]->td_average->buffer(buff4);
		simulationsEDX[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff5 = new Fl_Text_Buffer();
		buff5->append(std::to_string(simulationsEBP[index]->average).c_str());
		simulationsEBP[index]->td_average->buffer(buff5);
		simulationsEBP[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff6 = new Fl_Text_Buffer();
		buff6->append(std::to_string(simulationsEDI[index]->average).c_str());
		simulationsEDI[index]->td_average->buffer(buff6);
		simulationsEDI[index]->btn_show_graph->show();
		Fl_Text_Buffer* buff7 = new Fl_Text_Buffer();
		buff7->append(std::to_string(simulationsESI[index]->average).c_str());
		simulationsESI[index]->td_average->buffer(buff7);
		simulationsESI[index]->btn_show_graph->show();
		Fl::unlock();


		Util::LogToSTDOUT("FINISHED SIM");
		sim->btn_show_graph->show();

		index++;
	}

	for (SimulationStruct* sim : simulationsArgments)
	{
		int batch_count = Application::total_instruction_count / sim->batch_size;
		Util::LogToSTDOUT("INSTRUCTION COUNT IS " + std::to_string(Application::total_instruction_count));
		sim->sim_count = 0;
		sim->average = 0;
		sim->sum = 0;

		delete text_parser;
		text_parser = new TextParser(file_name);
		batch_parser = new BatchParserArguments(sim->batch_size);
		sim->result_vector_percentage = new std::vector<double>();

		for (int i = 0; i < batch_count; i++)
		{
			std::string line = text_parser->GetNextLine();
			//Feed the batch parser with enough instructions
			while (!batch_parser->Feed(line))
				line = text_parser->GetNextLine();

			int result = batch_parser->CollectResult();
			Util::LogToSTDOUT("REMAP file accessed " + std::to_string(result) + " times in the last batch.");

			double result_percentage = dynamic_cast<BatchParserArguments*>(batch_parser)->CollectResultPercentage();

			sim->min = min(result, sim->min);
			sim->max = max(result, sim->max);
			sim->result_vector_percentage->push_back(result_percentage);
			sim->sim_count++;
			sim->sum_percentage += result_percentage;
			sim->average = sim->sum_percentage / (double)sim->sim_count;


			Fl::lock();
			Fl_Text_Buffer* buff3 = new Fl_Text_Buffer();
			buff3->append(std::to_string(sim->average).c_str());
			sim->td_average->buffer(buff3);
			Fl::unlock();
			Util::LogToSTDOUT("AVERAGE IS " + std::to_string(sim->average));
		}
		Util::LogToSTDOUT("FINISHED SIM");
		sim->btn_show_graph->show();
	}

}

Fl_Window *Application::SetupGUI()
{
	window = new Fl_Window(800, 800, "Register Renaming Statistics Simulation");
	Fl_Text_Display *text = new Fl_Text_Display(30, 30, 250, 25, "Log file");
	Fl_Button *browse_button = new Fl_Button(290, 30, 60, 30, "Browse");
	
	FileOpenResult *file_result = new FileOpenResult();
	file_result->success = false;
	file_result->text_display = text;
	browse_button->callback(Application::OpenFileCallback, file_result);

	Fl_Button *sim_button = new Fl_Button(460, 30, 120, 30, "Start Simulations");
	sim_button->callback(Application::StartSimCallback, this);

	int starty = 100;
	int startx = 20;
	int width = 150;
	int dx = 10;
	int dy = 50;
	int i = 0;

	Fl_Tabs* tabs = new Fl_Tabs(10, 80, 780, 700);
	{
		tabs->labelsize(30);
		Fl_Group* groupGlobal = new Fl_Group(10, 80, 770, 690, "Global");
		{
			for (SimulationStruct* sim : simulationsGlobal)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_minimum = new Fl_Text_Display(startx + width + dx, starty * (i + 1), 150, 25, "Minimum");
				sim->td_maximum = new Fl_Text_Display(startx + 2 * (width + dx), starty * (i + 1), 150, 25, "Maximum");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "Average");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;

			}
		}
		groupGlobal->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupFinal = new Fl_Group(10, 80, 770, 690, "Final Submit");
		{
			for (SimulationStruct* sim : simulationsFinalSubmit)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_minimum = new Fl_Text_Display(startx + width + dx, starty * (i + 1), 150, 25, "Minimum");
				sim->td_maximum = new Fl_Text_Display(startx + 2 * (width + dx), starty * (i + 1), 150, 25, "Maximum");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "Average");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupFinal->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupArguments = new Fl_Group(10, 80, 770, 690, "Arguments");
		{
			for (SimulationStruct* sim : simulationsArgments)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of arguments in remap file");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupArguments->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterAX = new Fl_Group(10, 80, 770, 690, "    AX    ");
		{
			for (SimulationStruct* sim : simulationsEAX)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterAX->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterBX = new Fl_Group(10, 80, 770, 690, "    BX    ");
		{
			for (SimulationStruct* sim : simulationsEBX)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterBX->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterCX = new Fl_Group(10, 80, 770, 690, "    CX    ");
		{
			for (SimulationStruct* sim : simulationsECX)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterCX->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterDX = new Fl_Group(10, 80, 770, 690, "    DX    ");
		{
			for (SimulationStruct* sim : simulationsEDX)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterDX->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterBP = new Fl_Group(10, 80, 770, 690, "    BP    ");
		{
			for (SimulationStruct* sim : simulationsEBP)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterBP->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterDI = new Fl_Group(10, 80, 770, 690, "    DI    ");
		{
			for (SimulationStruct* sim : simulationsEDI)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterDI->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;

		Fl_Group* groupRegisterSI = new Fl_Group(10, 80, 770, 690, "    SI    ");
		{
			for (SimulationStruct* sim : simulationsESI)
			{
				sim->td_batch = new Fl_Text_Display(startx, starty * (i + 1), 150, 25, "Batch Size");
				sim->td_average = new Fl_Text_Display(startx + 3 * (width + dx), starty * (i + 1), 150, 25, "% of batches with renaming");
				sim->btn_show_graph = new Fl_Button(startx + 4 * (width + dx), starty * (i + 1), 120, 30, "Show graph");
				sim->btn_show_graph->callback(Application::ShowGraphCallback, sim);
				sim->btn_show_graph->hide();

				Fl_Text_Buffer* buff = new Fl_Text_Buffer();
				buff->append(std::to_string(sim->batch_size).c_str());
				sim->td_batch->buffer(buff);
				i++;
			}
		}
		groupRegisterSI->end();
		starty = 100;
		startx = 20;
		width = 150;
		dx = 10;
		dy = 50;
		i = 0;
	}
	tabs->end();
	
	return window;
}

void Application::OpenFileCallback(Fl_Widget *w, void* file_result)
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

		//maybe move this somewhere
		if (static_cast<FileOpenResult*>(file_result)->success)
		{
			file_name = static_cast<FileOpenResult*>(file_result)->path;
		}
		break;  // FILE CHOSEN
	}
}

void Application::StartSimCallback(Fl_Widget *w, void* data)
{
	Application *application = static_cast<Application*>(data);
	std::thread t1(&Application::StartSim, application);
	t1.detach();
}

void Application::ShowGraphCallback(Fl_Widget* w, void* data)
{
	SimulationStruct* sim = static_cast<SimulationStruct*>(data);

	//plt::scatter(v, *sim->result_vector);
	if (sim->result_vector != NULL)
		plt::plot(*sim->result_vector);
	else
		plt::plot(*sim->result_vector_percentage);
	plt::xlabel("Batch no");
	plt::ylabel("Access number");
	plt::show();
}
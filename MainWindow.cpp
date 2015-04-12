#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

[STAThread]

void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Sim_interface::MainWindow myForm;
	Application::Run(%myForm);
}

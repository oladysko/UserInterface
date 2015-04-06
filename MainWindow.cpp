#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

[STAThread]
void MainWindow(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UserInterface::MainWindow mWindow;
	Application::Run(%mWindow);
}
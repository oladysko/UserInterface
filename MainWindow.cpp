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

namespace Sim_interface{
	System::Void MainWindow::button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//variables
		unsigned int frameNumber;
		String^ debugInfo;
		String^ fileName;
		int bitmapHeight = 0, bitmapWidth = 0;
		std::string stdFileName;

		try
		{
			//get frame number
			frameNumber = Convert::ToUInt32(this->frame_textBox->Text);
			debugInfo = "selected frame = " + Convert::ToString(frameNumber) + "\n";
			//get file
			//TO DO Add filters, filename corectness checking
			OpenFileDialog^ dlg = gcnew OpenFileDialog();
			dlg->ShowDialog();
			fileName = dlg->FileName;
			ParserH::MarshalString(fileName, stdFileName);
			ParserH::fileNametoPath(stdFileName);
			String^ tmpString = gcnew String(stdFileName.c_str());
			debugInfo = debugInfo + "selected file = \n" + tmpString + "\n";
		}
		catch (Exception^ errorHandle){
			this->Info_label->Text = errorHandle->Message;
			return;
		}
		//get height and width
		ParserH::getImageSize(bitmapHeight, bitmapWidth, frameNumber, stdFileName);
		debugInfo = "bitmapHeight = " + bitmapHeight + "\nbitmapWidth = " + bitmapWidth;//Format16bppGrayScale
		//create bitmap
		//Bitmap^ dicomImage = gcnew Bitmap(bitmapHeight, bitmapWidth, Imaging::PixelFormat::Format16bppGrayScale);  //http://stackoverflow.com/questions/743549/how-to-put-image-in-a-picture-box-from-bitmap
		this->dicomImage = gcnew Bitmap(bitmapHeight, bitmapWidth, Imaging::PixelFormat::Format24bppRgb);  //http://stackoverflow.com/questions/743549/how-to-put-image-in-a-picture-box-from-bitmap
		//dicomImage->SetPixel(1, 1, Color::FromArgb(0,0x1f, 0x1f, 0x1f));
		ParserH::getBitmap(bitmapHeight, bitmapWidth, frameNumber, stdFileName, this->dicomImage);
		//display picture
		pictureBox1->Image = this->dicomImage;
		//fileName->
		//puntoexe::imebra::testView(frameNumber, stdFileName);
		this->Info_label->Text = debugInfo;
	}
	System::Void MainWindow::saveCurrent_Click(System::Object^  sender, System::EventArgs^  e) {
		//Displays a save file dialog so the user can save the Image assigned to button
		SaveFileDialog ^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif";
		saveFileDialog->Title = "Save an Image File";
		saveFileDialog->ShowDialog();
		//if filename is not empty string
		if (saveFileDialog->FileName != ""){
			//Console::WriteLine(saveFileDialog->FileName);
			this->Info_label->Text = "filename for saving: " + saveFileDialog->FileName;
			this->dicomImage->Save(saveFileDialog->FileName, Imaging::ImageFormat::Jpeg);
		}
	}
}


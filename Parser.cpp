#include "Parser.h"
namespace  ParserH
{
	void MarshalString(String ^ s, std::string& os)
	{
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	void fileNametoPath(std::string% os)
	{
		std::string tmp;
		std::size_t found = 0;
		while ((found = os.find("\\", found + 2)) != std::string::npos){
			os.insert(found, "\\");
			if (found + 2 > os.size())
				return;
		}
	}

	void getImageSize(int& height, int& width, unsigned int frameNumber, std::string fileName)
	{
		height = 0;
		width = 0;
		imbxUint32 tmpHeight = 0;
		imbxUint32 tmpWidth = 0;
		puntoexe::imebra::Maro::getFrameSize(frameNumber, fileName, tmpHeight, tmpWidth);
		height = (int)tmpHeight;
		width = (int)tmpWidth;
	}
	void getBitmap(const int height,const int width, unsigned int frameNumber, std::string fileName,Bitmap^ dicomImage)
	{	//function converts dicom image to bitmap

		//allocate memory for dicom data, wchih is passed to imebra function, declare some variables
		int * tmpData = new int[height *width];
		int maxPixelValue = 1, minPixelValue = 255; // 1 to prevent dicision by 0
		//create rectangle, special structure for storaging image data
		Drawing::Rectangle rect = Drawing::Rectangle(0, 0, dicomImage->Width, dicomImage->Height);//https://msdn.microsoft.com/pl-pl/library/5ey6h79d%28v=vs.110%29.aspx?cs-save-lang=1&cs-lang=cpp#code-snippet-2
		//lock bits of image
		BitmapData^	bmpData = dicomImage->LockBits(rect, ImageLockMode::ReadWrite, dicomImage->PixelFormat);			 //https://msdn.microsoft.com/en-us/library/ms229672%28v=vs.90%29.aspx?cs-save-lang=1&cs-lang=csharp#code-snippet-1
		//get the addres of the first line
		IntPtr ptr = bmpData->Scan0;
		//declare an array to hold the bytes ot the bitmap,,doesn't work for bitmaps with grayscale or other than 24 bits per pixel
		int bytes = Math::Abs(bmpData->Stride) * dicomImage->Height;//get data size
		array<Byte>^ rgbValues = gcnew array<Byte>(bytes);			  
		//retrive data from imebra
		puntoexe::imebra::Maro::getValuesMatrix(frameNumber, fileName, height, width,tmpData);
		//need to process data for correct display
		//find min and max values
		for (int n = 0; n < height*width; n++){
			if (tmpData[n] > maxPixelValue)
				maxPixelValue = tmpData[n];
			if (tmpData[n] < minPixelValue)
				minPixelValue = tmpData[n];
		}
		//normalize data to 255 in other words, make some artefacts
		for (int n = 0; n < height*width; n++){
			tmpData[n] = (int)((double)tmpData[n]*255 / (double)maxPixelValue);
		}
		Console::WriteLine();

		//copy data to bitmap, it doesn't work for simple grayscale and nedd to do something with RGB values
		for (int counter = 2; counter < rgbValues->Length; counter += 3){
			rgbValues[counter - 2] = tmpData[(int)((counter - 2)/3)];
			rgbValues[counter - 1] = tmpData[(int)((counter - 2) / 3)];
			rgbValues[counter - 0] = tmpData[(int)((counter - 2) / 3)];
		}

		//for (int y = 0; y < dicomImage->Height; y++){
		//	for (int x = 0; x < dicomImage->Width; x++){
		//		//rgbValues
		//	}
		//	//cout << tmpData[128 + 128 * height] << endl;
		//}
		//copy array to bitmap
		Runtime::InteropServices::Marshal::Copy(rgbValues, 0, ptr, bytes);
		//unlock bits
		dicomImage->UnlockBits(bmpData);
		//delete pointer to data
		delete[] tmpData;
	}
}
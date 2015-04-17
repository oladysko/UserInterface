#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <cstddef>
#include "imebra.h""
#include "Maro.h"

using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace  ParserH
{
	//convert C# string to std::string (C++)
	void MarshalString(String ^ s, std::string& os);//https://msdn.microsoft.com/en-us/library/1b4az623.aspx
	void fileNametoPath(std::string% os);
	void getImageSize(int& height,int& width, unsigned int frameNumber, std::string fileName);
	void getBitmap(const int height, const int width, unsigned int frameNumber, std::string fileName, Bitmap^ dicomImage);
}
#endif
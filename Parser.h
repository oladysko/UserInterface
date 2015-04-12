#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <cstddef>
using namespace std;
using namespace System;

//convert C# string to std::string (C++)
void MarshalString(String ^ s, std::string& os);//https://msdn.microsoft.com/en-us/library/1b4az623.aspx

//void inverseMarshalString()

//convert all "\" to "\\"
void fileNametoPath(std::string% os);

#endif
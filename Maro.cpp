#include <iostream>
#include <fstream>
//#include <boost/lambda/lambda.hpp>
//#include <boost/foreach.hpp>
#include <string>
#include <vector> 
#include "Maro.h"
#include <boost/shared_ptr.hpp>
#include "imebra.h"
//#include "../include/viewHelper.h"
//#include "../include/image.h"
//#include "windows.h"

//#define _WIN32_WINNT 0x400

using namespace std;
using namespace puntoexe;
//using namespace boost::lambda;

int imebra_test_function()
{
	std::vector <double> vec_doub = { 1, 1.1, 1.2, 3.2, -8.8 };
	//typedef std::istream_iterator<int> in;
	/*BOOST_FOREACH(double x, vec_doub){
	cout << x << "\t";
	}*/
	//create a filestream and open dicom file
	ptr<stream> readStream(new stream);
	//readStream->openFile("C:\\Users\\maro\\Documents\\DicomFiles\\PNEUMATIX\\Cardiovascular Heart-Cardiac Function\\cine_retro_aortic arch\\IM-0001-0011.dcm", std::ios::in);
	//readStream->openFile("C:\\Users\\maro\\Documents\\DicomFiles\\KNIX\\Knee (R)\\Sag FSE T2 - 6\\IM-0001-0011.dcm", std::ios::in);
	readStream->openFile("C:\\Users\\maro\\Documents\\DicomFiles\\digest_article\\brain_001.dcm", std::ios::in);
	//parse content of the file
	ptr<streamReader> reader(new streamReader(readStream));
	//create dataSet structure, that contains the dicom tags defined in the file
	// Get a codec factory and let it use the right codec to create a dataset
	//  from the input stream	
	//ptr<imebra::codecs::codecFactory> codecsFactory(imebra::codecs::codecFactory::getCodecFactory());
	//ptr<imebra::dataSet> testDataSet1 = imebra::codecs::codecFactory
	ptr<imebra::dataSet> testDataSet = imebra::codecs::codecFactory::getCodecFactory()->load(reader);
	//ptr<imebra::dataSet> testDataSet = codecsFactory->load(reader);

	//read patients name
	string patientNameCharacter = testDataSet->getString(0x0010, 0, 0x0010, 0);
	string patientNameIdeographic = testDataSet->getString(0x0010, 0, 0x0010, 1);
	//print patient neme
	cout << "patients name: " << patientNameCharacter << endl;
	cout << "patients name ideographic: " << patientNameIdeographic << endl;

	//read image
	ptr<imebra::image> firstImage = testDataSet->getImage(0);
	//image should be processed by the modalityVOILUT
	ptr<imebra::transforms::transform> modVOILUT(new imebra::transforms::modalityVOILUT(testDataSet));
	imbxUint32 width, height;
	firstImage->getSize(&width, &height);
	//print image size
	cout << "image width: " << width << " pixels" << endl;
	cout << "image height: " << height << " pixels" << endl;
	ptr<imebra::image> convertedImage(modVOILUT->allocateOutputImage(firstImage, width, height));
	modVOILUT->runTransform(firstImage, 0, 0, width, height, convertedImage, 0, 0);

	//sometimes further processing may be required for presentation on the screen
	//voilut is used for converting pixel values to something that makes sense
	ptr<imebra::transforms::VOILUT> myVoiLut(new imebra::transforms::VOILUT(testDataSet));
	//Apply the first VOI or LUT (Value Of Interest or smthing, just guessing?)
	imbxUint32 lutId = myVoiLut->getVOILUTId(0);
	myVoiLut->setVOILUT(lutId);
	//prepare image for presentation
	ptr<imebra::image> presentationImage(myVoiLut->allocateOutputImage(convertedImage, width, height));
	myVoiLut->runTransform(convertedImage, 0, 0, width, height, presentationImage, 0, 0);

	//print information about presentation image
	double mm_width, mm_height;
	cout << "Number of channels : " << presentationImage->getChannelsNumber() << endl;
	cout << "Depth : " << presentationImage->getDepth() << endl;
	cout << "High bit : " << presentationImage->getHighBit();
	presentationImage->getSizeMm(&mm_width, &mm_height);
	cout << "height in mm : " << mm_height << endl;
	cout << "width in mm : " << mm_width << endl;

	//convert image to RGB
	imebra::transforms::colorTransforms::colorTransformsFactory * pFactory = imebra::transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory();
	ptr<imebra::transforms::transform> myColorTransform = pFactory->getTransform(presentationImage->getColorSpace(), L"RGB");
	if (myColorTransform == 0){ //don't need any transformation if factory returns 0
		ptr<imebra::image> rgbPresentationImage(myColorTransform->allocateOutputImage(presentationImage, width, height));
		myColorTransform->runTransform(presentationImage, 0, 0, width, height, rgbPresentationImage, 0, 0);
	}

	//acces image pixels
	//and save it to file .txt
	//ofstream
	ofstream output_file("C:\\Users\\maro\\Documents\\Visual Studio 2013\\Projects\\SIM_Projekt\\txt files\\dicom_values.txt");
	//imebra
	imbxUint32 rowSize, channelPixelSize, channelNumber;
	ptr<imebra::handlers::dataHandlerNumericBase> myHandler = presentationImage->getDataHandler(false, &rowSize, &channelNumber, &channelNumber);
	//Retrive image's size in pizels
	imbxUint32 sizeX, sizeY;
	presentationImage->getSize(&sizeX, &sizeY);
	//scan all the rows
	imbxUint32 index(0);
	for (imbxUint32 scanY = 0; scanY < sizeY; ++scanY){
		//output_file << "" << scanY << "\t";
		//scan all the colums
		for (imbxUint32 scanX = 0; scanX < sizeX; ++scanX){
			for (imbxUint32 scanChannel = 0; scanChannel < channelNumber; ++scanChannel){
				imbxInt32 channelValue = myHandler->getSignedLong(index++);
				output_file << channelValue << " ";
			}
			output_file << ",";
		}
		output_file << ";" << endl;
	}

	output_file.close();

	return 0;
}

namespace puntoexe
{
	namespace imebra
	{
		myView::myView(imbxInt32 rowByteAlign, bool bBGR)
			:view(rowByteAlign, bBGR)
		{

		}
		void myView::getWindowSize(imbxUint32* pSizeX, imbxUint32* pSizeY)
		{
			/// \brief Overwrite this method with a function that
			///         retrieve the size of the window's client area,
			///         in screen's pixels.
			///
			/// @param pSizeX    a pointer to the value that the
			///                   function fills with the window's
			///                   width, in pixels
			/// @param pSizeY    a pointer to the value that the
			///                   function fills with the window's
			///                   height, in pixels
			///
			///////////////////////////////////////////////////////////
		}
		void myView::getScrollSize(imbxUint32* pScrollSizeX, imbxUint32* pScrollSizeY)
		{
			/// \brief Overwrite this method with a function that
			///         retrieves the total virtual size of the window.
			///
			/// The virtual size is the size managed by the window's
			///  scroll bars, in screen's pixels.
			///
			/// @param pScrollSizeX a pointer to the value that the
			///                      function fills with the window's
			///                      virtual width, in pixels
			/// @param pScrollSizeY a pointer to the value that the
			///                      function fills with the window's
			///                      virtual height, in pixels
			///
			///////////////////////////////////////////////////////////
		}

		void myView::setScrollSize(imbxUint32 newScrollSizeX, imbxUint32 newScrollSizeY, bool bInvalidate)
		{
			/// \brief Overwrite this method with a function that sets
			///         the window's virtual size.
			///
			/// The virtual size is the size managed by the window's
			///  scroll bars, in screen's pixels.
			///
			/// @param newScrollSizeX  the virtual window's width that
			///                         must be set
			/// @param newScrollSizeY  the virtual window's height that
			///                         must be set
			/// @param bInvalidate     is true if the function must
			///                         invalidate the window after
			///                         changing the virtual size,
			///                         false otherwise.
			///                         Note that the background
			///                          doesn't need to be invalidated
			///
			///////////////////////////////////////////////////////////
		}


		void myView::getScrollPosition(imbxInt32* pScrollX, imbxInt32* pScrollY)
		{
			/// \brief Overwrite this method with a function that
			///         retrieves the current position in the scroll
			///         bars, in screen's pixels.
			///
			/// @param pScrollX    a pointer to a variable that the
			///                     function must fill with the
			///                     horizontal scroll bar's position
			/// @param pScrollY    a pointer to a variable that the
			///                     function must fill with the
			///                     vertical scroll bar's position
			///
			///////////////////////////////////////////////////////////
		}


		void myView::setScrollPosition(imbxInt32 scrollX, imbxInt32 scrollY)
		{
			/// \brief Overwrite this method with a function that
			///         changes the position in the scroll bars, in
			///         screen's pixels.
			///
			/// @param scrollX  the new position for the horizontal
			///                  scroll bar, in pixels
			/// @param scrollY  the new position for the vertical
			///                  scroll bar, in pixels
			///
			///////////////////////////////////////////////////////////
		}


		void myView::drawRectangle(void* pDeviceContext, imbxInt32 left, imbxInt32 top, imbxInt32 right, imbxInt32 bottom, imbxUint8 colorRed, imbxUint8 colorGreen, imbxUint8 colorBlue)
		{
			/// \brief Overwrite this method with a function that
			///         draws a rectangle on a device context.
			///
			/// @param pDeviceContext a pointer to a device context
			///                        class. Is the same pointer
			///                        that your application passes
			///                        to the draw() or the
			///                        drawCursor() functions.
			/// @param left           the horizontal coordinate of the
			///                        rectangle's top-left corner
			/// @param top            the vertical coordinate of the
			///                        rectangle's top-left corner
			/// @param right          the horizontal coordinate of the
			///                        rectangle's bottom-right corner
			/// @param bottom         the vertical coordinate of the
			///                        rectangle's bottom-right corner
			/// @param colorRed       the red component of the
			///                        rectangle's color
			/// @param colorGreen     the green component of the
			///                        rectangle's color
			/// @param colorBlue      the blue component of the
			///                        rectangle's color
			///
			///////////////////////////////////////////////////////////
		}

		void myView::drawBitmap(void* pDeviceContext, imbxInt32 left, imbxInt32 top, imbxInt32 right, imbxInt32 bottom, imbxUint32 bufferRowSizeBytes, imbxUint8* pBuffer)
		{
			/// \brief Overwrite this method with a function that
			///         draws a bitmap on the screen in the specified
			///         window's rectangle.
			///
			/// @param pDeviceContext the device context to use for
			///                        the drawing. This is the same
			///                        value that your application
			///                        passes to the draw() function
			/// @param left           the horizontal coordinate of the
			///                        top-left corner of the rectangle
			///                        that contains the bitmap
			/// @param top            the vertical coordinate of the
			///                        top-left corner of the rectangle
			///                        that contains the bitmap
			/// @param right          the horizontal coordinate of the
			///                        bottom-right corner of the
			///                        rectangle that contains the
			///                        bitmap
			/// @param bottom         the vertical coordinate of the
			///                        bottom-right corner of the
			///                        rectangle that contains the
			///                        bitmap
			/// @param bufferRowSizeBytes the size of a bitmap's row,
			///                        in bytes
			/// @param pBuffer        a pointer to an array if bytes
			///                        representing the bitmap.
			///
			///////////////////////////////////////////////////////////
		}

		void myView::drawCursorLine(void* pDeviceContext, imbxInt32 startPointX, imbxInt32 startPointY, imbxInt32 endPointX, imbxInt32 endPointY, imbxUint8 colorRed, imbxUint8 colorGreen, imbxUint8 colorBlue, cursorLine::tStyle style, imbxUint32 width)
		{
			/// \brief Overwrite this method with a function that
			///         draws a line on the specified device context.
			///
			/// @param pDeviceContext the device context to use for
			///                        the drawing. This is the same
			///                        value that your application
			///                        passes to the drawCursor()
			///                        function
			/// @param startPointX    the horizontal coordinate of the
			///                        line's starting point, in
			///                        pixels
			/// @param startPointY    the vertical coordinate of the
			///                        line's starting point, in
			///                        pixels
			/// @param endPointX      the horizontal coordinate of the
			///                        line's ending point, in
			///                        pixels
			/// @param endPointY      the vertical coordinate of the
			///                        line's ending point, in
			///                        pixels
			/// @param colorRed       the red component of the
			///                        line's color
			/// @param colorGreen     the green component of the
			///                        line's color
			/// @param colorBlue      the blue component of the
			///                        line's color
			/// @param style          the line's style. It can be one
			///                        of the following values:
			///                        - cursorLine::line
			///                        - cursorLine::dotted
			/// @param width          the line's width, in pixels.
			///                       0 means really thin.
			///
			///////////////////////////////////////////////////////////
		}

		void myView::invalidate()
		{
			/// \brief Overwrite this method with a function that
			///         invalidate the window, without
			///         redrawing it immediatly. The code doesn't
			///         have to invalidate the background.
			///
			///////////////////////////////////////////////////////////
		}


		void myView::updateWindow()
		{
			/// \brief Overwrite this method with a function that
			///         launches a redraw of the invalidated areas of
			///         the window.
			///
			///////////////////////////////////////////////////////////
		}

		void myView::getScreenDPI(imbxUint32* pHorzDPI, imbxUint32* pVertDPI)
		{
			/// \brief Overwrite this method with a function that
			///         retrieve the screen's resolution, in pixels
			///         per inch.
			///
			/// @param pHorzDPI a pointer to a variable that the
			///                  function must fill with the
			///                  horizontal resolution, in pixels
			///                  per inch
			/// @param pVertDPI a pointer to a variable that the
			///                  function must fill with the
			///                  vertical resolution, in pixels
			///                  per inch
			///
			///////////////////////////////////////////////////////////
		}

		bool myView::isMouseCaptured()
		{

			return false;
		}


		int testView(imbxUint32 frameNumber, std::string fileName)
		{
			cout << "testView begin" << endl;
			string path = "C:\\Users\\maro\\Documents\\DicomFiles\\digest_article\\brain_001.dcm";
			cout << "frame number = " << frameNumber << endl;
			cout << "file name = " << fileName << endl;

			ptr<stream> readStream(new stream);
			readStream->openFile(fileName, std::ios::in);
			//parse content of the file
			ptr<streamReader> reader(new streamReader(readStream));
			//create dataSet structure, that contains the dicom tags defined in the file
			//Get a codec factory and let it use the right codec to create a dataset
			//from the input stream	
			ptr<dataSet> testDataSet = codecs::codecFactory::getCodecFactory()->load(reader);
			//read image
			ptr<image> firstImage = testDataSet->getImage(frameNumber);
			imbxUint32 width, height;
			firstImage->getSize(&width, &height);
			// Build the transforms chain
			ptr<transforms::transformsChain> chain(new transforms::transformsChain);
			//image should be processed by the modalityVOILUT
			ptr<transforms::transform> modVOILUT(new transforms::modalityVOILUT(testDataSet));
			chain->addTransform(modVOILUT);
			ptr<image> convertedImage(modVOILUT->allocateOutputImage(firstImage, width, height));
			//modVOILUT->runTransform(firstImage, 0, 0, width, height, convertedImage, 0, 0);
			//sometimes further processing may be required for presentation on the screen
			//voilut is used for converting pixel values
			ptr<transforms::VOILUT> myVoiLut(new transforms::VOILUT(testDataSet));
			//Apply the first VOI or LUT
			imbxUint32 lutId = myVoiLut->getVOILUTId(0);
			myVoiLut->setVOILUT(lutId);
			//prepare image for presentation
			ptr<image> presentationImage(myVoiLut->allocateOutputImage(convertedImage, width, height));
			myVoiLut->runTransform(convertedImage, 0, 0, width, height, presentationImage, 0, 0);
			//chain->addTransform(myVoiLut);

			//====================================================================================================View Test
			imbxInt32 iheight = height;
			imbxInt32 iwidth = width;

			myView myViewer(1, false);
			myViewer.setImage(convertedImage, chain);

			drawBitmap testBitmap(convertedImage, chain);
			//ptr<unsigned> bitMapMemory = NULL;
			testBitmap.getBitmap<drawBitmapBGRA, 1 >(iheight, iwidth, (imbxInt32)0, (imbxInt32)0, iheight, iwidth, NULL);
			//myViewer.draw()
			//viev is an abstract class
			//====================================================================================================View Test

			cout << "testView end" << endl;

			return 0;
		}
	}
}
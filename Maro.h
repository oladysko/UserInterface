#ifndef _MARO_H_
#define _MARO_H_
#include "viewHelper.h"


int imebra_test_function();

namespace puntoexe
{

	namespace imebra
	{
		class myView : public view
		{
		public:
			myView(imbxInt32 rowByteAlign, bool bBGR);

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
			void getWindowSize(imbxUint32* pSizeX, imbxUint32* pSizeY);

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
			void getScrollSize(imbxUint32* pScrollSizeX, imbxUint32* pScrollSizeY);

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
			void setScrollSize(imbxUint32 newScrollSizeX, imbxUint32 newScrollSizeY, bool bInvalidate);

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
			void getScrollPosition(imbxInt32* pScrollX, imbxInt32* pScrollY);

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
			void setScrollPosition(imbxInt32 scrollX, imbxInt32 scrollY);

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
			void drawRectangle(void* pDeviceContext, imbxInt32 left, imbxInt32 top, imbxInt32 right, imbxInt32 bottom, imbxUint8 colorRed, imbxUint8 colorGreen, imbxUint8 colorBlue);

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
			void drawBitmap(void* pDeviceContext, imbxInt32 left, imbxInt32 top, imbxInt32 right, imbxInt32 bottom, imbxUint32 bufferRowSizeBytes, imbxUint8* pBuffer);

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
			void drawCursorLine(void* pDeviceContext, imbxInt32 startPointX, imbxInt32 startPointY, imbxInt32 endPointX, imbxInt32 endPointY, imbxUint8 colorRed, imbxUint8 colorGreen, imbxUint8 colorBlue, cursorLine::tStyle style, imbxUint32 width);

			/// \brief Overwrite this method with a function that
			///         invalidate the window, without
			///         redrawing it immediatly. The code doesn't
			///         have to invalidate the background.
			///
			///////////////////////////////////////////////////////////
			void invalidate();

			/// \brief Overwrite this method with a function that
			///         launches a redraw of the invalidated areas of
			///         the window.
			///
			///////////////////////////////////////////////////////////
			void updateWindow();

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
			void getScreenDPI(imbxUint32* pHorzDPI, imbxUint32* pVertDPI);

			bool isMouseCaptured();
		};
		int testView(imbxUint32 frameNumber, std::string fileName);
		namespace Maro
		{
			void getFrameSize(imbxUint32 frameNumber, std::string fileName, imbxUint32& height, imbxUint32& width);
			void getValuesMatrix(imbxUint32 frameNumber, std::string fileName, imbxUint32 height, imbxUint32 width, int * outputMatrix);
		}
	}
}

#endif
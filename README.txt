Program narazie podlg�da DICOM, po czym mo�na zapisa� obrazek, pozostawia wiele do �yczenia ale dzia�a.

Nie zmienia�bym nru. frame'u, nie tylko na pocz�tku ale i w og�le, najpro�ciej wybra� przycisk view,
wybra� odpowidni plik i cieszy� si� podgl�dem.

Mo�e wymaga� usuni�cia �cie�ki obrazka z pictureBoxa (domy�lnego)

Podczas ogl�dania nowych bitmap stare nie s� usuwane, co mo�e skutkowa� "memory leaking",
ale powinno si� to �atwo naprawi� poprzez wprowadzenie bitmapy tymczasowej

Maro.cpp s� zdefiniowane funkcje do obs�ugi imebry (namespace puntoexe::imebra::Maro)
	myView::myView: do usuni�cia, z reszt� ca�a klasa myView jest do usuni�cia
	testView: do usuni�cia
	getFrameSize: pobiera rozmiar frame'u
	getValuesMatrix: przetwarza warto�ci pixeli (woxeli) na tablic� dwuwymiarow� int�w
	 

Parser.cpp Po�redniczy pomi�dzy GUI i imebr� (ParserH::)
	MarshalString: Konwertuje string z c# String do std::string (C++), �eby mog�a go u�ywa� imebra
	fileNametoPath: podwaja \ �eby imebra mog�a odczyta� �cie�k�
	getImageSize: odczytuje rozmiar obrazu
	getBitmap: konwertuje obaz do bitmapy UWAGA: ka�dy obraz jest normalizowany do warto�ci od 0 do 255,
		je�eli jest tworzone video to to mo�e by� u�ywaana normalizacja, ale do maksymalnej warto�ci ze
		wszystkich obraz�w, a nie z jednego

MainWindow.cpp
	
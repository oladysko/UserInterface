Program narazie podlg¹da DICOM, po czym mo¿na zapisaæ obrazek, pozostawia wiele do ¿yczenia ale dzia³a.

Nie zmienia³bym nru. frame'u, nie tylko na pocz¹tku ale i w ogóle, najproœciej wybraæ przycisk view,
wybraæ odpowidni plik i cieszyæ siê podgl¹dem.

Mo¿e wymagaæ usuniêcia œcie¿ki obrazka z pictureBoxa (domyœlnego)

Podczas ogl¹dania nowych bitmap stare nie s¹ usuwane, co mo¿e skutkowaæ "memory leaking",
ale powinno siê to ³atwo naprawiæ poprzez wprowadzenie bitmapy tymczasowej

Maro.cpp s¹ zdefiniowane funkcje do obs³ugi imebry (namespace puntoexe::imebra::Maro)
	myView::myView: do usuniêcia, z reszt¹ ca³a klasa myView jest do usuniêcia
	testView: do usuniêcia
	getFrameSize: pobiera rozmiar frame'u
	getValuesMatrix: przetwarza wartoœci pixeli (woxeli) na tablicê dwuwymiarow¹ intów
	 

Parser.cpp Poœredniczy pomiêdzy GUI i imebr¹ (ParserH::)
	MarshalString: Konwertuje string z c# String do std::string (C++), ¿eby mog³a go u¿ywaæ imebra
	fileNametoPath: podwaja \ ¿eby imebra mog³a odczytaæ œcie¿kê
	getImageSize: odczytuje rozmiar obrazu
	getBitmap: konwertuje obaz do bitmapy UWAGA: ka¿dy obraz jest normalizowany do wartoœci od 0 do 255,
		je¿eli jest tworzone video to to mo¿e byæ u¿ywaana normalizacja, ale do maksymalnej wartoœci ze
		wszystkich obrazów, a nie z jednego

MainWindow.cpp
	
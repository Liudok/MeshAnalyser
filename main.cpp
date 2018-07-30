#include "MeshAnalyser.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "ObjParser.h"
#include <iostream>
#include<string>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (argc < 2)
	{
		QMessageBox noObjToParseMessage;
		noObjToParseMessage.critical(0, "Error", "No *.obj file to parse! :(");
		noObjToParseMessage.setFixedSize(700, 200);
		return -1;
	}

	MeshAnalyser w;
	try {
		Mesh ourMesh = parseObjFile(argv[1]);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	w.show();
	return a.exec();
}

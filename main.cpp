#include "MeshAnalyser.h"
#include <QtWidgets/QApplication>
#include "ObjParser.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MeshAnalyser w;
	try {
		parseObjFile("C:\\Users\\noprysk\\Source\\Repos\\MeshAnalyser2\\sphere.obj");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	w.show();
	return a.exec();
}

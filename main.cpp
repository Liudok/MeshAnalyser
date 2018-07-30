#include "MeshAnalyser.h"
#include <QtWidgets/QApplication>
#include "ObjParser.h"
#include <iostream>
#include "LogicLib/logic.h"

int main(int argc, char *argv[])
{
	std::cout << mySum(10, 20) << std::endl;
	QApplication a(argc, argv);
	MeshAnalyser w;
	try {
		Mesh ourMesh = parseObjFile("C:\\Users\\noprysk\\Source\\Repos\\MeshAnalyser2\\sphere.obj");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	w.show();
	return a.exec();
}

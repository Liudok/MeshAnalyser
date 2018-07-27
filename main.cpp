#include "MeshAnalyser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MeshAnalyser w;
	w.show();
	return a.exec();
}

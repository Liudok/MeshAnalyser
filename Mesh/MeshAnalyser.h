#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MeshAnalyser.h"

class MeshAnalyser : public QMainWindow
{
	Q_OBJECT

public:
	MeshAnalyser(QWidget *parent = Q_NULLPTR);

private:
	Ui::MeshAnalyserClass ui;
};

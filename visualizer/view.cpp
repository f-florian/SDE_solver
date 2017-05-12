#include "view.h"
#include "ui_view.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <forward_list>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QFileDialog>

using namespace std;

View::View(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::View)
{
	ui->setupUi(this);
	ui->centralwidget->setLayout(ui->mainLO);
}

View::~View()
{
	delete ui;
}

//void View::load(char *filename)
//{
//	FILE *tmp=fopen(filename, "r");

//}

void View::load(istream &input)
{
	QGraphicsScene scene;
//	double current, previous, step, clock;
//	if(input.eof())
//		return;
//	input >> step;
//	step/=100;
//	printf("a\n");
//	fflush(stdout);
//	if(input.eof())
//		return;
//	printf("a\n");
//	fflush(stdout);
//	input >> previous;
//	for(clock=0;!input.eof();clock+=step)
//	{
//		printf("%lf ", clock);
//		fflush(stdout);
//		input >> current;
//		scene.addLine(clock, previous, clock+step, current);
//		swap(current, previous);
//	}
//	scene.addLine(0,0,10,10);
//	scene.addLine(0,0,-1000,10);
//	scene.addRect(2,2,3,3,QPen(),QBrush(Qt::black,Qt::SolidPattern));
	scene.addText("Hello, world!");
	ui->view->setScene(&scene);
	ui->view->centerOn(0,0);
	ui->view->setFrameRect(QRect(-10, 100, 100, 100));
	ui->view->show();
}

void View::on_actionOpen_file_triggered()
{
	ifstream in;
//	in.open(QFileDialog::getOpenFileName(this, "Open data file").toStdString());
	load(in);
//	in.close();
}

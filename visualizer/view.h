#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <iostream>

namespace Ui {
	class View;
}

class View : public QMainWindow
{
	Q_OBJECT

public:
	explicit View(QWidget *parent = 0);
	~View();
	void load(std::istream &input);

private slots:
	void on_actionOpen_file_triggered();

private:
	Ui::View *ui;	
};

#endif // VIEW_H

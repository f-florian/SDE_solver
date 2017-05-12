#include <cstdio>
#include <QtWidgets/QApplication>

#include "view.h"

using namespace std;

int main(int argc, char *argv[])
{
		QApplication a(argc, argv);
		View window;
		window.show();
		a.setApplicationName(cmake_NAME);
		a.setApplicationVersion(QString("%1.%2").arg(cmake_MAJOR).arg(cmake_MINOR));

		return a.exec();
}

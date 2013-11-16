#include "dadero.h"
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	Dadero dadero;
	dadero.show();

	return dadero.exec();
}
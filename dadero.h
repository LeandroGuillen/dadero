#ifndef DADERO_H
#define DADERO_H

#include "ui_dadero.h"
#include <QtGui>

class Dadero : public QDialog, public Ui::dialogo
{
	Q_OBJECT
    public:
	Dadero(QWidget* parent=0);

    private slots:
	void procesarLinea();
	void ayuda();
	void creditos();

    private:
	bool validarDado();
	QString calcularDados(QStringList& listaDados);
};


#endif

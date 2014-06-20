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

    void click4(){  clickN(4);  }
    void click6(){  clickN(6);  }
    void click10(){ clickN(10); }
    void click12(){ clickN(12); }
    void click20(){ clickN(20); }

private:
    void clickN(int n);
    bool validarDado();
    QString calcularDados(QStringList& listaDados);
};


#endif

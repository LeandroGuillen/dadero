#include "dadero.h"
#include <QRegExp>
#include <QTime>
#include <QMessageBox>

Dadero::Dadero(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
	QObject::connect ( linea, SIGNAL ( returnPressed() ), this, SLOT ( procesarLinea() ) );
	QObject::connect ( botonAyuda, SIGNAL ( clicked() ), this, SLOT ( ayuda() ) );
	// BUG: He tenido que desactivar esta linea porque cada vez que pulsas intro...
	// ... aparecen los creditos.
	//QObject::connect ( botonCreditos, SIGNAL ( clicked() ), this, SLOT ( creditos() ) );
}


void Dadero::procesarLinea()
{
	if(validarDado())
	{
		QStringList listaDados=linea->text().split(" ");
		QString mensaje=calcularDados(listaDados);

		if(!(mensaje=="OK"))
		{
			// Si ha ocurrido algun error lo mostramos en el cuadro de texto
			QFont fuente=cajaTexto->currentFont();
			QFont nuevaFuente(fuente.family(), fuente.pointSize(), QFont::Bold, true);
			cajaTexto->setCurrentFont(nuevaFuente);
			cajaTexto->setTextColor(Qt::red);
			cajaTexto->append(mensaje);
			cajaTexto->setTextColor(Qt::black);
			cajaTexto->setCurrentFont(fuente);

		}
	}
	else
	{
// 		linea->clear();
	}

}

bool Dadero::validarDado()
{
	/* Expresion regular:
	1.	<numero>x	Numero de veces que se tirara ese combinacion
	2.	nDm		n veces se tira el dado de m caras
	3.	+t | -t		Modificador de mas o menos t
	4.	A+B		Suma dos tiradas
	5.	A-B		Resta dos tiradas
	6.	A,B,C, ...	Realiza tiradas independientes
	*/
	QRegExp reg("(\\d+[dD]\\d+[\\+\\-]?\\d*)([\\+\\-, ]((\\d+[xX])?\\d+[dD]\\d+[\\+\\-]?\\d*))*");
	return reg.exactMatch(linea->text());
}

QString Dadero::calcularDados(QStringList& listaDados)
{
	QString res="<";
	res+=QTime::currentTime().toString("hh:mm:ss");
	res+="> ";
	for(int i=0; i<listaDados.size(); i++)
	{
		int veces, carasDado, modificador;
		QStringList num=listaDados[i].split("d");
		veces=num[0].toInt();

		if(veces==0) return "No puedo tirar un dado 0 veces!";

		if(num[1].contains("+"))
		{
			QStringList num2=num[1].split("+");
			carasDado=num2[0].toInt();
			modificador=num2[1].toInt();
		}
		else if(num[1].contains("-"))
		{
			QStringList num2=num[1].split("-");
			carasDado=num2[0].toInt();
			modificador=-(num2[1].toInt());
		}
		else
		{
			carasDado=num[1].toInt();
			modificador=0;
		}
		if(carasDado==0) return "No puedo tirar un dado de 0 caras!";

		res+="[";
		int total=0;
		QString temp;
		for(int j=0; j<veces; j++)
		{
			if(j>0) res+="+";
			int n=((qrand()%carasDado)+1)+modificador;
			temp.setNum(n);
			total+=n;
			res+=temp;
		}
		temp.setNum(total);
		res+="="+temp+"] ";


	}
	// Si hemos llegado hasta aqui, todo correcto: imprime el resultado
	cajaTexto->setTextColor(Qt::blue);
	cajaTexto->append(res);
	cajaTexto->setTextColor(Qt::black);

	return "OK";
}

void Dadero::ayuda()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Ayuda");
	msgBox.setText("Ejemplos de uso:");
	QString msj="1d6    --> tira un dado de 6.\n2d6+1  --> tira dos dados de 6 mas 1.\n3D4-1  --> tira 3 dados de 4 menos 1.";
	msgBox.setInformativeText(msj);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

void Dadero::creditos()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Creditos");
	msgBox.setText("Dadero Beta. Programa para lanzar dados para Qt.\nCreado por Leandro J. Guillen.\nHerramientas utilizadas: Kate+QtDesigner. Use con moderacion.");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

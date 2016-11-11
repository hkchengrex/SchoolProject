#include "main_window.h"
//#include "point.h"
#include <vector>
#include <iostream>
#include <QTextStream>

using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
 
 	QString name(argv[1]);
    QFile file(name);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		exit(1);
	}

	QString str(file.readAll());
	QTextStream myStream(&str);

	int N;
	myStream >> N;

	vector<Point*> pts(N);
	for (int i=0; i<N; i++){
		int x, y;
		myStream >> x >> y;
		pts[i] = new Point(x, y);
	}

    MainWindow *window = new MainWindow(pts);
    window->show();
    return app.exec();
}

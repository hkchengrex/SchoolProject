#include "main.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
 
    GameWindow *window = GameWindow::getWindow();
    window->show();
    return app.exec();
}

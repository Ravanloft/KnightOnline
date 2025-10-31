// main.cpp: QtN3Viewer uygulamasının ana entry point'i

#include "MainWindow.h"
#include <QtWidgets/QApplication>

#ifdef USE_QT_DIRECT3D

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}

#else

#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "QtDirect3D desteği aktif değil. USE_QT_DIRECT3D preprocessor tanımını ekleyin." << std::endl;
    return 1;
}

#endif // USE_QT_DIRECT3D

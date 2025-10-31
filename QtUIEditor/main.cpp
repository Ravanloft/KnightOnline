// main.cpp: QtUIEditor - Knight Online UI Editor

#include "MainWindow.h"
#include <QtWidgets/QApplication>

#ifdef USE_QT_DIRECT3D

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Application bilgileri
    a.setApplicationName("Knight Online UI Editor");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("OpenKO");
    
    MainWindow w;
    w.show();
    
    return a.exec();
}

#else

#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "QtDirect3D desteği aktif değil!" << std::endl;
    return 1;
}

#endif // USE_QT_DIRECT3D

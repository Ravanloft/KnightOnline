// MainWindow.cpp: QtN3Viewer ana pencere implementasyonu

#ifdef USE_QT_DIRECT3D

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QAction>
#include <QCloseEvent>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

// QtDirect3D widget
#include <QDirect3D9Widget.h>

// UI dosyası
#include "ui_MainWindow.h"

// QtDirect3D Adapter
#include "../shared/QtDirect3DAdapter.h"

// Knight Online N3Base
#include <N3Base/N3Eng.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui_MainWindowClass())
    , m_pD3DWidget(nullptr)
    , m_pAdapter(nullptr)
    , m_pN3Eng(nullptr)
{
    m_ui->setupUi(this);
    setupUI();
    connectSignals();

    // N3Eng instance'ını oluştur
    // Not: N3Eng constructor'ı Direct3D9'u initialize eder
    // Ancak biz Qt widget'ın device'ını kullanacağız
    m_pN3Eng = new CN3Eng();

    // QtDirect3D9Widget'ı oluştur (UI'da central widget olarak set edilmiş olmalı)
    // Eğer UI'da yoksa, programatik olarak oluşturabiliriz
}

MainWindow::~MainWindow()
{
    // Adapter'ı temizle (N3Eng'i de temizler)
    if (m_pAdapter)
    {
        m_pAdapter->CleanupN3Eng();
        delete m_pAdapter;
        m_pAdapter = nullptr;
    }

    // N3Eng'i temizle
    if (m_pN3Eng)
    {
        delete m_pN3Eng;
        m_pN3Eng = nullptr;
    }

    delete m_ui;
}

void MainWindow::setupUI()
{
    // UI'da tanımlı QDirect3D9Widget'ı al
    // UI dosyasında "view" isimli widget QDirect3D9Widget olarak tanımlanmış
    m_pD3DWidget = qobject_cast<QDirect3D9Widget*>(m_ui->view);
    
    if (!m_pD3DWidget)
    {
        // Eğer UI'da yoksa, programatik olarak oluştur
        m_pD3DWidget = new QDirect3D9Widget(this);
        setCentralWidget(m_pD3DWidget);
    }
}

void MainWindow::connectSignals()
{
    // QtDirect3D widget'ın signal'larını bağla
    if (m_pD3DWidget)
    {
        connect(m_pD3DWidget, &QDirect3D9Widget::deviceInitialized,
                this, &MainWindow::onDeviceInitialized);
        connect(m_pD3DWidget, &QDirect3D9Widget::ticked,
                this, &MainWindow::onTick);
        connect(m_pD3DWidget, &QDirect3D9Widget::rendered,
                this, &MainWindow::onRender);
    }
    
    // Menu action'larını bağla
    if (m_ui)
    {
        connect(m_ui->actionOpen, &QAction::triggered,
                this, &MainWindow::onActionOpen);
        connect(m_ui->actionExit, &QAction::triggered,
                this, &MainWindow::onActionExit);
    }
}

void MainWindow::onDeviceInitialized(bool success)
{
    if (!success)
    {
        QMessageBox::critical(this, "Hata", 
                             "Direct3D9 device başlatılamadı!\n"
                             "DirectX 9 SDK'nın yüklü olduğundan emin olun.");
        return;
    }

    // Adapter'ı oluştur ve N3Eng'i initialize et
    if (m_pD3DWidget && m_pN3Eng)
    {
        m_pAdapter = new CQtDirect3DAdapter(m_pD3DWidget, this);
        
        QSize widgetSize = m_pD3DWidget->size();
        if (m_pAdapter->InitializeN3Eng(m_pN3Eng, 
                                       widgetSize.width(), 
                                       widgetSize.height(), 
                                       true,  // windowed
                                       32,    // 32-bit color
                                       true)) // hardware vertex processing
        {
            // Render loop'u başlat
            QTimer::singleShot(500, this, [this]() {
                if (m_pD3DWidget)
                {
                    m_pD3DWidget->run();
                }
            });
        }
    }
}

void MainWindow::onTick()
{
    // Her frame'de güncellenecek işlemler
    // Örneğin: animasyon, fizik, input handling
    
    if (m_pN3Eng && m_pAdapter && m_pAdapter->IsRenderActive())
    {
        // N3Eng tick işlemleri burada çağrılabilir
        // Örnek: m_pN3Eng->Update();
    }
}

void MainWindow::onRender()
{
    // Her frame'de render edilecek işlemler
    
    if (m_pN3Eng && m_pAdapter && m_pAdapter->IsRenderActive())
    {
        // Scene'i render et
        // CN3Base::Clear(0xFF000000); // Siyah arka plan
        
        // ... render models, meshes, etc. ...
        
        // Present işlemi Qt widget tarafından yapılıyor
    }
}

void MainWindow::onActionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Knight Online Model Dosyası Aç",
        "",
        "N3 Files (*.N3);;All Files (*.*)"
    );

    if (!fileName.isEmpty())
    {
        // Model dosyasını yükle
        // Örnek: LoadModel(fileName);
        QMessageBox::information(this, "Bilgi", 
                                QString("Model yüklenecek: %1").arg(fileName));
    }
}

void MainWindow::onActionExit()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    // Widget'ı durdur
    if (m_pD3DWidget)
    {
        m_pD3DWidget->release();
    }

    // Kısa bir gecikme (kaynakların temizlenmesi için)
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    event->accept();
}

#endif // USE_QT_DIRECT3D

// MainWindow.cpp: Qt UI Editor Ana Pencere Implementasyonu

#ifdef USE_QT_DIRECT3D

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PropertyEditor.h"
#include "D3DViewWidget.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QCloseEvent>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>

// QtDirect3D
#include <QDirect3D9Widget.h>

// QtDirect3D Adapter
#include "../shared/QtDirect3DAdapter.h"

// Knight Online N3Base
#include <N3Base/N3Eng.h>
#include <N3Base/N3UIWndBase.h>
#include <N3Base/N3UIBase.h>
#include <N3Base/N3Base.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui_MainWindowClass())
    , m_pD3DWidget(nullptr)
    , m_pAdapter(nullptr)
    , m_pN3Eng(nullptr)
    , m_pCurrentUI(nullptr)
    , m_bIsModified(false)
    , m_pPropertyEditor(nullptr)
    , m_pHierarchyTree(nullptr)
    , m_pMainSplitter(nullptr)
    , m_pRightSplitter(nullptr)
    , m_pFileToolBar(nullptr)
    , m_pEditToolBar(nullptr)
    , m_pViewToolBar(nullptr)
{
    m_ui->setupUi(this);
    setupUI();
    setupToolBar();
    setupMenuBar();
    setupStatusBar();
    connectSignals();
    
    // N3Eng instance'ını oluştur
    m_pN3Eng = new CN3Eng();
    
    // Asset path'i ayarla (örnek)
    // Gerçek projede bu path'i ayarlardan alabilirsiniz
    CN3Base::PathSet(getAssetPath().toStdString().c_str());
    
    updateWindowTitle();
}

MainWindow::~MainWindow()
{
    // UI'yı temizle
    if (m_pCurrentUI)
    {
        delete m_pCurrentUI;
        m_pCurrentUI = nullptr;
    }
    
    // Adapter'ı temizle
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
    // Central widget - Splitter layout
    m_pMainSplitter = new QSplitter(Qt::Horizontal, this);
    
    // Sol panel - Hierarchy Tree
    m_pHierarchyTree = new QTreeWidget(m_pMainSplitter);
    m_pHierarchyTree->setHeaderLabel("UI Hierarchy");
    m_pHierarchyTree->setMinimumWidth(200);
    
    // Orta panel - Direct3D Widget (rendering + görsel düzenleme)
    m_pD3DWidget = new D3DViewWidget(m_pMainSplitter);
    m_pD3DWidget->setMinimumSize(640, 480);
    
    // Element seçimi signal'ını bağla
    connect(m_pD3DWidget, &D3DViewWidget::elementSelected,
            this, [this](CN3UIBase* pElement) {
                if (m_pPropertyEditor)
                {
                    m_pPropertyEditor->setUIElement(pElement);
                }
            });
    
    connect(m_pD3DWidget, &D3DViewWidget::elementMoved,
            this, [this](CN3UIBase* pElement) {
                m_bIsModified = true;
                updateWindowTitle();
            });
    
    // Sağ panel - Property Editor (GUI tabanlı)
    m_pRightSplitter = new QSplitter(Qt::Vertical, m_pMainSplitter);
    
    m_pPropertyEditor = new PropertyEditor(m_pRightSplitter);
    m_pPropertyEditor->setMinimumWidth(300);
    
    connect(m_pPropertyEditor, &PropertyEditor::propertyChanged,
            this, &MainWindow::onPropertyChanged);
    
    // Splitter'a ekle
    m_pMainSplitter->addWidget(m_pHierarchyTree);
    m_pMainSplitter->addWidget(m_pD3DWidget);
    m_pRightSplitter->addWidget(m_pPropertyEditor);
    m_pMainSplitter->addWidget(m_pRightSplitter);
    
    // Splitter oranları
    m_pMainSplitter->setStretchFactor(0, 0);
    m_pMainSplitter->setStretchFactor(1, 1);
    m_pMainSplitter->setStretchFactor(2, 0);
    
    setCentralWidget(m_pMainSplitter);
}

void MainWindow::setupToolBar()
{
    // File Toolbar
    m_pFileToolBar = addToolBar("File");
    m_pFileToolBar->addAction("New", this, &MainWindow::onActionNew);
    m_pFileToolBar->addAction("Open", this, &MainWindow::onActionOpen);
    m_pFileToolBar->addAction("Save", this, &MainWindow::onActionSave);
    m_pFileToolBar->addSeparator();
    
    // Edit Toolbar
    m_pEditToolBar = addToolBar("Edit");
    m_pEditToolBar->addAction("Undo", this, &MainWindow::onActionUndo);
    m_pEditToolBar->addAction("Redo", this, &MainWindow::onActionRedo);
    m_pEditToolBar->addSeparator();
    m_pEditToolBar->addAction("Copy", this, &MainWindow::onActionCopy);
    m_pEditToolBar->addAction("Paste", this, &MainWindow::onActionPaste);
    m_pEditToolBar->addAction("Delete", this, &MainWindow::onActionDelete);
}

void MainWindow::setupMenuBar()
{
    // File Menu
    QMenu* pFileMenu = menuBar()->addMenu("&File");
    pFileMenu->addAction("&New", this, &MainWindow::onActionNew, QKeySequence::New);
    pFileMenu->addAction("&Open...", this, &MainWindow::onActionOpen, QKeySequence::Open);
    pFileMenu->addSeparator();
    pFileMenu->addAction("&Save", this, &MainWindow::onActionSave, QKeySequence::Save);
    pFileMenu->addAction("Save &As...", this, &MainWindow::onActionSaveAs, QKeySequence::SaveAs);
    pFileMenu->addSeparator();
    
    QMenu* pLoadUIMenu = pFileMenu->addMenu("Load UI");
    pLoadUIMenu->addAction("Elmorad Inventory", [this]() { onActionLoadInventory("el"); });
    pLoadUIMenu->addAction("Karus Inventory", [this]() { onActionLoadInventory("ka"); });
    pLoadUIMenu->addAction("Trade Inventory", [this]() { loadUIFile(getUIPath() + "co_tradeinventory_us.uif"); });
    
    pFileMenu->addSeparator();
    pFileMenu->addAction("E&xit", this, &MainWindow::onActionExit, QKeySequence::Quit);
    
    // Edit Menu
    QMenu* pEditMenu = menuBar()->addMenu("&Edit");
    pEditMenu->addAction("&Undo", this, &MainWindow::onActionUndo, QKeySequence::Undo);
    pEditMenu->addAction("&Redo", this, &MainWindow::onActionRedo, QKeySequence::Redo);
    pEditMenu->addSeparator();
    pEditMenu->addAction("Cu&t", this, &MainWindow::onActionCopy, QKeySequence::Cut);
    pEditMenu->addAction("&Copy", this, &MainWindow::onActionCopy, QKeySequence::Copy);
    pEditMenu->addAction("&Paste", this, &MainWindow::onActionPaste, QKeySequence::Paste);
    pEditMenu->addAction("&Delete", this, &MainWindow::onActionDelete, QKeySequence::Delete);
    
    // View Menu
    QMenu* pViewMenu = menuBar()->addMenu("&View");
    // View menü öğeleri buraya eklenebilir
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::connectSignals()
{
    // Direct3D widget signals
    if (m_pD3DWidget)
    {
        connect(m_pD3DWidget, &QDirect3D9Widget::deviceInitialized,
                this, &MainWindow::onDeviceInitialized);
        connect(m_pD3DWidget, &QDirect3D9Widget::ticked,
                this, &MainWindow::onTick);
        connect(m_pD3DWidget, &QDirect3D9Widget::rendered,
                this, &MainWindow::onRender);
    }
    
    // Hierarchy tree signals
    if (m_pHierarchyTree)
    {
        connect(m_pHierarchyTree, &QTreeWidget::itemSelectionChanged,
                this, &MainWindow::onSelectedUIElementChanged);
        connect(m_pHierarchyTree, &QTreeWidget::itemDoubleClicked,
                this, &MainWindow::onUIElementDoubleClicked);
    }
}

void MainWindow::onDeviceInitialized(bool success)
{
    if (!success)
    {
        QMessageBox::critical(this, "Error", 
                             "Direct3D9 device başlatılamadı!");
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
                                       true, 32, true))
        {
            // Render loop'u başlat
            QTimer::singleShot(500, this, [this]() {
                if (m_pD3DWidget)
                {
                    m_pD3DWidget->run();
                }
            });
            
            statusBar()->showMessage("Direct3D initialized successfully");
        }
    }
}

void MainWindow::onTick()
{
    // Tick işlemleri
}

void MainWindow::onRender()
{
    // UI'yı render et
    renderUI();
    
    // Seçili element varsa seçim çerçevesini çiz
    if (m_pD3DWidget && m_pD3DWidget->getSelectedElement())
    {
        // Seçim çerçevesi çizimi D3DViewWidget içinde yapılabilir
    }
}

void MainWindow::onActionNew()
{
    // Yeni UI oluştur
    if (m_bIsModified)
    {
        int ret = QMessageBox::warning(this, "Unsaved Changes",
                                       "Dosyada kaydedilmemiş değişiklikler var. "
                                       "Yeni dosya oluşturmak istiyor musunuz?",
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (ret != QMessageBox::Yes)
            return;
    }
    
    // Yeni UI oluştur
    if (m_pCurrentUI)
    {
        delete m_pCurrentUI;
        m_pCurrentUI = nullptr;
    }
    
    m_pCurrentUI = new CN3UIWndBase();
    m_sCurrentFilePath.clear();
    m_bIsModified = false;
    
    refreshUIHierarchy();
    updateWindowTitle();
}

void MainWindow::onActionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "UI Dosyası Aç",
        getUIPath(),
        "UI Files (*.uif);;All Files (*.*)"
    );
    
    if (!fileName.isEmpty())
    {
        loadUIFile(fileName);
    }
}

void MainWindow::onActionSave()
{
    if (m_sCurrentFilePath.isEmpty())
    {
        onActionSaveAs();
    }
    else
    {
        saveUIFile(m_sCurrentFilePath);
    }
}

void MainWindow::onActionSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "UI Dosyasını Kaydet",
        getUIPath(),
        "UI Files (*.uif);;All Files (*.*)"
    );
    
    if (!fileName.isEmpty())
    {
        saveUIFile(fileName);
    }
}

void MainWindow::onActionExit()
{
    close();
}

void MainWindow::onActionLoadInventory(const QString& nation)
{
    QString fileName;
    if (nation == "el")
        fileName = getUIPath() + "el_inventory_us.uif";
    else if (nation == "ka")
        fileName = getUIPath() + "ka_inventory_us.uif";
    else
        return;
    
    loadUIFile(fileName);
}

bool MainWindow::loadUIFile(const QString& filePath)
{
    if (filePath.isEmpty()) return false;
    
    // Mevcut UI'yı temizle
    if (m_pCurrentUI)
    {
        delete m_pCurrentUI;
        m_pCurrentUI = nullptr;
    }
    
    // Yeni UI oluştur ve yükle
    m_pCurrentUI = new CN3UIWndBase();
    
    // Knight Online'ın UI yükleme sistemi
    if (m_pCurrentUI->LoadFromFile(filePath.toStdString()))
    {
        m_sCurrentFilePath = filePath;
        m_bIsModified = false;
        
        refreshUIHierarchy();
        updateWindowTitle();
        
        statusBar()->showMessage(QString("Loaded: %1").arg(filePath));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error", 
                            QString("UI dosyası yüklenemedi:\n%1").arg(filePath));
        delete m_pCurrentUI;
        m_pCurrentUI = nullptr;
        return false;
    }
}

bool MainWindow::saveUIFile(const QString& filePath)
{
    if (!m_pCurrentUI || filePath.isEmpty()) return false;
    
    // UI'yı kaydet
    if (m_pCurrentUI->SaveToFile(filePath.toStdString()))
    {
        m_sCurrentFilePath = filePath;
        m_bIsModified = false;
        updateWindowTitle();
        statusBar()->showMessage(QString("Saved: %1").arg(filePath));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error", 
                            QString("UI dosyası kaydedilemedi:\n%1").arg(filePath));
        return false;
    }
}

void MainWindow::renderUI()
{
    if (!m_pCurrentUI || !m_pAdapter) return;
    
    if (!m_pAdapter->IsRenderActive()) return;
    
    // Direct3D device'ı al
    IDirect3DDevice9* pDevice = (IDirect3DDevice9*)m_pAdapter->GetDirect3DDevice();
    if (!pDevice) return;
    
    // Clear
    pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
    
    pDevice->BeginScene();
    
    // UI'yı render et
    if (m_pCurrentUI && m_pCurrentUI->IsVisible())
    {
        m_pCurrentUI->Render();
    }
    
    pDevice->EndScene();
    // Present Qt widget tarafından yapılıyor
}

void MainWindow::refreshUIHierarchy()
{
    if (!m_pHierarchyTree) return;
    
    m_pHierarchyTree->clear();
    
    if (!m_pCurrentUI) return;
    
    m_pHierarchyTree->clear();
    
    // UI hierarchy'sini tree widget'a ekle
    QTreeWidgetItem* pRootItem = new QTreeWidgetItem(m_pHierarchyTree);
    QString rootText = QString::fromStdString(m_pCurrentUI->GetID());
    if (rootText.isEmpty()) rootText = "Root";
    pRootItem->setText(0, rootText);
    pRootItem->setData(0, Qt::UserRole, QVariant::fromValue((void*)m_pCurrentUI));
    pRootItem->setExpanded(true);
    
    // D3D Widget'a UI'yı set et
    if (m_pD3DWidget)
    {
        m_pD3DWidget->setUI(m_pCurrentUI);
    }
    
    // TODO: Child element'leri recursive olarak ekle
}

void MainWindow::onSelectedUIElementChanged(QTreeWidgetItem* item, QTreeWidgetItem* previous)
{
    if (!item) return;
    
    // Seçili element'in pointer'ını al
    void* pData = item->data(0, Qt::UserRole).value<void*>();
    CN3UIBase* pElement = static_cast<CN3UIBase*>(pData);
    
    if (pElement)
    {
        updatePropertyEditor(pElement);
    }
}

void MainWindow::updatePropertyEditor(CN3UIBase* pElement)
{
    if (!m_pPropertyEditor) return;
    m_pPropertyEditor->setUIElement(pElement);
}

void MainWindow::updateWindowTitle()
{
    QString title = "Knight Online UI Editor";
    
    if (!m_sCurrentFilePath.isEmpty())
    {
        QFileInfo fi(m_sCurrentFilePath);
        title += " - " + fi.fileName();
    }
    
    if (m_bIsModified)
    {
        title += "*";
    }
    
    setWindowTitle(title);
}

QString MainWindow::getAssetPath() const
{
    // Asset path - gerçek projede ayarlardan alınmalı
    return QApplication::applicationDirPath() + "/assets/";
}

QString MainWindow::getUIPath() const
{
    return getAssetPath() + "UI_US/";
}

QString MainWindow::getTexturePath() const
{
    return getAssetPath() + "UI/";
}

void MainWindow::onActionCopy()
{
    // Copy implementation
}

void MainWindow::onActionPaste()
{
    // Paste implementation
}

void MainWindow::onActionDelete()
{
    // Delete implementation
}

void MainWindow::onActionUndo()
{
    // Undo implementation
}

void MainWindow::onActionRedo()
{
    // Redo implementation
}

void MainWindow::onUIElementDoubleClicked(QTreeWidgetItem* item, int column)
{
    // Double-click implementation
}

void MainWindow::onPropertyChanged()
{
    m_bIsModified = true;
    updateWindowTitle();
    renderUI();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_bIsModified)
    {
        int ret = QMessageBox::warning(this, "Unsaved Changes",
                                       "Dosyada kaydedilmemiş değişiklikler var. "
                                       "Çıkmak istiyor musunuz?",
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
        else if (ret == QMessageBox::Save)
        {
            onActionSave();
        }
    }
    
    // Widget'ı durdur
    if (m_pD3DWidget)
    {
        m_pD3DWidget->release();
    }
    
    // Kısa bir gecikme
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    
    event->accept();
}

#endif // USE_QT_DIRECT3D

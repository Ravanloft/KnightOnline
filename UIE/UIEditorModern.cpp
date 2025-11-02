// UIEditorModern.cpp: Modernize edilmiş UIE Editor Implementasyonu

#ifdef USE_QT_DIRECT3D

#include "UIEditorModern.h"
#include "ui_UIEditorModern.h"

#include "D3DViewWidget.h"
#include "PropertyEditor.h"
#include "UndoCommands.h"
#include "../shared/QtDirect3DAdapter.h"

#include <N3Base/N3Eng.h>
#include <N3Base/N3UIWndBase.h>
#include <N3Base/N3UIBase.h>
#include <N3Base/N3Base.h>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QCoreApplication>
#include <QtCore/QEventLoop>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QUndoView>

UIEditorModern::UIEditorModern(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui_UIEditorModernClass())
    , m_pD3DWidget(nullptr)
    , m_pPropertyEditor(nullptr)
    , m_pAdapter(nullptr)
    , m_pN3Eng(nullptr)
    , m_pRootUI(nullptr)
    , m_bIsModified(false)
    , m_bPreviewMode(false)
    , m_pHierarchyTree(nullptr)
    , m_pUndoView(nullptr)
    , m_pUndoStack(new QUndoStack(this))
    , m_pDockHierarchy(nullptr)
    , m_pDockProperty(nullptr)
    , m_pDockUndo(nullptr)
    , m_pFileToolBar(nullptr)
    , m_pEditToolBar(nullptr)
    , m_pViewToolBar(nullptr)
    , m_pUIToolBar(nullptr)
{
    m_ui->setupUi(this);
    
    setupUI();
    setupMenuBar();
    setupToolBar();
    setupDockWidgets();
    setupStatusBar();
    connectSignals();
    
    // N3Eng instance
    m_pN3Eng = new CN3Eng();
    
    // Asset path
    CN3Base::PathSet(getAssetPath().toStdString().c_str());
    
    // Recent files
    loadRecentFiles();
    
    // Undo view
    m_pUndoView = new QUndoView(m_pUndoStack);
    m_pDockUndo->setWidget(m_pUndoView);
    
    updateWindowTitle();
    updateModeButtons();
}

UIEditorModern::~UIEditorModern()
{
    // Save recent files
    saveRecentFiles();
    
    // Cleanup
    if (m_pRootUI)
    {
        delete m_pRootUI;
        m_pRootUI = nullptr;
    }
    
    if (m_pAdapter)
    {
        m_pAdapter->CleanupN3Eng();
        delete m_pAdapter;
        m_pAdapter = nullptr;
    }
    
    if (m_pN3Eng)
    {
        delete m_pN3Eng;
        m_pN3Eng = nullptr;
    }
    
    delete m_ui;
}

void UIEditorModern::setupUI()
{
    // Central widget - Direct3D View
    m_pD3DWidget = new D3DViewWidget(this);
    m_pD3DWidget->setMinimumSize(640, 480);
    setCentralWidget(m_pD3DWidget);
}

void UIEditorModern::setupMenuBar()
{
    // File Menu
    QMenu* pFileMenu = menuBar()->addMenu("&File");
    pFileMenu->addAction("&New", this, &UIEditorModern::onFileNew, QKeySequence::New);
    pFileMenu->addAction("&Open...", this, &UIEditorModern::onFileOpen, QKeySequence::Open);
    pFileMenu->addSeparator();
    
    QMenu* pRecentMenu = pFileMenu->addMenu("Recent Files");
    for (int i = 0; i < m_recentFiles.size(); ++i)
    {
        QAction* pAction = pRecentMenu->addAction(m_recentFiles[i]);
        connect(pAction, &QAction::triggered, [this, i]() {
            loadUIFile(m_recentFiles[i]);
        });
    }
    
    pFileMenu->addSeparator();
    pFileMenu->addAction("&Save", this, &UIEditorModern::onFileSave, QKeySequence::Save);
    pFileMenu->addAction("Save &As...", this, &UIEditorModern::onFileSaveAs, QKeySequence::SaveAs);
    pFileMenu->addSeparator();
    pFileMenu->addAction("E&xit", this, &UIEditorModern::close, QKeySequence::Quit);
    
    // Edit Menu
    QMenu* pEditMenu = menuBar()->addMenu("&Edit");
    pEditMenu->addAction("&Undo", this, &UIEditorModern::onEditUndo, QKeySequence::Undo);
    pEditMenu->addAction("&Redo", this, &UIEditorModern::onEditRedo, QKeySequence::Redo);
    pEditMenu->addSeparator();
    pEditMenu->addAction("Cu&t", this, &UIEditorModern::onEditCut, QKeySequence::Cut);
    pEditMenu->addAction("&Copy", this, &UIEditorModern::onEditCopy, QKeySequence::Copy);
    pEditMenu->addAction("&Paste", this, &UIEditorModern::onEditPaste, QKeySequence::Paste);
    pEditMenu->addAction("&Delete", this, &UIEditorModern::onEditDelete, QKeySequence::Delete);
    pEditMenu->addAction("Du&plicate", this, &UIEditorModern::onEditDuplicate, QKeySequence("Ctrl+D"));
    
    // View Menu
    QMenu* pViewMenu = menuBar()->addMenu("&View");
    m_pActionPreview = pViewMenu->addAction("&Preview Mode", this, &UIEditorModern::onViewPreview, QKeySequence("F5"));
    m_pActionPreview->setCheckable(true);
    m_pActionEdit = pViewMenu->addAction("&Edit Mode", this, &UIEditorModern::onViewEdit, QKeySequence("F6"));
    m_pActionEdit->setCheckable(true);
    m_pActionEdit->setChecked(true);
    pViewMenu->addSeparator();
    m_pActionGrid = pViewMenu->addAction("Show &Grid", this, &UIEditorModern::onViewGrid);
    m_pActionGrid->setCheckable(true);
    m_pActionSnapToGrid = pViewMenu->addAction("&Snap to Grid", this, &UIEditorModern::onViewSnapToGrid);
    m_pActionSnapToGrid->setCheckable(true);
    pViewMenu->addSeparator();
    pViewMenu->addAction("Background &Color...", this, &UIEditorModern::onViewBackgroundColor);
    pViewMenu->addSeparator();
    pViewMenu->addAction(m_pDockHierarchy->toggleViewAction());
    pViewMenu->addAction(m_pDockProperty->toggleViewAction());
    pViewMenu->addAction(m_pDockUndo->toggleViewAction());
    
    // UI Menu
    QMenu* pUIMenu = menuBar()->addMenu("&UI");
    pUIMenu->addAction("Insert &Image", this, &UIEditorModern::onUIInsertImage);
    pUIMenu->addAction("Insert &String", this, &UIEditorModern::onUIInsertString);
    pUIMenu->addAction("Insert &Button", this, &UIEditorModern::onUIInsertButton);
    pUIMenu->addAction("Insert &Edit", this, &UIEditorModern::onUIInsertEdit);
}

void UIEditorModern::setupToolBar()
{
    // File Toolbar
    m_pFileToolBar = addToolBar("File");
    m_pFileToolBar->addAction("New", this, &UIEditorModern::onFileNew);
    m_pFileToolBar->addAction("Open", this, &UIEditorModern::onFileOpen);
    m_pFileToolBar->addAction("Save", this, &UIEditorModern::onFileSave);
    m_pFileToolBar->addSeparator();
    
    // Edit Toolbar
    m_pEditToolBar = addToolBar("Edit");
    m_pEditToolBar->addAction("Undo", this, &UIEditorModern::onEditUndo);
    m_pEditToolBar->addAction("Redo", this, &UIEditorModern::onEditRedo);
    m_pEditToolBar->addSeparator();
    m_pEditToolBar->addAction("Cut", this, &UIEditorModern::onEditCut);
    m_pEditToolBar->addAction("Copy", this, &UIEditorModern::onEditCopy);
    m_pEditToolBar->addAction("Paste", this, &UIEditorModern::onEditPaste);
    m_pEditToolBar->addAction("Delete", this, &UIEditorModern::onEditDelete);
    
    // View Toolbar
    m_pViewToolBar = addToolBar("View");
    m_pViewToolBar->addAction(m_pActionPreview);
    m_pViewToolBar->addAction(m_pActionEdit);
    m_pViewToolBar->addSeparator();
    m_pViewToolBar->addAction(m_pActionGrid);
    
    // UI Toolbar
    m_pUIToolBar = addToolBar("UI");
    m_pUIToolBar->addAction("Image", this, &UIEditorModern::onUIInsertImage);
    m_pUIToolBar->addAction("String", this, &UIEditorModern::onUIInsertString);
    m_pUIToolBar->addAction("Button", this, &UIEditorModern::onUIInsertButton);
}

void UIEditorModern::setupDockWidgets()
{
    // Hierarchy Dock
    m_pDockHierarchy = new QDockWidget("Hierarchy", this);
    m_pDockHierarchy->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_pHierarchyTree = new QTreeWidget(m_pDockHierarchy);
    m_pHierarchyTree->setHeaderLabel("UI Elements");
    m_pDockHierarchy->setWidget(m_pHierarchyTree);
    addDockWidget(Qt::LeftDockWidgetArea, m_pDockHierarchy);
    
    // Property Dock
    m_pDockProperty = new QDockWidget("Properties", this);
    m_pDockProperty->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_pPropertyEditor = new PropertyEditor(m_pDockProperty);
    m_pDockProperty->setWidget(m_pPropertyEditor);
    addDockWidget(Qt::RightDockWidgetArea, m_pDockProperty);
    
    // Undo Dock
    m_pDockUndo = new QDockWidget("Undo History", this);
    m_pDockUndo->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, m_pDockUndo);
    m_pDockUndo->hide(); // Varsayılan olarak gizli
}

void UIEditorModern::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void UIEditorModern::connectSignals()
{
    // Direct3D widget
    if (m_pD3DWidget)
    {
        connect(m_pD3DWidget, &D3DViewWidget::deviceInitialized,
                this, &UIEditorModern::onDeviceInitialized);
        connect(m_pD3DWidget, &D3DViewWidget::ticked,
                this, &UIEditorModern::onTick);
        connect(m_pD3DWidget, &D3DViewWidget::rendered,
                this, &UIEditorModern::onRender);
        connect(m_pD3DWidget, &D3DViewWidget::elementSelected,
                this, &UIEditorModern::onSelectedElementChanged);
        connect(m_pD3DWidget, &D3DViewWidget::elementMoved,
                this, &UIEditorModern::onElementMoved);
    }
    
    // Property editor
    if (m_pPropertyEditor)
    {
        connect(m_pPropertyEditor, &PropertyEditor::propertyChanged,
                this, &UIEditorModern::onPropertyChanged);
    }
    
    // Hierarchy tree
    if (m_pHierarchyTree)
    {
        connect(m_pHierarchyTree, &QTreeWidget::itemSelectionChanged,
                this, &UIEditorModern::onHierarchySelectionChanged);
        connect(m_pHierarchyTree, &QTreeWidget::itemDoubleClicked,
                this, &UIEditorModern::onHierarchyDoubleClicked);
        m_pHierarchyTree->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_pHierarchyTree, &QTreeWidget::customContextMenuRequested,
                this, &UIEditorModern::onHierarchyContextMenu);
    }
    
    // Undo stack
    connect(m_pUndoStack, &QUndoStack::canUndoChanged,
            m_pEditToolBar->actions()[0], &QAction::setEnabled);
    connect(m_pUndoStack, &QUndoStack::canRedoChanged,
            m_pEditToolBar->actions()[1], &QAction::setEnabled);
}

void UIEditorModern::onDeviceInitialized(bool success)
{
    if (!success)
    {
        QMessageBox::critical(this, "Error", "Direct3D9 device başlatılamadı!");
        return;
    }
    
    if (m_pD3DWidget && m_pN3Eng)
    {
        m_pAdapter = new CQtDirect3DAdapter(m_pD3DWidget, this);
        
        QSize widgetSize = m_pD3DWidget->size();
        if (m_pAdapter->InitializeN3Eng(m_pN3Eng, widgetSize.width(), widgetSize.height(), true, 32, true))
        {
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

void UIEditorModern::onTick()
{
    // Tick operations
}

void UIEditorModern::onRender()
{
    if (m_bPreviewMode)
    {
        renderPreviewMode();
    }
    else
    {
        renderEditMode();
    }
}

void UIEditorModern::onFileNew()
{
    if (m_bIsModified)
    {
        int ret = QMessageBox::warning(this, "Unsaved Changes",
                                       "Kaydedilmemiş değişiklikler var. Yeni dosya oluşturulsun mu?",
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (ret != QMessageBox::Yes)
            return;
    }
    
    if (m_pRootUI)
    {
        delete m_pRootUI;
        m_pRootUI = nullptr;
    }
    
    m_pRootUI = new CN3UIWndBase();
    m_sCurrentFilePath.clear();
    m_bIsModified = false;
    
    if (m_pD3DWidget)
    {
        m_pD3DWidget->setUI(m_pRootUI);
    }
    
    refreshHierarchy();
    updateWindowTitle();
}

void UIEditorModern::onFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "UI Dosyası Aç",
        getAssetPath() + "UI_US/",
        "UI Files (*.uif);;All Files (*.*)"
    );
    
    if (!fileName.isEmpty())
    {
        loadUIFile(fileName);
    }
}

void UIEditorModern::onFileSave()
{
    if (m_sCurrentFilePath.isEmpty())
    {
        onFileSaveAs();
    }
    else
    {
        saveUIFile(m_sCurrentFilePath);
    }
}

void UIEditorModern::onFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "UI Dosyasını Kaydet",
        getAssetPath() + "UI_US/",
        "UI Files (*.uif);;All Files (*.*)"
    );
    
    if (!fileName.isEmpty())
    {
        saveUIFile(fileName);
    }
}

bool UIEditorModern::loadUIFile(const QString& filePath)
{
    if (filePath.isEmpty()) return false;
    
    if (m_pRootUI)
    {
        delete m_pRootUI;
        m_pRootUI = nullptr;
    }
    
    m_pRootUI = new CN3UIWndBase();
    
    if (m_pRootUI->LoadFromFile(filePath.toStdString()))
    {
        m_sCurrentFilePath = filePath;
        m_bIsModified = false;
        
        if (m_pD3DWidget)
        {
            m_pD3DWidget->setUI(m_pRootUI);
        }
        
        refreshHierarchy();
        updateWindowTitle();
        addRecentFile(filePath);
        
        statusBar()->showMessage(QString("Loaded: %1").arg(filePath));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error", QString("UI dosyası yüklenemedi:\n%1").arg(filePath));
        delete m_pRootUI;
        m_pRootUI = nullptr;
        return false;
    }
}

bool UIEditorModern::saveUIFile(const QString& filePath)
{
    if (!m_pRootUI || filePath.isEmpty()) return false;
    
    if (m_pRootUI->SaveToFile(filePath.toStdString()))
    {
        m_sCurrentFilePath = filePath;
        m_bIsModified = false;
        updateWindowTitle();
        addRecentFile(filePath);
        statusBar()->showMessage(QString("Saved: %1").arg(filePath));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error", QString("UI dosyası kaydedilemedi:\n%1").arg(filePath));
        return false;
    }
}

void UIEditorModern::renderUI()
{
    if (!m_pRootUI || !m_pAdapter) return;
    if (!m_pAdapter->IsRenderActive()) return;
    
    IDirect3DDevice9* pDevice = (IDirect3DDevice9*)m_pAdapter->GetDirect3DDevice();
    if (!pDevice) return;
    
    pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
    
    pDevice->BeginScene();
    
    if (m_pRootUI && m_pRootUI->IsVisible())
    {
        m_pRootUI->Render();
    }
    
    pDevice->EndScene();
}

void UIEditorModern::renderEditMode()
{
    renderUI();
    // Edit mode için ek görsel öğeler (grid, selection handles, vb.)
}

void UIEditorModern::renderPreviewMode()
{
    renderUI();
    // Preview mode - sadece UI render edilir
}

void UIEditorModern::onViewPreview()
{
    m_bPreviewMode = true;
    m_pActionPreview->setChecked(true);
    m_pActionEdit->setChecked(false);
    updateModeButtons();
}

void UIEditorModern::onViewEdit()
{
    m_bPreviewMode = false;
    m_pActionPreview->setChecked(false);
    m_pActionEdit->setChecked(true);
    updateModeButtons();
}

void UIEditorModern::onViewGrid()
{
    // Grid görünümünü aç/kapat
    m_pActionGrid->setChecked(!m_pActionGrid->isChecked());
}

void UIEditorModern::onViewSnapToGrid()
{
    // Snap to grid aç/kapat
    m_pActionSnapToGrid->setChecked(!m_pActionSnapToGrid->isChecked());
}

void UIEditorModern::onViewBackgroundColor()
{
    // Background color seçimi
    // TODO: Color dialog
}

void UIEditorModern::onSelectedElementChanged(CN3UIBase* pElement)
{
    updateSelection(pElement);
}

void UIEditorModern::onElementMoved(CN3UIBase* pElement)
{
    if (!pElement) return;
    
    // Undo command ekle
    RECT rc = pElement->GetRegion();
    QRect newRect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    
    // TODO: Old rect'i saklamak için bir mekanizma gerekli
    // Şimdilik basit bir yaklaşım
    QRect oldRect = newRect; // Gerçek implementasyonda önceki rect'i saklamalı
    
    MoveUIElementCommand* pCmd = new MoveUIElementCommand(pElement, oldRect, newRect);
    m_pUndoStack->push(pCmd);
    
    m_bIsModified = true;
    updateWindowTitle();
}

void UIEditorModern::onPropertyChanged()
{
    m_bIsModified = true;
    updateWindowTitle();
    // TODO: Undo command ekle
}

void UIEditorModern::refreshHierarchy()
{
    if (!m_pHierarchyTree) return;
    
    m_pHierarchyTree->clear();
    
    if (!m_pRootUI) return;
    
    QTreeWidgetItem* pRootItem = new QTreeWidgetItem(m_pHierarchyTree);
    QString rootText = QString::fromStdString(m_pRootUI->GetID());
    if (rootText.isEmpty()) rootText = "Root";
    pRootItem->setText(0, rootText);
    pRootItem->setData(0, Qt::UserRole, QVariant::fromValue((void*)m_pRootUI));
    pRootItem->setExpanded(true);
    
    // Child element'leri recursive olarak ekle
    addUIToHierarchy(pRootItem, m_pRootUI);
}

void UIEditorModern::addUIToHierarchy(QTreeWidgetItem* pParent, CN3UIBase* pUI)
{
    if (!pUI || !pParent) return;
    
    // TODO: Child element'leri recursive olarak ekle
    // CN3UIBase'in children listesini iterate et
}

void UIEditorModern::onHierarchySelectionChanged()
{
    QList<QTreeWidgetItem*> selected = m_pHierarchyTree->selectedItems();
    if (selected.isEmpty())
    {
        clearSelection();
        return;
    }
    
    CN3UIBase* pElement = getUIFromHierarchyItem(selected.first());
    if (pElement)
    {
        updateSelection(pElement);
    }
}

void UIEditorModern::updateSelection(CN3UIBase* pElement)
{
    if (m_pPropertyEditor)
    {
        m_pPropertyEditor->setUIElement(pElement);
    }
    
    if (m_pD3DWidget)
    {
        // D3D widget'a seçimi bildir
    }
}

void UIEditorModern::clearSelection()
{
    if (m_pPropertyEditor)
    {
        m_pPropertyEditor->clear();
    }
}

CN3UIBase* UIEditorModern::getUIFromHierarchyItem(QTreeWidgetItem* item)
{
    if (!item) return nullptr;
    
    void* pData = item->data(0, Qt::UserRole).value<void*>();
    return static_cast<CN3UIBase*>(pData);
}

void UIEditorModern::updateWindowTitle()
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

void UIEditorModern::updateModeButtons()
{
    // Mode button'larını güncelle
}

QString UIEditorModern::getAssetPath() const
{
    return QApplication::applicationDirPath() + "/assets/";
}

void UIEditorModern::addRecentFile(const QString& filePath)
{
    m_recentFiles.removeAll(filePath);
    m_recentFiles.prepend(filePath);
    
    while (m_recentFiles.size() > MAX_RECENT_FILES)
    {
        m_recentFiles.removeLast();
    }
    
    // TODO: Menu'yu güncelle
}

void UIEditorModern::loadRecentFiles()
{
    QSettings settings;
    m_recentFiles = settings.value("recentFiles").toStringList();
}

void UIEditorModern::saveRecentFiles()
{
    QSettings settings;
    settings.setValue("recentFiles", m_recentFiles);
}

// Placeholder implementations
void UIEditorModern::onEditUndo() { m_pUndoStack->undo(); }
void UIEditorModern::onEditRedo() { m_pUndoStack->redo(); }
void UIEditorModern::onEditCut() { /* TODO */ }
void UIEditorModern::onEditCopy() { /* TODO */ }
void UIEditorModern::onEditPaste() { /* TODO */ }
void UIEditorModern::onEditDelete() { /* TODO */ }
void UIEditorModern::onEditDuplicate() { /* TODO */ }
void UIEditorModern::onUIInsert() { /* TODO */ }
void UIEditorModern::onUIInsertImage() { /* TODO */ }
void UIEditorModern::onUIInsertString() { /* TODO */ }
void UIEditorModern::onUIInsertButton() { /* TODO */ }
void UIEditorModern::onUIInsertEdit() { /* TODO */ }
void UIEditorModern::onHierarchyDoubleClicked(QTreeWidgetItem* item, int column) { /* TODO */ }
void UIEditorModern::onHierarchyContextMenu(const QPoint& pos) { /* TODO */ }

void UIEditorModern::closeEvent(QCloseEvent *event)
{
    if (m_bIsModified)
    {
        int ret = QMessageBox::warning(this, "Unsaved Changes",
                                       "Kaydedilmemiş değişiklikler var. Çıkmak istiyor musunuz?",
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
        else if (ret == QMessageBox::Save)
        {
            onFileSave();
        }
    }
    
    if (m_pD3DWidget)
    {
        m_pD3DWidget->release();
    }
    
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    
    event->accept();
}

#endif // USE_QT_DIRECT3D

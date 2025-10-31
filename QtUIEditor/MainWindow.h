// MainWindow.h: Qt UI Editor Ana Pencere

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPropertyBrowser>
#include <memory>

// Forward declarations
class QDirect3D9Widget;
class CQtDirect3DAdapter;
class CN3Eng;
class CN3UIWndBase;
class CN3UIBase;
class QSplitter;
class QToolBar;
class QStatusBar;
class Ui_MainWindowClass;
class PropertyEditor;
class D3DViewWidget;

/**
 * @brief Knight Online UI Editor Ana Pencere
 * 
 * Bu sınıf, Knight Online'ın UI dosyalarını (.uif) düzenlemek için
 * Qt tabanlı modern bir editör sağlar.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    // Direct3D device initialized
    void onDeviceInitialized(bool success);
    
    // Render loop
    void onTick();
    void onRender();
    
    // File operations
    void onActionNew();
    void onActionOpen();
    void onActionSave();
    void onActionSaveAs();
    void onActionExit();
    
    // UI operations
    void onActionLoadInventory(const QString& nation); // "el" or "ka"
    void onSelectedUIElementChanged(QTreeWidgetItem* item, QTreeWidgetItem* previous);
    void onPropertyChanged();
    
    // Edit operations
    void onActionCopy();
    void onActionPaste();
    void onActionDelete();
    void onActionUndo();
    void onActionRedo();

private slots:
    // UI hierarchy
    void refreshUIHierarchy();
    void onUIElementDoubleClicked(QTreeWidgetItem* item, int column);
    
    // Property editing
    void updatePropertyEditor(CN3UIBase* pElement);

private:
    void setupUI();
    void setupToolBar();
    void setupMenuBar();
    void setupStatusBar();
    void connectSignals();
    
    // UI loading
    bool loadUIFile(const QString& filePath);
    bool saveUIFile(const QString& filePath);
    
    // UI rendering
    void renderUI();
    
    // Helper functions
    void updateWindowTitle();
    QString getAssetPath() const;
    QString getUIPath() const;
    QString getTexturePath() const;
    
    // UI Components
    Ui_MainWindowClass* m_ui;
    D3DViewWidget* m_pD3DWidget;         // Görsel düzenleme için özel widget
    CQtDirect3DAdapter* m_pAdapter;
    CN3Eng* m_pN3Eng;
    PropertyEditor* m_pPropertyEditor;   // GUI Property Editor
    
    // UI Data
    CN3UIWndBase* m_pCurrentUI;          // Şu an düzenlenen UI
    QString m_sCurrentFilePath;          // Açık dosyanın yolu
    bool m_bIsModified;                  // Değişiklik yapıldı mı?
    
    // Widgets
    QTreeWidget* m_pHierarchyTree;       // UI element hierarchy
    QSplitter* m_pMainSplitter;          // Main splitter
    QSplitter* m_pRightSplitter;         // Right panel splitter
    
    // Toolbars
    QToolBar* m_pFileToolBar;
    QToolBar* m_pEditToolBar;
    QToolBar* m_pViewToolBar;
};

#endif // USE_QT_DIRECT3D

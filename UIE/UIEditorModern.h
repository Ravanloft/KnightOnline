// UIEditorModern.h: Modernize edilmiş UIE Editor Ana Pencere
// QtDirect3D ile geliştirilmiş versiyon

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QDockWidget>
#include <memory>

// Forward declarations
class D3DViewWidget;
class PropertyEditor;
class CQtDirect3DAdapter;
class CN3Eng;
class CN3UIWndBase;
class CN3UIBase;
class Ui_UIEditorModernClass;
class QUndoStack;
class QUndoView;

/**
 * @brief Modernize edilmiş UIE Editor
 * 
 * Mevcut MFC tabanlı UIE editörünün QtDirect3D ile modernize edilmiş versiyonu.
 * Tüm mevcut özellikleri korur ve yeni modern özellikler ekler.
 */
class UIEditorModern : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIEditorModern(QWidget *parent = nullptr);
    ~UIEditorModern();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    // Direct3D
    void onDeviceInitialized(bool success);
    void onTick();
    void onRender();
    
    // File operations
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onFileRecent();
    
    // Edit operations
    void onEditUndo();
    void onEditRedo();
    void onEditCut();
    void onEditCopy();
    void onEditPaste();
    void onEditDelete();
    void onEditDuplicate();
    
    // View operations
    void onViewPreview();
    void onViewEdit();
    void onViewGrid();
    void onViewSnapToGrid();
    void onViewBackgroundColor();
    
    // UI operations
    void onUIInsert();
    void onUIInsertImage();
    void onUIInsertString();
    void onUIInsertButton();
    void onUIInsertEdit();
    
    // Selection
    void onSelectedElementChanged(CN3UIBase* pElement);
    void onElementMoved(CN3UIBase* pElement);
    
    // Property changes
    void onPropertyChanged();

private slots:
    // Hierarchy
    void onHierarchySelectionChanged();
    void onHierarchyDoubleClicked(QTreeWidgetItem* item, int column);
    void onHierarchyContextMenu(const QPoint& pos);
    
    // UI mode
    void updateModeButtons();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupDockWidgets();
    void setupStatusBar();
    void connectSignals();
    
    // UI loading/saving
    bool loadUIFile(const QString& filePath);
    bool saveUIFile(const QString& filePath);
    
    // UI rendering
    void renderUI();
    void renderEditMode();
    void renderPreviewMode();
    
    // Selection
    void updateSelection(CN3UIBase* pElement);
    void clearSelection();
    
    // Hierarchy
    void refreshHierarchy();
    void addUIToHierarchy(QTreeWidgetItem* pParent, CN3UIBase* pUI);
    CN3UIBase* getUIFromHierarchyItem(QTreeWidgetItem* item);
    
    // Helper
    void updateWindowTitle();
    QString getAssetPath() const;
    void addRecentFile(const QString& filePath);
    
    // UI Components
    Ui_UIEditorModernClass* m_ui;
    D3DViewWidget* m_pD3DWidget;
    PropertyEditor* m_pPropertyEditor;
    CQtDirect3DAdapter* m_pAdapter;
    CN3Eng* m_pN3Eng;
    
    // Document
    CN3UIWndBase* m_pRootUI;
    QString m_sCurrentFilePath;
    bool m_bIsModified;
    bool m_bPreviewMode;  // true = Preview, false = Edit
    
    // Views
    QTreeWidget* m_pHierarchyTree;
    QUndoView* m_pUndoView;
    
    // Undo/Redo
    QUndoStack* m_pUndoStack;
    
    // UI
    QDockWidget* m_pDockHierarchy;
    QDockWidget* m_pDockProperty;
    QDockWidget* m_pDockUndo;
    
    // Toolbars
    QToolBar* m_pFileToolBar;
    QToolBar* m_pEditToolBar;
    QToolBar* m_pViewToolBar;
    QToolBar* m_pUIToolBar;
    
    // Actions
    QAction* m_pActionPreview;
    QAction* m_pActionEdit;
    QAction* m_pActionGrid;
    QAction* m_pActionSnapToGrid;
    
    // Recent files
    QStringList m_recentFiles;
    static const int MAX_RECENT_FILES = 10;
};

#endif // USE_QT_DIRECT3D

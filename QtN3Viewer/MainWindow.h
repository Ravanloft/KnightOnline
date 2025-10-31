// MainWindow.h: QtN3Viewer ana pencere sınıfı

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QtWidgets/QMainWindow>
#include <memory>

// Forward declarations
class QDirect3D9Widget;
class CQtDirect3DAdapter;
class CN3Eng;
class Ui_MainWindowClass;

/**
 * @brief QtN3Viewer ana pencere sınıfı
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
    /**
     * @brief Direct3D device başarıyla initialize edildiğinde çağrılır
     * @param success Device başarıyla initialize edildi mi
     */
    void onDeviceInitialized(bool success);

    /**
     * @brief Her frame'de tick işlemlerini yapar
     */
    void onTick();

    /**
     * @brief Her frame'de render işlemlerini yapar
     */
    void onRender();

private slots:
    void onActionOpen();
    void onActionExit();

private:
    void setupUI();
    void connectSignals();

    Ui_MainWindowClass* m_ui;                    ///< UI pointer'ı
    QDirect3D9Widget* m_pD3DWidget;              ///< Direct3D9 widget pointer'ı
    CQtDirect3DAdapter* m_pAdapter;              ///< QtDirect3D adapter
    CN3Eng* m_pN3Eng;                            ///< N3Eng instance
};

#endif // USE_QT_DIRECT3D

// D3DViewWidget.h: Direct3D Widget ile Görsel UI Düzenleme

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QDirect3D9Widget.h>
#include <QMouseEvent>
#include <QKeyEvent>

class CN3UIBase;
class CN3UIWndBase;

/**
 * @brief Direct3D Widget ile görsel UI düzenleme
 * 
 * Bu widget, UI element'lerini mouse ile seçme, taşıma ve
 * boyutlandırma işlemlerini yapar.
 */
class D3DViewWidget : public QDirect3D9Widget
{
    Q_OBJECT

public:
    explicit D3DViewWidget(QWidget* parent = nullptr);
    
    /**
     * @brief Düzenlenecek UI'yı set et
     */
    void setUI(CN3UIWndBase* pUI);
    
    /**
     * @brief Seçili element'i döner
     */
    CN3UIBase* getSelectedElement() const { return m_pSelectedElement; }

signals:
    /**
     * @brief Element seçildiğinde emit edilir
     */
    void elementSelected(CN3UIBase* pElement);
    
    /**
     * @brief Element taşındığında emit edilir
     */
    void elementMoved(CN3UIBase* pElement);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    CN3UIWndBase* m_pUI;
    CN3UIBase* m_pSelectedElement;
    
    bool m_bDragging;
    QPoint m_ptLastMousePos;
    
    // UI element bulma
    CN3UIBase* findElementAtPoint(const QPoint& pt, CN3UIBase* pParent = nullptr);
    bool isPointInRect(const QPoint& pt, const RECT& rc);
    
    // Seçim gösterimi
    void drawSelectionRect();
};

#endif // USE_QT_DIRECT3D

// D3DViewWidget.cpp: Görsel UI Düzenleme Implementasyonu

#ifdef USE_QT_DIRECT3D

#include "D3DViewWidget.h"

#include <N3Base/N3UIWndBase.h>
#include <N3Base/N3UIBase.h>
#include <d3d9.h>

#include <QMouseEvent>
#include <QKeyEvent>

D3DViewWidget::D3DViewWidget(QWidget* parent)
    : QDirect3D9Widget(parent)
    , m_pUI(nullptr)
    , m_pSelectedElement(nullptr)
    , m_bDragging(false)
{
}

void D3DViewWidget::setUI(CN3UIWndBase* pUI)
{
    m_pUI = pUI;
    m_pSelectedElement = nullptr;
    m_bDragging = false;
}

void D3DViewWidget::mousePressEvent(QMouseEvent* event)
{
    if (!m_pUI) return;
    
    if (event->button() == Qt::LeftButton)
    {
        // Mouse pozisyonunu widget koordinatlarına çevir
        QPoint widgetPos = event->pos();
        
        // UI element'ini bul
        CN3UIBase* pElement = findElementAtPoint(widgetPos, m_pUI);
        
        if (pElement && pElement != m_pUI)
        {
            m_pSelectedElement = pElement;
            emit elementSelected(pElement);
            
            // Drag başlat
            m_bDragging = true;
            m_ptLastMousePos = widgetPos;
        }
    }
    
    QDirect3D9Widget::mousePressEvent(event);
}

void D3DViewWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bDragging && m_pSelectedElement && event->buttons() & Qt::LeftButton)
    {
        // Element'i taşı
        QPoint delta = event->pos() - m_ptLastMousePos;
        
        RECT rc = m_pSelectedElement->GetRegion();
        rc.left += delta.x();
        rc.right += delta.x();
        rc.top += delta.y();
        rc.bottom += delta.y();
        
        m_pSelectedElement->SetRegion(rc);
        m_ptLastMousePos = event->pos();
        
        emit elementMoved(m_pSelectedElement);
        
        // Render'ı tetikle
        update();
    }
    
    QDirect3D9Widget::mouseMoveEvent(event);
}

void D3DViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bDragging = false;
    }
    
    QDirect3D9Widget::mouseReleaseEvent(event);
}

void D3DViewWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete && m_pSelectedElement)
    {
        // Element'i sil (basit implementasyon)
        // Gerçek implementasyonda parent'tan remove etmek gerekir
        m_pSelectedElement = nullptr;
        emit elementSelected(nullptr);
        update();
    }
    
    QDirect3D9Widget::keyPressEvent(event);
}

CN3UIBase* D3DViewWidget::findElementAtPoint(const QPoint& pt, CN3UIBase* pParent)
{
    if (!pParent) return nullptr;
    
    // UI element'in region'ını kontrol et
    RECT rc = pParent->GetRegion();
    if (isPointInRect(pt, rc))
    {
        // Child'ları kontrol et (z-order'a göre ters sırada)
        // Basit implementasyon - recursive olmalı
        CN3UIBase* pChild = pParent->GetChildByID("");
        
        // Child var mı kontrol et ve recursive arama yap
        // Şimdilik sadece parent'ı döndür
        return pParent;
    }
    
    return nullptr;
}

bool D3DViewWidget::isPointInRect(const QPoint& pt, const RECT& rc)
{
    return pt.x() >= rc.left && pt.x() <= rc.right &&
           pt.y() >= rc.top && pt.y() <= rc.bottom;
}

void D3DViewWidget::drawSelectionRect()
{
    if (!m_pSelectedElement || !device()) return;
    
    // Seçili element'in etrafına seçim çerçevesi çiz
    RECT rc = m_pSelectedElement->GetRegion();
    
    // Direct3D ile çizgi çizme kodu buraya eklenebilir
    // ID3DXLine veya primitive drawing kullanılabilir
}

#endif // USE_QT_DIRECT3D

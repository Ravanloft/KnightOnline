// QtDirect3DAdapter.cpp: QtDirect3D9Widget ile Knight Online N3Eng entegrasyonu için adapter implementasyonu

#ifdef USE_QT_DIRECT3D

#include "QtDirect3DAdapter.h"

#include <QDirect3D9Widget>
#include <QDebug>
#include <d3d9.h>

#include <N3Base/N3Eng.h>
#include <N3Base/N3Base.h>

// QtDirect3D widget header'ını include et
// Not: Bu dosya deps/QtDirect3D/source/QDirect3D9Widget/ dizininde
#include <QDirect3D9Widget.h>

CQtDirect3DAdapter::CQtDirect3DAdapter(QDirect3D9Widget* pD3DWidget, QObject* pParent)
    : QObject(pParent)
    , m_pD3DWidget(pD3DWidget)
    , m_pN3Eng(nullptr)
    , m_bInitialized(false)
    , m_bDeviceReady(false)
{
    if (m_pD3DWidget)
    {
        // Qt widget'ın signal'larını slot'larımıza bağla
        connect(m_pD3DWidget, &QDirect3D9Widget::deviceInitialized, 
                this, &CQtDirect3DAdapter::OnDeviceInitialized);
        connect(m_pD3DWidget, &QDirect3D9Widget::ticked, 
                this, &CQtDirect3DAdapter::OnTick);
        connect(m_pD3DWidget, &QDirect3D9Widget::rendered, 
                this, &CQtDirect3DAdapter::OnRender);
    }
}

CQtDirect3DAdapter::~CQtDirect3DAdapter()
{
    CleanupN3Eng();
}

bool CQtDirect3DAdapter::InitializeN3Eng(CN3Eng* pEng, 
                                         uint32_t nWidth, 
                                         uint32_t nHeight, 
                                         bool bWindowed, 
                                         uint32_t nBPP, 
                                         bool bUseHW)
{
    if (!m_pD3DWidget || !pEng)
    {
        qWarning() << "CQtDirect3DAdapter::InitializeN3Eng - Invalid parameters";
        return false;
    }

    m_pN3Eng = pEng;

    // Device hazır olana kadar bekleyelim
    if (!m_bDeviceReady)
    {
        qWarning() << "CQtDirect3DAdapter::InitializeN3Eng - Device not ready yet";
        return false;
    }

    // Qt widget'ın native window handle'ını al
    HWND hWnd = m_pD3DWidget->nativeHandle();
    if (!hWnd)
    {
        qWarning() << "CQtDirect3DAdapter::InitializeN3Eng - Failed to get native window handle";
        return false;
    }

    // Qt widget'ın Direct3D device'ını al
    IDirect3DDevice9* pDevice = m_pD3DWidget->device();
    if (!pDevice)
    {
        qWarning() << "CQtDirect3DAdapter::InitializeN3Eng - Failed to get Direct3D device";
        return false;
    }

    // N3Base static device pointer'ını Qt widget'ın device'ına set et
    // Bu çok kritik! Knight Online'ın tüm rendering kodu CN3Base::s_lpD3DDev kullanıyor
    CN3Base::s_lpD3DDev = pDevice;
    CN3Base::s_hWndBase = hWnd;
    CN3Base::s_hWndPresent = hWnd;

    // N3Eng'i initialize et
    // Not: N3Eng::Init() normalde kendi device'ını oluşturur,
    // ama biz zaten Qt widget'tan device'ı aldığımız için
    // burada sadece device'ı set etmemiz yeterli olabilir
    // Alternatif olarak, N3Eng'in Init fonksiyonunu modifiye edebiliriz
    // veya device'ı manuel olarak set edebiliriz

    // Viewport'u ayarla
    RECT rcViewport;
    rcViewport.left = 0;
    rcViewport.top = 0;
    rcViewport.right = nWidth;
    rcViewport.bottom = nHeight;
    
    if (m_pN3Eng)
    {
        m_pN3Eng->SetViewPort(rcViewport);
        m_pN3Eng->SetDefaultEnvironment();
    }

    m_bInitialized = true;
    qDebug() << "CQtDirect3DAdapter::InitializeN3Eng - Successfully initialized";
    
    return true;
}

void CQtDirect3DAdapter::CleanupN3Eng()
{
    if (m_bInitialized)
    {
        // N3Eng'i temizle
        if (m_pN3Eng)
        {
            // N3Eng cleanup işlemleri burada yapılabilir
            // m_pN3Eng->Release();
        }

        // Static device pointer'ı temizle
        CN3Base::s_lpD3DDev = nullptr;
        CN3Base::s_hWndBase = nullptr;
        CN3Base::s_hWndPresent = nullptr;

        m_bInitialized = false;
        m_pN3Eng = nullptr;
    }
}

HWND CQtDirect3DAdapter::GetNativeWindowHandle() const
{
    if (m_pD3DWidget)
    {
        return m_pD3DWidget->nativeHandle();
    }
    return nullptr;
}

void* CQtDirect3DAdapter::GetDirect3DDevice() const
{
    if (m_pD3DWidget)
    {
        return static_cast<void*>(m_pD3DWidget->device());
    }
    return nullptr;
}

bool CQtDirect3DAdapter::IsRenderActive() const
{
    if (m_pD3DWidget)
    {
        return m_pD3DWidget->renderActive();
    }
    return false;
}

void CQtDirect3DAdapter::OnDeviceInitialized(bool bSuccess)
{
    m_bDeviceReady = bSuccess;
    
    if (bSuccess)
    {
        qDebug() << "CQtDirect3DAdapter::OnDeviceInitialized - Device ready";
        
        // Device hazır olduğunda N3Eng'i initialize etmeyi dene
        if (m_pN3Eng && !m_bInitialized)
        {
            // Widget'ın boyutlarını al
            QSize widgetSize = m_pD3DWidget->size();
            InitializeN3Eng(m_pN3Eng, 
                          widgetSize.width(), 
                          widgetSize.height(), 
                          true,  // windowed
                          32,    // 32-bit color
                          true); // hardware vertex processing
        }
    }
    else
    {
        qWarning() << "CQtDirect3DAdapter::OnDeviceInitialized - Device initialization failed";
    }
}

void CQtDirect3DAdapter::OnTick()
{
    // N3Eng'in tick işlemlerini burada çağırabiliriz
    // Örneğin: m_pN3Eng->Tick();
    
    if (m_bInitialized && m_pN3Eng)
    {
        // Knight Online'ın tick mekanizması buraya entegre edilebilir
        // Örnek: m_pN3Eng->Update();
    }
}

void CQtDirect3DAdapter::OnRender()
{
    // N3Eng'in render işlemlerini burada çağırabiliriz
    
    if (m_bInitialized && m_pN3Eng && CN3Base::s_lpD3DDev)
    {
        // Scene'i render et
        // Örnek: 
        // CN3Base::Clear(0xFF000000); // Siyah arka plan
        // ... render scene ...
        // m_pN3Eng->Present(hWnd, nullptr);
        
        // Not: Present() işlemi Qt widget tarafından yapılıyor,
        // bu yüzden sadece rendering kodlarını çağırmamız yeterli
    }
}

void CQtDirect3DAdapter::SetN3BaseDevice()
{
    if (m_pD3DWidget && m_bDeviceReady)
    {
        IDirect3DDevice9* pDevice = m_pD3DWidget->device();
        if (pDevice)
        {
            CN3Base::s_lpD3DDev = pDevice;
        }
    }
}

#endif // USE_QT_DIRECT3D

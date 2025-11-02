// QtDirect3DAdapter.h: QtDirect3D9Widget ile Knight Online N3Eng entegrasyonu için adapter sınıfı
//
// Bu sınıf, QtDirect3D widget'ının Direct3D device'ını Knight Online'ın N3Eng sistemi ile 
// entegre etmek için kullanılır.

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QObject>
#include <memory>

// Forward declarations
class QDirect3D9Widget;
class CN3Eng;
struct HWND__;
typedef struct HWND__* HWND;

/**
 * @brief QtDirect3D9Widget ile Knight Online N3Eng arasında köprü görevi gören adapter sınıfı
 * 
 * Bu sınıf, Qt widget'ının Direct3D device'ını N3Eng'in kullanabileceği şekilde yapılandırır
 * ve render loop'unu Qt'nin signal/slot sistemine entegre eder.
 */
class CQtDirect3DAdapter : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param pD3DWidget QtDirect3D9Widget pointer'ı (nullptr olmamalı)
     * @param pParent Parent QObject
     */
    explicit CQtDirect3DAdapter(QDirect3D9Widget* pD3DWidget, QObject* pParent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~CQtDirect3DAdapter();

    /**
     * @brief N3Eng'i Qt widget'ın device'ı ile initialize eder
     * @param pEng N3Eng instance pointer'ı
     * @param nWidth Viewport genişliği
     * @param nHeight Viewport yüksekliği
     * @param bWindowed Windowed mode (true) veya fullscreen (false)
     * @param nBPP Bits per pixel (16 veya 32)
     * @param bUseHW Hardware vertex processing kullanılsın mı
     * @return Başarılı ise true
     */
    bool InitializeN3Eng(CN3Eng* pEng, 
                         uint32_t nWidth, 
                         uint32_t nHeight, 
                         bool bWindowed = true, 
                         uint32_t nBPP = 32, 
                         bool bUseHW = true);

    /**
     * @brief N3Eng'i temizler ve kaynakları serbest bırakır
     */
    void CleanupN3Eng();

    /**
     * @brief Qt widget'ının native window handle'ını döner
     * @return HWND handle
     */
    HWND GetNativeWindowHandle() const;

    /**
     * @brief Qt widget'ının Direct3D device pointer'ını döner
     * @return IDirect3DDevice9* pointer
     */
    void* GetDirect3DDevice() const;

    /**
     * @brief Render aktif mi kontrol eder
     * @return true ise render aktif
     */
    bool IsRenderActive() const;

public slots:
    /**
     * @brief Qt widget device initialized signal'ını handle eder
     * @param bSuccess Device başarıyla initialize edildi mi
     */
    void OnDeviceInitialized(bool bSuccess);

    /**
     * @brief Qt widget tick signal'ını handle eder
     * Bu slot, N3Eng'in tick işlemlerini çağırır
     */
    void OnTick();

    /**
     * @brief Qt widget render signal'ını handle eder
     * Bu slot, N3Eng'in render işlemlerini çağırır
     */
    void OnRender();

private:
    QDirect3D9Widget* m_pD3DWidget;      ///< QtDirect3D9Widget pointer'ı
    CN3Eng* m_pN3Eng;                    ///< N3Eng instance pointer'ı
    bool m_bInitialized;                 ///< Initialize edildi mi?
    bool m_bDeviceReady;                 ///< Device hazır mı?
    
    /**
     * @brief N3Base static device pointer'ını Qt widget'ın device'ına set eder
     */
    void SetN3BaseDevice();
};

#endif // USE_QT_DIRECT3D

# QtDirect3D Entegrasyonu - Hızlı Başlangıç

## Özet

QtDirect3D projesi başarıyla Knight Online projesine entegre edilmiştir. Bu dokümantasyon, hızlı başlangıç için gerekli adımları özetler.

## Ne Yapıldı?

1. ✅ **QtDirect3D Projesi Eklendi**: `deps/QtDirect3D/` klasörüne submodule olarak eklendi
2. ✅ **Adapter Sınıfı Oluşturuldu**: `shared/QtDirect3DAdapter.h/.cpp` - Qt widget ile N3Eng arasında köprü
3. ✅ **Örnek Uygulama**: `QtN3Viewer/` - N3Viewer'ın Qt versiyonu için temel yapı
4. ✅ **Dokümantasyon**: Detaylı entegrasyon rehberi hazırlandı

## Hızlı Başlangıç Adımları

### 1. Qt Kurulumu

```bash
# Qt 5.12+ indirin ve kurun
# https://www.qt.io/download

# Visual Studio için Qt VS Tools extension'ını yükleyin
# Extensions > Manage Extensions > Qt Visual Studio Tools
```

### 2. Proje Yapılandırması

**Visual Studio'da:**

1. Extensions > Qt VS Tools > Qt Options
2. Qt versiyonunu ekleyin (örn: Qt 5.15.2 MSVC2019 64-bit)
3. Project Properties > C/C++ > Preprocessor > Preprocessor Definitions
4. `USE_QT_DIRECT3D` ekleyin

### 3. Dosyaları Projeye Ekleme

**shared.vcxproj için:**
```xml
<!-- ItemGroup içine ekleyin -->
<ClCompile Include="QtDirect3DAdapter.cpp" Condition="'$(Configuration)'!=''">
  <PrecompiledHeader>NotUsing</PrecompiledHeader>
</ClCompile>
<ClInclude Include="QtDirect3DAdapter.h" />
```

**Qt projesi için:**
- QtDirect3D9Widget source dosyalarını projeye ekleyin
- Include dizinlerini ayarlayın
- Qt Modules: core, gui, widgets

### 4. Basit Kullanım Örneği

```cpp
#include <QDirect3D9Widget.h>
#include "QtDirect3DAdapter.h"
#include <N3Base/N3Eng.h>

// Widget oluştur
QDirect3D9Widget* pWidget = new QDirect3D9Widget(parent);

// Adapter oluştur
CQtDirect3DAdapter* pAdapter = new CQtDirect3DAdapter(pWidget);

// N3Eng oluştur
CN3Eng* pEng = new CN3Eng();

// Signal'ları bağla
connect(pWidget, &QDirect3D9Widget::deviceInitialized, 
        [pAdapter, pEng](bool success) {
    if (success) {
        QSize size = pWidget->size();
        pAdapter->InitializeN3Eng(pEng, size.width(), size.height());
        pWidget->run(); // Render loop'u başlat
    }
});

connect(pWidget, &QDirect3D9Widget::ticked, 
        [pEng]() {
    // N3Eng tick işlemleri
});

connect(pWidget, &QDirect3D9Widget::rendered, 
        [pEng]() {
    // N3Eng render işlemleri
});
```

## Oluşturulan Dosyalar

```
deps/QtDirect3D/              # QtDirect3D kaynak kodu
shared/
├── QtDirect3DAdapter.h       # Adapter header
└── QtDirect3DAdapter.cpp     # Adapter implementation

QtN3Viewer/                    # Örnek Qt uygulaması
├── main.cpp
├── MainWindow.h/.cpp
├── MainWindow.ui
└── README.md

QT_INTEGRATION_README.md       # Detaylı dokümantasyon
QT_INTEGRATION_QUICKSTART.md   # Bu dosya
```

## Önemli Notlar

⚠️ **Qt Kurulu Olmalı**: QtDirect3D kullanmak için Qt'nin kurulu olması gerekir

⚠️ **Preprocessor Tanımı**: `USE_QT_DIRECT3D` tanımı olmadan adapter derlenmeyecektir

⚠️ **Device Pointer**: Adapter, `CN3Base::s_lpD3DDev` static pointer'ını Qt widget'ın device'ına set eder

## Sonraki Adımlar

1. **Qt Kurulumu**: Qt'yi kurun ve Visual Studio'da yapılandırın
2. **Test Et**: QtN3Viewer örneğini derleyip test edin
3. **Geliştir**: Kendi Qt uygulamalarınızı oluşturun

## Daha Fazla Bilgi

Detaylı dokümantasyon için `QT_INTEGRATION_README.md` dosyasına bakın.

## Destek

Sorun yaşarsanız:
- QtDirect3D dokümantasyonu: `deps/QtDirect3D/docs/`
- Knight Online proje dokümantasyonu: `README.md`

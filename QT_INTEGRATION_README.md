# Knight Online - QtDirect3D Entegrasyon Rehberi

Bu dokümantasyon, QtDirect3D projesinin Knight Online projesine nasıl entegre edildiğini açıklar.

## Genel Bakış

QtDirect3D entegrasyonu, Knight Online'ın Direct3D9 rendering engine'ini Qt widget'ları içinde kullanmayı sağlar. Bu sayede:
- Modern Qt UI framework'ü kullanılabilir
- Geliştirme araçları modernize edilebilir
- Cross-platform potansiyeli artar

## Proje Yapısı

### Eklenen Dosyalar

```
deps/
└── QtDirect3D/              # QtDirect3D kaynak kodu (submodule olarak eklenmiş)

shared/
├── QtDirect3DAdapter.h      # Qt widget ile N3Eng arasında köprü
└── QtDirect3DAdapter.cpp    # Adapter implementasyonu

QtN3Viewer/                   # Örnek Qt uygulaması
├── main.cpp
├── MainWindow.h/.cpp
├── MainWindow.ui
└── README.md
```

## Kurulum Gereksinimleri

### 1. Qt Kurulumu

1. Qt 5.12 veya üzeri sürümü indirin: https://www.qt.io/download
2. Qt Modules: Core, Gui, Widgets
3. Qt Visual Studio Tools extension'ını yükleyin

### 2. Visual Studio Yapılandırması

1. Visual Studio'yu açın
2. Extensions > Qt VS Tools > Qt Options
3. Qt versiyonunu ekleyin (örneğin: Qt 5.15.2 MSVC2019 64-bit)

### 3. Preprocessor Tanımları

QtDirect3D desteğini aktif etmek için projenize şu preprocessor tanımını ekleyin:
```cpp
USE_QT_DIRECT3D
```

Visual Studio'da:
- Project Properties > C/C++ > Preprocessor > Preprocessor Definitions
- `USE_QT_DIRECT3D` ekleyin

## Kullanım

### Temel Entegrasyon

```cpp
#include <QDirect3D9Widget.h>
#include "QtDirect3DAdapter.h"
#include <N3Base/N3Eng.h>

// Qt widget oluştur
QDirect3D9Widget* pWidget = new QDirect3D9Widget(parent);

// Adapter oluştur
CQtDirect3DAdapter* pAdapter = new CQtDirect3DAdapter(pWidget);

// N3Eng oluştur
CN3Eng* pEng = new CN3Eng();

// Initialize et
pAdapter->InitializeN3Eng(pEng, width, height, true, 32, true);

// Signal'ları bağla
connect(pWidget, &QDirect3D9Widget::deviceInitialized, ...);
connect(pWidget, &QDirect3D9Widget::ticked, ...);
connect(pWidget, &QDirect3D9Widget::rendered, ...);

// Render loop'u başlat
pWidget->run();
```

### CQtDirect3DAdapter Kullanımı

`CQtDirect3DAdapter` sınıfı, Qt widget'ın Direct3D device'ını Knight Online'ın N3Eng sistemi ile entegre eder:

- **InitializeN3Eng()**: N3Eng'i Qt widget'ın device'ı ile initialize eder
- **CleanupN3Eng()**: Kaynakları temizler
- **GetNativeWindowHandle()**: Native window handle döner
- **GetDirect3DDevice()**: Direct3D device pointer döner

### Önemli Notlar

1. **Device Pointer**: Adapter, `CN3Base::s_lpD3DDev` static pointer'ını Qt widget'ın device'ına set eder. Bu sayede Knight Online'ın tüm rendering kodu aynı device'ı kullanır.

2. **Present()**: Qt widget otomatik olarak Present() işlemini yapar. N3Eng'in Present() fonksiyonunu çağırmanıza gerek yok.

3. **Window Handle**: Qt widget'ın native window handle'ı, Knight Online'ın window handle gerektiren fonksiyonları için kullanılabilir.

## Örnek Uygulama: QtN3Viewer

`QtN3Viewer` klasöründe, N3Viewer'ın Qt versiyonu örnek olarak sunulmuştur. Bu örnek:
- QtDirect3D9Widget kullanımını gösterir
- CQtDirect3DAdapter entegrasyonunu örnekler
- Knight Online modellerini görüntülemek için temel yapıyı sağlar

### Derleme

```bash
# QtN3Viewer projesini Visual Studio'da açın
# veya mevcut solution'a ekleyin
# Qt VS Tools extension'ının yüklü olduğundan emin olun
```

## Build Sistemi Entegrasyonu

### Visual Studio Proje Dosyası

Qt projeleri için `.vcxproj` dosyasına şu eklemeler yapılmalıdır:

1. Qt Modules ekleme:
```xml
<QtModules>core;gui;widgets</QtModules>
```

2. Include dizinleri:
```xml
<AdditionalIncludeDirectories>
  $(DependencyDir)QtDirect3D\source\QDirect3D9Widget;%(AdditionalIncludeDirectories)
</AdditionalIncludeDirectories>
```

3. Qt MOC dosyaları:
```xml
<QtMoc Include="QtDirect3DAdapter.h" />
<QtMoc Include="QDirect3D9Widget.h" />
```

### CMake (Alternatif)

QtDirect3D CMake desteği sunar. CMake kullanmak isterseniz:

```cmake
add_subdirectory(deps/QtDirect3D)
target_link_libraries(your_target QDirect3D9Widget)
```

## Sorun Giderme

### Qt Bulunamıyor

- Qt VS Tools extension'ının yüklü olduğundan emin olun
- Qt versiyonunu Qt Options'da yapılandırın
- Proje properties'te Qt settings'leri kontrol edin

### Direct3D Device Hatası

- DirectX 9 SDK'nın yüklü olduğundan emin olun
- Qt widget'ın device initialized signal'ını kontrol edin
- Adapter'ın InitializeN3Eng() fonksiyonunun başarılı olup olmadığını kontrol edin

### MOC (Meta-Object Compiler) Hataları

- Qt MOC dosyalarının doğru include edildiğinden emin olun
- Q_OBJECT macro'sunun sınıf tanımında olduğundan emin olun
- Qt VS Tools extension'ının MOC işlemlerini yaptığından emin olun

## Geliştirme Notları

### N3Eng Modifikasyonu

Mevcut N3Eng::Init() fonksiyonu kendi device'ını oluşturur. Qt entegrasyonu için:
- Device'ı external olarak alabilir
- Veya Init() fonksiyonu modifiye edilebilir
- Ya da adapter device'ı direkt set eder (mevcut yaklaşım)

### Render Loop

Knight Online'ın render loop'u Qt'nin signal/slot sistemine entegre edilmiştir:
- `ticked` signal → N3Eng update işlemleri
- `rendered` signal → N3Eng render işlemleri
- Present() Qt widget tarafından otomatik yapılır

## Gelecek Geliştirmeler

- [ ] N3Viewer'ın tam Qt versiyonu
- [ ] N3ME (Map Editor) Qt versiyonu
- [ ] N3CE (Character Editor) Qt versiyonu
- [ ] N3FXE (Effect Editor) Qt versiyonu
- [ ] ImGui entegrasyonu (QtDirect3D destekler)

## Referanslar

- QtDirect3D GitHub: https://github.com/giladreich/QtDirect3D
- Qt Dokümantasyonu: https://doc.qt.io/
- Knight Online OpenKO: Bu proje

## Lisans

QtDirect3D: MIT License
Knight Online OpenKO: Proje lisansına bakın

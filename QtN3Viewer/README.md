# QtN3Viewer - Qt ile Knight Online Model Viewer

Bu proje, Knight Online'ın N3Viewer aracının Qt + Direct3D9 ile modernize edilmiş versiyonudur.

## Özellikler

- Qt tabanlı modern UI
- QtDirect3D9Widget ile Direct3D9 rendering entegrasyonu
- Knight Online'ın N3Base rendering engine'ini kullanır
- Model, texture ve effect görüntüleme

## Gereksinimler

### Qt
- Qt 5.12 veya üzeri
- Qt Modules: Core, Gui, Widgets
- Qt Visual Studio Tools (QtMsBuild) yüklü olmalı

### Visual Studio
- Visual Studio 2019 veya 2022
- C++ Desktop Development workload
- Qt VS Tools extension

### Diğer
- DirectX 9 SDK
- Knight Online'ın N3Base kütüphanesi
- QtDirect3D projesi (deps/QtDirect3D)

## Kurulum

1. Qt'yi kurun: https://www.qt.io/download
2. Qt Visual Studio Tools extension'ını yükleyin
3. Visual Studio'da Qt versiyonunu yapılandırın: Extensions > Qt VS Tools > Qt Options

## Derleme

```bash
# QtDirect3D'nin mevcut olduğundan emin olun
# deps/QtDirect3D klasöründe olmalı

# Visual Studio'da QtN3Viewer.sln dosyasını açın
# veya QtN3Viewer.vcxproj dosyasını mevcut solution'a ekleyin
```

## Kullanım

1. Uygulamayı çalıştırın
2. File > Open menüsünden Knight Online model dosyası (.N3) seçin
3. Model viewer penceresinde model görüntülenir

## Proje Yapısı

```
QtN3Viewer/
├── main.cpp                 # Ana uygulama entry point
├── MainWindow.h/.cpp        # Ana pencere
├── MainWindow.ui            # Qt Designer UI dosyası
├── ModelViewWidget.h/.cpp   # Direct3D rendering widget'ı
└── README.md               # Bu dosya
```

## Notlar

- Bu uygulama, Knight Online'ın orijinal MFC tabanlı N3Viewer'ının Qt versiyonudur
- QtDirect3D9Widget, Direct3D9 rendering'i Qt widget içinde yapmayı sağlar
- CQtDirect3DAdapter sınıfı, Qt widget'ın device'ını N3Eng ile entegre eder

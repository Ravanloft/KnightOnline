# QtUIEditor - Kurulum ve Kullanım Rehberi

## Özet

**QtUIEditor**, Knight Online projesine eklenmiş **ayrı bir Qt projesi**dir. Bu proje ile Knight Online'ın UI dosyalarını (.uif) düzenleyebilirsiniz.

## Proje Yapısı

```
/workspace/
├── QtUIEditor/          # ✨ YENİ: UI Editor projesi
│   ├── main.cpp
│   ├── MainWindow.h/.cpp
│   ├── MainWindow.ui
│   └── README.md
│
├── deps/QtDirect3D/     # QtDirect3D library
├── shared/              # CQtDirect3DAdapter (bridge)
├── Client/              # Knight Online client
└── assets/              # Client assets (ko-client-assets)
```

## Nasıl Çalışır?

### 1. **QtUIEditor Projesi**
   - Knight Online projesine **ayrı bir proje** olarak eklenir
   - Qt tabanlı modern UI editörü
   - Visual Studio solution'a eklenebilir

### 2. **QtDirect3D Widget**
   - Direct3D9 rendering için widget
   - QtDirect3D library'sini kullanır

### 3. **CQtDirect3DAdapter**
   - Qt widget ile Knight Online'ın N3Eng'i arasında köprü
   - Device pointer'ını yönetir

### 4. **Knight Online N3Base**
   - UI dosyalarını yükleme/kaydetme
   - UI rendering
   - UI element düzenleme

## Kurulum Adımları

### 1. Qt Kurulumu
```bash
# Qt 5.12+ kurun
# Qt VS Tools extension'ını yükleyin
```

### 2. Asset'leri İndirin
```bash
cd /workspace
git clone https://github.com/Open-KO/ko-client-assets.git assets
```

### 3. Visual Studio'da Proje Oluşturun
- Yeni Qt Widgets Application projesi oluşturun
- QtUIEditor klasöründeki dosyaları kullanın
- QtDirect3D ve Knight Online bağımlılıklarını ekleyin

### 4. Preprocessor Tanımı
```cpp
USE_QT_DIRECT3D  // Proje ayarlarına ekleyin
```

## Kullanım

### 1. Editor'ü Açın
```bash
QtUIEditor.exe
```

### 2. UI Dosyası Yükleyin
- **File > Load UI > Elmorad Inventory** veya
- **File > Open** ile `.uif` dosyası seçin

### 3. UI Element'lerini Düzenleyin
- **Hierarchy Tree**'den element seçin
- **Property Panel**'den özellikleri düzenleyin
- **Direct3D Widget**'ta canlı önizleme görün

### 4. Kaydedin
- **File > Save** ile kaydedin

## Önemli Notlar

⚠️ **Bu Ayrı Bir Proje**: QtUIEditor, Knight Online projesine **ek bir proje** olarak eklenir. Ana oyun projesinden bağımsızdır.

⚠️ **Asset Gereksinimi**: UI dosyalarını düzenlemek için `ko-client-assets` deposunu indirmeniz gerekir.

⚠️ **Qt Kurulumu**: Qt'nin kurulu olması ve Qt VS Tools extension'ının yüklü olması gerekir.

## Sorun Giderme

### Qt Bulunamıyor
- Qt VS Tools > Qt Options'dan Qt versiyonunu ekleyin

### Asset'ler Bulunamıyor
- `assets/` klasörünün doğru konumda olduğundan emin olun
- Path'leri `MainWindow.cpp` içinde düzenleyebilirsiniz

### UI Dosyası Yüklenemiyor
- Asset'lerin doğru indirildiğinden emin olun
- Knight Online N3Base kütüphanesinin doğru link edildiğinden emin olun

## Geliştirme

### Yeni Özellik Ekleme
1. `MainWindow.cpp` içindeki ilgili fonksiyonları düzenleyin
2. UI element düzenleme özellikleri ekleyin
3. Property editor'ı genişletin

### Custom Widget'lar
- Qt'nin zengin widget ekosistemini kullanabilirsiniz
- QPropertyBrowser gibi özel widget'lar eklenebilir

## Sonuç

**QtUIEditor**, Knight Online projesine **ek bir proje** olarak eklenir ve UI dosyalarını düzenlemenizi sağlar. Bu sayede:

✅ Modern Qt UI ile çalışabilirsiniz  
✅ Real-time Direct3D preview alabilirsiniz  
✅ UI element'lerini kolayca düzenleyebilirsiniz  
✅ Inventory ve diğer UI görsellerini değiştirebilirsiniz

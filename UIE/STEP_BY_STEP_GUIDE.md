# UIE Editörü Geliştirme - Adım Adım Rehber

## 🎯 Genel Bakış

Bu rehber, UIE editörünü QtDirect3D ile modernize etmek için yapmanız gereken adımları sıralı olarak açıklar.

---

## 📋 ADIM 1: Qt Kurulumu ve Yapılandırma

### 1.1 Qt İndirme ve Kurulum
```bash
# Qt 5.12 veya üzeri indirin
# https://www.qt.io/download
# 
# Kurulum sırasında:
# - Qt 5.15.2 veya üzeri seçin
# - MSVC 2019 64-bit veya MSVC 2022 64-bit seçin
# - Qt Modules: Core, Gui, Widgets seçili olmalı
```

### 1.2 Qt VS Tools Extension
```
1. Visual Studio'yu açın
2. Extensions > Manage Extensions
3. "Qt Visual Studio Tools" arayın ve yükleyin
4. Visual Studio'yu yeniden başlatın
```

### 1.3 Qt Yapılandırma
```
1. Extensions > Qt VS Tools > Qt Options
2. Add butonuna tıklayın
3. Qt versiyonunu ekleyin (örn: C:\Qt\5.15.2\msvc2019_64)
4. OK'a tıklayın
```

**Kontrol**: Qt kurulumunuz doğru mu?
```bash
# Visual Studio'da yeni bir Qt Widgets Application projesi oluşturmayı deneyin
# Eğer proje oluşturulabiliyorsa Qt doğru kurulmuştur
```

---

## 📋 ADIM 2: Projeye QtDirect3D Entegrasyonu

### 2.1 QtDirect3D Dosyalarını Kopyala
```
1. deps/QtDirect3D/source/QDirect3D9Widget/ klasöründeki dosyaları:
   - QDirect3D9Widget.h
   - QDirect3D9Widget.cpp
   
2. Bu dosyaları UIE/ klasörüne kopyalayın
   VEYA
   Include path'e ekleyin: deps/QtDirect3D/source/QDirect3D9Widget/
```

### 2.2 Visual Studio Proje Ayarları

**Proje Properties (UIEditorModern.vcxproj):**

1. **C/C++ > Preprocessor > Preprocessor Definitions**
   ```
   USE_QT_DIRECT3D ekleyin
   ```

2. **C/C++ > General > Additional Include Directories**
   ```
   $(DependencyDir)QtDirect3D\source\QDirect3D9Widget
   $(Qt_INCLUDEPATH_)
   ```

3. **Linker > General > Additional Library Directories**
   ```
   $(Qt_LIBPATH_)
   ```

4. **Qt Settings (Project Properties > Qt Settings)**
   ```
   Qt Modules: core;gui;widgets
   Qt Version: [Seçtiğiniz Qt versiyonu]
   ```

---

## 📋 ADIM 3: Shared Dosyalarını Projeye Ekle

### 3.1 QtDirect3DAdapter Dosyalarını Ekle

**shared/ klasöründeki dosyaları UIE/ klasörüne kopyalayın:**
```
- QtDirect3DAdapter.h → UIE/QtDirect3DAdapter.h
- QtDirect3DAdapter.cpp → UIE/QtDirect3DAdapter.cpp
```

**VEYA**

Projeye existing item olarak ekleyin (relative path ile)

### 3.2 PropertyEditor ve D3DViewWidget Dosyalarını Ekle

**QtUIEditor/ klasöründen:**
```
- PropertyEditor.h → UIE/PropertyEditor.h
- PropertyEditor.cpp → UIE/PropertyEditor.cpp
- D3DViewWidget.h → UIE/D3DViewWidget.h
- D3DViewWidget.cpp → UIE/D3DViewWidget.cpp
```

### 3.3 Projeye Dosyaları Ekle

**Visual Studio'da:**
```
1. Solution Explorer'da UIE projesine sağ tıklayın
2. Add > Existing Item
3. Kopyaladığınız dosyaları seçin:
   - QtDirect3DAdapter.h/.cpp
   - PropertyEditor.h/.cpp
   - D3DViewWidget.h/.cpp
   - UIEditorModern.h/.cpp
   - UIEditorModern.ui
   - UndoCommands.h/.cpp
```

---

## 📋 ADIM 4: Proje Bağımlılıklarını Ayarla

### 4.1 N3Base Kütüphanesi
```
Proje Properties > Linker > Input > Additional Dependencies:
- N3Base.lib (Debug/Release için)
```

### 4.2 Include Path'leri
```
C/C++ > General > Additional Include Directories:
- ..\Client\N3Base
- ..\shared
- $(DependencyDir)QtDirect3D\source\QDirect3D9Widget
```

### 4.3 Library Path'leri
```
Linker > General > Additional Library Directories:
- $(SolutionDir)lib\$(Platform)\$(Configuration)
```

---

## 📋 ADIM 5: UI Dosyasını Derle (MOC)

### 5.1 UI Dosyasını Qt MOC'e Ekle
**Project Properties > Qt > MOC Files:**
```
UIEditorModern.h ekleyin (MOC otomatik algılamalı)
```

**VEYA manuel olarak:**
```
<QtMoc Include="UIEditorModern.h" />
<QtUic Include="UIEditorModern.ui" />
```

### 5.2 Derleme Kontrolü
```bash
# İlk derleme denemesi
# Hata alırsanız adım adım kontrol edin
```

---

## 📋 ADIM 6: Asset'leri Hazırla

### 6.1 Client Asset'lerini İndir
```bash
cd /workspace
git clone https://github.com/Open-KO/ko-client-assets.git assets
```

### 6.2 Asset Path'i Ayarla
**UIEditorModern.cpp içinde:**
```cpp
QString UIEditorModern::getAssetPath() const
{
    // Gerçek path'inizi buraya yazın
    return "C:/path/to/assets/";  // VEYA
    return QApplication::applicationDirPath() + "/assets/";
}
```

---

## 📋 ADIM 7: İlk Derleme ve Test

### 7.1 Derleme
```
1. Visual Studio'da Build > Build Solution
2. Hataları kontrol edin
3. Eksik include'ları ekleyin
4. Link hatalarını düzeltin
```

### 7.2 Çalıştırma
```
1. Debug > Start Debugging (F5)
2. Editör açılmalı
3. File > Open ile .uif dosyası açmayı deneyin
```

### 7.3 İlk Test
```
✅ Editör açılıyor mu?
✅ Direct3D widget görünüyor mu?
✅ File > Open çalışıyor mu?
✅ Hierarchy tree görünüyor mu?
```

---

## 📋 ADIM 8: Temel Özellikleri Test Et

### 8.1 UI Dosyası Yükleme
```
1. File > Open
2. assets/UI_US/el_inventory_us.uif seç
3. UI yüklenmeli
4. Hierarchy tree'de element'ler görünmeli
```

### 8.2 Element Seçme
```
1. Hierarchy tree'den bir element seç
2. Property Editor'da özellikler görünmeli
3. Direct3D widget'ta UI render edilmeli
```

### 8.3 Property Düzenleme
```
1. Position X değerini değiştir
2. UI element pozisyonu değişmeli
3. Real-time preview çalışmalı
```

---

## 📋 ADIM 9: Eksik Implementasyonları Tamamla

### 9.1 Hierarchy Tree - Child Element'leri Ekle

**UIEditorModern.cpp > addUIToHierarchy():**
```cpp
void UIEditorModern::addUIToHierarchy(QTreeWidgetItem* pParent, CN3UIBase* pUI)
{
    if (!pUI || !pParent) return;
    
    // CN3UIBase'in child listesini al (UIList)
    // Her child için recursive olarak tree item ekle
    // TODO: CN3UIBase'in child list API'sini kullan
}
```

### 9.2 Undo Command - Old Rect Saklama

**D3DViewWidget.cpp:**
```cpp
// Mouse press'te old rect'i sakla
void D3DViewWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_pSelectedElement)
    {
        RECT rc = m_pSelectedElement->GetRegion();
        m_oldRect = QRect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }
    // ...
}
```

### 9.3 Property Editor - Texture File Picker

**PropertyEditor.cpp:**
```cpp
void PropertyEditor::onTextureBrowse()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Texture Seç",
        getTexturePath(),
        "DXT Files (*.dxt *.DXT);;All Files (*.*)"
    );
    
    if (!fileName.isEmpty())
    {
        // Texture path'ini set et
        // TODO: CN3UIImage::SetTex() veya benzeri
    }
}
```

---

## 📋 ADIM 10: Gelişmiş Özellikler

### 10.1 Copy/Paste Implementasyonu
```
1. Clipboard'a UI element serialize et
2. Clipboard'tan deserialize et
3. Yeni element oluştur ve ekle
```

### 10.2 Resize Handles
```
1. Seçili element'in köşelerine handle'lar çiz
2. Handle'lara mouse ile tıklayıp sürükleyerek resize
3. ResizeUIElementCommand ile undo/redo
```

### 10.3 Grid Rendering
```
1. Direct3D widget'ta grid çiz
2. Grid spacing ayarlanabilir olmalı
3. Snap to grid özelliği
```

---

## 🚨 Yaygın Sorunlar ve Çözümleri

### Sorun 1: Qt Bulunamıyor
```
Çözüm:
- Qt VS Tools > Qt Options'dan Qt path'ini kontrol edin
- Project Properties > Qt Settings'ten Qt version seçin
```

### Sorun 2: MOC Hataları
```
Çözüm:
- Q_OBJECT macro'sunun olduğundan emin olun
- Qt VS Tools extension'ın MOC işlemini yaptığından emin olun
- Clean solution yapıp tekrar build edin
```

### Sorun 3: Direct3D Device Hatası
```
Çözüm:
- DirectX 9 SDK'nın kurulu olduğundan emin olun
- Qt widget'ın device initialized signal'ını kontrol edin
- CN3Base::s_lpD3DDev'in set edildiğinden emin olun
```

### Sorun 4: UI Dosyası Yüklenemiyor
```
Çözüm:
- Asset path'inin doğru olduğundan emin olun
- .uif dosyasının varlığını kontrol edin
- CN3Base::PathSet() ile path'i ayarlayın
```

---

## ✅ Kontrol Listesi

### Kurulum
- [ ] Qt kuruldu
- [ ] Qt VS Tools extension yüklendi
- [ ] Qt versiyonu yapılandırıldı

### Proje Yapılandırması
- [ ] USE_QT_DIRECT3D preprocessor tanımı eklendi
- [ ] Include path'leri ayarlandı
- [ ] Library path'leri ayarlandı
- [ ] Qt modules seçildi

### Dosyalar
- [ ] QtDirect3DAdapter dosyaları eklendi
- [ ] PropertyEditor dosyaları eklendi
- [ ] D3DViewWidget dosyaları eklendi
- [ ] UIEditorModern dosyaları eklendi
- [ ] UIEditorModern.ui eklendi
- [ ] UndoCommands dosyaları eklendi

### Derleme
- [ ] Proje derleniyor (hata yok)
- [ ] MOC dosyaları oluşturuldu
- [ ] Link hataları yok

### Test
- [ ] Editör açılıyor
- [ ] UI dosyası yükleniyor
- [ ] Hierarchy görüntüleniyor
- [ ] Property editor çalışıyor
- [ ] Real-time preview çalışıyor

---

## 📝 Sonraki Adımlar (İsteğe Bağlı)

1. **AdvancedPropertyEditor** implementasyonu
2. **UI Element Operations** (Insert, Delete, Copy, Paste)
3. **Visual Improvements** (Grid, Snap, Resize handles)
4. **Keyboard Shortcuts** ekleme
5. **Template System** oluşturma

---

## 💡 İpucular

1. **Adım adım ilerleyin**: Her adımı tamamlayıp test edin
2. **Hataları hemen düzeltin**: Bir adımdaki hata sonraki adımları etkiler
3. **Backup alın**: Çalışan versiyonları kaydedin
4. **Test edin**: Her özelliği ekledikten sonra test edin

---

## 🎯 Hızlı Başlangıç (Özet)

```
1. Qt kur → Qt VS Tools yükle
2. USE_QT_DIRECT3D tanımı ekle
3. Dosyaları projeye ekle
4. Include/Library path'leri ayarla
5. Build et ve test et
```

Herhangi bir adımda sorun yaşarsanız, o adımın detaylarına bakın veya hata mesajını kontrol edin!

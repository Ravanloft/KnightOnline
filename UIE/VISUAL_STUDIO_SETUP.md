# Visual Studio'da UIE Projesini Qt ile Yapılandırma

## ✅ Tamamlanan İşlemler

1. ✅ QtDirect3D klonlandı (`deps/QtDirect3D`)
2. ✅ Gerekli dosyalar UIE klasörüne kopyalandı:
   - `QtDirect3DAdapter.h/cpp`
   - `PropertyEditor.h/cpp`
   - `D3DViewWidget.h/cpp`
3. ✅ `UIE.vcxproj` dosyası güncellendi:
   - Yeni dosyalar eklendi
   - Include path'ler eklendi
   - Preprocessor definition'lar eklendi

---

## 📋 Visual Studio'da Yapılacaklar

### ADIM 1: Visual Studio'yu Açın

```
1. Tools.sln dosyasını açın
2. Solution Explorer'da UIE projesini görmelisiniz
```

---

### ADIM 2: Qt Kurulumunu Kontrol Edin

**Qt kurulu mu?**

Kontrol için:
```
File Explorer'da:
C:\Qt\5.15.2\msvc2019_64\ (veya benzeri)
```

**Eğer Qt yoksa:**
1. https://www.qt.io/download-open-source adresinden indirin
2. Qt 5.15.2 veya 5.15.x sürümünü kurun
3. MSVC 2019 64-bit veya 2017 64-bit seçin

---

### ADIM 3: Qt Değişkenlerini Ayarlayın

#### Yöntem 1: Environment Variable (ÖNERİLEN)

**Windows Environment Variable ekleyin:**

1. Windows + R → `sysdm.cpl` → Enter
2. Advanced → Environment Variables
3. System Variables → New
4. Variable name: `Qt5Dir`
5. Variable value: `C:\Qt\5.15.2\msvc2019_64` (Qt kurulum yolunuz)

**VEYA User Variables:**
- Yalnızca sizin kullanıcı hesabınız için geçerli olur

#### Yöntem 2: Visual Studio Project Properties

1. Solution Explorer'da **UIE** projesine sağ tıklayın
2. **Properties** seçin
3. **Configuration Properties** → **VC++ Directories**
4. **Include Directories** → Edit
5. Şunları ekleyin:
   ```
   C:\Qt\5.15.2\msvc2019_64\include
   C:\Qt\5.15.2\msvc2019_64\include\QtCore
   C:\Qt\5.15.2\msvc2019_64\include\QtGui
   C:\Qt\5.15.2\msvc2019_64\include\QtWidgets
   ```
6. **Library Directories** → Edit
7. Şunu ekleyin:
   ```
   C:\Qt\5.15.2\msvc2019_64\lib
   ```

---

### ADIM 4: Qt Bin Klasörünü PATH'e Ekleyin

**Qt DLL'lerini çalıştırmak için:**

1. Environment Variables → System Variables → Path → Edit
2. New → Şunu ekleyin:
   ```
   C:\Qt\5.15.2\msvc2019_64\bin
   ```
3. OK → OK → OK
4. Visual Studio'yu yeniden başlatın

---

### ADIM 5: Proje Dosyalarını Kontrol Edin

**Solution Explorer'da şu dosyalar görünmeli:**

**Source Files (.cpp):**
- ✅ QtDirect3DAdapter.cpp
- ✅ PropertyEditor.cpp
- ✅ D3DViewWidget.cpp
- ✅ UIEditorModern.cpp
- ✅ UndoCommands.cpp

**Header Files (.h):**
- ✅ QtDirect3DAdapter.h
- ✅ PropertyEditor.h
- ✅ D3DViewWidget.h
- ✅ UIEditorModern.h
- ✅ AdvancedPropertyEditor.h
- ✅ UndoCommands.h

**Eğer görünmüyorsa:**
1. Solution Explorer'da UIE projesine sağ tıklayın
2. **Add** → **Existing Item...**
3. Dosyaları seçin ve ekleyin

---

### ADIM 6: Build Ayarlarını Kontrol Edin

1. **UIE** projesine sağ tıklayın → **Properties**
2. **Configuration Properties** → **C/C++** → **Preprocessor**
3. **Preprocessor Definitions** kontrol edin:
   - ✅ `USE_QT_DIRECT3D` olmalı
   - ✅ `_N3UIE` olmalı
   - ✅ `_N3TOOL` olmalı

4. **C/C++** → **General** → **Additional Include Directories**:
   - ✅ `$(SolutionDir)deps\QtDirect3D\source` olmalı
   - ✅ `$(Qt5Dir)\include` olmalı (veya tam yol)

5. **Linker** → **Input** → **Additional Dependencies**:
   - ✅ `Qt5Core.lib` olmalı
   - ✅ `Qt5Gui.lib` olmalı
   - ✅ `Qt5Widgets.lib` olmalı

---

### ADIM 7: İlk Build Denemesi

1. **Build** → **Clean Solution**
2. **Build** → **Rebuild Solution**
3. Hataları kontrol edin

---

## 🚨 Olası Hatalar ve Çözümleri

### Hata 1: Qt Include Dosyaları Bulunamıyor

```
fatal error C1083: Cannot open include file: 'QtWidgets/QWidget': No such file or directory
```

**Çözüm:**
- Qt5Dir environment variable'ını kontrol edin
- Include path'lerini kontrol edin
- Qt kurulum yolunu doğru yazdığınızdan emin olun

---

### Hata 2: Qt Library Dosyaları Bulunamıyor

```
error LNK2019: unresolved external symbol
```

**Çözüm:**
1. Library Directories'te Qt lib klasörü var mı kontrol edin
2. Additional Dependencies'te Qt5*.lib dosyaları var mı kontrol edin
3. Qt bin klasörünü PATH'e eklediğinizden emin olun

---

### Hata 3: QDirect3D9Widget Bulunamıyor

```
fatal error C1083: Cannot open include file: 'QDirect3D9Widget.h': No such file or directory
```

**Çözüm:**
1. `deps\QtDirect3D\source\QDirect3D9Widget\QDirect3D9Widget.h` dosyası var mı kontrol edin
2. Include path'te `$(SolutionDir)deps\QtDirect3D\source` var mı kontrol edin

---

### Hata 4: MOC (Meta-Object Compiler) Hatası

```
error: MOC file not found
```

**Çözüm:**
Qt dosyaları için MOC gerekli. Visual Studio Qt extension kurun:
1. Visual Studio → Extensions → Manage Extensions
2. "Qt Visual Studio Tools" ara
3. Install

**VEYA manuel MOC:**
1. Project Properties → Configuration Properties → General
2. **Item Type** → **Qt MOC** olarak ayarlayın (.h dosyaları için)

---

## 📝 Qt Yolunu Bulma

**Qt kurulum yolunuzu bulmak için:**

**Windows'ta:**
```
1. Qt Maintenance Tool'u açın
2. Settings → Repositories → Local Repository gösterir
```

**VEYA File Explorer'da:**
```
C:\Qt\ dizinine bakın
Genellikle: C:\Qt\5.15.2\msvc2019_64\
```

---

## ✅ Kontrol Listesi

**Qt Kurulumu:**
- [ ] Qt 5.15.x kurulu mu?
- [ ] Qt5Dir environment variable ayarlandı mı?
- [ ] Qt bin klasörü PATH'e eklendi mi?

**Proje Ayarları:**
- [ ] Tüm dosyalar Solution Explorer'da görünüyor mu?
- [ ] USE_QT_DIRECT3D preprocessor definition var mı?
- [ ] Include path'ler doğru mu?
- [ ] Library path'ler doğru mu?
- [ ] Qt5*.lib dosyaları link ediliyor mu?

**QtDirect3D:**
- [ ] deps\QtDirect3D klasörü var mı?
- [ ] QDirect3D9Widget.h dosyası var mı?

**Build:**
- [ ] Clean Solution yapıldı mı?
- [ ] Build başarılı mı?

---

## 🎯 Sonraki Adımlar

Build başarılı olduktan sonra:
1. ✅ Qt DLL'lerini çalıştırılabilir klasöre kopyalayın
2. ✅ İlk çalıştırma testi yapın
3. ✅ UI dosyalarını yüklemeyi test edin

---

## 💡 Hızlı Komutlar

**Qt yolunu kontrol:**
```cmd
echo %Qt5Dir%
```

**Qt include dosyalarını kontrol:**
```cmd
dir C:\Qt\5.15.2\msvc2019_64\include\QtCore
```

**Qt lib dosyalarını kontrol:**
```cmd
dir C:\Qt\5.15.2\msvc2019_64\lib\Qt5Core.lib
```

---

## 📚 Ek Kaynaklar

- Qt Installation Guide: https://doc.qt.io/qt-5/gettingstarted.html
- Visual Studio Qt Tools: https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools2019
- QtDirect3D GitHub: https://github.com/giladreich/QtDirect3D

---

## 🆘 Yardım

Hala sorun yaşıyorsanız:
1. Build Output penceresindeki hataları kontrol edin
2. Error List penceresindeki hataları okuyun
3. Qt kurulum yolunuzu kontrol edin
4. Environment variable'ları kontrol edin

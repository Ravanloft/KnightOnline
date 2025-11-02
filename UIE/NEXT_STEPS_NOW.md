# Şimdi Yapılacaklar - Hızlı Başlangıç

## ✅ Tamamlanan İşlemler

1. ✅ QtDirect3D klonlandı
2. ✅ Gerekli dosyalar UIE klasörüne kopyalandı
3. ✅ UIE.vcxproj dosyası güncellendi
4. ✅ Include path'ler ve library ayarları eklendi

---

## 🎯 ŞİMDİ YAPMANIZ GEREKENLER

### 1. Visual Studio'da Projeyi Yeniden Yükleyin

```
1. Visual Studio'yu açın (Tools.sln zaten açık olmalı)
2. Solution Explorer'da UIE projesine sağ tıklayın
3. "Unload Project" seçin
4. Tekrar sağ tıklayın → "Reload Project"
```

**VEYA:**
```
1. Visual Studio'yu kapatın
2. Tools.sln'i tekrar açın
```

---

### 2. Dosyaları Kontrol Edin

**Solution Explorer'da şu dosyalar görünmeli:**

**Source Files:**
- QtDirect3DAdapter.cpp
- PropertyEditor.cpp
- D3DViewWidget.cpp
- UIEditorModern.cpp
- UndoCommands.cpp

**Header Files:**
- QtDirect3DAdapter.h
- PropertyEditor.h
- D3DViewWidget.h
- UIEditorModern.h
- AdvancedPropertyEditor.h
- UndoCommands.h

**Eğer görünmüyorsa:**
1. UIE projesine sağ tıklayın
2. Add → Existing Item...
3. UIE klasöründen bu dosyaları seçin ve ekleyin

---

### 3. Qt Kurulumunu Kontrol Edin

**Qt kurulu mu?**

Windows File Explorer'da:
```
C:\Qt\5.15.2\msvc2019_64\
```
klasörü var mı kontrol edin.

**Eğer yoksa:**
- https://www.qt.io/download-open-source
- Qt 5.15.2 veya 5.15.x indirin ve kurun
- MSVC 2019 64-bit seçin

---

### 4. Qt Environment Variable Ayarlayın

**Windows Environment Variable ekleyin:**

**Yöntem 1: CMD ile (Hızlı)**
```cmd
setx Qt5Dir "C:\Qt\5.15.2\msvc2019_64"
```
(Visual Studio'yu yeniden başlatın)

**Yöntem 2: GUI ile**
1. Windows + R → `sysdm.cpl` → Enter
2. Advanced → Environment Variables
3. System Variables → New
4. Variable name: `Qt5Dir`
5. Variable value: `C:\Qt\5.15.2\msvc2019_64` (Qt kurulum yolunuz)
6. OK → OK → OK

**Visual Studio'yu yeniden başlatın!**

---

### 5. Qt Bin Klasörünü PATH'e Ekleyin

**Qt DLL'lerini çalıştırmak için:**

1. Environment Variables → System Variables → Path → Edit
2. New → Şunu ekleyin:
   ```
   C:\Qt\5.15.2\msvc2019_64\bin
   ```
3. OK → OK → OK

---

### 6. Build Denemesi Yapın

**Visual Studio'da:**

1. **Build** → **Clean Solution**
2. **Build** → **Rebuild Solution**

**İlk build muhtemelen hata verecek** (Qt path'leri ayarlanmadıysa), bu normal!

---

## 🚨 Olası İlk Hatalar

### Hata 1: Qt Include Dosyaları Bulunamıyor

```
fatal error C1083: Cannot open include file: 'QtWidgets/QWidget'
```

**Çözüm:**
- Qt5Dir environment variable ayarlandı mı kontrol edin
- Visual Studio'yu yeniden başlattınız mı?
- Qt kurulum yolunu doğru yazdınız mı?

**Kontrol:**
```cmd
echo %Qt5Dir%
```
Qt yolunuzu göstermeli.

---

### Hata 2: QDirect3D9Widget Bulunamıyor

```
fatal error: 'QDirect3D9Widget.h': No such file or directory
```

**Çözüm:**
1. `deps\QtDirect3D\source\QDirect3D9Widget\QDirect3D9Widget.h` dosyası var mı?
2. File Explorer'da kontrol edin

---

### Hata 3: MOC Hatası

```
error: MOC file not found
```

**Şimdilik önemli değil** - Qt extension kurulduğunda çözülecek.

**Çözüm:**
1. Visual Studio → Extensions → Manage Extensions
2. "Qt Visual Studio Tools" ara ve kur

---

## ✅ Başarılı Build İçin Kontrol Listesi

**Qt:**
- [ ] Qt 5.15.x kurulu mu?
- [ ] Qt5Dir environment variable ayarlandı mı?
- [ ] Qt bin klasörü PATH'e eklendi mi?
- [ ] Visual Studio yeniden başlatıldı mı?

**Proje:**
- [ ] Tüm dosyalar Solution Explorer'da görünüyor mu?
- [ ] Clean Solution yapıldı mı?
- [ ] Build denemesi yapıldı mı?

---

## 📝 Detaylı Bilgi

Daha detaylı bilgi için:
- `UIE/VISUAL_STUDIO_SETUP.md` dosyasına bakın

---

## 🎯 Sonraki Adımlar

Build başarılı olduktan sonra:
1. ✅ UIEditorModern kodunu test et
2. ✅ UI dosyalarını yükle
3. ✅ Görsel düzenlemeyi dene

**Sorun yaşıyorsanız hata mesajlarını paylaşın!**

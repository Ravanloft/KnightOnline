# Mevcut Durum: Tools.sln Açık, UIE Görünüyor ✅

## 🎯 Şu Anda Durumunuz

```
✅ Tools.sln açıldı
✅ UIE projesi Solution Explorer'da görünüyor
```

**Sonraki adımlar:**

---

## 🔥 ÖNCELİK 1: Qt Kurulumunu Kontrol Et

### Qt Kurulu mu?

**Kontrol Et:**
```
1. Visual Studio'da Extensions menüsüne bak
2. "Qt Visual Studio Tools" görünüyor mu?
```

**YOKSA:**
```
1. Extensions > Manage Extensions
2. "Qt Visual Studio Tools" ara ve yükle
3. VS'yu yeniden başlat
```

**Qt SDK var mı?**
```
Eğer Qt SDK yoksa:
1. https://www.qt.io/download
2. Qt 5.12+ indir ve kur
3. MSVC 2019/2022 64-bit seç
```

**Qt VS'da yapılandırıldı mı?**
```
1. Extensions > Qt VS Tools > Qt Options
2. Add > Qt path'i ekle (örn: C:\Qt\5.15.2\msvc2019_64)
3. OK
```

---

## 📋 ÖNCELİK 2: Dosyaları Hazırla

### Hangi Dosyaları Kopyalamalıyım?

**1. QtDirect3DAdapter:**
```
shared/QtDirect3DAdapter.h → UIE/ klasörüne kopyala
shared/QtDirect3DAdapter.cpp → UIE/ klasörüne kopyala
```

**2. PropertyEditor:**
```
QtUIEditor/PropertyEditor.h → UIE/ klasörüne kopyala
QtUIEditor/PropertyEditor.cpp → UIE/ klasörüne kopyala
```

**3. D3DViewWidget:**
```
QtUIEditor/D3DViewWidget.h → UIE/ klasörüne kopyala
QtUIEditor/D3DViewWidget.cpp → UIE/ klasörüne kopyala
```

**4. UndoCommands (zaten var):**
```
UIE/UndoCommands.h ✅
UIE/UndoCommands.cpp ✅
```

---

## 📋 ÖNCELİK 3: Visual Studio'ya Ekle

### Dosyaları Projeye Ekle

```
1. Solution Explorer'da UIE projesine sağ tıkla
2. Add > Existing Item
3. Kopyaladığınız 6 dosyayı seç:
   - QtDirect3DAdapter.h
   - QtDirect3DAdapter.cpp
   - PropertyEditor.h
   - PropertyEditor.cpp
   - D3DViewWidget.h
   - D3DViewWidget.cpp
4. Add butonuna tıkla
```

---

## 📋 ÖNCELİK 4: Proje Ayarları

### 1. Preprocessor Tanımı

```
1. UIE projesine sağ tıkla > Properties
2. Configuration Properties > C/C++ > Preprocessor
3. Preprocessor Definitions > Edit
4. Yeni satır ekle: USE_QT_DIRECT3D
5. OK
```

### 2. Include Path'leri

```
1. Properties > C/C++ > General
2. Additional Include Directories > Edit
3. Şunları ekle:
   - $(DependencyDir)QtDirect3D\source\QDirect3D9Widget
   - ..\shared
   - ..\Client\N3Base
   - $(Qt_INCLUDEPATH_)
4. OK
```

---

## 📋 ÖNCELİK 5: İlk Build

### Build Et

```
1. Build > Clean Solution
2. Build > Build Solution (F7)
```

### Hataları Kontrol Et

**"Qt bulunamadı" hatası:**
→ Qt kurulumunu kontrol et (Öncelik 1)

**"Include bulunamadı" hatası:**
→ Include path'lerini kontrol et (Öncelik 4)

**"USE_QT_DIRECT3D tanımlı değil" hatası:**
→ Preprocessor tanımını kontrol et (Öncelik 4.1)

---

## ✅ Hızlı Kontrol Listesi

```
[ ] Qt SDK kurulu mu?
[ ] Qt VS Tools extension var mı?
[ ] Qt versiyonu VS'da yapılandırıldı mı?
[ ] Dosyalar kopyalandı mı? (6 dosya)
[ ] Dosyalar VS'ya eklendi mi?
[ ] USE_QT_DIRECT3D tanımı eklendi mi?
[ ] Include path'leri ayarlandı mı?
[ ] Build denemesi yapıldı mı?
```

---

## 🎯 ŞİMDİ NE YAPMALISINIZ?

### ADIM 1: Qt Kontrolü (5 dakika)
```
Qt VS Tools var mı kontrol et
Yoksa kur
Qt SDK var mı kontrol et
Yoksa indir ve kur
Qt versiyonunu VS'da yapılandır
```

### ADIM 2: Dosyaları Kopyala (5 dakika)
```
6 dosyayı UIE/ klasörüne kopyala
VS'ya ekle
```

### ADIM 3: Ayarları Yap (5 dakika)
```
Preprocessor tanımı ekle
Include path'leri ekle
```

### ADIM 4: Build Et (10 dakika)
```
Build et
Hataları düzelt
Tekrar build et
```

---

## 📝 Adım Adım Checklist

### ✅ Tamamlanan
- [x] Tools.sln açıldı
- [x] UIE projesi görünüyor

### 🔄 Şu Anda Yapılacaklar
- [ ] Qt kurulumu kontrol
- [ ] Dosyaları kopyala
- [ ] VS'ya ekle
- [ ] Proje ayarları
- [ ] Build et

### 📋 Sonraki Adımlar
- [ ] Asset'leri indir
- [ ] İlk test
- [ ] Geliştirme

---

## 💡 İpucu

**Her adımı tamamladıktan sonra test edin!**
- Qt kuruldu → Test: Qt Options açılabiliyor mu?
- Dosyalar kopyalandı → Test: Dosyalar UIE/ klasöründe var mı?
- VS'ya eklendi → Test: Solution Explorer'da görünüyor mu?
- Ayarlar yapıldı → Test: Properties'te görünüyor mu?
- Build edildi → Test: Hata var mı?

---

## ❓ Hangi Adımdasınız?

Lütfen şunu söyleyin:
1. Qt kurulu mu? (Evet/Hayır)
2. Dosyaları kopyaladınız mı? (Evet/Hayır)
3. Proje ayarlarını yaptınız mı? (Evet/Hayır)

Size göre bir sonraki adımı detaylandırabilirim!

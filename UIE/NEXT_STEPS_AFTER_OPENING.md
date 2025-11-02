# Tools.sln Açıldıktan Sonra Yapılacaklar

## ✅ Durum: Tools.sln açıldı, UIE projesi görünüyor

Şimdi sırayla şunları yapın:

---

## 📋 ADIM 1: Qt Kurulumunu Kontrol Et (İlk Öncelik!)

### 1.1 Qt Kurulu mu Kontrol Et
```
1. Visual Studio'da
2. Extensions > Manage Extensions
3. "Qt" arayın
4. "Qt Visual Studio Tools" görünüyor mu?
   ✅ Görünüyorsa → Kurulu
   ❌ Görünmüyorsa → Kurulum gerekli
```

### 1.2 Qt VS Tools Yoksa Kur
```
1. Extensions > Manage Extensions
2. "Qt Visual Studio Tools" ara
3. Download (veya Install) tıkla
4. Visual Studio'yu yeniden başlat
```

### 1.3 Qt SDK Kurulu mu?
```
Eğer Qt SDK yoksa:
1. https://www.qt.io/download adresine git
2. Qt 5.12 veya üzeri indir
3. Kurulum sırasında:
   - MSVC 2019 64-bit veya MSVC 2022 64-bit seç
   - Qt Modules: Core, Gui, Widgets seç
```

### 1.4 Qt Versiyonunu Visual Studio'ya Ekle
```
1. Extensions > Qt VS Tools > Qt Options
2. Add butonuna tıkla
3. Qt Installation Path: (örn: C:\Qt\5.15.2\msvc2019_64)
4. Version: (otomatik algılanır)
5. OK
```

**Kontrol:** Qt kurulumu tamam mı?
```
- Qt VS Tools extension var mı? ✅
- Qt SDK kurulu mu? ✅
- Qt versiyonu VS'da yapılandırılmış mı? ✅
```

---

## 📋 ADIM 2: UIE Projesini Yapılandır

### 2.1 UIE Projesini Seç
```
1. Solution Explorer'da UIE projesine sağ tıkla
2. Properties'i seç
```

### 2.2 Preprocessor Tanımı Ekle
```
1. Configuration Properties > C/C++ > Preprocessor
2. Preprocessor Definitions satırını bul
3. Edit'e tıkla (üç nokta)
4. Yeni satıra ekle:
   USE_QT_DIRECT3D
5. OK
```

### 2.3 Qt Ayarlarını Yapılandır (Eğer Qt projesi yapıyorsanız)

**ŞİMDİLİK:** Mevcut UIE MFC projesi ile çalışıyoruz, bu adım şimdilik opsiyonel.

---

## 📋 ADIM 3: İlk Build Denemesi

### 3.1 Mevcut Projeyi Build Et
```
1. Solution Explorer'da UIE'ye sağ tıkla
2. Build'i seç
   VEYA
3. Build > Build Solution (F7)
```

### 3.2 Hataları Not Et
```
Build çıktısını kontrol edin:
- Hangi dosyalar bulunamıyor?
- Hangi kütüphaneler eksik?
- Hangi include path'leri yanlış?

Hataları not alın, sonraki adımlarda düzelteceğiz.
```

### 3.3 Bağımlılıkları Build Et
```
Eğer bağımlılıklar eksikse:
1. Solution Explorer'da N3Base projesine sağ tıkla
2. Build'i seç
3. shared projesini build et
4. Sonra tekrar UIE'yi build et
```

---

## 📋 ADIM 4: Modern Qt Editor Projesini Oluştur

### 4.1 Yeni Qt Projesi Ekle (ÖNERİLEN)

**Seçenek A: Yeni Qt Widgets Application**

```
1. Solution Explorer'da Tools solution'ına sağ tıkla
2. Add > New Project
3. "Qt" arayın
4. "Qt Widgets Application" seç
5. Next
6. Project name: UIEditorModern
7. Location: KnightOnline\UIE\ klasörü
8. Create
```

**Seçenek B: Mevcut Dosyaları Kullan**

Hazırladığımız dosyaları kullanabilirsiniz:
- `UIE/UIEditorModern.h/.cpp` (zaten var)
- Ancak bunlar şimdilik Qt projesi değil, MFC ile uyumlu olacak şekilde hazırlanmış

---

## 📋 ADIM 5: Gerekli Dosyaları Projeye Ekle

### 5.1 QtDirect3D Dosyalarını Kontrol Et
```
Kontrol edin:
deps/QtDirect3D/source/QDirect3D9Widget/ klasöründe:
- QDirect3D9Widget.h
- QDirect3D9Widget.cpp

Bu dosyalar var mı? ✅/❌
```

### 5.2 Shared Dosyalarını UIE'ye Kopyala
```
Şu dosyaları UIE/ klasörüne kopyalayın:
1. shared/QtDirect3DAdapter.h → UIE/QtDirect3DAdapter.h
2. shared/QtDirect3DAdapter.cpp → UIE/QtDirect3DAdapter.cpp
```

### 5.3 Property Editor Dosyalarını Kopyala
```
Şu dosyaları UIE/ klasörüne kopyalayın:
1. QtUIEditor/PropertyEditor.h → UIE/PropertyEditor.h
2. QtUIEditor/PropertyEditor.cpp → UIE/PropertyEditor.cpp
```

### 5.4 D3DViewWidget Dosyalarını Kopyala
```
Şu dosyaları UIE/ klasörüne kopyalayın:
1. QtUIEditor/D3DViewWidget.h → UIE/D3DViewWidget.h
2. QtUIEditor/D3DViewWidget.cpp → UIE/D3DViewWidget.cpp
```

### 5.5 Undo Commands Dosyalarını Kopyala
```
Şu dosyalar zaten UIE/ klasöründe:
1. UIE/UndoCommands.h (zaten var)
2. UIE/UndoCommands.cpp (zaten var)
```

### 5.6 Visual Studio'ya Dosyaları Ekle
```
1. Solution Explorer'da UIE projesine sağ tıkla
2. Add > Existing Item
3. Kopyaladığınız dosyaları seç:
   - QtDirect3DAdapter.h/.cpp
   - PropertyEditor.h/.cpp
   - D3DViewWidget.h/.cpp
   - UndoCommands.h/.cpp (zaten ekli olabilir)
4. Add
```

---

## 📋 ADIM 6: Include Path'lerini Ayarla

### 6.1 UIE Proje Properties
```
1. UIE projesine sağ tıkla > Properties
2. Configuration Properties > C/C++ > General
3. Additional Include Directories satırını bul
4. Edit'e tıkla
```

### 6.2 Path'leri Ekle
```
Şu path'leri ekleyin:
- $(DependencyDir)QtDirect3D\source\QDirect3D9Widget
- ..\shared
- ..\Client\N3Base
- $(Qt_INCLUDEPATH_)

Her birini ayrı satıra ekleyin.
```

---

## 📋 ADIM 7: İlk Build Denemesi (Qt ile)

### 7.1 Build
```
1. Build > Clean Solution
2. Build > Rebuild Solution
```

### 7.2 Hataları Kontrol Et
```
Yaygın hatalar ve çözümleri:

"Hata: QDirect3D9Widget.h bulunamadı"
→ Include path'i kontrol et (ADIM 6)

"Hata: USE_QT_DIRECT3D tanımlı değil"
→ Preprocessor tanımını kontrol et (ADIM 2.2)

"Hata: Qt bulunamadı"
→ Qt VS Tools ve Qt SDK kurulumunu kontrol et (ADIM 1)

"Hata: N3Base.h bulunamadı"
→ Include path'e ..\Client\N3Base ekle
```

---

## 📋 ADIM 8: Asset'leri Hazırla

### 8.1 Asset Deposunu İndir
```bash
# Terminal'de KnightOnline klasörüne gidin
cd C:\Projects\KnightOnline

# Asset'leri klonlayın
git clone https://github.com/Open-KO/ko-client-assets.git assets
```

### 8.2 Asset Path'ini Ayarla
```
UIEditorModern.cpp dosyasını açın
getAssetPath() fonksiyonunu bulun
Path'i düzenleyin:

QString UIEditorModern::getAssetPath() const
{
    return QApplication::applicationDirPath() + "/assets/";
    // VEYA tam path:
    // return "C:/Projects/KnightOnline/assets/";
}
```

---

## 📋 ADIM 9: İlk Çalıştırma

### 9.1 Debug Modda Çalıştır
```
1. Solution Explorer'da UIE projesine sağ tıkla
2. Set as StartUp Project
3. Debug > Start Debugging (F5)
   VEYA
4. Build > Build Solution
5. bin klasöründe UIE.exe'yi çalıştır
```

### 9.2 İlk Test
```
Editör açıldığında kontrol edin:
✅ Pencere açılıyor mu?
✅ Menüler görünüyor mu?
✅ Direct3D widget görünüyor mu? (eğer Qt versiyonuysa)
```

---

## 🎯 Hangi Sırayla Yapmalısınız?

### Öncelik 1: Qt Kurulumu ⭐⭐⭐
```
1. Qt SDK kuruldu mu?
2. Qt VS Tools extension kuruldu mu?
3. Qt versiyonu VS'da yapılandırıldı mı?

Bu olmadan devam edemezsiniz!
```

### Öncelik 2: Dosyaları Ekle ⭐⭐
```
1. Shared dosyaları kopyala
2. PropertyEditor dosyaları kopyala
3. D3DViewWidget dosyaları kopyala
4. Visual Studio'ya ekle
```

### Öncelik 3: Proje Ayarları ⭐⭐
```
1. Preprocessor tanımı (USE_QT_DIRECT3D)
2. Include path'leri
3. Library path'leri
```

### Öncelik 4: Build ve Test ⭐
```
1. Build et
2. Hataları düzelt
3. Çalıştır ve test et
```

---

## 📊 İlerleme Takibi

### Faz 1: Hazırlık
- [ ] Tools.sln açıldı ✅
- [ ] UIE projesi görünüyor ✅
- [ ] Qt SDK kuruldu
- [ ] Qt VS Tools kuruldu
- [ ] Qt versiyonu yapılandırıldı

### Faz 2: Dosyalar
- [ ] QtDirect3DAdapter dosyaları eklendi
- [ ] PropertyEditor dosyaları eklendi
- [ ] D3DViewWidget dosyaları eklendi
- [ ] UndoCommands dosyaları eklendi
- [ ] Visual Studio'ya eklendi

### Faz 3: Yapılandırma
- [ ] Preprocessor tanımı eklendi
- [ ] Include path'leri ayarlandı
- [ ] Library path'leri ayarlandı

### Faz 4: Build
- [ ] İlk build denemesi
- [ ] Hatalar düzeltildi
- [ ] Başarılı build

### Faz 5: Test
- [ ] Editör açılıyor
- [ ] UI dosyası yükleniyor
- [ ] Temel özellikler çalışıyor

---

## 🚨 Şu Anda Yapmanız Gerekenler

### İLK ÖNCE (Öncelik):
```
1. Qt SDK kuruldu mu kontrol et
2. Qt VS Tools extension var mı kontrol et
3. Qt versiyonu Visual Studio'da yapılandırıldı mı?

Bu adımlar tamamlanmadan devam etmeyin!
```

### SONRA:
```
4. Dosyaları kopyala ve projeye ekle
5. Proje ayarlarını yap
6. Build et
7. Test et
```

---

## ❓ Sorularınız Varsa

Hangi adımdasınız? Size göre detaylandırabilirim:
- Qt kurulumu
- Dosya kopyalama
- Proje ayarları
- Build hataları
- Test

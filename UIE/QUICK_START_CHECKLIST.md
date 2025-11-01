# Hızlı Başlangıç Kontrol Listesi

## ✅ Adım Adım Kontrol Listesi

### ADIM 1: Qt Kurulumu (5 dakika)
```
☐ Qt 5.12+ indirildi ve kuruldu
☐ Qt VS Tools extension yüklendi
☐ Qt versiyonu Visual Studio'da yapılandırıldı
☐ Test: Yeni Qt projesi oluşturulabildi
```

### ADIM 2: Proje Yapılandırması (10 dakika)
```
☐ USE_QT_DIRECT3D preprocessor tanımı eklendi
☐ Qt modules (core, gui, widgets) seçildi
☐ Include path'leri ayarlandı:
  - $(DependencyDir)QtDirect3D\source\QDirect3D9Widget
  - ..\Client\N3Base
  - ..\shared
☐ Library path'leri ayarlandı
☐ N3Base.lib link edildi
```

### ADIM 3: Dosyaları Ekle (5 dakika)
```
☐ QtDirect3DAdapter.h/.cpp → UIE/ klasörüne kopyalandı
☐ PropertyEditor.h/.cpp → UIE/ klasörüne kopyalandı
☐ D3DViewWidget.h/.cpp → UIE/ klasörüne kopyalandı
☐ UIEditorModern.h/.cpp → UIE/ klasöründe
☐ UIEditorModern.ui → UIE/ klasöründe
☐ UndoCommands.h/.cpp → UIE/ klasöründe
☐ Tüm dosyalar Visual Studio projesine eklendi
```

### ADIM 4: UI Dosyası (2 dakika)
```
☐ UIEditorModern.ui Qt Designer'da açılabiliyor
☐ MOC dosyaları otomatik oluşturuluyor
☐ ui_UIEditorModern.h dosyası oluştu
```

### ADIM 5: İlk Derleme (5 dakika)
```
☐ Clean Solution yapıldı
☐ Build başlatıldı
☐ Derleme hataları kontrol edildi
☐ Include hataları düzeltildi
☐ Link hataları düzeltildi
☐ Başarılı derleme yapıldı
```

### ADIM 6: Asset'ler (3 dakika)
```
☐ ko-client-assets deposu klonlandı
☐ assets/UI_US/ klasörü var
☐ getAssetPath() fonksiyonu doğru path döndürüyor
```

### ADIM 7: İlk Çalıştırma (5 dakika)
```
☐ UIE Editor çalıştırıldı
☐ Pencere açıldı
☐ Direct3D widget görünüyor
☐ Menüler çalışıyor
☐ Status bar görünüyor
```

### ADIM 8: Temel Test (10 dakika)
```
☐ File > Open çalışıyor
☐ .uif dosyası açılabiliyor
☐ Hierarchy tree'de element'ler görünüyor
☐ Element seçildiğinde Property Editor güncelleniyor
☐ Direct3D widget'ta UI render ediliyor
☐ Property değişikliği UI'ya yansıyor
```

---

## 🚨 Hata Kontrolü

### Derleme Hataları
```
☐ "Qt bulunamadı" → Qt Options kontrol et
☐ "MOC hatası" → Q_OBJECT macro kontrol et
☐ "Include bulunamadı" → Include path'leri kontrol et
☐ "Link hatası" → Library path'leri ve .lib dosyalarını kontrol et
```

### Çalışma Hataları
```
☐ "Direct3D device hatası" → DirectX 9 SDK kontrol et
☐ "UI yüklenemiyor" → Asset path kontrol et
☐ "Crash" → Debug modda çalıştır ve stack trace'e bak
```

---

## 📊 İlerleme Takibi

### Faz 1: Kurulum ✅
- [x] Qt kurulumu
- [x] Proje yapılandırması
- [x] Dosyaları ekleme

### Faz 2: Derleme 🔄
- [ ] İlk derleme
- [ ] Hata düzeltme
- [ ] Başarılı derleme

### Faz 3: Test ✅
- [ ] İlk çalıştırma
- [ ] Temel özellikler
- [ ] UI yükleme

### Faz 4: Geliştirme 📋
- [ ] Eksik implementasyonlar
- [ ] Yeni özellikler
- [ ] İyileştirmeler

---

## ⏱️ Tahmini Süre

- **Kurulum**: 20-30 dakika
- **Yapılandırma**: 15-20 dakika
- **İlk Derleme**: 10-15 dakika (hata varsa daha uzun)
- **Test**: 15-20 dakika
- **Toplam**: ~1-1.5 saat (sorunsuz)

---

## 🎯 Hızlı Komutlar

### Temiz Derleme
```
1. Build > Clean Solution
2. Build > Rebuild Solution
```

### Qt MOC Manuel Çalıştırma
```
1. Project Properties > Qt > MOC
2. Manual override (gerekirse)
```

### Asset Path Test
```cpp
// UIEditorModern.cpp içinde test edin:
QMessageBox::information(this, "Path", getAssetPath());
```

---

## ✅ Başarı Kriterleri

Editör başarıyla kurulduysa:
- ✅ Derleme hatası yok
- ✅ Editör açılıyor
- ✅ UI dosyası yükleniyor
- ✅ Element'ler görüntüleniyor
- ✅ Property düzenleme çalışıyor

**Tebrikler! 🎉**

Artık geliştirmeye devam edebilirsiniz!

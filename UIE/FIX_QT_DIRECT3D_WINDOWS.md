# QtDirect3D Klasörü Boş - Windows'ta Çözüm

## 🔍 Durum
`deps\QtDirect3D` klasörü boş görünüyor.

## ✅ Çözüm: QtDirect3D'yi İndir

### ADIM 1: Terminal/CMD Aç

**Windows'ta:**
```
1. Windows + R tuşlarına bas
2. "cmd" yaz ve Enter
   VEYA
1. Başlat menüsünde "Command Prompt" ara
2. Aç
```

---

### ADIM 2: KnightOnline Klasörüne Git

**CMD'de şunu yazın:**
```cmd
cd C:\Projects\KnightOnline
```
**VEYA projenizin olduğu klasör:**
```cmd
cd C:\Users\YourName\Documents\KnightOnline
```

---

### ADIM 3: deps Klasörüne Git

```cmd
cd deps
```

---

### ADIM 4: QtDirect3D Klasörünü Kontrol Et

```cmd
dir QtDirect3D
```

**Eğer klasör boşsa veya yoksa:**
```cmd
rmdir /s /q QtDirect3D
```
(Önce silin)

---

### ADIM 5: QtDirect3D'yi Klonla

**ÖNEMLİ:** `--recursive` parametresi şart!

```cmd
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D
```

**Bekleyin:** İndirme biraz sürebilir (1-2 dakika)

---

### ADIM 6: Kontrol Et

```cmd
cd QtDirect3D
dir source\QDirect3D9Widget
```

**Görmeli:**
```
QDirect3D9Widget.h
QDirect3D9Widget.cpp
ImGui (klasör)
```

---

## 🎯 Alternatif: File Explorer ile

### Yöntem 1: GitHub Desktop

```
1. GitHub Desktop uygulamasını açın
2. File > Clone Repository
3. URL sekmesine tıklayın
4. Şu URL'yi yapıştırın:
   https://github.com/giladreich/QtDirect3D.git
5. Local path:
   C:\Projects\KnightOnline\deps\QtDirect3D
6. Clone Repository butonuna tıklayın
```

### Yöntem 2: ZIP İndir

```
1. Tarayıcıda şu adrese gidin:
   https://github.com/giladreich/QtDirect3D
2. Yeşil "Code" butonuna tıklayın
3. "Download ZIP" seçin
4. ZIP'i C:\Projects\KnightOnline\deps\ klasörüne indirin
5. ZIP'i çıkarın
6. Klasör adını "QtDirect3D" olarak değiştirin
```

---

## ✅ Kontrol Listesi

### Terminal Komutları (Sırayla)
```cmd
cd C:\Projects\KnightOnline
cd deps
rmdir /s /q QtDirect3D
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D
cd QtDirect3D
dir source\QDirect3D9Widget
```

**Sonuç:** 2 dosya görünmeli ✅

---

## 🔍 Dosyaların Doğru Yerde Olduğunu Kontrol Et

**File Explorer'da:**
```
KnightOnline\
└── deps\
    └── QtDirect3D\
        └── source\
            └── QDirect3D9Widget\
                ├── QDirect3D9Widget.h      ← BUNU ARIYORUZ ✅
                └── QDirect3D9Widget.cpp    ← BUNU ARIYORUZ ✅
```

**Kontrol:**
```
1. File Explorer'ı açın
2. KnightOnline\deps\QtDirect3D\source\QDirect3D9Widget\ klasörüne gidin
3. QDirect3D9Widget.h dosyası görünmeli
4. QDirect3D9Widget.cpp dosyası görünmeli
```

---

## 🚨 Hala Boş Görünüyorsa

### Sorun 1: Git Kurulu Değil
```
1. https://git-scm.com/downloads/win adresinden Git indirin
2. Kurun
3. Terminal'i yeniden açın
4. Tekrar deneyin
```

### Sorun 2: İnternet Bağlantısı
```
1. İnternet bağlantınızı kontrol edin
2. GitHub'a erişebildiğinizi kontrol edin
3. Firewall ayarlarını kontrol edin
```

### Sorun 3: Klasör İzinleri
```
1. deps klasörüne sağ tıklayın
2. Properties > Security
3. Yazma izniniz olduğundan emin olun
```

---

## 💡 Hızlı Test

**Terminal'de şunu çalıştırın:**
```cmd
cd C:\Projects\KnightOnline\deps
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D
```

**Başarılı olursa:**
```
Cloning into 'QtDirect3D'...
Submodule 'thirdparty/imgui' ...
remote: ...
```

**Sonra kontrol:**
```cmd
dir QtDirect3D\source\QDirect3D9Widget
```

---

## ✅ Başarı Kontrolü

QtDirect3D başarıyla indirildiyse:
```
[✅] QtDirect3D klasörü var
[✅] source\QDirect3D9Widget\ klasörü var
[✅] QDirect3D9Widget.h dosyası var
[✅] QDirect3D9Widget.cpp dosyası var
```

**Artık devam edebilirsiniz!** 🎉

---

## 📋 Sonraki Adım

QtDirect3D indirildikten sonra:
1. ✅ Dosyaların varlığını kontrol et
2. ⏭️ Visual Studio'da include path'i ayarla
3. ⏭️ Dosyaları projeye ekle
4. ⏭️ Build et

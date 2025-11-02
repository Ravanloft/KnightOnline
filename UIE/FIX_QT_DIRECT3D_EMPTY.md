# QtDirect3D Klasörü Boşsa - Çözüm

## ❌ Sorun
`deps/QtDirect3D` klasörü boş görünüyor.

## ✅ Çözüm

### Yöntem 1: Git ile Klonlama (ÖNERİLEN)

**Terminal/CMD'de:**
```bash
# 1. KnightOnline klasörüne gidin
cd C:\Projects\KnightOnline

# 2. deps klasörüne gidin
cd deps

# 3. QtDirect3D'yi klonlayın
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D

# 4. Kontrol edin
cd QtDirect3D
dir
```

**Dosyalar görünmeli:**
```
QtDirect3D/
├── source/
│   └── QDirect3D9Widget/
│       ├── QDirect3D9Widget.h
│       └── QDirect3D9Widget.cpp
└── ...
```

### Yöntem 2: GitHub Desktop ile

```
1. GitHub Desktop'u açın
2. File > Clone Repository
3. URL: https://github.com/giladreich/QtDirect3D.git
4. Local path: C:\Projects\KnightOnline\deps\QtDirect3D
5. Clone
```

### Yöntem 3: ZIP İndirme

```
1. https://github.com/giladreich/QtDirect3D adresine gidin
2. Code > Download ZIP
3. ZIP'i C:\Projects\KnightOnline\deps\ klasörüne çıkarın
4. Klasör adını QtDirect3D olarak değiştirin
```

---

## 🔍 Kontrol

Klonladıktan sonra şu dosyalar olmalı:

```
deps/QtDirect3D/
├── source/
│   └── QDirect3D9Widget/
│       ├── QDirect3D9Widget.h      ← BUNU ARIYORUZ! ✅
│       └── QDirect3D9Widget.cpp    ← BUNU ARIYORUZ! ✅
└── examples/
    └── Direct3D9Widget/
        └── ...
```

**Kontrol komutu:**
```bash
# File Explorer'da:
deps\QtDirect3D\source\QDirect3D9Widget\ klasörüne gidin
QDirect3D9Widget.h dosyası var mı kontrol edin
```

---

## ⚠️ Önemli Not

**--recursive** parametresi önemli!
Submodule'ları da indirmek için gereklidir.

**Yanlış:**
```bash
git clone https://github.com/giladreich/QtDirect3D.git QtDirect3D
```

**Doğru:**
```bash
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D
```

---

## 🚨 Hala Boş Görünüyorsa

### Sorun 1: .gitignore Dosyası
```
Bazı dosyalar .gitignore'da olabilir
File Explorer'da "Hidden items" göster'i açın
```

### Sorun 2: Klonlama Hatası
```
1. deps/QtDirect3D klasörünü silin
2. Tekrar klonlayın
3. Hata mesajlarını kontrol edin
```

### Sorun 3: Dosyalar Başka Yerde
```
1. File Explorer'da arama yapın:
   "QDirect3D9Widget.h" ara
2. Dosyanın nerede olduğunu bulun
```

---

## ✅ Kontrol Listesi

```
[ ] Git kurulu mu? (git --version)
[ ] deps klasörü var mı?
[ ] QtDirect3D klasörü silindi mi? (eğer boşsa)
[ ] --recursive ile klonlandı mı?
[ ] source/QDirect3D9Widget/ klasörü var mı?
[ ] QDirect3D9Widget.h dosyası var mı?
[ ] QDirect3D9Widget.cpp dosyası var mı?
```

---

## 📝 Adım Adım (Terminal)

```bash
# 1. Proje klasörüne git
cd C:\Projects\KnightOnline

# 2. deps klasörüne git
cd deps

# 3. Eğer QtDirect3D varsa ve boşsa, sil
rmdir /s QtDirect3D
# VEYA File Explorer'dan sil

# 4. Klonla
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D

# 5. Kontrol et
cd QtDirect3D
dir source\QDirect3D9Widget
```

**Sonuç:**
```
QDirect3D9Widget.h
QDirect3D9Widget.cpp
ImGui/ (klasör)
```

---

## 🎯 Sonraki Adım

QtDirect3D klonlandıktan sonra:
1. Dosyaların varlığını kontrol et
2. Visual Studio'da include path'i ayarla
3. Build et

---

## 💡 Hızlı Komut

**Tek seferde:**
```bash
cd C:\Projects\KnightOnline\deps
git clone --recursive https://github.com/giladreich/QtDirect3D.git QtDirect3D
```

**Kontrol:**
```bash
cd QtDirect3D\source\QDirect3D9Widget
dir
```

2 dosya görünmeli: `.h` ve `.cpp` ✅

# Başlangıç Rehberi - Hızlı Başvuru

## 🚀 İlk 5 Adım

### 1️⃣ Projeyi Klonla
```bash
git clone https://github.com/Open-KO/KnightOnline.git
cd KnightOnline
```

### 2️⃣ Visual Studio'da Aç
```
File > Open > Project/Solution
→ Tools.sln seç
```

### 3️⃣ Qt Kurulumu
```
Qt 5.12+ indir ve kur
Qt VS Tools extension yükle
```

### 4️⃣ Proje Ayarları
```
Project Properties > Preprocessor
→ USE_QT_DIRECT3D ekle
```

### 5️⃣ Build Et
```
Build > Build Solution (F7)
```

---

## 📂 Hangi Dosyayı Açmalısınız?

### ✅ UIE Editor Geliştirmek İçin:
**`Tools.sln`** ← BUNU AÇIN! ⭐

### ❌ Diğer Seçenekler:
- `All.sln` - Tüm projeler (yavaş)
- `Client.sln` - Sadece client (UIE yok)
- `Server.sln` - Sadece server (UIE yok)

---

## 📍 Dosya Konumları

Klonladıktan sonra:
```
KnightOnline/
└── Tools.sln          ← BUNU AÇ ⭐
```

UIE editörü:
```
KnightOnline/
└── UIE/
    └── ...            ← Editör dosyaları burada
```

---

## ⚡ Hızlı Komut

```bash
# Terminal'de:
cd C:\Projects
git clone https://github.com/Open-KO/KnightOnline.git
cd KnightOnline
start Tools.sln
```

VEYA

```bash
# File Explorer'da:
KnightOnline klasörüne git
Tools.sln'e çift tıkla
```

---

## ✅ Kontrol

Tools.sln açıldığında:
- Solution Explorer'da **UIE** projesi görünmeli
- UIE klasörü altında dosyalar görünmeli

**Tamam! Artık geliştirmeye başlayabilirsiniz!** 🎉

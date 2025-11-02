# Proje Kurulum Rehberi - Adım Adım

## 📥 ADIM 1: Projeyi Klonlama (Git)

### Seçenek 1: GitHub'dan Klonlama (Önerilen)

```bash
# 1. Terminal/Command Prompt'u açın

# 2. Çalışmak istediğiniz klasöre gidin
cd C:\Projects
# VEYA istediğiniz başka bir klasör

# 3. Projeyi klonlayın
git clone https://github.com/Open-KO/KnightOnline.git

# 4. Proje klasörüne girin
cd KnightOnline
```

### Seçenek 2: GitHub Desktop ile

```
1. GitHub Desktop uygulamasını açın
2. File > Clone Repository
3. URL sekmesine tıklayın
4. https://github.com/Open-KO/KnightOnline.git yapıştırın
5. Local path seçin (örnek: C:\Projects\KnightOnline)
6. Clone butonuna tıklayın
```

### Seçenek 3: ZIP İndirme

```
1. https://github.com/Open-KO/KnightOnline adresine gidin
2. Code > Download ZIP
3. ZIP'i istediğiniz yere çıkarın
```

---

## 📁 ADIM 2: Proje Klasör Yapısını Anlama

Klonladıktan sonra şu klasör yapısına sahip olacaksınız:

```
KnightOnline/
├── Client/              # Oyun client'ı
├── Server/              # Oyun sunucusu
├── UIE/                 # UI Editor (geliştireceğimiz)
├── deps/                # Bağımlılıklar
├── shared/              # Paylaşılan kod
├── Client.sln          # Client solution dosyası
├── Server.sln          # Server solution dosyası
├── Tools.sln           # Tools solution dosyası
├── All.sln             # Tüm projeler
└── ...
```

---

## 🔧 ADIM 3: Hangi Solution Dosyasını Açmalısınız?

### Seçenek A: Sadece UI Editor Geliştirmek İçin ⭐ (ÖNERİLEN)

**Açılacak Dosya:** `Tools.sln`

**Neden?**
- UIE editörü Tools solution'ında
- Daha hızlı açılır
- Sadece ihtiyacınız olan projeler yüklenir

**Adımlar:**
```
1. Visual Studio'yu açın
2. File > Open > Project/Solution
3. KnightOnline klasörüne gidin
4. Tools.sln dosyasını seçin
5. Open'a tıklayın
```

### Seçenek B: Tüm Projeleri Geliştirmek İçin

**Açılacak Dosya:** `All.sln`

**Neden?**
- Tüm projeleri içerir
- Client, Server, Tools hepsi bir arada
- Daha uzun sürer açılması

### Seçenek C: Sadece Client Geliştirmek İçin

**Açılacak Dosya:** `Client.sln`

---

## 🎯 ADIM 4: Visual Studio'da Projeyi Açma (Detaylı)

### 4.1 Visual Studio'yu Başlatma

```
1. Visual Studio 2019 veya 2022'yi açın
2. "Open a project or solution" seçin
```

### 4.2 Solution Dosyasını Seçme

**UI Editor için (ÖNERİLEN):**
```
1. File > Open > Project/Solution
2. KnightOnline klasörüne gidin
3. Tools.sln dosyasını seçin
4. Open'a tıklayın
```

**VEYA**

```
1. File Explorer'da KnightOnline klasörüne gidin
2. Tools.sln dosyasına çift tıklayın
3. Visual Studio otomatik açılır
```

### 4.3 Solution Explorer'da Projeleri Kontrol Etme

Solution açıldıktan sonra şunları görmelisiniz:

```
Solution 'Tools' (X projects)
├── N3CE
├── N3ME
├── N3FXE
├── N3Viewer
├── N3TexViewer
├── SkyViewer
├── UIE              ← BURASI! ✨
├── ItemEditor
├── TblEditor
└── ...
```

**Önemli:** `UIE` projesi listede görünmeli!

---

## 🔍 ADIM 5: UIE Projesini Bulma ve Kontrol Etme

### 5.1 Solution Explorer'da Kontrol

```
1. Solution Explorer penceresini açın (View > Solution Explorer)
2. Tools solution'ını genişletin
3. UIE projesini bulun
4. Sağ tıklayıp "Set as StartUp Project" seçin (isteğe bağlı)
```

### 5.2 Proje Dosyalarını Kontrol

```
1. Solution Explorer'da UIE projesini genişletin
2. Şu dosyaları görmelisiniz:
   ├── UIE.h/.cpp
   ├── MainFrm.h/.cpp
   ├── UIEView.h/.cpp
   ├── PropertyView.h/.cpp
   └── ...
```

---

## ✅ ADIM 6: İlk Build (Derleme)

### 6.1 Projeyi Derleme

```
1. Solution Explorer'da UIE projesine sağ tıklayın
2. Build'i seçin
   VEYA
3. Build > Build Solution (F7)
```

### 6.2 İlk Build Sonuçları

**Başarılı olursa:**
```
========== Build: X succeeded, 0 failed ==========
```

**Hata alırsanız:**
- Bağımlılıklar eksik olabilir
- Include path'leri yanlış olabilir
- Şimdilik normal, sonraki adımlarda düzelteceğiz

---

## 📋 ADIM 7: Qt Projesini Eklemek İçin Hazırlık

### 7.1 Yeni Qt Projesi Ekleme (İleride)

UI Editor'ü Qt'ye çevirmek için:

```
1. Solution Explorer'da Tools solution'ına sağ tıklayın
2. Add > New Project
3. Qt Widgets Application seçin
4. Proje adı: UIEditorModern
5. Create
```

**ANCAK ŞİMDİLİK:** Önce mevcut UIE projesini anlayalım.

---

## 🎯 Hangi Projeyi Açmalısınız? (Özet)

| Ne Yapmak İstiyorsunuz? | Açılacak Solution |
|------------------------|-------------------|
| **UI Editor geliştirmek** | `Tools.sln` ⭐ |
| Tüm projeler | `All.sln` |
| Sadece Client | `Client.sln` |
| Sadece Server | `Server.sln` |

**ÖNERİLEN:** `Tools.sln` ile başlayın!

---

## 📍 Dosya Yolları Örneği

Eğer projeyi `C:\Projects\KnightOnline` konumuna klonladıysanız:

```
C:\Projects\KnightOnline\
├── Tools.sln          ← Bunu açın! ⭐
├── All.sln
├── Client.sln
├── UIE\               ← UIE editörü burada
│   ├── UIE.h
│   ├── UIE.cpp
│   └── ...
└── ...
```

---

## ✅ Kontrol Listesi

### Klonlama
- [ ] Git kurulu mu? (git --version)
- [ ] Proje klonlandı mı?
- [ ] KnightOnline klasörü var mı?

### Visual Studio
- [ ] Visual Studio açıldı mı?
- [ ] Tools.sln açıldı mı?
- [ ] Solution Explorer'da UIE projesi görünüyor mu?

### İlk Kontrol
- [ ] UIE projesi listede mi?
- [ ] UIE dosyaları görünüyor mu?
- [ ] Build denemesi yapıldı mı?

---

## 🚨 Sorun Giderme

### Sorun: "Solution bulunamadı"
```
Çözüm:
- Dosya yolunun doğru olduğundan emin olun
- .sln uzantılı dosyayı açtığınızdan emin olun
```

### Sorun: "Proje yüklenemedi"
```
Çözüm:
- Visual Studio'yu yönetici olarak çalıştırın
- Proje dosyalarının okuma/yazma izinleri olduğundan emin olun
```

### Sorun: "UIE projesi görünmüyor"
```
Çözüm:
- Solution Explorer'ı yenileyin (Refresh)
- Tools.sln'i kapatıp tekrar açın
- UIE.vcxproj dosyasının mevcut olduğunu kontrol edin
```

---

## 📝 Hızlı Başlangıç Komutları

### Terminal/CMD ile:
```bash
# 1. Proje klasörüne git
cd C:\Projects

# 2. Klonla
git clone https://github.com/Open-KO/KnightOnline.git

# 3. Klasöre gir
cd KnightOnline

# 4. Visual Studio ile aç
start Tools.sln
```

### PowerShell ile:
```powershell
cd C:\Projects
git clone https://github.com/Open-KO/KnightOnline.git
cd KnightOnline
.\Tools.sln
```

---

## 🎉 Sonuç

**Açılacak Dosya:** `Tools.sln` ⭐

**Neden?**
- UIE editörü bu solution'da
- Geliştirme için yeterli
- Hızlı açılır

**Sonraki Adım:** Qt kurulumu ve proje yapılandırması!

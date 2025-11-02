# Modernize Edilmiş UIE Editor

## Genel Bakış

UIE editörü QtDirect3D ile modernize edilmiştir. Mevcut MFC tabanlı editörün tüm özelliklerini korur ve yeni modern özellikler ekler.

## Yeni Özellikler

### ✨ Modern UI
- Qt tabanlı modern arayüz
- Dock widget'lar (Hierarchy, Properties, Undo History)
- Modern toolbar'lar
- Keyboard shortcuts

### 🎨 Gelişmiş Görsel Düzenleme
- Real-time Direct3D preview
- Mouse ile element seçme
- Drag & drop taşıma
- Visual property editor

### 🔄 Undo/Redo Sistemi
- Tam undo/redo desteği
- Undo history görüntüleme
- Command pattern kullanımı

### 📋 Gelişmiş Özellikler
- Copy/Paste
- Multi-select (planlanan)
- Alignment tools (planlanan)
- Grid & Snap to grid

## Dosya Yapısı

```
UIE/
├── UIEditorModern.h/.cpp    # Modern Qt Editor (YENİ)
├── UIEditorModern.ui        # UI dosyası
├── UndoCommands.h/.cpp      # Undo/Redo komutları (YENİ)
├── PropertyEditor.h/.cpp    # Property Editor (QtUIEditor'dan)
├── D3DViewWidget.h/.cpp     # Direct3D View Widget (QtUIEditor'dan)
│
├── UIEView.h/.cpp           # Mevcut MFC Editor (eski)
├── MainFrm.h/.cpp           # Mevcut MFC Frame (eski)
├── PropertyView.h/.cpp      # Mevcut MFC Property View (eski)
└── ...
```

## Kullanım

### Derleme
```bash
# Qt kurulu olmalı
# USE_QT_DIRECT3D preprocessor tanımı gerekli
```

### Çalıştırma
```bash
UIEditorModern.exe
```

### Temel İşlemler
1. **File > Open**: UI dosyası aç
2. **Hierarchy**: Element seç
3. **Properties**: Düzenle
4. **Edit > Undo/Redo**: Geri alma/ileri alma
5. **File > Save**: Kaydet

## Mevcut vs Modern

| Özellik | Mevcut (MFC) | Modern (Qt) |
|---------|-------------|-------------|
| UI Framework | MFC | Qt |
| Rendering | Direct3D | QtDirect3D |
| Undo/Redo | ❌ | ✅ |
| Copy/Paste | ❌ | ✅ (planlanan) |
| Modern UI | ❌ | ✅ |
| Dock Widgets | ❌ | ✅ |
| Keyboard Shortcuts | Kısıtlı | Tam destek |

## Geçiş Stratejisi

1. **Paralel Geliştirme**: Mevcut editör çalışmaya devam ederken modern versiyon geliştirilir
2. **Özellik Eşleştirme**: Mevcut özellikler yeni editöre taşınır
3. **Yeni Özellikler**: Modern editöre yeni özellikler eklenir
4. **Test**: Her iki editör de test edilir
5. **Geçiş**: Yeterli özellik eklenince modern editör ana editör olur

## Geliştirme Durumu

- ✅ Temel yapı hazır
- ✅ QtDirect3D entegrasyonu
- ✅ File operations
- 🔄 Undo/Redo (devam ediyor)
- 📋 Property Editor (geliştirilecek)
- 📋 Visual editing (planlanan)

## Katkıda Bulunma

1. Özellik eklemek için `UIEditorModern.cpp` dosyasını düzenleyin
2. Undo command eklemek için `UndoCommands.h/.cpp` kullanın
3. Property editor özellikleri için `PropertyEditor.h/.cpp` kullanın

## Dokümantasyon

- `UIE_IMPROVEMENTS.md` - Geliştirme planı
- `DEVELOPMENT_ROADMAP.md` - Yol haritası
- `ENHANCED_PROPERTY_EDITOR.md` - Property editor planı

# UIE Editörü Geliştirme Planı

## Mevcut UIE Editörü Özellikleri

### Var Olan Özellikler
- ✅ MFC tabanlı UI Editor
- ✅ Hierarchy View (CTreeView)
- ✅ Property View (CPropertyList)
- ✅ Edit View (Direct3D rendering)
- ✅ Preview/Edit modları
- ✅ .uif dosyası yükleme/kaydetme
- ✅ UI element seçimi
- ✅ Rectangle düzenleme (Region, Move, Click)
- ✅ Grid görünümü
- ✅ Background color ayarlama

### Eksik/İyileştirilebilir Özellikler
- ❌ Modern UI framework (MFC eski)
- ❌ Undo/Redo sistemi
- ❌ Copy/Paste
- ❌ Multi-select
- ❌ Layer management
- ❌ Alignment tools
- ❌ Snap to grid
- ❌ Keyboard shortcuts
- ❌ Drag & drop ile texture değiştirme
- ❌ Real-time preview (şu an sadece edit mode var)

## Geliştirme Planı

### Faz 1: QtDirect3D Entegrasyonu ✅
- [x] QtDirect3D widget entegrasyonu
- [x] CQtDirect3DAdapter ile N3Eng bağlantısı
- [x] Real-time Direct3D rendering

### Faz 2: Modern Property Editor 🔄
- [ ] Gelişmiş property editor widget
- [ ] Kategorize edilmiş property'ler
- [ ] Color picker
- [ ] File picker (texture seçimi)
- [ ] Font selector
- [ ] Enum/combo box'lar

### Faz 3: Görsel Düzenleme İyileştirmeleri 📋
- [ ] Mouse ile element seçme (şu an var ama geliştirilebilir)
- [ ] Drag & drop ile taşıma
- [ ] Resize handles (köşelerden boyutlandırma)
- [ ] Multi-select (Ctrl+Click)
- [ ] Selection box
- [ ] Visual feedback (hover effects)

### Faz 4: Editör Özellikleri 📋
- [ ] Undo/Redo sistemi
- [ ] Copy/Paste/Cut
- [ ] Duplicate element
- [ ] Delete element
- [ ] Group/Ungroup
- [ ] Lock/Unlock element

### Faz 5: Alignment & Layout Tools 📋
- [ ] Align Left/Right/Center
- [ ] Align Top/Bottom/Middle
- [ ] Distribute Horizontally/Vertically
- [ ] Snap to grid
- [ ] Ruler/Guide lines
- [ ] Grid settings

### Faz 6: Advanced Features 📋
- [ ] Layer management
- [ ] Search/Find element
- [ ] Batch operations
- [ ] Import/Export (JSON/XML)
- [ ] Template system
- [ ] Keyboard shortcuts editor

## Uygulama Stratejisi

### Seçenek 1: Mevcut MFC Editörünü Geliştirme
**Avantajlar:**
- Mevcut kod tabanını kullanır
- Daha az yeniden yazma

**Dezavantajlar:**
- MFC eski teknoloji
- Modern özellikler eklemek zor
- Qt entegrasyonu zor

### Seçenek 2: Yeni Qt Editörü Oluşturma (Önerilen) ⭐
**Avantajlar:**
- Modern Qt framework
- Daha iyi UI/UX
- Kolay genişletilebilir
- Cross-platform potansiyeli

**Dezavantajlar:**
- Daha fazla geliştirme süresi
- Mevcut kodun yeniden yazılması

## Önerilen Yaklaşım

**Hibrit Yaklaşım:**
1. Mevcut UIE editörünü QtDirect3D ile modernize et
2. Yeni özellikleri aşamalı olarak ekle
3. MFC kodunu Qt'ye migrate et (isteğe bağlı)

## Öncelikli Geliştirmeler

1. **QtDirect3D Entegrasyonu** (Yapıldı ✅)
2. **Property Editor İyileştirmeleri**
3. **Undo/Redo Sistemi**
4. **Copy/Paste**
5. **Görsel Düzenleme İyileştirmeleri**

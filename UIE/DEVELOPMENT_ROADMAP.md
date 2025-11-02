# UIE Editörü Geliştirme Yol Haritası

## ✅ Tamamlanan Özellikler

- [x] QtDirect3D entegrasyonu
- [x] Temel UI Editor yapısı
- [x] File Open/Save
- [x] Hierarchy View
- [x] Property Editor (temel)
- [x] Undo/Redo sistemi (yapı hazır)

## 🔄 Devam Eden Geliştirmeler

### Faz 1: Temel Özellikler (1-2 Hafta)
- [ ] Undo/Redo implementasyonu
- [ ] Property Editor genişletme
- [ ] UI element ekleme (Image, String, Button)
- [ ] UI element silme
- [ ] Copy/Paste

### Faz 2: Görsel Düzenleme (2-3 Hafta)
- [ ] Mouse ile element seçme (geliştirilmiş)
- [ ] Drag & drop taşıma
- [ ] Resize handles
- [ ] Multi-select
- [ ] Selection box
- [ ] Grid rendering
- [ ] Snap to grid

### Faz 3: Gelişmiş Özellikler (3-4 Hafta)
- [ ] Texture picker (File dialog)
- [ ] Font selector
- [ ] Sound picker
- [ ] Z-order yönetimi
- [ ] Parent/Child ilişkileri
- [ ] Alignment tools
- [ ] Distribute tools

### Faz 4: Advanced Features (4+ Hafta)
- [ ] Layer management
- [ ] Template system
- [ ] Import/Export (JSON)
- [ ] Batch operations
- [ ] Search/Find
- [ ] Keyboard shortcuts
- [ ] Custom widgets

## Kullanım Senaryoları

### Senaryo 1: Yeni Inventory UI Oluşturma
1. File > New
2. UI > Insert Image (Background için)
3. UI > Insert Button (Close button için)
4. UI > Insert String (Title için)
5. Properties ile düzenle
6. File > Save

### Senaryo 2: Mevcut Inventory UI Düzenleme
1. File > Open > el_inventory_us.uif
2. Hierarchy'den element seç
3. Property Editor ile düzenle
4. Real-time preview
5. Undo/Redo ile test
6. Save

### Senaryo 3: Texture Değiştirme
1. Image element seç
2. Property Editor > Texture
3. File picker'dan yeni .dxt seç
4. Real-time görünüm
5. Save

## Test Planı

### Birim Testler
- [ ] Undo/Redo komutları
- [ ] Property Editor update
- [ ] UI loading/saving

### Entegrasyon Testleri
- [ ] QtDirect3D rendering
- [ ] Mouse interaction
- [ ] Keyboard shortcuts

### Kullanıcı Testleri
- [ ] UI Editor workflow
- [ ] Performance test
- [ ] Usability test

## Önemli Notlar

1. **Mevcut MFC Editörü**: Mevcut UIE editörü çalışmaya devam edecek, yeni Qt versiyonu paralel geliştirilecek

2. **Compatibility**: Yeni editör mevcut .uif dosyalarını okuyup yazabilmeli

3. **Performance**: Real-time preview performanslı olmalı

4. **Documentation**: Her özellik için kullanım dokümantasyonu

## Geliştirme Öncelikleri

1. ⭐⭐⭐ **Yüksek Öncelik**
   - Undo/Redo
   - Property Editor
   - Basic element operations

2. ⭐⭐ **Orta Öncelik**
   - Visual editing improvements
   - Copy/Paste
   - Alignment tools

3. ⭐ **Düşük Öncelik**
   - Advanced features
   - Import/Export
   - Templates

# QtUIEditor - GUI Tabanlı Görsel Düzenleme Özellikleri

## ✅ Evet, Tamamen GUI ile Düzenleme Yapıyoruz!

QtUIEditor, **tamamen görsel bir GUI editörü**dür. Kod yazmadan, mouse ve keyboard ile UI düzenleme yaparsınız.

## 🎨 GUI Özellikleri

### 1. **Mouse ile Element Seçme**
- ✅ Direct3D widget'ta UI element'lerine **mouse ile tıklayarak** seçim
- ✅ Seçili element'in etrafında **görsel seçim çerçevesi**
- ✅ Hierarchy tree'den de seçim yapabilme

### 2. **Drag & Drop ile Taşıma**
- ✅ Element'i **mouse ile sürükleyerek** taşıma
- ✅ **Real-time** pozisyon güncelleme
- ✅ Direct3D widget'ta **canlı önizleme**

### 3. **Property Editor (GUI Kontroller)**
- ✅ **SpinBox** ile pozisyon (X, Y) ayarlama
- ✅ **SpinBox** ile boyut (Width, Height) ayarlama
- ✅ **Color Picker** ile renk seçme
- ✅ **Textbox** ile ID değiştirme
- ✅ **Checkbox** ile Visible özelliği

### 4. **Hierarchy Tree**
- ✅ UI element'lerinin **tree görünümü**
- ✅ Double-click ile element seçme
- ✅ Expand/Collapse ile gezinme

### 5. **Real-time Preview**
- ✅ Değişiklikleri **anında görüntüleme**
- ✅ Direct3D ile **oyun engine'i ile aynı görünüm**

## 📋 Kullanım Senaryosu

### Senaryo: Inventory Slot Pozisyonunu Değiştirme

1. **UI Dosyasını Yükle**
   - File > Load UI > Elmorad Inventory
   - Veya File > Open ile `.uif` dosyası seç

2. **Element Seç**
   - Direct3D widget'ta **mouse ile tıklayarak** inventory slot'unu seç
   - Veya Hierarchy tree'den element'i seç

3. **Property Editor ile Düzenle**
   - **Position X** spinbox'ını kullanarak sağa/sola kaydır
   - **Position Y** spinbox'ını kullanarak yukarı/aşağı kaydır
   - Veya **mouse ile sürükleyerek** taşı

4. **Canlı Önizleme**
   - Değişiklikler **anında** Direct3D widget'ta görünür
   - Oyun engine'i ile **aynı görünüm**

5. **Kaydet**
   - File > Save ile kaydet
   - Düzenlenmiş UI dosyası `.uif` formatında kaydedilir

## 🖱️ Mouse İşlemleri

### Left Click
- Element seçimi
- Element seçildiğinde Property Editor otomatik güncellenir

### Left Drag
- Element taşıma
- Real-time pozisyon güncelleme

### Double Click
- Hierarchy tree'de element detaylarını açma

## ⌨️ Keyboard İşlemleri

### Delete Key
- Seçili element'i silme

### Arrow Keys
- Element'i 1 piksel taşıma (gelecek versiyonda)

## 🎯 GUI Kontrolleri

### Position Group
```
X: [━━━━━━━━━━━] 100
Y: [━━━━━━━━━━━] 200
```
- SpinBox ile pixel-perfect pozisyon ayarlama
- Değişiklik anında UI'ya yansır

### Size Group
```
Width:  [━━━━━━━━━━━] 50
Height: [━━━━━━━━━━━] 50
```
- SpinBox ile boyut ayarlama
- Real-time önizleme

### Appearance Group
```
ID:      [inventory_slot_01]
Visible: [✓] Visible
Color:   [Choose Color] [███]
```
- Textbox ile ID düzenleme
- Checkbox ile görünürlük
- Color picker ile renk seçme

## 📊 Editor Layout

```
┌─────────────┬──────────────────────┬─────────────┐
│ Hierarchy   │   Direct3D Widget    │  Property   │
│ Tree        │   (Görsel Düzenleme) │  Editor     │
│             │                      │             │
│ [Root]      │  ┌──────────────┐   │ Position    │
│  ├─ Slot1   │  │              │   │ X: [___]    │
│  ├─ Slot2   │  │  UI Preview  │   │ Y: [___]    │
│  └─ Slot3   │  │  (Clickable) │   │             │
│             │  │              │   │ Size        │
│             │  └──────────────┘   │ W: [___]    │
│             │                      │ H: [___]    │
└─────────────┴──────────────────────┴─────────────┘
```

## 🔄 Workflow

1. **Yükle** → UI dosyasını aç
2. **Seç** → Mouse ile element seç
3. **Düzenle** → Property Editor veya Drag & Drop
4. **Görüntüle** → Real-time preview
5. **Kaydet** → Değişiklikleri kaydet

## ✨ Gelecek Özellikler

- [ ] Element resize handles (köşelerden boyutlandırma)
- [ ] Multi-select (Ctrl+Click ile çoklu seçim)
- [ ] Copy/Paste (Element kopyalama)
- [ ] Undo/Redo (Geri alma)
- [ ] Alignment tools (Hizalama araçları)
- [ ] Snap to grid (Izgara hizalama)
- [ ] Layer management (Katman yönetimi)

## 🎉 Sonuç

**Evet, tamamen GUI ile düzenleme yapıyoruz!**

- ❌ Kod yazmanıza gerek yok
- ✅ Mouse ile tıklayıp sürükleyerek düzenleyin
- ✅ Property Editor ile değerleri ayarlayın
- ✅ Real-time önizleme ile sonucu görün
- ✅ Kaydedin ve oyunda kullanın!

Bu bir **WYSIWYG (What You See Is What You Get)** editörüdür!

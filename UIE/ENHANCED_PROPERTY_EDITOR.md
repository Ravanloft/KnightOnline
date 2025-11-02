# Gelişmiş Property Editor

## Mevcut Property Editor Özellikleri

### Temel Özellikler ✅
- Position (X, Y) - SpinBox
- Size (Width, Height) - SpinBox
- Color - Color Picker
- ID - Textbox
- Visible - Checkbox

### Geliştirilmesi Gereken Özellikler

#### 1. Texture/Image Properties
```cpp
- Texture Path: File picker (DXT texture seçimi)
- Texture Coordinates: UV mapping editor
- Texture Filter: ComboBox (Linear, Point, vb.)
- Texture Format: Read-only label
```

#### 2. String Properties
```cpp
- Text: Multi-line textbox
- Font: Font selector
- Font Size: SpinBox
- Font Style: Checkboxes (Bold, Italic, Underline)
- Text Align: ComboBox (Left, Center, Right)
- Color: Color picker (mevcut)
```

#### 3. Button Properties
```cpp
- Normal Image: File picker
- Pressed Image: File picker
- Disabled Image: File picker
- Hover Image: File picker
- Click Sound: File picker (.wav)
```

#### 4. Area Properties
```cpp
- Clickable: Checkbox
- Hover Effect: Checkbox
- Tooltip: Textbox
```

#### 5. Advanced Properties
```cpp
- Z-Order: SpinBox
- Alpha: Slider (0-255)
- Scale X/Y: SpinBox
- Rotation: SpinBox (degrees)
- Parent: ComboBox (UI hierarchy)
```

## Property Editor Widget Yapısı

```cpp
PropertyEditor
├── ScrollArea
    ├── PropertyGroup (Position)
    │   ├── X: [SpinBox]
    │   └── Y: [SpinBox]
    ├── PropertyGroup (Size)
    │   ├── Width: [SpinBox]
    │   └── Height: [SpinBox]
    ├── PropertyGroup (Appearance)
    │   ├── ID: [LineEdit]
    │   ├── Visible: [CheckBox]
    │   └── Color: [ColorPicker]
    ├── PropertyGroup (Texture) - UIImage için
    │   ├── Texture: [FilePicker]
    │   └── ...
    ├── PropertyGroup (Text) - UIString için
    │   ├── Text: [TextEdit]
    │   └── ...
    └── PropertyGroup (Button) - UIButton için
        ├── Normal: [FilePicker]
        └── ...
```

## Kullanım Örneği

### Image Element Düzenleme
1. Hierarchy'den image element'i seç
2. Property Editor'da Texture bölümü görünür
3. "Texture" file picker'dan .dxt dosyası seç
4. UV coordinates ile texture mapping ayarla
5. Değişiklikler real-time görünür

### Button Element Düzenleme
1. Button element'i seç
2. Button Properties görünür
3. Normal/Pressed/Disabled image'leri seç
4. Click sound dosyası seç
5. Button hazır!

## Implementasyon Notları

- Property Editor dinamik olmalı (element tipine göre değişmeli)
- Her UI element tipi için özel property group'ları
- File picker'lar asset path'lerini kullanmalı
- Real-time update ile değişiklikler anında görünmeli

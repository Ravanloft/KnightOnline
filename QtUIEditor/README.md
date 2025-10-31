# QtUIEditor - Knight Online UI Editor

Knight Online'ın UI dosyalarını (.uif) düzenlemek için Qt + Direct3D9 tabanlı modern bir editör.

## Özellikler

- ✅ **UI Dosyası Yükleme**: `.uif` dosyalarını yükleme
- ✅ **Real-time Preview**: Direct3D9 ile canlı önizleme
- ✅ **Hierarchy Görüntüleme**: UI element hierarchy tree
- ✅ **Property Editing**: UI element özelliklerini düzenleme
- ✅ **UI Dosyası Kaydetme**: Düzenlenmiş UI'ları kaydetme

## Gereksinimler

- Qt 5.12+
- Qt Modules: Core, Gui, Widgets
- DirectX 9 SDK
- Knight Online N3Base kütüphanesi
- QtDirect3D projesi
- Knight Online client assets

## Kurulum

1. Qt'yi kurun
2. Asset'leri klonlayın:
   ```bash
   git clone https://github.com/Open-KO/ko-client-assets.git assets
   ```
3. Projeyi derleyin

## Kullanım

1. **UI Dosyası Yükle**: File > Open veya File > Load UI menüsünden
2. **Element Seç**: Hierarchy tree'den bir element seçin
3. **Özellik Düzenle**: Property panel'den özellikleri düzenleyin
4. **Kaydet**: File > Save ile kaydedin

## UI Dosyaları

UI dosyaları `assets/UI_US/` klasöründe:
- `el_inventory_us.uif` - Elmorad Inventory
- `ka_inventory_us.uif` - Karus Inventory
- `co_tradeinventory_us.uif` - Trade Inventory
- ... (174 UI dosyası)

## Proje Yapısı

```
QtUIEditor/
├── main.cpp              # Entry point
├── MainWindow.h/.cpp     # Ana pencere
├── MainWindow.ui         # UI dosyası
└── README.md            # Bu dosya
```

## Notlar

Bu editör, Knight Online projesine entegre edilmiş bir Qt uygulamasıdır.
QtDirect3D sayesinde Direct3D9 rendering desteği sağlar.

# QtDirect3D ile Knight Online UI Asset'lerini Kullanma

## Asset Deposu Yapısı

Knight Online client asset'leri şu GitHub deposunda bulunuyor:
**https://github.com/Open-KO/ko-client-assets**

### Önemli Klasörler

```
ko-client-assets/
├── UI_US/           # UI Dosyaları (.uif formatında)
│   ├── el_inventory_us.uif      # Elmorad Inventory UI
│   ├── ka_inventory_us.uif      # Karus Inventory UI
│   ├── co_tradeinventory_us.uif # Trade Inventory UI
│   └── ... (174 .uif dosyası)
│
├── UI/              # UI Texture'ları (.dxt formatında)
│   ├── itemicon_*.dxt    # Item icon texture'ları
│   ├── skillicon_*.dxt   # Skill icon texture'ları
│   └── ... (2114 .dxt dosyası)
│
├── Item/            # Item 3D modelleri
│   ├── *.n3cpart
│   ├── *.n3cskins
│   └── *.dxt (item texture'ları)
│
└── Data/            # UI tanımlama tabloları
    ├── UIs_us.tbl        # UI dosya listesi
    └── UI_Help_us.tbl    # UI help metinleri
```

## UI Dosya Formatı

### .UIF Dosyaları
- Knight Online'ın özel UI dosya formatı
- Binary format (N3Base file format)
- `CN3UIWndBase::LoadFromFile()` ile yüklenir
- Inventory, Trade, Character Select vb. UI'ları içerir

### .DXT Dosyaları
- DirectX Texture formatı
- UI icon'ları, background'lar, button texture'ları
- `CN3Texture::LoadFromFile()` ile yüklenir
- DXT1, DXT3, DXT5 formatlarında

## QtDirect3D ile UI Editor Oluşturma

### 1. Asset Depoyu Klonlama

```bash
# Asset'leri projenize ekleyin
git clone https://github.com/Open-KO/ko-client-assets.git assets
# veya submodule olarak:
git submodule add https://github.com/Open-KO/ko-client-assets.git assets
```

### 2. Qt UI Editor Sınıfı

```cpp
class QtUIEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtUIEditor(QWidget* parent = nullptr);
    
private slots:
    void onDeviceInitialized(bool success);
    void onRender();
    void loadInventoryUI(const QString& nation); // "el" veya "ka"
    void editUIElement(CN3UIBase* pElement);
    void saveUI();

private:
    QDirect3D9Widget* m_pD3DWidget;
    CQtDirect3DAdapter* m_pAdapter;
    CN3Eng* m_pN3Eng;
    
    // Yüklenen UI
    CN3UIWndBase* m_pInventoryUI;
    
    // Asset yolu
    QString m_sAssetPath; // "assets/UI_US/"
    QString m_sTexturePath; // "assets/UI/"
    
    void initializeN3Base();
    void renderUI();
};
```

### 3. Inventory UI Yükleme

```cpp
void QtUIEditor::loadInventoryUI(const QString& nation)
{
    QString fileName;
    if (nation == "el")
        fileName = m_sAssetPath + "el_inventory_us.uif";
    else if (nation == "ka")
        fileName = m_sAssetPath + "ka_inventory_us.uif";
    
    // UI dosyasını yükle
    m_pInventoryUI = new CN3UIWndBase();
    
    // Knight Online'ın UI yükleme sistemi
    if (m_pInventoryUI->LoadFromFile(fileName.toStdString()))
    {
        qDebug() << "Inventory UI yüklendi:" << fileName;
        
        // UI texture'larını yükle
        loadUITextures();
        
        // UI'yı görüntüle
        renderUI();
    }
    else
    {
        qWarning() << "UI dosyası yüklenemedi:" << fileName;
    }
}
```

### 4. UI Texture Yükleme

```cpp
void QtUIEditor::loadUITextures()
{
    // UI texture'ları UI/ klasöründe
    QString textureDir = m_sTexturePath;
    
    // Örnek: Item icon texture'larını yükle
    // UI/itemicon_*.dxt dosyaları
    
    // CN3Texture ile yükleme
    CN3Texture* pTex = new CN3Texture();
    pTex->LoadFromFile((textureDir + "itemicon_1_3031_00_0.dxt").toStdString());
    
    // UI element'ine texture atama
    if (m_pInventoryUI)
    {
        // UI element'lerini bul ve texture atama
        // Bu örnek genel bir yaklaşım
    }
}
```

### 5. UI Element Düzenleme

```cpp
void QtUIEditor::editUIElement(CN3UIBase* pElement)
{
    if (!pElement) return;
    
    // UI element özelliklerini düzenle
    // Örnek: Pozisyon değiştirme
    RECT rc = pElement->GetRegion();
    rc.left += 10; // 10 piksel sağa kaydır
    pElement->SetRegion(rc);
    
    // Örnek: Renk değiştirme
    if (pElement->UIType() == UI_TYPE_STRING)
    {
        CN3UIString* pStr = (CN3UIString*)pElement;
        pStr->SetColor(D3DCOLOR_XRGB(255, 0, 0)); // Kırmızı yap
    }
    
    // Değişiklikleri render et
    renderUI();
}
```

### 6. UI Dosyasını Kaydetme

```cpp
void QtUIEditor::saveUI()
{
    if (!m_pInventoryUI) return;
    
    QString savePath = QFileDialog::getSaveFileName(
        this,
        "UI Dosyasını Kaydet",
        m_sAssetPath,
        "UI Files (*.uif)"
    );
    
    if (!savePath.isEmpty())
    {
        // UI'yı kaydet
        m_pInventoryUI->SaveToFile(savePath.toStdString());
        qDebug() << "UI kaydedildi:" << savePath;
    }
}
```

## UI Element Türleri

Knight Online UI sisteminde farklı element türleri var:

```cpp
enum eUI_TYPE {
    UI_TYPE_BASE = 0,
    UI_TYPE_STRING,      // Text
    UI_TYPE_IMAGE,       // Image/Texture
    UI_TYPE_BUTTON,      // Button
    UI_TYPE_STATIC,      // Static element
    UI_TYPE_EDIT,        // Edit box
    UI_TYPE_PROGRESS,    // Progress bar
    UI_TYPE_TRACKBAR,    // Track bar
    UI_TYPE_SCROLLBAR,   // Scroll bar
    UI_TYPE_LIST,        // List
    UI_TYPE_AREA,        // Clickable area
    // ...
};
```

## Inventory UI Örneği

Inventory UI'da şu elementler bulunur:

```cpp
// Inventory slot'ları
__IconItemSkill* m_pMySlot[ITEM_SLOT_COUNT];  // Equipment slot'ları
__IconItemSkill* m_pMyInvWnd[MAX_ITEM_INVENTORY]; // Inventory slot'ları

// UI element'leri
CN3UIImage* m_pBkgndImage;      // Background image
CN3UIString* m_pText_Weight;    // Weight text
CN3UIButton* m_pBtn_Close;      // Close button
CN3UIEdit* m_pEdit_Destroy;     // Destroy item edit
```

## Örnek Kullanım Senaryosu

### Senaryo 1: Inventory UI Pozisyonunu Değiştirme

```cpp
// 1. Inventory UI'yı yükle
loadInventoryUI("el"); // Elmorad

// 2. UI pozisyonunu bul
RECT rc = m_pInventoryUI->GetRegion();

// 3. Pozisyonu değiştir
rc.left = 100;
rc.top = 100;
m_pInventoryUI->SetRegion(rc);

// 4. Kaydet
saveUI();
```

### Senaryo 2: Inventory Slot Boyutunu Değiştirme

```cpp
// Inventory slot'larını bul
CN3UIBase* pInvArea = m_pInventoryUI->GetChildByID("InventoryArea");

if (pInvArea)
{
    // Slot boyutlarını değiştir
    RECT rcSlot = pInvArea->GetRegion();
    rcSlot.right = rcSlot.left + 40;  // 40x40 yap
    rcSlot.bottom = rcSlot.top + 40;
    pInvArea->SetRegion(rcSlot);
}
```

### Senaryo 3: UI Texture'ını Değiştirme

```cpp
// Background texture'ını değiştir
CN3UIImage* pBkgnd = (CN3UIImage*)m_pInventoryUI->GetChildByID("Background");

if (pBkgnd)
{
    // Yeni texture yükle
    CN3Texture* pNewTex = new CN3Texture();
    pNewTex->LoadFromFile("custom_inventory_bg.dxt");
    
    // Texture'ı değiştir
    pBkgnd->SetTex(pNewTex);
}
```

## Qt Widget Entegrasyonu

QtDirect3D widget ile UI görüntüleme:

```cpp
void QtUIEditor::onRender()
{
    if (!m_pInventoryUI || !m_pAdapter) return;
    
    // Direct3D device'ı hazırla
    IDirect3DDevice9* pDevice = m_pAdapter->GetDirect3DDevice();
    if (!pDevice) return;
    
    // Clear
    pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
    
    pDevice->BeginScene();
    
    // UI'yı render et
    if (m_pInventoryUI->IsVisible())
    {
        m_pInventoryUI->Render();
    }
    
    pDevice->EndScene();
    // Present Qt widget tarafından yapılıyor
}
```

## Asset Yönetimi

### Asset Yolu Yapılandırması

```cpp
// Proje root'unda asset'leri sakla
QString QtUIEditor::getAssetPath()
{
    return QApplication::applicationDirPath() + "/assets/";
}

QString QtUIEditor::getUIPath()
{
    return getAssetPath() + "UI_US/";
}

QString QtUIEditor::getTexturePath()
{
    return getAssetPath() + "UI/";
}
```

## Önemli Notlar

1. **UI Dosya Formatı**: `.uif` dosyaları binary format'ta. Knight Online'ın N3Base sistemi ile okunup yazılabilir.

2. **Texture Formatı**: `.dxt` dosyaları DirectX Texture formatı. Knight Online'ın texture loader'ı ile yüklenir.

3. **Path Management**: Asset yolları Knight Online'ın path sistemine uygun olmalı. `CN3Base::PathSet()` kullanılabilir.

4. **UI Element ID'leri**: UI element'lerine ID atanmış olmalı. `SetID()` ve `GetChildByID()` kullanılır.

5. **Real-time Preview**: QtDirect3D sayesinde UI değişikliklerini canlı olarak görebilirsiniz.

## Sonuç

QtDirect3D ile:
- ✅ Inventory UI'ları yükleyip görüntüleyebilirsiniz
- ✅ UI element'lerini düzenleyebilirsiniz
- ✅ Texture'ları değiştirebilirsiniz
- ✅ UI dosyalarını kaydedebilirsiniz
- ✅ Real-time preview yapabilirsiniz

Bu sayede Knight Online'ın inventory ve diğer UI görsellerini modern bir Qt editörü ile düzenleyebilirsiniz!

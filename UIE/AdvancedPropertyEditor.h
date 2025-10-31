// AdvancedPropertyEditor.h: Gelişmiş Property Editor
// UI element tipine göre özel property'ler gösterir

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFileDialog>

// Forward declarations
class CN3UIBase;
class CN3UIImage;
class CN3UIString;
class CN3UIButton;
class CN3UIEdit;
class CN3UIProgress;
class CN3UITrackBar;
class CN3UIScrollBar;
class CN3UIArea;

/**
 * @brief Gelişmiş Property Editor
 * 
 * UI element tipine göre özel property grupları gösterir:
 * - Base properties (tüm element'ler için)
 * - Image properties (UIImage için)
 * - String properties (UIString için)
 * - Button properties (UIButton için)
 * - vb.
 */
class AdvancedPropertyEditor : public QScrollArea
{
    Q_OBJECT

public:
    explicit AdvancedPropertyEditor(QWidget* parent = nullptr);
    ~AdvancedPropertyEditor();
    
    /**
     * @brief UI element'ini yükle
     */
    void setUIElement(CN3UIBase* pElement);
    
    /**
     * @brief Property editor'ı temizle
     */
    void clear();

signals:
    /**
     * @brief Property değiştiğinde emit edilir
     */
    void propertyChanged();

private slots:
    // Base properties
    void onIDChanged(const QString& text);
    void onPositionXChanged(int value);
    void onPositionYChanged(int value);
    void onWidthChanged(int value);
    void onHeightChanged(int value);
    void onVisibleToggled(bool checked);
    void onZOrderChanged(int value);
    
    // String properties
    void onTextChanged();
    void onFontSizeChanged(int value);
    void onTextAlignChanged(int index);
    void onStringColorChanged();
    void onBoldToggled(bool checked);
    void onItalicToggled(bool checked);
    
    // Image properties
    void onTexturePathChanged();
    void onTextureBrowse();
    void onTextureFilterChanged(int index);
    
    // Button properties
    void onNormalTextureChanged();
    void onPressedTextureChanged();
    void onDisabledTextureChanged();
    void onHoverTextureChanged();
    void onButtonSoundChanged();
    
    // Edit properties
    void onEditMaxLengthChanged(int value);
    void onEditPasswordToggled(bool checked);
    
private:
    void setupUI();
    void updateFromElement();
    
    void showBaseProperties(CN3UIBase* pElement);
    void showImageProperties(CN3UIImage* pImage);
    void showStringProperties(CN3UIString* pString);
    void showButtonProperties(CN3UIButton* pButton);
    void showEditProperties(CN3UIEdit* pEdit);
    void showProgressProperties(CN3UIProgress* pProgress);
    void showTrackBarProperties(CN3UITrackBar* pTrackBar);
    void showScrollBarProperties(CN3UIScrollBar* pScrollBar);
    void showAreaProperties(CN3UIArea* pArea);
    
    void hideAllGroups();
    QString getAssetTexturePath() const;
    
    CN3UIBase* m_pCurrentElement;
    bool m_bUpdating;
    
    // Layout
    QWidget* m_pContentWidget;
    QVBoxLayout* m_pMainLayout;
    
    // Base properties group (her zaman görünür)
    QGroupBox* m_pGroupBase;
    
    // Specific property groups (element tipine göre gösterilir)
    QGroupBox* m_pGroupImage;
    QGroupBox* m_pGroupString;
    QGroupBox* m_pGroupButton;
    QGroupBox* m_pGroupEdit;
    QGroupBox* m_pGroupProgress;
    QGroupBox* m_pGroupTrackBar;
    QGroupBox* m_pGroupScrollBar;
    QGroupBox* m_pGroupArea;
    
    // Base controls (tüm element'ler için)
    class QLineEdit* m_pEditID;
    class QSpinBox* m_pSpinPosX;
    class QSpinBox* m_pSpinPosY;
    class QSpinBox* m_pSpinWidth;
    class QSpinBox* m_pSpinHeight;
    class QCheckBox* m_pCheckVisible;
    class QSpinBox* m_pSpinZOrder;
    
    // String controls
    class QTextEdit* m_pTextEdit;
    class QSpinBox* m_pSpinFontSize;
    class QComboBox* m_pComboTextAlign;
    class QPushButton* m_pBtnStringColor;
    class QCheckBox* m_pCheckBold;
    class QCheckBox* m_pCheckItalic;
    
    // Image controls
    class QLineEdit* m_pEditTexturePath;
    class QPushButton* m_pBtnBrowseTexture;
    class QComboBox* m_pComboTextureFilter;
    
    // Button controls
    class QLineEdit* m_pEditNormalTex;
    class QPushButton* m_pBtnBrowseNormal;
    class QLineEdit* m_pEditPressedTex;
    class QPushButton* m_pBtnBrowsePressed;
    class QLineEdit* m_pEditDisabledTex;
    class QPushButton* m_pBtnBrowseDisabled;
    class QLineEdit* m_pEditHoverTex;
    class QPushButton* m_pBtnBrowseHover;
    class QLineEdit* m_pEditButtonSound;
    class QPushButton* m_pBtnBrowseSound;
};

#endif // USE_QT_DIRECT3D

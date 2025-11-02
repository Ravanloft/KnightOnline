// PropertyEditor.h: GUI tabanlı Property Editor Widget

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>

// Forward declaration
class CN3UIBase;

/**
 * @brief GUI tabanlı Property Editor
 * 
 * UI element özelliklerini görsel olarak düzenlemek için widget.
 * Textbox, spinbox, color picker gibi GUI element'leri ile çalışır.
 */
class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyEditor(QWidget* parent = nullptr);
    
    /**
     * @brief UI element'ini yükle ve property'leri göster
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
    void onPositionXChanged(int value);
    void onPositionYChanged(int value);
    void onWidthChanged(int value);
    void onHeightChanged(int value);
    void onColorChanged();
    void onIDChanged(const QString& text);
    void onVisibleToggled(bool checked);

private:
    void setupUI();
    void updateFromElement();
    
    CN3UIBase* m_pCurrentElement;
    
    // Position controls
    QSpinBox* m_pSpinPosX;
    QSpinBox* m_pSpinPosY;
    
    // Size controls
    QSpinBox* m_pSpinWidth;
    QSpinBox* m_pSpinHeight;
    
    // Color controls
    QPushButton* m_pBtnColor;
    QLabel* m_pLabelColor;
    
    // ID control
    QLineEdit* m_pEditID;
    
    // Visible control
    QPushButton* m_pBtnVisible;
    
    // Layout
    QVBoxLayout* m_pMainLayout;
    QFormLayout* m_pFormLayout;
    QGroupBox* m_pGroupPosition;
    QGroupBox* m_pGroupSize;
    QGroupBox* m_pGroupAppearance;
    
    bool m_bUpdating;
};

#endif // USE_QT_DIRECT3D

// PropertyEditor.cpp: GUI Property Editor Implementasyonu

#ifdef USE_QT_DIRECT3D

#include "PropertyEditor.h"

#include <N3Base/N3UIBase.h>
#include <N3Base/N3UIString.h>
#include <N3Base/N3UIImage.h>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QColorDialog>

PropertyEditor::PropertyEditor(QWidget* parent)
    : QWidget(parent)
    , m_pCurrentElement(nullptr)
    , m_pSpinPosX(nullptr)
    , m_pSpinPosY(nullptr)
    , m_pSpinWidth(nullptr)
    , m_pSpinHeight(nullptr)
    , m_pBtnColor(nullptr)
    , m_pLabelColor(nullptr)
    , m_pEditID(nullptr)
    , m_pBtnVisible(nullptr)
    , m_pMainLayout(nullptr)
    , m_pFormLayout(nullptr)
    , m_pGroupPosition(nullptr)
    , m_pGroupSize(nullptr)
    , m_pGroupAppearance(nullptr)
    , m_bUpdating(false)
{
    setupUI();
}

void PropertyEditor::setupUI()
{
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(5, 5, 5, 5);
    
    // Position Group
    m_pGroupPosition = new QGroupBox("Position", this);
    QFormLayout* pPosLayout = new QFormLayout(m_pGroupPosition);
    
    m_pSpinPosX = new QSpinBox(this);
    m_pSpinPosX->setRange(-10000, 10000);
    m_pSpinPosX->setValue(0);
    connect(m_pSpinPosX, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PropertyEditor::onPositionXChanged);
    pPosLayout->addRow("X:", m_pSpinPosX);
    
    m_pSpinPosY = new QSpinBox(this);
    m_pSpinPosY->setRange(-10000, 10000);
    m_pSpinPosY->setValue(0);
    connect(m_pSpinPosY, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PropertyEditor::onPositionYChanged);
    pPosLayout->addRow("Y:", m_pSpinPosY);
    
    // Size Group
    m_pGroupSize = new QGroupBox("Size", this);
    QFormLayout* pSizeLayout = new QFormLayout(m_pGroupSize);
    
    m_pSpinWidth = new QSpinBox(this);
    m_pSpinWidth->setRange(0, 10000);
    m_pSpinWidth->setValue(100);
    connect(m_pSpinWidth, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PropertyEditor::onWidthChanged);
    pSizeLayout->addRow("Width:", m_pSpinWidth);
    
    m_pSpinHeight = new QSpinBox(this);
    m_pSpinHeight->setRange(0, 10000);
    m_pSpinHeight->setValue(100);
    connect(m_pSpinHeight, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PropertyEditor::onHeightChanged);
    pSizeLayout->addRow("Height:", m_pSpinHeight);
    
    // Appearance Group
    m_pGroupAppearance = new QGroupBox("Appearance", this);
    QFormLayout* pAppLayout = new QFormLayout(m_pGroupAppearance);
    
    m_pEditID = new QLineEdit(this);
    connect(m_pEditID, &QLineEdit::textChanged,
            this, &PropertyEditor::onIDChanged);
    pAppLayout->addRow("ID:", m_pEditID);
    
    m_pBtnVisible = new QPushButton("Visible", this);
    m_pBtnVisible->setCheckable(true);
    m_pBtnVisible->setChecked(true);
    connect(m_pBtnVisible, &QPushButton::toggled,
            this, &PropertyEditor::onVisibleToggled);
    pAppLayout->addRow("Visible:", m_pBtnVisible);
    
    QHBoxLayout* pColorLayout = new QHBoxLayout();
    m_pBtnColor = new QPushButton("Choose Color", this);
    m_pLabelColor = new QLabel(this);
    m_pLabelColor->setFixedSize(50, 20);
    m_pLabelColor->setStyleSheet("background-color: rgb(255, 255, 255); border: 1px solid black;");
    connect(m_pBtnColor, &QPushButton::clicked,
            this, &PropertyEditor::onColorChanged);
    pColorLayout->addWidget(m_pBtnColor);
    pColorLayout->addWidget(m_pLabelColor);
    pAppLayout->addRow("Color:", pColorLayout);
    
    // Add groups to main layout
    m_pMainLayout->addWidget(m_pGroupPosition);
    m_pMainLayout->addWidget(m_pGroupSize);
    m_pMainLayout->addWidget(m_pGroupAppearance);
    m_pMainLayout->addStretch();
    
    setLayout(m_pMainLayout);
}

void PropertyEditor::setUIElement(CN3UIBase* pElement)
{
    m_pCurrentElement = pElement;
    updateFromElement();
}

void PropertyEditor::clear()
{
    m_pCurrentElement = nullptr;
    m_pSpinPosX->setValue(0);
    m_pSpinPosY->setValue(0);
    m_pSpinWidth->setValue(100);
    m_pSpinHeight->setValue(100);
    m_pEditID->clear();
    m_pBtnVisible->setChecked(true);
}

void PropertyEditor::updateFromElement()
{
    if (!m_pCurrentElement)
    {
        clear();
        return;
    }
    
    m_bUpdating = true;
    
    // Position
    RECT rc = m_pCurrentElement->GetRegion();
    m_pSpinPosX->setValue(rc.left);
    m_pSpinPosY->setValue(rc.top);
    
    // Size
    m_pSpinWidth->setValue(rc.right - rc.left);
    m_pSpinHeight->setValue(rc.bottom - rc.top);
    
    // ID
    m_pEditID->setText(QString::fromStdString(m_pCurrentElement->GetID()));
    
    // Visible
    m_pBtnVisible->setChecked(m_pCurrentElement->IsVisible());
    
    // Color (UI String için)
    if (m_pCurrentElement->UIType() == UI_TYPE_STRING)
    {
        CN3UIString* pStr = (CN3UIString*)m_pCurrentElement;
        D3DCOLOR color = pStr->GetColor();
        
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        
        QString style = QString("background-color: rgb(%1, %2, %3); border: 1px solid black;")
                       .arg(r).arg(g).arg(b);
        m_pLabelColor->setStyleSheet(style);
    }
    
    m_bUpdating = false;
}

void PropertyEditor::onPositionXChanged(int value)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    RECT rc = m_pCurrentElement->GetRegion();
    int width = rc.right - rc.left;
    rc.left = value;
    rc.right = value + width;
    m_pCurrentElement->SetRegion(rc);
    
    emit propertyChanged();
}

void PropertyEditor::onPositionYChanged(int value)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    RECT rc = m_pCurrentElement->GetRegion();
    int height = rc.bottom - rc.top;
    rc.top = value;
    rc.bottom = value + height;
    m_pCurrentElement->SetRegion(rc);
    
    emit propertyChanged();
}

void PropertyEditor::onWidthChanged(int value)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    RECT rc = m_pCurrentElement->GetRegion();
    rc.right = rc.left + value;
    m_pCurrentElement->SetRegion(rc);
    
    emit propertyChanged();
}

void PropertyEditor::onHeightChanged(int value)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    RECT rc = m_pCurrentElement->GetRegion();
    rc.bottom = rc.top + value;
    m_pCurrentElement->SetRegion(rc);
    
    emit propertyChanged();
}

void PropertyEditor::onColorChanged()
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    if (m_pCurrentElement->UIType() != UI_TYPE_STRING) return;
    
    CN3UIString* pStr = (CN3UIString*)m_pCurrentElement;
    D3DCOLOR currentColor = pStr->GetColor();
    
    int r = (currentColor >> 16) & 0xFF;
    int g = (currentColor >> 8) & 0xFF;
    int b = currentColor & 0xFF;
    
    QColor color = QColorDialog::getColor(QColor(r, g, b), this, "Choose Color");
    
    if (color.isValid())
    {
        D3DCOLOR d3dColor = D3DCOLOR_XRGB(color.red(), color.green(), color.blue());
        pStr->SetColor(d3dColor);
        
        QString style = QString("background-color: rgb(%1, %2, %3); border: 1px solid black;")
                       .arg(color.red()).arg(color.green()).arg(color.blue());
        m_pLabelColor->setStyleSheet(style);
        
        emit propertyChanged();
    }
}

void PropertyEditor::onIDChanged(const QString& text)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    m_pCurrentElement->SetID(text.toStdString());
    emit propertyChanged();
}

void PropertyEditor::onVisibleToggled(bool checked)
{
    if (m_bUpdating || !m_pCurrentElement) return;
    
    m_pCurrentElement->SetVisible(checked);
    emit propertyChanged();
}

#endif // USE_QT_DIRECT3D

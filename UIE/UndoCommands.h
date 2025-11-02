// UndoCommands.h: Undo/Redo komutları

#pragma once

#ifdef USE_QT_DIRECT3D

#include <QUndoCommand>
#include <QRect>

class CN3UIBase;

/**
 * @brief UI Element pozisyon değiştirme komutu
 */
class MoveUIElementCommand : public QUndoCommand
{
public:
    MoveUIElementCommand(CN3UIBase* pElement, const QRect& oldRect, const QRect& newRect, QUndoCommand* parent = nullptr);
    
    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand* command) override;
    
private:
    CN3UIBase* m_pElement;
    QRect m_oldRect;
    QRect m_newRect;
};

/**
 * @brief UI Element boyut değiştirme komutu
 */
class ResizeUIElementCommand : public QUndoCommand
{
public:
    ResizeUIElementCommand(CN3UIBase* pElement, const QRect& oldRect, const QRect& newRect, QUndoCommand* parent = nullptr);
    
    void undo() override;
    void redo() override;
    
private:
    CN3UIBase* m_pElement;
    QRect m_oldRect;
    QRect m_newRect;
};

/**
 * @brief UI Element renk değiştirme komutu
 */
class ChangeColorCommand : public QUndoCommand
{
public:
    ChangeColorCommand(CN3UIBase* pElement, DWORD oldColor, DWORD newColor, QUndoCommand* parent = nullptr);
    
    void undo() override;
    void redo() override;
    
private:
    CN3UIBase* m_pElement;
    DWORD m_oldColor;
    DWORD m_newColor;
};

/**
 * @brief UI Element ekleme komutu
 */
class AddUIElementCommand : public QUndoCommand
{
public:
    AddUIElementCommand(CN3UIBase* pParent, CN3UIBase* pElement, QUndoCommand* parent = nullptr);
    
    void undo() override;
    void redo() override;
    
private:
    CN3UIBase* m_pParent;
    CN3UIBase* m_pElement;
};

/**
 * @brief UI Element silme komutu
 */
class DeleteUIElementCommand : public QUndoCommand
{
public:
    DeleteUIElementCommand(CN3UIBase* pParent, CN3UIBase* pElement, QUndoCommand* parent = nullptr);
    
    void undo() override;
    void redo() override;
    
private:
    CN3UIBase* m_pParent;
    CN3UIBase* m_pElement;
};

#endif // USE_QT_DIRECT3D

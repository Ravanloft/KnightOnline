// UndoCommands.cpp: Undo/Redo komut implementasyonları

#ifdef USE_QT_DIRECT3D

#include "UndoCommands.h"
#include <N3Base/N3UIBase.h>
#include <N3Base/N3UIString.h>

MoveUIElementCommand::MoveUIElementCommand(CN3UIBase* pElement, const QRect& oldRect, const QRect& newRect, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_pElement(pElement)
    , m_oldRect(oldRect)
    , m_newRect(newRect)
{
    setText("Move Element");
}

void MoveUIElementCommand::undo()
{
    if (!m_pElement) return;
    
    RECT rc;
    rc.left = m_oldRect.left();
    rc.top = m_oldRect.top();
    rc.right = m_oldRect.right();
    rc.bottom = m_oldRect.bottom();
    m_pElement->SetRegion(rc);
}

void MoveUIElementCommand::redo()
{
    if (!m_pElement) return;
    
    RECT rc;
    rc.left = m_newRect.left();
    rc.top = m_newRect.top();
    rc.right = m_newRect.right();
    rc.bottom = m_newRect.bottom();
    m_pElement->SetRegion(rc);
}

bool MoveUIElementCommand::mergeWith(const QUndoCommand* command)
{
    const MoveUIElementCommand* cmd = static_cast<const MoveUIElementCommand*>(command);
    if (m_pElement != cmd->m_pElement)
        return false;
    
    m_newRect = cmd->m_newRect;
    return true;
}

ResizeUIElementCommand::ResizeUIElementCommand(CN3UIBase* pElement, const QRect& oldRect, const QRect& newRect, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_pElement(pElement)
    , m_oldRect(oldRect)
    , m_newRect(newRect)
{
    setText("Resize Element");
}

void ResizeUIElementCommand::undo()
{
    if (!m_pElement) return;
    
    RECT rc;
    rc.left = m_oldRect.left();
    rc.top = m_oldRect.top();
    rc.right = m_oldRect.right();
    rc.bottom = m_oldRect.bottom();
    m_pElement->SetRegion(rc);
}

void ResizeUIElementCommand::redo()
{
    if (!m_pElement) return;
    
    RECT rc;
    rc.left = m_newRect.left();
    rc.top = m_newRect.top();
    rc.right = m_newRect.right();
    rc.bottom = m_newRect.bottom();
    m_pElement->SetRegion(rc);
}

ChangeColorCommand::ChangeColorCommand(CN3UIBase* pElement, DWORD oldColor, DWORD newColor, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_pElement(pElement)
    , m_oldColor(oldColor)
    , m_newColor(newColor)
{
    setText("Change Color");
}

void ChangeColorCommand::undo()
{
    if (!m_pElement || m_pElement->UIType() != UI_TYPE_STRING) return;
    
    CN3UIString* pStr = (CN3UIString*)m_pElement;
    pStr->SetColor(m_oldColor);
}

void ChangeColorCommand::redo()
{
    if (!m_pElement || m_pElement->UIType() != UI_TYPE_STRING) return;
    
    CN3UIString* pStr = (CN3UIString*)m_pElement;
    pStr->SetColor(m_newColor);
}

AddUIElementCommand::AddUIElementCommand(CN3UIBase* pParent, CN3UIBase* pElement, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_pParent(pParent)
    , m_pElement(pElement)
{
    setText("Add Element");
}

void AddUIElementCommand::undo()
{
    if (!m_pParent || !m_pElement) return;
    
    // Remove element from parent
    // TODO: Implement CN3UIBase::RemoveChild or similar
}

void AddUIElementCommand::redo()
{
    if (!m_pParent || !m_pElement) return;
    
    // Add element to parent
    // TODO: Implement CN3UIBase::AddChild or similar
}

DeleteUIElementCommand::DeleteUIElementCommand(CN3UIBase* pParent, CN3UIBase* pElement, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_pParent(pParent)
    , m_pElement(pElement)
{
    setText("Delete Element");
}

void DeleteUIElementCommand::undo()
{
    if (!m_pParent || !m_pElement) return;
    
    // Re-add element to parent
    // TODO: Implement
}

void DeleteUIElementCommand::redo()
{
    if (!m_pParent || !m_pElement) return;
    
    // Remove element from parent
    // TODO: Implement
}

#endif // USE_QT_DIRECT3D

#include "cbase.h"
#include <vgui/IScheme.h>
#include <vgui/ILocalize.h>
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include "inputsystem/iinputsystem.h"
#include "ReplayContextMenu.h"

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CReplayContextMenu::CReplayContextMenu(Panel *parent) : Menu(parent, "ReplayContextMenu")
{
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CReplayContextMenu::~CReplayContextMenu()
{
}

//-----------------------------------------------------------------------------
// Purpose: Activates the menu
//-----------------------------------------------------------------------------
void CReplayContextMenu::ShowMenu(Panel *target, const char *runName)
{
    if (runName)
    {
        AddMenuItem("StartMap", "#MOM_Leaderboards_WatchReplay", new KeyValues("ContextWatchReplay", "runName", runName), target);
    }

    int x, y, gx, gy;
    input()->GetCursorPos(x, y);
    ipanel()->GetPos(surface()->GetEmbeddedPanel(), gx, gy);
    SetPos(x - gx - 5, y - gy - 5);
    SetVisible(true);
    SetMouseInputEnabled(true);
}

void CReplayContextMenu::OnCursorExitedMenuItem(int vpanel)
{ 
    SetVisible(false);
    SetMouseInputEnabled(false);
    BaseClass::OnCursorExitedMenuItem(vpanel);
}

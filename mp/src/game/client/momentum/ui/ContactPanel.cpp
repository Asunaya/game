//The following include files are necessary to allow your  the panel .cpp to compile.
#include "cbase.h"

#include "IContactPanel.h"
#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/TextEntry.h>
#include <vgui_controls/pch_vgui_controls.h>
#include "momentum/util/mom_util.h"

#include "tier0/memdbgon.h"

using namespace vgui;

class CContactPanel : public Frame
{
    DECLARE_CLASS_SIMPLE(CContactPanel, vgui::Frame);
    //CBugReportPanel : This Class / vgui::Frame : BaseClass

    CContactPanel(VPANEL parent); 	// Constructor
    ~CContactPanel() {};				// Destructor

    void OnThink() override;
    void Activate() override;
    void InitPanel();
protected:
    MESSAGE_FUNC_CHARPTR(OnURLChange, "OnFinishRequest", URL)
    {
        DevLog("URL FINISHED LOADING %s\n", URL);
        //MOM_TODO: Do we want to have anything custom when they submit a contact form?
    }

private:
    HTML *m_pWebPage;
};

// Constuctor: Initializes the Panel
CContactPanel::CContactPanel(VPANEL parent)
    : BaseClass(nullptr, "CBugReportPanel")
{
    SetParent(parent);
    SetPaintBackgroundType(1);
    SetRoundedCorners(PANEL_ROUND_CORNER_ALL);
    SetKeyBoardInputEnabled(true);
    SetMouseInputEnabled(true);

    SetProportional(true);
    SetTitleBarVisible(true);
    SetMinimizeButtonVisible(false);
    SetMaximizeButtonVisible(false);
    SetCloseButtonVisible(true);
    SetSizeable(false);
    SetMoveable(true);
    SetVisible(false);
    AddActionSignalTarget(this);

    LoadControlSettings("resource/ui/ContactPanel.res");
    m_pWebPage = new HTML(this, "HTMLForm", true);
    m_pWebPage->AddActionSignalTarget(this);

    InitPanel();
}

void CContactPanel::InitPanel()
{
#define SCALE(num) scheme()->GetProportionalScaledValue(num)
#define SCALEXY(x,y) SCALE(x), SCALE(y)

    m_pWebPage->SetPos(SCALEXY(0, 25));
    m_pWebPage->SetSize(GetWide(), GetTall() - SCALE(25));
    m_pWebPage->OpenURL("http://momentum-mod.org/contact", nullptr);
}

//Class: CBugReportPanelInterface Class. Used for construction.
class CContactPanelInterface : public IContactPanel
{
private:
    CContactPanel *contact_panel;
public:
    CContactPanelInterface()
    {
        contact_panel = nullptr;
    }
    ~CContactPanelInterface()
    {
        contact_panel = nullptr;
    }
    void Create(VPANEL parent) override
    {
        contact_panel = new CContactPanel(parent);
    }
    void Destroy() override
    {
        if (contact_panel)
        {
            contact_panel->SetParent(nullptr);
            delete contact_panel;
        }
    }
    void Activate(void) override
    {
        if (contact_panel)
        {
            contact_panel->Activate();
            contact_panel->SetKeyBoardInputEnabled(true);
        }
    }
    void Close() override
    {
        if (contact_panel)
        {
            contact_panel->Close();
            contact_panel->SetKeyBoardInputEnabled(false);
        }
    }
};
static CContactPanelInterface g_ContactPanel;
IContactPanel* contact_panel = static_cast<IContactPanel*>(&g_ContactPanel);

CON_COMMAND(mom_contact_show, "Shows the contact panel.\n")
{
    contact_panel->Activate();
}

void CContactPanel::OnThink()
{
    BaseClass::OnThink();
    GetAnimationController()->UpdateAnimations(system()->GetFrameTime());
}

void CContactPanel::Activate()
{
    BaseClass::Activate();
    InitPanel();
}
#include "BasePanel.h"
#include "PanelManager.h"

BasePanel::BasePanel()
{
	PanelManager::GetInstance().AddPanel(this);
}

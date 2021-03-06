#include "stdafx.h"

#include "MainMenu.h"
#include "AllLookFeel.h"

namespace UIEditor {

	MainMenu::MainMenu()
	{
		mLayout = new MGUI_Layout(AllLookFeel::Instance()->GetMenu());

		mButton_LookFeelFile = new MGUI_Button(AllLookFeel::Instance()->GetLookFeelFile(), mLayout);
		mButton_LookFeelFile->SetRect(MGUI_Rect(1, 1, 32, 32));
	}

	MainMenu::~MainMenu()
	{
		delete mLayout;
	}

	void MainMenu::Layout()
	{
		MGUI_Rect rect;

		rect.x0 = 0;
		rect.y0 = 0;
		rect.x1 = MGUI_Engine::Instance()->GetRect().x1;
		rect.y1 = 32;

		mLayout->SetRect(rect);
	}

}
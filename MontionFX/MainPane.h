//////////////////////////////////////////////////////////////////////////
//
// MotionFX: Motion Tool For Myway3D
//   
//	 author: Myway
//	 e-mail: Myway3D@Gmail.com
//
//
//
#pragma once

#include "Common\\BaseLayout.h"
#include "MainMenu.h"
#include "MainWorkSpace.h"

namespace MotionFX {

	class MainPane : public wraps::BaseLayout
	{
	public:
		MainPane();
		~MainPane();

	protected:
		MainMenu * mMainMenu;
		MainWorkSpace * mWorkSpace;
	};

}



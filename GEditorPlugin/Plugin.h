#pragma once

#include "Editor.h"
#include "EditorGameMode.h"

namespace game {

	class GamePlugin : public Infinite::iPlugin
	{
	public:
		GamePlugin();
		~GamePlugin();

		virtual const char * getName() { return "game plugin"; }
		virtual const char * GetExpExtern() { return ".gmap"; }
		virtual const char * GetImpExtern() { return ""; }

		virtual int GetUsages() { return Infinite::iPlugin::eExport; }

		virtual void Export(const char * filename);

	protected:
		void _OnInit(Event * _sender);
		void _OnShutdown(Event * _sender);
		void _OnUpdate(Event * _sender);

	protected:
		tEventListener<GamePlugin> OnInit;
		tEventListener<GamePlugin> OnShutown;
		tEventListener<GamePlugin> OnUpdate;

		EditorGameMode * mGameMain;
	};
}
#include "MWRenderEvent.h"

namespace Myway {

	Event RenderEvent::OnEngineInit;
	Event RenderEvent::OnEngineShutdown;

    Event RenderEvent::OnPreUpdateScene;
    Event RenderEvent::OnPostUpdateScene;

    Event RenderEvent::OnPreRenderEvent;
    Event RenderEvent::OnPostRenderEvent;

    Event RenderEvent::OnPreVisibleCull;
    Event RenderEvent::OnPostVisibleCull;
	Event RenderEvent::OnFilterCullResult;
	Event RenderEvent::OnOptimizeMirrorCullResult;

    Event RenderEvent::OnLostDevice;
    Event RenderEvent::OnResetDevice;

    Event RenderEvent::OnResize;

	Event RenderEvent::OnBeginRender;

	Event RenderEvent::OnRenderSolid1;
	Event RenderEvent::OnRenderSolid2;
	Event RenderEvent::OnRenderSolid3;

	Event RenderEvent::OnAfterRenderSolid;
	Event RenderEvent::OnAfterRenderTrans;

	Event RenderEvent::OnAfterDefferedShading;
	Event RenderEvent::OnAfterTerrainRender;

	Event RenderEvent::OnMirrorRenderSolid1;
	Event RenderEvent::OnMirrorRenderSolid2;
	Event RenderEvent::OnMirrorRenderSolid3;

	Event RenderEvent::OnAfterRender;
	Event RenderEvent::OnDebugRender;

	Event RenderEvent::OnRenderGUI1;
	Event RenderEvent::OnRenderGUI2;
	Event RenderEvent::OnRenderGUI3;
}
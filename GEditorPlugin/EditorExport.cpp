#include "stdafx.h"

#include "EditorExport.h"
#include "Shape.h"
#include "xMesh.h"
#include "Helper.h"

using namespace Infinite;

void EditorExport::Export(const char * filename)
{
	File file;

	file.Open(filename);

	SaveHead(file);
	SaveEnvironment(file);
	SaveTerrain(file);
	SaveMesh(file);
	SaveForest(file);
	SaveParticle(file);
	SaveSound(file);

	file.Close();

	//TString128 helperFile = File::RemoveExternName(filename);
	//helperFile += ".sv_map";
	//ServerExport svExport;
	//svExport.Export(helperFile.c_str());
}

void EditorExport::SaveHead(File & file)
{
	int Magic = GmMap::K_FILE_MAGIC;
	int Version = GmMap::K_FILE_VERSION;

	file.Write(&Magic, sizeof(int));
	file.Write(&Version, sizeof(int));
}

void EditorExport::SaveEnvironment(File & file)
{
	int ckId = GmMap::FCI_Enviroment;
	const int K_Version = GmMap::K_Enviroment_Version;

	file.Write(&ckId, sizeof(int));
	file.Write(&K_Version, sizeof(int));

	EvKeyFrame * kNight = Environment::Instance()->GetKeyFrame(EVKT_Night);
	EvKeyFrame * kMorning = Environment::Instance()->GetKeyFrame(EVKT_Morning);
	EvKeyFrame * kNoon = Environment::Instance()->GetKeyFrame(EVKT_Noon);
	EvKeyFrame * kEvening = Environment::Instance()->GetKeyFrame(EVKT_Evening);
	EvGlobalParam * kGlobal = Environment::Instance()->GetGlobalParam();

	file.WriteProperty(kNight);
	file.WriteProperty(kMorning);
	file.WriteProperty(kNoon);
	file.WriteProperty(kEvening);
	file.WriteProperty(kGlobal);
}

void EditorExport::SaveTerrain(File & file)
{
	int ckId = GmMap::FCI_Terrain;
	int K_Version = GmMap::K_Terrain_Version;

	file.Write(&ckId, sizeof(int));
	file.Write(&K_Version, sizeof(int));
}

void EditorExport::SaveMesh(File & file)
{
	int ckId = GmMap::FCI_Mesh;
	int ckVr = GmMap::K_Mesh_Version;

	file.Write(&ckId, sizeof(int));
	file.Write(&ckVr, sizeof(int));

	int shapeCount = ShapeManager::Instance()->GetShapeCount();

	int meshCount = 0;

	for (int i = 0; i < shapeCount; ++i)
	{
		Shape * shape = ShapeManager::Instance()->GetShape(i);

		if (RTTI_TypeOf(xMesh, shape))
			++meshCount;
	}

	file.Write(&meshCount, sizeof(int));

	for (int i = 0; i < shapeCount; ++i)
	{
		Shape * shape = ShapeManager::Instance()->GetShape(i);

		if (RTTI_TypeOf(xMesh, shape))
		{
			xMesh * mesh = (xMesh *)shape;

			TString128 MeshFile;
			Vec3 Position;
			Quat Orientation;
			float Scale;

			MeshFile = mesh->MeshFile;
			Position = mesh->GetPosition();
			Orientation = mesh->GetOrientation();
			Scale = mesh->GetScale();

			file.Write(MeshFile.c_str(), 128);
			file.Write(&Position, sizeof(Vec3));
			file.Write(&Orientation, sizeof(Quat));
			file.Write(&Scale, sizeof(float));
		}
	}
}

void EditorExport::SaveForest(File & file)
{
}

void EditorExport::SaveParticle(File & file)
{
}

void EditorExport::SaveSound(File & file)
{
}





void ServerExport::Export(const char * filename)
{
	File file;

	file.Open(filename);

	SaveHead(file);
	SaveHelper(file);

	file.Close();
}

void ServerExport::SaveHead(File & file)
{
	int Magic = K_FILE_MAGIC;
	int Version = K_FILE_VERSION;

	file.Write(&Magic, sizeof(int));
	file.Write(&Version, sizeof(int));
}

void ServerExport::SaveHelper(File & file)
{
	int ckId = FCI_Helper;
	int ckVr = K_Helper_Version;

	file.Write(&ckId, sizeof(int));
	file.Write(&ckVr, sizeof(int));

	int shapeCount = ShapeManager::Instance()->GetShapeCount();

	int helperCount = 0;

	for (int i = 0; i < shapeCount; ++i)
	{
		Shape * shape = ShapeManager::Instance()->GetShape(i);

		if (RTTI_TypeOf(Helper, shape))
			++helperCount;
	}

	file.Write(&helperCount, sizeof(int));

	for (int i = 0; i < shapeCount; ++i)
	{
		Shape * shape = ShapeManager::Instance()->GetShape(i);

		if (RTTI_TypeOf(Helper, shape))
		{
			Helper * helper = (Helper *)shape;

			TString128 Name = helper->GetName();
			Vec3 Position = helper->GetPosition();
			float Radius = helper->GetScale();
			TString128 UserString = helper->GetUserString();

			file.Write(Name.c_str(), 128);
			file.Write(&Position, sizeof(Vec3));
			file.Write(&Radius, sizeof(float));
			file.Write(UserString.c_str(), 128);
		}
	}
}
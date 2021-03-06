//////////////////////////////////////////////////////////////////////////
//
// Infinite. Scene Editor For Myway3D
//   
//	 author: Myway
//	 e-mail: Myway3D@Gmail.com
//
//
//
#pragma once

#include "Shape.h"
#include "Editor.h"

namespace Infinite {

	class xPointLight : public Shape
	{
		DECLARE_PROPERTY(Shape);
		DeclareRTTI();

	public:
		Vec3 Position;
		Color4 Diffuse;
		Color4 Specular;
		float Range;

	public:
		xPointLight(const TString128 & name);
		virtual ~xPointLight();

		virtual TString128 GetTypeName() { return "PointLight"; }

		virtual void SetName(const TString128 & name);

		virtual Shape * Clone();
		virtual bool IsSceneNode(SceneNode * node);

		virtual void SetPosition(const Vec3 & p);
		virtual Vec3 GetPosition() { return Position; }

		virtual void SetScale(float s);
		virtual float GetScale() { return GetRange(); }

		virtual void SetDiffuse(const Color4 & clr);
		virtual Color4 GetDiffuse() { return Diffuse; }

		virtual void SetSpecular(const Color4 & clr);
		virtual Color4 GetSpecular() { return Specular; }

		virtual void SetRange(float range);
		virtual float GetRange() { return Range; }

		virtual void Serialize(xSerializer & serializer);

		virtual Aabb GetBound();

		virtual bool OnPropertyChanged(const Property * p);

	protected:
		SceneNode * mNode;
		Light * mLight;
		Billboard * mBillboard;
	};

	class xPointLightFactory : public ShapeFactory
	{
	public:
		xPointLightFactory() {};
		virtual ~xPointLightFactory() {};

		virtual xPointLight * Create(const char * name) { return new xPointLight(name); }

		virtual const char * GetGroupName()		{ return "Light"; }
		virtual const char * GetTypeName()		{ return "PointLight"; }
	};
}

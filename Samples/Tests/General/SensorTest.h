// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Tests/Test.h>
#include <Jolt/Physics/Ragdoll/Ragdoll.h>

class SensorTest : public Test, public ContactListener
{
public:
	JPH_DECLARE_RTTI_VIRTUAL(JPH_NO_EXPORT, SensorTest)

	virtual				~SensorTest() override;

	// Description of the test
	virtual const char *GetDescription() const override
	{
		return	"Different types of sensors. See the description of each sensor.";
	}

	// Number used to scale the terrain and camera movement to the scene
	virtual float		GetWorldScale() const override		{ return 0.2f; }

	// See: Test
	virtual void		Initialize() override;
	virtual void		PrePhysicsUpdate(const PreUpdateParams &inParams) override;

	// If this test implements a contact listener, it should be returned here
	virtual ContactListener *GetContactListener() override	{ return this; }

	// See: ContactListener
	virtual void		OnContactAdded(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold, ContactSettings &ioSettings) override;
	virtual void		OnContactRemoved(const SubShapeIDPair &inSubShapePair) override;

	// Saving / restoring state for replay
	virtual void		SaveState(StateRecorder &inStream) const override;
	virtual void		RestoreState(StateRecorder &inStream) override;

private:
	float				mTime = 0.0f;						// Total elapsed time

	enum
	{
		StaticAttractor,									// A static sensor that attracts dynamic bodies that enter its area
		StaticSensor,										// A static sensor that only detects active bodies
		KinematicSensor,									// A kinematic sensor that also detects sleeping bodies
		SensorDetectingStatic,								// A kinematic sensor that detects static bodies
		NumSensors
	};

	BodyID				mSensorID[NumSensors];				// Body ID of the various sensors

	Ref<Ragdoll>		mRagdoll;							// Ragdoll that is falling into the sensor

	BodyID				mKinematicBodyID;					// Body ID of a kinematic body that is animating in and out of the sensor

	Mutex				mMutex;								// Mutex that protects mBodiesInSensor and mKinematicBodyInSensor

	// Structure that keeps track of how many contact point each body has with the sensor
	struct BodyAndCount
	{
		BodyID			mBodyID;
		int				mCount;

		bool			operator < (const BodyAndCount &inRHS) const { return mBodyID < inRHS.mBodyID; }
	};

	using BodiesInSensor = Array<BodyAndCount>;
	BodiesInSensor		mBodiesInSensor[NumSensors];		// Dynamic bodies that are currently inside the sensor
};

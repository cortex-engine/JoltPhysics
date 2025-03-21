// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Tests/Test.h>
#include <Jolt/Physics/Body/Body.h>

class KinematicTest : public Test
{
public:
	JPH_DECLARE_RTTI_VIRTUAL(JPH_NO_EXPORT, KinematicTest)

	// Description of the test
	virtual const char *GetDescription() const override
	{
		return "Tests kinematic objects against a pile of dynamic boxes.";
	}

	// See: Test
	virtual void	Initialize() override;
	virtual void	PrePhysicsUpdate(const PreUpdateParams &inParams) override;

private:
	Body *			mKinematic[2];
};

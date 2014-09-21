#include <GarrysMod/Lua/Interface.h>
#include "EulerAngles.h"
#include <unistd.h>

using namespace GarrysMod::Lua;

#define registerFunction(Func) \
	state->luabase->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );\
	state->luabase->PushString(#Func);\
	state->luabase->PushCFunction(Func);\
	state->luabase->SetTable(-3);

static ovrHmd hmd;

static void freeReference(lua_State *state)
{
	/*if (skelCallbackRef)
		LUA->ReferenceFree(skelCallbackRef);

	skelCallbackRef = 0;*/
}

int OculusAvailable(lua_State *state)
{
	LUA->PushBool(hmd != nullptr);
	return 1;
}

int OculusGetRotation(lua_State *state)
{
	static EulerAngles angles;
	if (hmd) {
		ovrFrameTiming fTiming = ovrHmd_BeginFrame(hmd, 0);
		OVR::SensorState ss = ovrHmd_GetSensorState(hmd, fTiming.ScanoutMidpointSeconds);
		if (ss.StatusFlags & ovrStatus_OrientationTracked) {
			OVR::Transformf pose = ss.Predicted.Pose;
			angles = EulerAngles(pose.Rotation);
		}
		ovrHmd_EndFrame(hmd);
	}

	LUA->PushNumber(angles.pitch);
	LUA->PushNumber(angles.yaw);
	LUA->PushNumber(angles.roll);
	return 3;
}

int OculusResetSensor(lua_State *state)
{
	if (hmd)
		ovrHmd_ResetSensor(hmd);
	return 0;
}

GMOD_MODULE_OPEN()
{
	ovr_Initialize();

	hmd = ovrHmd_Create(0);
	ovrHmdDesc hmdDesc;

	if (hmd) {
		ovrHmd_GetDesc(hmd, &hmdDesc);
		ovrHmd_StartSensor(hmd, ovrSensorCap_Orientation | ovrSensorCap_YawCorrection, ovrSensorCap_Orientation);
	}

	registerFunction(OculusAvailable);
	registerFunction(OculusGetRotation);
	registerFunction(OculusResetSensor);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	if (hmd) {
		ovrHmd_Destroy(hmd);
	}

	ovr_Shutdown();

	return 0;
}

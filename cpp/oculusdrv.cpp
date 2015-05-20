#include <GarrysMod/Lua/Interface.h>
#include "EulerAngles.h"
#include <unistd.h>

using namespace GarrysMod::Lua;

#define registerFunction(Func) \
	state->luabase->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );\
	state->luabase->PushString(#Func);\
	state->luabase->PushCFunction(Func);\
	state->luabase->SetTable(-3);

static ovrHmd hmd = NULL;

static int OculusAvailable(lua_State *state)
{
	LUA->PushBool(hmd != NULL);
	return 1;
}

static void OculusDestroy()
{
	if (hmd) {
		ovrHmd_Destroy(hmd);
	}

	ovr_Shutdown();
	hmd = NULL;
}

static int OculusReconnect(lua_State *state)
{
	if (hmd) {
		OculusDestroy();
		usleep(600);
	}
	ovr_Initialize();

	hmd = ovrHmd_Create(0);

	if (hmd) {
		ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection, ovrTrackingCap_Orientation);
	}
	return 0;
}

int OculusGetRotation(lua_State *state)
{
	static EulerAngles angles;
	if (hmd) {
		ovrFrameTiming fTiming = ovrHmd_BeginFrameTiming(hmd, 0);
		ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, fTiming.ScanoutMidpointSeconds);
		if (ts.StatusFlags & ovrStatus_OrientationTracked) {
			OVR::Posef pose = ts.HeadPose.ThePose;
			angles = EulerAngles(pose.Rotation);
		}
		ovrHmd_EndFrameTiming(hmd);
	}

	LUA->PushNumber(angles.pitch);
	LUA->PushNumber(angles.yaw);
	LUA->PushNumber(angles.roll);
	return 3;
}

int OculusResetSensor(lua_State *state)
{
	if (hmd)
		ovrHmd_RecenterPose(hmd);

	return 0;
}

GMOD_MODULE_OPEN()
{
	OculusReconnect(NULL);

	registerFunction(OculusAvailable);
	registerFunction(OculusGetRotation);
	registerFunction(OculusResetSensor);
	registerFunction(OculusReconnect);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	OculusDestroy();

	return 0;
}

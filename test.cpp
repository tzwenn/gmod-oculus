#include <cstdio>
#include "cpp/EulerAngles.h"
#include <unistd.h>

int main()
{
	ovr_Initialize();
	ovrHmd hmd = ovrHmd_Create(0);

	ovrHmdDesc hmdDesc;

	printf("%p\n", hmd);
	if (!hmd)
		return 1;

	ovrHmd_GetDesc(hmd, &hmdDesc);
	if (!ovrHmd_StartSensor(hmd, ovrSensorCap_Orientation | ovrSensorCap_YawCorrection, ovrSensorCap_Orientation)) {
		printf("Screw you");
		return 2;
	}

	static EulerAngles angles;
	while (true) {
		usleep(200);
		ovrFrameTiming fTiming = ovrHmd_BeginFrame(hmd, 0);
		OVR::SensorState ss = ovrHmd_GetSensorState(hmd, fTiming.ScanoutMidpointSeconds);
		if (ss.StatusFlags & ovrStatus_OrientationTracked) {
			OVR::Transformf pose = ss.Predicted.Pose;
			angles = EulerAngles(pose.Rotation);
		}
		ovrHmd_EndFrame(hmd);
		printf("%f\t%f\t%f\n", angles.pitch, angles.yaw, angles.roll);
	}

	ovrHmd_Destroy(hmd);
	ovr_Shutdown();

	return 0;
}

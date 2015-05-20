#include <cstdio>
#include "cpp/EulerAngles.h"
#include <unistd.h>

int main()
{
	ovr_Initialize();
	ovrHmd hmd = ovrHmd_Create(0);

	printf("%p\n", hmd);
	if (!hmd)
		return 1;

	if (!ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection, ovrTrackingCap_Orientation)) {
		printf("Screw you");
		return 2;
	}

	static EulerAngles angles;
	while (true) {
		usleep(200);
		ovrFrameTiming fTiming = ovrHmd_BeginFrameTiming(hmd, 0);
		ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, fTiming.ScanoutMidpointSeconds);
		if (ts.StatusFlags & ovrStatus_OrientationTracked) {
			OVR::Posef pose = ts.HeadPose.ThePose;
			angles = EulerAngles(pose.Rotation);
		}
		ovrHmd_EndFrameTiming(hmd);
		printf("%f\t%f\t%f\n", angles.pitch, angles.yaw, angles.roll);
	}

	ovrHmd_Destroy(hmd);
	ovr_Shutdown();

	return 0;
}

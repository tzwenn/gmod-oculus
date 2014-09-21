#include <OVR.h>

struct EulerAngles
{
	double yaw, pitch, roll;

	EulerAngles() :
		yaw(0),
		pitch(0),
		roll(0)
	{
		;;
	}

	EulerAngles(const OVR::Quatf & q)
	{
		using namespace OVR;
		static const double scale = 180.0 / M_PI;

		Quatd quat(q.w, q.x, q.y, q.z);

		quat.GetEulerAngles<Axis_X, Axis_Y, Axis_Z, Rotate_CCW, Handed_R>(&yaw, &pitch, &roll);
		yaw *= scale;
		pitch *= scale;
		roll *= scale;
	}
};

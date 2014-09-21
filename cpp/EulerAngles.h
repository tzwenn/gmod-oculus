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

		Quatd quat(q.x, q.y, q.z, q.w);

		//quat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z, Rotate_CW, Handed_L>(&yaw, &pitch, &roll);
		quat.GetEulerAngles<Axis_Y, Axis_Z, Axis_X, Rotate_CCW, Handed_L>(&yaw, &roll, &pitch);
		pitch *= scale;
		yaw *= scale * -1;
		roll *= scale * -1;


		corr(pitch);
		corr(yaw);
		corr(roll);
	}

private:

	void corr(double & a)
	{
		a = a < -180 ? a + 360 : a;
	}
};

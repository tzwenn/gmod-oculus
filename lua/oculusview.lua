require("oculus")

local function OculusView( ply, pos, angles, fov )
	local view = {}

	view.origin = pos
	pitch, yaw, roll = OculusGetRotation()
	view.angles = Angle(pitch, yaw + angles.y, roll * 0)
	view.fov = fov

	return view
end


function StartOcculus()
	OculusResetSensor()
	hook.Add("CalcView", "OculusView", OculusView)
	manually_pp_stereoscpy = true
end

function StopOcculus()
	hook.Remove("CalcView", "OculusView")
	manually_pp_stereoscpy = false
end

OculusReconnect()


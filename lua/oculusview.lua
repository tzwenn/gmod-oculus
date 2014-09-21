require("oculus")

local function OculusView( ply, pos, angles, fov )
	local view = {}

	view.origin = pos
	pitch, yaw, roll = OculusGetRotation()
	--view.angles = Angle(180 - rz, ry + angles.y - 180, -rx)
	--view.angles = Angle(180 + rz, 180 + angles.y - rx, ry)
	view.angles = Angle(pitch, yaw, roll)
	view.fov = fov

	return view
end


function StartOcculus()
	OculusResetSensor()
	hook.Add("CalcView", "OculusView", OculusView)
--	manually_pp_stereoscpy = false
end

function StopOcculus()
	hook.Remove("CalcView", "OculusView")
--	manually_pp_stereoscpy = false
end

StartOcculus()

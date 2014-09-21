require("oculus")

local function OculusView( ply, pos, angles, fov )
	local view = {}

	view.origin = pos
	rx, ry, rz = OculusGetRotation()
	view.angles = Angle(180 - rz, ry + angles.y - 180, -rx)
	view.fov = fov

	return view
end


function StartOcculus()
	OculusResetSensor()
	hook.Add("CalcView", "OculusView", OculusView)
	--manually_pp_stereoscpy = true
end

function StopOcculus()
	hook.Remove("CalcView", "OculusView")
	--manually_pp_stereoscpy = false
end

StartOcculus()

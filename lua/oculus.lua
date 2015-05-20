
--[[---------------------------------------------------------
   Register the convars that will control this effect
-----------------------------------------------------------]]
local pp_oculus			= CreateClientConVar( "pp_oculus", "0", false, false )
local pp_oculus_size		= CreateClientConVar( "pp_oculus_size", "1.8", true, false )
local pp_oculus_eyeshift	= CreateClientConVar( "pp_oculus_eyeshift", "1.0", true, false )

manually_pp_stereoscpy = false

--[[---------------------------------------------------------
   Can be called from engine or hooks using bloom.Draw
-----------------------------------------------------------]]
local function RenderStereoOculus( ViewOrigin, ViewAngles )

	render.Clear( 0, 0, 0, 255 )
	
	local w = ScrW() / 2.2
	local h = ScrH() / 2.2

	local Right = -ViewAngles:Right() * pp_oculus_size:GetFloat()
	
	local view = {}
	local eyeshift = pp_oculus_eyeshift:GetFloat()
	
	view.y = ScrH() / 2 - h / 2
	view.w = w
	view.h = h
	view.angles = ViewAngles
	
	-- Left
	view.x = ScrW() / 2 - w - eyeshift
	view.origin = ViewOrigin + Right
	render.RenderView( view )

	-- Right
	view.x = ScrW() / 2 + eyeshift
	view.origin = ViewOrigin - Right
	render.RenderView( view )
	
end

--[[---------------------------------------------------------
   The function to draw the bloom (called from the hook)
-----------------------------------------------------------]]
local function DrawInternal( ViewOrigin, ViewAngles, ViewFOV )

	if ( !pp_oculus:GetBool() && !manually_pp_stereoscpy ) then return end

	RenderStereoOculus( ViewOrigin, ViewAngles )
				
	-- Return true to override drawing the scene
	return true

end
hook.Add( "RenderScene", "RenderStereoOculus", DrawInternal )

--[[---------------------------------------------------------
   The function to set the camera rotation according to the IMU
-----------------------------------------------------------]]
require("oculusdrv")
local function OculusView( ply, pos, angles, fov )

	if ( !pp_oculus:GetBool() && !manually_pp_stereoscpy ) then
		return {}
	end

	local view = {}

	view.origin = pos
	pitch, yaw, roll = OculusGetRotation()
	view.angles = Angle(pitch, yaw + angles.y, 0)
	view.fov = fov

	return view
end
hook.Add("CalcView", "OculusView", OculusView)

local function AlignOculus()
	OculusResetSensor()
	LocalPlayer():PrintMessage(HUD_PRINTTALK, "Aligned oculus" )
end

list.Set( "PostProcess", "#oculus_pp", {

	icon		= "gui/postprocess/stereoscopy.png",
	convar		= "pp_oculus",
	category	= "#effects_pp",

	cpanel		= function( CPanel )

		CPanel:AddControl( "Header", { Description = "#oculus_pp.desc" } )
		CPanel:AddControl( "CheckBox", { Label = "#oculus_pp.enable", Command = "pp_oculus" } )

		CPanel:AddControl( "Slider", { Label = "#oculus_pp.size", Command = "pp_oculus_size", Type = "Float", Min = "0", Max = "10" } )
		CPanel:AddControl( "Slider", { Label = "#oculus_pp.eyeshift", Command = "pp_oculus_eyeshift", Type = "Float", Min = "0", Max = "10" } )

		---------------
		local resetButton = vgui.Create( "DButton", CPanel )
		resetButton:SetText( "#oculus_pp.reset" )
		resetButton.DoClick = AlignOculus
		CPanel:AddItem( resetButton, nil )

	end
	
} )

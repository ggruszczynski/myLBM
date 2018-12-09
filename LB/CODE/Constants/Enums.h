#pragma once

enum CardinalDirections
{
	North,
	East,
	South,
	West,
};

enum NodeType
{
	FluidType,
	WallType,
	MovingWallType,
	VelocityInletType,
	PressureOutletType,
	PeriodicType,
	SymmetryType
};

enum MeshType
{
	diffusion_validation_channel,
	advection_validation_channel,
	vonKarman_channel,
	lid,
};
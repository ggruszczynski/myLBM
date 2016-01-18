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
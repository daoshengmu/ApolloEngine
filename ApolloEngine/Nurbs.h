
#pragma once

#include "core/core.h"
#include <vector>

using namespace Apollo;

class Nurbs
{

public:
	void SetKnots( const std::vector<float>& knots );
	void SetControlPoints( const std::vector<Vector3f>& controls );
	void RationalBSplineCurve( uint numPoints, uint kOrder, uint numCurvPoints, const float* ctrlPoints 
		, const float* weights, float* curvePoints );

private:
	void GenerateUniformKnots( uint numCtrlPoints, int order, std::vector<int>&knotPoints );
	void RationalBasis( int ord, float params, int numCtrlPoints, std::vector<int> knots
		, const float* weights, std::vector<float>& rationBasis );

private:
	std::vector<float>		_knots;
	std::vector<Vector3f>	_controls;
};
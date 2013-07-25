#include "stdafx.h"
#include "Nurbs.h"

void Nurbs::SetKnots( const std::vector<float>& knots )
{
	_knots = knots;
}

void Nurbs::SetControlPoints( const std::vector<Vector3f>& controls )
{
	_controls = controls;
}

void Nurbs::GenerateUniformKnots( uint numCtrlPoints, int order, std::vector<int>&knotPoints )
{
	int nplusc,nplus2,i;

	nplusc = numCtrlPoints + order;
	nplus2 = numCtrlPoints + 2;

	knotPoints[1] = 0;

	for (i = 2; i <= nplusc; i++){
		knotPoints[i] = i-1;
	}
}

void Nurbs::RationalBasis( int order, float params, int numCtrlPoints, std::vector<int> knots
							, const float* weights, std::vector<float>& rationBasis )
{
	int nplusc;
	int i,j,k;
	float d,e;
	float sum;
	float temp[36];

	nplusc = numCtrlPoints + order;

/*		printf("knot vector is \n");
		for (i = 1; i <= nplusc; i++){
			printf(" %d %d \n", i,x[i]);
		}
		printf("t is %f \n", t);
*/

/* calculate the first order nonrational basis functions n[i]	*/

	for (i = 1; i<= nplusc-1; i++){
    	if (( params >= knots[i]) && (params < knots[i+1]))
			temp[i] = 1;
	    else
			temp[i] = 0;
	}

/* calculate the higher order nonrational basis functions */

	for (k = 2; k <= order; k++){
    	for (i = 1; i <= nplusc-k; i++){
        	if (temp[i] != 0)    /* if the lower order basis function is zero skip the calculation */
           		d = ((params-knots[i])*temp[i])/(knots[i+k-1]-knots[i]);
	        else
				d = 0;

    	    if (temp[i+1] != 0)     /* if the lower order basis function is zero skip the calculation */
        		e = ((knots[i+k]-params)*temp[i+1])/(knots[i+k]-knots[i+1]);
	        else
    			e = 0;

    	    temp[i] = d + e;
		}
	}

	if (params == (float)knots[nplusc]){		/*    pick up last point	*/
 		temp[numCtrlPoints] = 1;
	}
/*
	printf("Nonrational basis functions are \n");
	for (i=1; i<= npts; i++){
		printf("%f ", temp[i]);
	}
	printf("\n");
*/
/* calculate sum for denominator of rational basis functions */

	sum = 0.;
	for (i = 1; i <= numCtrlPoints; i++){
		    sum = sum + temp[i]*weights[i];
	}

/* form rational basis functions and put in r vector */

	for (i = 1; i <= numCtrlPoints; i++){
    	if (sum != 0){
        	rationBasis[i] = (temp[i]*weights[i])/(sum);}
		else
			rationBasis[i] = 0;
	}
}

void Nurbs::RationalBSplineCurve( uint numPoints, uint kOrder, uint numCurvPoints, const float* ctrlPoints 
, const float* weights, float* curvePoints )
{
	 	uint numKnots = numPoints + kOrder;
	 	std::vector<float> nbasis(30);
	 	std::vector<int> knots(20);
	 	int i,j, jcount;
		float temp;

	 	for(i = 0; i <= numPoints; i++){
 			nbasis.push_back( 0. );
	 	}
	 
	 	for(i = 0; i <= numKnots; i++){
	 		knots.push_back( 0. );
	 	}

		/* generate the uniform periodic knot vector */
		GenerateUniformKnots( numKnots, kOrder, knots );

		int icount = 0;
	//	std::vector<int> knotPoints;
		/*    calculate the points on the rational B-spline curve */
		//int nplusc;
		float t = kOrder-1;
		float step = ((float)((numPoints)-(kOrder-1)))/((float)(numCurvPoints-1));	
		 
		for (int i1 = 1; i1<= numCurvPoints; i1++){
		 
		 	if ((float)knots[numKnots] - t < 5e-6){
		 		t = (float)knots[numKnots];
		 	}
		 		
			RationalBasis(kOrder,t,numPoints,knots,weights,nbasis);      /* generate the basis function for this value of t */
				
			for (j = 1; j <= 3; j++){      /* generate a point on the curve */
				jcount = j;
				curvePoints[icount+j] = 0.;

				for (i = 1; i <= numPoints; i++){ /* Do local matrix multiplication */
					temp = nbasis[i]*ctrlPoints[jcount];
					curvePoints[icount + j] = curvePoints[icount + j] + temp;
	/*
					printf("jcount,nbasis,b,nbasis*b,p = %d %f %f %f %f\n",jcount,nbasis[i],b[jcount],temp,p[icount+j]);
	*/
					jcount = jcount + 3;
				}
			}
	/*
			printf("icount, p %d %f %f %f \n",icount,p[icount+1],p[icount+2],p[icount+3]);
	*/
    		icount = icount + 3;
			t = t + step;
		
		}
}

// void Nurbs::RationalBSplineCurve( uint numPoints, uint kOrder, uint numCurvPoints, Vector3f& ctrlPoints 
// 								, const std::vector<float>& weights, Vector3f& curvePoints)
// {
// 	uint numKnots = numPoints + kOrder;
// 	std::vector<float> nbasis;
// 	std::vector<int> knots;
// 	int i;
// 
// 	for(i = 0; i <= numPoints; i++){
// 		nbasis[i] = 0.;
// 	}
// 
// 	for(i = 0; i <= numKnots; i++){
// 		knots[i] = 0.;
// 	}
// 
// 	/* generate the uniform periodic knot vector */
// 	GenerateUniformKnots( numKnots, kOrder, knots );
// 
// 	int icount = 0;
// 	std::vector<int> knotPoints;
// 	/*    calculate the points on the rational B-spline curve */
// 	int nplusc;
// 	float t = kOrder-1;
// 	float step = ((float)((numPoints)-(kOrder-1)))/((float)(numCurvPoints-1));	
// 
// 	for (int i1 = 1; i1<= numCurvPoints; i1++){
// 
// 		if ((float)knotPoints[nplusc] - t < 5e-6){
// 			t = (float)knotPoints[nplusc];
// 		}
// 		
// 	RationalBasis(kOrder,t,numPoints,knotPoints,weights,nbasis);      /* generate the basis function for this value of t */
// }
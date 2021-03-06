/*
 * Copyright (c) The Shogun Machine Learning Toolbox
 * Written (w) 2014 Wu Lin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Shogun Development Team.
 *
 *
 * Code adapted from 
 * https://github.com/emtiyaz/VariationalApproxExample
 *
 * and the reference paper is
 * Marlin, Benjamin M., Mohammad Emtiyaz Khan, and Kevin P. Murphy.
 * "Piecewise Bounds for Estimating Bernoulli-Logistic Latent Gaussian Models." ICML. 2011.
 *
 * 
 */

#include <shogun/lib/config.h>

#ifdef HAVE_EIGEN3

#include <shogun/labels/BinaryLabels.h>
#include <shogun/machine/gp/LogitVariationalPiecewiseBoundLikelihood.h>
#include <shogun/mathematics/Math.h>
#include <gtest/gtest.h>

using namespace shogun;

SGMatrix<float64_t> init_bound()
{
	//load('llp.mat'); from the Matlab code example.m 
	index_t row = 20;
	index_t col= 5;
	SGMatrix<float64_t> bound(row, col);

	bound(0,0)=0.000188712193000;
	bound(1,0)=0.028090310300000;
	bound(2,0)=0.110211757000000;
	bound(3,0)=0.232736440000000;
	bound(4,0)=0.372524706000000;
	bound(5,0)=0.504567936000000;
	bound(6,0)=0.606280283000000;
	bound(7,0)=0.666125432000000;
	bound(8,0)=0.689334264000000;
	bound(9,0)=0.693147181000000;
	bound(10,0)=0.693147181000000;
	bound(11,0)=0.689334264000000;
	bound(12,0)=0.666125432000000;
	bound(13,0)=0.606280283000000;
	bound(14,0)=0.504567936000000;
	bound(15,0)=0.372524706000000;
	bound(16,0)=0.232736440000000;
	bound(17,0)=0.110211757000000;
	bound(18,0)=0.028090310400000;
	bound(19,0)=0.000188712000000;

	bound(0,1)=0;
	bound(1,1)=0.006648614600000;
	bound(2,1)=0.034432684600000;
	bound(3,1)=0.088701969900000;
	bound(4,1)=0.168024214000000;
	bound(5,1)=0.264032863000000;
	bound(6,1)=0.360755794000000;
	bound(7,1)=0.439094482000000;
	bound(8,1)=0.485091758000000;
	bound(9,1)=0.499419205000000;
	bound(10,1)=0.500580795000000;
	bound(11,1)=0.514908242000000;
	bound(12,1)=0.560905518000000;
	bound(13,1)=0.639244206000000;
	bound(14,1)=0.735967137000000;
	bound(15,1)=0.831975786000000;
	bound(16,1)=0.911298030000000;
	bound(17,1)=0.965567315000000;
	bound(18,1)=0.993351385000000;
	bound(19,1)=1.000000000000000;

	bound(0,2)=0;
	bound(1,2)=0.000397791059000;
	bound(2,2)=0.002753100850000;
	bound(3,2)=0.008770186980000;
	bound(4,2)=0.020034759300000;
	bound(5,2)=0.037511596000000;
	bound(6,2)=0.060543032900000;
	bound(7,2)=0.086256780600000;
	bound(8,2)=0.109213531000000;
	bound(9,2)=0.123026104000000;
	bound(10,2)=0.123026104000000;
	bound(11,2)=0.109213531000000;
	bound(12,2)=0.086256780600000;
	bound(13,2)=0.060543032900000;
	bound(14,2)=0.037511596000000;
	bound(15,2)=0.020034759300000;
	bound(16,2)=0.008770186980000;
	bound(17,2)=0.002753100850000;
	bound(18,2)=0.000397791059000;
	bound(19,2)=0;

	bound(0,3)=-CMath::INFTY;
	bound(1,3)=-8.575194939999999;
	bound(2,3)=-5.933689180000000;
	bound(3,3)=-4.525933600000000;
	bound(4,3)=-3.528107790000000;
	bound(5,3)=-2.751548540000000;
	bound(6,3)=-2.097898790000000;
	bound(7,3)=-1.519690830000000;
	bound(8,3)=-0.989533382000000;
	bound(9,3)=-0.491473077000000;
	bound(10,3)=0;
	bound(11,3)=0.491473077000000;
	bound(12,3)=0.989533382000000;
	bound(13,3)=1.519690830000000;
	bound(14,3)=2.097898790000000;
	bound(15,3)=2.751548540000000;
	bound(16,3)=3.528107790000000;
	bound(17,3)=4.525933600000000;
	bound(18,3)=5.933689180000000;
	bound(19,3)=8.575194939999999;

	bound(0,4)=-8.575194939999999;
	bound(1,4)=-5.933689180000000;
	bound(2,4)=-4.525933600000000;
	bound(3,4)=-3.528107790000000;
	bound(4,4)=-2.751548540000000;
	bound(5,4)=-2.097898790000000;
	bound(6,4)=-1.519690830000000;
	bound(7,4)=-0.989533382000000;
	bound(8,4)=-0.491473077000000;
	bound(9,4)=0;
	bound(10,4)=0.491473077000000;
	bound(11,4)=0.989533382000000;
	bound(12,4)=1.519690830000000;
	bound(13,4)=2.097898790000000;
	bound(14,4)=2.751548540000000;
	bound(15,4)=3.528107790000000;
	bound(16,4)=4.525933600000000;
	bound(17,4)=5.933689180000000;
	bound(18,4)=8.575194939999999;
	bound(19,4)= CMath::INFTY;

	return bound;
}

TEST(LogitVariationalPiecewiseBoundLikelihood,get_variational_expection)
{
	float64_t rel_tolorance = 1e-2;
	float64_t abs_tolorance;

	SGMatrix<float64_t> bound = init_bound();

	const index_t dim = 10;
	SGVector<float64_t> y(dim);
	SGVector<float64_t> m(dim);
	SGVector<float64_t> v(dim);

	y[0] = 1;
	y[1] = 1;
	y[2] = 1;
	y[3] = 1;
	y[4] = 1;
	y[5] = -1;
	y[6] = -1;
	y[7] = -1;
	y[8] = -1;
	y[9] = -1;

	m[0] = 0.1;
	m[1] = 0.5;
	m[2] = 1;
	m[3] = 2;
	m[4] = 4;
	m[5] = 8;
	m[6] = 16;
	m[7] = 32;
	m[8] = 64;
	m[9] = 128;

	v[0] = 0.01;
	v[1] = 0.04;
	v[2] = 0.25;
	v[3] = 0.16;
	v[4] = 1;
	v[5] = 4;
	v[6] = 16;
	v[7] = 49;
	v[8] = 64;
	v[9] = 625;

	CLogitVariationalPiecewiseBoundLikelihood *lik = new CLogitVariationalPiecewiseBoundLikelihood();
	lik->set_variational_bound(bound);
	CBinaryLabels* lab = new CBinaryLabels(y);
	lik->set_variational_distribution(m, v, lab);

	SGVector<float64_t> fi = lik->get_variational_expection();

	// comparison of the result with result from the Matlab code
	abs_tolorance = CMath::get_abs_tolorance(-0.6456754556952, rel_tolorance);
	EXPECT_NEAR(fi[0],  -0.6456754556952,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.4788252132355, rel_tolorance);
	EXPECT_NEAR(fi[1],  -0.4788252132355,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.3376385737846, rel_tolorance);
	EXPECT_NEAR(fi[2],  -0.3376385737846,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.1355429430892, rel_tolorance);
	EXPECT_NEAR(fi[3],  -0.1355429430892,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.0291926624830, rel_tolorance);
	EXPECT_NEAR(fi[4],  -0.0291926624830,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-8.0024833587412, rel_tolorance);
	EXPECT_NEAR(fi[5],  -8.0024833587412,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-16.0003769229306, rel_tolorance);
	EXPECT_NEAR(fi[6],  -16.0003769229306,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-32.0001965353636, rel_tolorance);
	EXPECT_NEAR(fi[7],  -32.0001965353636,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-64.0001887120000, rel_tolorance);
	EXPECT_NEAR(fi[8],  -64.0001887120000,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-128.0001894653420, rel_tolorance);
	EXPECT_NEAR(fi[9],  -128.0001894653420,  abs_tolorance);

	// clean up
	SG_UNREF(lab);
	SG_UNREF(lik);
}

TEST(LogitVariationalPiecewiseBoundLikelihood,get_variational_first_derivative_wrt_sigma2)
{
	float64_t rel_tolorance = 1e-2;
	float64_t abs_tolorance;

	SGMatrix<float64_t> bound = init_bound();

	const index_t dim = 10;
	SGVector<float64_t> y(dim);
	SGVector<float64_t> m(dim);
	SGVector<float64_t> v(dim);

	y[0] = 1;
	y[1] = 1;
	y[2] = 1;
	y[3] = 1;
	y[4] = 1;
	y[5] = -1;
	y[6] = -1;
	y[7] = -1;
	y[8] = -1;
	y[9] = -1;

	m[0] = 0.1;
	m[1] = 0.5;
	m[2] = 1;
	m[3] = 2;
	m[4] = 4;
	m[5] = 8;
	m[6] = 16;
	m[7] = 32;
	m[8] = 64;
	m[9] = 128;

	v[0] = 0.01;
	v[1] = 0.04;
	v[2] = 0.25;
	v[3] = 0.16;
	v[4] = 1;
	v[5] = 4;
	v[6] = 16;
	v[7] = 49;
	v[8] = 64;
	v[9] = 625;

	CLogitVariationalPiecewiseBoundLikelihood *lik = new CLogitVariationalPiecewiseBoundLikelihood();
	lik->set_variational_bound(bound);
	CBinaryLabels* lab = new CBinaryLabels(y);
	lik->set_variational_distribution(m, v, lab);

	TParameter* s2_param=lik->m_gradient_parameters->get_parameter("sigma2");

	SGVector<float64_t> gvi = lik->get_variational_first_derivative(s2_param);

	// comparison of the result with result from the Matlab code
	abs_tolorance = CMath::get_abs_tolorance(-0.124427581470330, rel_tolorance);
	EXPECT_NEAR(gvi[0],  -0.124427581470330,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.116464777495544, rel_tolorance);
	EXPECT_NEAR(gvi[1],  -0.116464777495544,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.095944910771785, rel_tolorance);
	EXPECT_NEAR(gvi[2],  -0.095944910771785,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.053928836060417, rel_tolorance);
	EXPECT_NEAR(gvi[3],  -0.053928836060417,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.013150889239670, rel_tolorance);
	EXPECT_NEAR(gvi[4],  -0.013150889239670,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.001100858445787, rel_tolorance);
	EXPECT_NEAR(gvi[5],  -0.001100858445787,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.000067933801262, rel_tolorance);
	EXPECT_NEAR(gvi[6],  -0.000067933801262,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.000001623384590, rel_tolorance);
	EXPECT_NEAR(gvi[7],  -0.000001623384590,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.00000000000000220044, rel_tolorance);
	EXPECT_NEAR(gvi[8],  -0.00000000000000220044, abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.000000017317396, rel_tolorance);
	EXPECT_NEAR(gvi[9],  -0.000000017317396,  abs_tolorance);

	// clean up
	SG_UNREF(lab);
	SG_UNREF(lik);
}

TEST(LogitVariationalPiecewiseBoundLikelihood,get_variational_first_derivative_wrt_mu)
{
	float64_t rel_tolorance = 1e-2;
	float64_t abs_tolorance;

	SGMatrix<float64_t> bound = init_bound();

	const index_t dim = 10;
	SGVector<float64_t> y(dim);
	SGVector<float64_t> m(dim);
	SGVector<float64_t> v(dim);

	y[0] = 1;
	y[1] = 1;
	y[2] = 1;
	y[3] = 1;
	y[4] = 1;
	y[5] = -1;
	y[6] = -1;
	y[7] = -1;
	y[8] = -1;
	y[9] = -1;

	m[0] = 0.1;
	m[1] = 0.5;
	m[2] = 1;
	m[3] = 2;
	m[4] = 4;
	m[5] = 8;
	m[6] = 16;
	m[7] = 32;
	m[8] = 64;
	m[9] = 128;

	v[0] = 0.01;
	v[1] = 0.04;
	v[2] = 0.25;
	v[3] = 0.16;
	v[4] = 1;
	v[5] = 4;
	v[6] = 16;
	v[7] = 49;
	v[8] = 64;
	v[9] = 625;

	CLogitVariationalPiecewiseBoundLikelihood *lik = new CLogitVariationalPiecewiseBoundLikelihood();
	lik->set_variational_bound(bound);
	CBinaryLabels* lab = new CBinaryLabels(y);
	lik->set_variational_distribution(m, v, lab);

	TParameter* mu_param=lik->m_gradient_parameters->get_parameter("mu");

	SGVector<float64_t> gmi = lik->get_variational_first_derivative(mu_param);

	// comparison of the result with result from the Matlab code
	abs_tolorance = CMath::get_abs_tolorance(0.474998473339850, rel_tolorance);
	EXPECT_NEAR(gmi[0],  0.474998473339850,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(0.378585673900550, rel_tolorance);
	EXPECT_NEAR(gmi[1],  0.378585673900550,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(0.279385305091804, rel_tolorance);
	EXPECT_NEAR(gmi[2],  0.279385305091804,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(0.125526678446964, rel_tolorance);
	EXPECT_NEAR(gmi[3],  0.125526678446964,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(0.028103686914264, rel_tolorance);
	EXPECT_NEAR(gmi[4],  0.028103686914264,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.997696157382387, rel_tolorance);
	EXPECT_NEAR(gmi[5],  -0.997696157382387,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.999836111483197, rel_tolorance);
	EXPECT_NEAR(gmi[6],  -0.999836111483197,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.999994859133653, rel_tolorance);
	EXPECT_NEAR(gmi[7],  -0.999994859133653,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.999999999999995, rel_tolorance);
	EXPECT_NEAR(gmi[8],  -0.999999999999995,  abs_tolorance);
	abs_tolorance = CMath::get_abs_tolorance(-0.999999835858964, rel_tolorance);
	EXPECT_NEAR(gmi[9],  -0.999999835858964,  abs_tolorance);

	// clean up
	SG_UNREF(lab);
	SG_UNREF(lik);
}

#endif /* HAVE_EIGEN3 */

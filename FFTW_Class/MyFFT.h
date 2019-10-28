#pragma once
#include <vector>
#include <complex>
#include <iostream>
#include "fftw3.h"

using namespace std;

typedef vector<double> vectord;
typedef complex<double> complexd;
typedef vector<complexd> vectorcd;
typedef vector<vectorcd> vectorMcd;

class MyFFT
{
private:
	int Nfft;
	int Nfft_r;//ÐÐÊý
	fftw_complex *_fftIn;
	fftw_complex *_fftOut;
	fftw_plan _fftPlan;
public:
	MyFFT()
	{
		Nfft = 0;
		_fftIn = nullptr;
		_fftOut = nullptr;
	}
	MyFFT(int N, int flag)
	{
		Nfft = N;
		_fftIn = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* Nfft);
		_fftOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* Nfft);
		_fftPlan = fftw_plan_dft_1d(Nfft, _fftIn, _fftOut, flag, FFTW_ESTIMATE);
		//_fftPlan = fftw_plan_dft_r2c_1d(Nfft, _fftIn, _fftOut, FFTW_ESTIMATE);
	}
	MyFFT(int N, int Nc, int flag)//2Î¬
	{
		Nfft = N;
		Nfft_r = Nc;
		_fftIn = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* Nfft * Nfft_r);
		_fftOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* Nfft* Nfft_r);
		_fftPlan = fftw_plan_dft_2d(Nfft, Nfft_r, _fftIn, _fftOut, flag, FFTW_ESTIMATE);
	}
	~MyFFT()
	{
		if (_fftIn != nullptr)
		fftw_free(_fftIn);
		if (_fftOut != nullptr)
		fftw_free(_fftOut);
		fftw_destroy_plan(_fftPlan);
		//fftw_cleanup();
	}

	//void PSD(double in[], double out[])
	//{
	//	for (auto i = 0; i<Nfft; i++)
	//		_fftIn[i] = in[i];

	//	fftw_execute(_fftPlan);

	//	for (auto i = 0; i<(Nfft / 2 + 1); i++)
	//		out[i] = (_fftOut[i][0] * _fftOut[i][0] + _fftOut[i][1] * _fftOut[i][1]) / Nfft;
	//}

	void c2c(fftw_complex in[], fftw_complex out[])
	{
		for (auto i = 0; i < Nfft; i++)
		{
			_fftIn[i][0] = in[i][0];
			_fftIn[i][1] = in[i][1];
		}
			
		fftw_execute(_fftPlan);

		for (auto i = 0; i < Nfft; i++)
		{
			out[i][0] = _fftOut[i][0];
			out[i][1] = _fftOut[i][1];
 		}
	}

	void c2c(vectorcd in, fftw_complex out[])
	{
		for (auto i = 0; i < Nfft; i++)
		{
			_fftIn[i][0] = in[i].real();
			_fftIn[i][1] = in[i].imag();
		}

		fftw_execute(_fftPlan);

		for (auto i = 0; i < Nfft; i++)
		{
			out[i][0] = _fftOut[i][0];
			out[i][1] = _fftOut[i][1];
		}
	}

	void c2c(vectorcd in, vectorcd& out)
	{
		for (auto i = 0; i < Nfft; i++)
		{
			_fftIn[i][0] = in[i].real();
			_fftIn[i][1] = in[i].imag();
		}

		fftw_execute(_fftPlan);

		for (auto i = 0; i < Nfft; i++)
			out[i] = complexd(_fftOut[i][0], _fftOut[i][1]);
	}

	void c2c(double in[], fftw_complex out[])
	{
		for (auto i = 0; i < Nfft; i++)
		{
			_fftIn[i][0] = in[i];
			_fftIn[i][1] = 0;
		}

		fftw_execute(_fftPlan);

		for (auto i = 0; i < Nfft; i++)
		{
			out[i][0] = _fftOut[i][0];
			out[i][1] = _fftOut[i][1];
		}
	}

	void c2c_2d(vectorMcd in, vectorMcd& out)
	{
		for (auto i = 0; i < Nfft; i++)
			for(auto j = 0; j < Nfft_r; ++j)
			{
				_fftIn[i + j*Nfft_r][0] = in[i][j].real();
				_fftIn[i + j*Nfft_r][1] = in[i][j].imag();
			}

		fftw_execute(_fftPlan);

		for (auto i = 0; i < Nfft; i++)
			for (auto j = 0; j < Nfft_r; ++j)
				out[i][j] = complexd(_fftOut[i + j*Nfft_r][0], _fftOut[i + j*Nfft_r][1]);
	}


};
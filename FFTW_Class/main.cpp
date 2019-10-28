#include "fftw3.h"
#include <stdio.h>

#include "MyFFT.h"
#define N 8


int main()
{
	MyFFT FFT(8, FFTW_FORWARD);
	vectorcd va = { 1, 2, 3, 4, 5, 6, 7, 8 }, vc;
	double a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	//double *b = new double(8);
	fftw_complex *b, *c;
	b = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * 8);
	c = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * 8);
	FFT.c2c(va, b);

	MyFFT IFFT(8, FFTW_BACKWARD);
	IFFT.c2c(b, c);

	MyFFT FFT2(4, 4, FFTW_FORWARD);
	MyFFT IFFT2(4, 4, FFTW_BACKWARD);
	vectorcd d = { 2, 3, 4, 1 };
	vectorMcd md = { d, d, d, d };
	vectorMcd me(4, vectorcd(4)), mf(4, vectorcd(4));
	FFT2.c2c_2d(md, me);
	IFFT2.c2c_2d(me, mf);

	for (auto i = 0; i < me.size(); ++i)
	{
		for (auto j = 0; j < me[0].size(); ++j)
			cout << me[i][j] << "\t";
		cout << endl;
	}
	for (auto i = 0; i < me.size(); ++i)
	{
		for (auto j = 0; j < me[0].size(); ++j)
			cout << mf[i][j] << "\t";
		cout << endl;
	}

	//for (auto i = 0; i<8; i++)/*OUTPUT*/
	//{
	//	printf("%f,%fi\n", b[i][0], b[i][1]);
	//}
	//printf("\n");

	//for (auto i = 0; i<8; i++)/*OUTPUT*/
	//{
	//	printf("%f,%fi\n", c[i][0] / 8, c[i][1] / 8);
	//}
	//printf("\n");
	fftw_free(b);
	fftw_free(c);

	//int i = 0;
	//fftw_complex *din, *dout;
	//fftw_plan p;
	//din = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	//dout = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	//if ((din == NULL) || (dout == NULL))
	//{
	//	printf("Error:insufficient available memory\n");
	//}
	//else
	//{
	//	for (i = 0; i<N; i++)/*测试数据*/
	//	{
	//		din[i][0] = i + 1;
	//		din[i][1] = i;
	//	}
	//}

	//p = fftw_plan_dft_1d(N, din, dout, FFTW_FORWARD, FFTW_ESTIMATE);
	////fftw_execute_dft(p, din, dout); /* repeat as needed */
	////fftw_execute(p); /* repeat as needed */

	//for (i = 0; i<N; i++)/*INPUT*/
	//{
	//	printf("%f,%fi\n", din[i][0], din[i][1]);
	//}
	//printf("\n");
	//for (i = 0; i<N; i++)/*OUTPUT*/
	//{
	//	printf("%f,%fi\n", dout[i][0], dout[i][1]);
	//}


	//for (i = 0; i<N; i++)/*测试数据*/
	//{
	//	din[i][0] = i + 2;
	//	din[i][1] = 0;
	//}

	//fftw_execute_dft(p, din, dout); /* repeat as needed */

	//for (i = 0; i<N; i++)/*INPUT*/
	//{
	//	printf("%f,%fi\n", din[i][0], din[i][1]);
	//}
	//printf("\n");
	//for (i = 0; i<N; i++)/*OUTPUT*/
	//{
	//	printf("%f,%fi\n", dout[i][0], dout[i][1]);
	//}

	//fftw_destroy_plan(p);
	//if (din != NULL) fftw_free(din);
	//if (dout != NULL) fftw_free(dout);



	getchar();
	return 0;
}

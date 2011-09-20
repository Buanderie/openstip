#include "CPUSTIPDetector.h"

#include <iostream>

//OpenMP
#include <omp.h>

using namespace std;
using namespace monadic::openstip;

#define CPUDET CCPUSTIPDetector

CPUDET::CPUDET()
{

}

CPUDET::~CPUDET()
{

}

void CPUDET::computeIntegralVolume( monadic::openstip::CSpaceTimeBuffer& stbuffer )
{
	//Retrieve raw float array
	const int arraySize =	stbuffer.getLength() *
							stbuffer.getFrameWidth() *
							stbuffer.getFrameHeight();
	float * raw = new float[ arraySize ];
	stbuffer.getRawData( raw );

	//allocate memory for the integral volume
	float * out = new float[ arraySize ];

	int height	= stbuffer.getFrameHeight();
	int width	= stbuffer.getFrameWidth();
	int length	= stbuffer.getLength();

	omp_set_num_threads( length );

	//For each time slice
	//Parallelisable OpenMP
	#pragma omp parallel for
	for( int k = 0; k < stbuffer.getLength(); ++k )
	{
		int idk = k * width * height;
		
		//int ID = omp_get_thread_num();
		//cout << "Thread_ID=" << ID << endl;

		for( int i = 0; i < width; ++i )
			out[ idk + i ] = 0.0f;

		for( int i = 1; i < height; ++i )
		{
			out[ idk + i*width ] = 0.0f; 
			float sum = 0.0f;
			for( int j = 0; j < width-1; ++j )
			{
				sum += raw[ idk + (j + (i-1)*width) ];
				out[ idk + (j + i*width + 1) ] = sum + out[ idk + (j + (i-1)*width + 1) ];
			}
		}
	}

	//Integration over t
	//Parallelisable OpenMP
	#pragma omp parallel for
	for( int i = 0; i < height; ++i )
	{
		//int ID = omp_get_thread_num();
		//cout << "Thread_ID=" << ID << endl;

		//Idem
		for( int j = 0; j < width; ++j )
		{
			for( int k = 1; k < length; ++k )
			{
				int idk_t1 = k * width * height;
				int idk_t0 = (k-1) * width * height;
				out[ idk_t1 + i*width + j ] += out[ idk_t0 + i*width + j ];
			}
		}
	}

	//for( int i = 0; i < arraySize; ++i )
	//	cout << "out[" << i << "]=" << out[i] << endl;

	delete[] raw;
	delete[] out;
}

#undef CPUDET
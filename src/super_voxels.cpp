//============================================================================
// Name        : super_voxels.cpp
// Author      : Oscar Cuadros Linares
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageSeriesReader.h"

#include <iostream>
using namespace std;

int main()
{
	typedef signed short input_pixel_t;
	typedef itk::Image<input_pixel_t, 3> image_t;
	typedef itk::ImageFileReader<image_t> reader_t;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

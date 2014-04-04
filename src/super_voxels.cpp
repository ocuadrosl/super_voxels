//============================================================================
// Name        : super_voxels.cpp
// Author      : Oscar Cuadros Linares
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Regular_grid.h"
#include "Super_voxels.h"

#include <iostream>
using namespace std;

int main()
{
	sv::Regular_grid* r_grid = new sv::Regular_grid();

	sv::Super_voxels*  super_voxels = new sv::Super_voxels(r_grid);

	super_voxels->read_volume("../volumes/prostata/prostata_lai.nii");




	return 0;
}

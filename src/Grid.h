/*
 * Grid.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef GRID_H_
#define GRID_H_

#include "Typedefs.h"
#include "Super_voxel.h"

using namespace std;

namespace sv
{

class Grid
{
public:
	Grid()
	{
	}
	;
	virtual ~Grid()
	{
	}
	;
	virtual void process(volume_tp __volume, vector<Super_voxel*>* __super_voxels)=0;
	virtual int mean_sv_size()=0;
};

} /* namespace sv */

#endif /* GRID_H_ */

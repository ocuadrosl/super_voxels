/*
 * Grid.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef GRID_H_
#define GRID_H_

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
	virtual void process()=0;
};

} /* namespace sv */

#endif /* GRID_H_ */

/*
 * Regular_grid.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef REGULAR_GRID_H_
#define REGULAR_GRID_H_

#include "Grid.h"
#include <iostream>

using namespace std;
namespace sv
{

class Regular_grid: public Grid
{
public:
	Regular_grid(){};
	void process();

};

void Regular_grid::process()
{
	cout << "regular Grid" << endl;
}

} /* namespace sv */

#endif /* REGULAR_GRID_H_ */

/*
 * Super_voxels.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef SUPER_VOXELS_H_
#define SUPER_VOXELS_H_

#include "Grid.h"
#include "Typedefs.h"

#include "itkImage.h"
#include "itkImageFileReader.h"

#include <string>

using namespace std;

namespace sv
{
/*
 * Super Voxels Class
 * @author Oscar
 *
 */
class Super_voxels
{
public:
	Super_voxels(Grid* __grid);
	~Super_voxels();

	void read_volume(string __file_name);

private:
	Grid* _grid; //initial grid type
	volume_tp _volume; // itk image

};

void Super_voxels::read_volume(string __file_name)
{

	typedef itk::ImageFileReader<volume_t> reader_t;

	reader_t::Pointer reader = reader_t::New();

	reader->SetFileName(__file_name); //pinche error que no es error

	try
	{
		reader->Update();
	} catch (itk::ExceptionObject & e)
	{
		std::cerr << "exception in file reader " << std::endl;
		std::cerr << e << std::endl;
	}

	_volume = reader->GetOutput();
	//

	////allocate matrix labels
	//image_t::RegionType region = _itk_image->GetLargestPossibleRegion();
	//_image_size = region.GetSize();

	cout << "volume read [ok]" << endl;

}

Super_voxels::Super_voxels(Grid* __grid)
{
	_grid = __grid;
	_grid->process();

}

}
#endif /* SUPER_VOXELS_H_ */

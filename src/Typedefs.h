/*
 * Typedefs.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include "itkImage.h"

namespace sv
{

/*itk typedefs
 *
 * t=type
 * tp= pointer type
 */

typedef signed short pixel_t;
typedef itk::Image<pixel_t, 3> volume_t;
typedef volume_t::Pointer volume_tp;

} /* namespace sv */

#endif /* TYPEDEFS_H_ */

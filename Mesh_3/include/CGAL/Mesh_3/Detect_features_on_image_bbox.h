// Copyright (c) 2022 GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Laurent Rineau, Jane Tournois
//
//******************************************************************************
//
//******************************************************************************

#ifndef CGAL_MESH_3_DETECT_FEATURES_ON_IMAGE_BBOX_H
#define CGAL_MESH_3_DETECT_FEATURES_ON_IMAGE_BBOX_H

#include <CGAL/license/Mesh_3.h>

#include <CGAL/Mesh_3/polylines_to_protect.h>

#include <vector>


namespace CGAL
{
namespace Mesh_3
{
namespace internal
{

template<typename Point>
std::vector<std::vector<Point>>
detect_features_on_bbox(const CGAL::Image_3& image)
{
  using Point_3 = Point;
  using Polyline_type = std::vector<Point_3>;
  using Polylines = std::vector<Polyline_type>;

  Polylines polylines_on_bbox;

  CGAL_IMAGE_IO_CASE(image.image(),
    {
      (CGAL::polylines_to_protect<Point_3, Word>(image, polylines_on_bbox));
      return polylines_on_bbox;
    }
  );
  CGAL_error_msg("This place should never be reached, because it would mean "
                 "the image word type is a type that is not handled by "
                 "CGAL_ImageIO.");
  return Polylines();
}

}// namespace internal

/*!
* \ingroup PkgMesh3FeatureDetection
*
* Functor for feature detection in labeled images.
*/
struct Detect_features_on_image_bbox
{
public:

  /*!
  * detects and constructs the polylines that lie at the
  * intersection of two or more subdomains and the bounding box
  * of the input labeled image.
  *
  * Each subdomain inside the bounding box
  * of the input labeled image is defined as the set of voxels
  * with the same value. The outside of the bounding box
  * of the image is considered as a subdomain with voxel value
  * `value_outside` (see \link CGAL::Labeled_mesh_domain_3::create_labeled_image_mesh_domain `create_labeled_image_mesh_domain()` \endlink
  * parameters description). Hence, this function computes
  * intersections of "internal" subdomains with the image bounding box.
  *
  * \tparam Point class model of `Kernel::Point_3`. The point type
  * must match the triangulation point type.
  *
  * \param image the input image
  *
  * \returns a `std::vector<std::vector<Point>>`
  * containing the constructed polylines for later feature protection.
  */
  template<typename Point>
  std::vector<std::vector<Point>>
  operator()(const CGAL::Image_3& image) const
  {
    return internal::detect_features_on_bbox<Point>(image);
  }
};

}//end namespace Mesh_3
}//end namespace CGAL


#endif //CGAL_MESH_3_DETECT_FEATURES_ON_IMAGE_BBOX_H

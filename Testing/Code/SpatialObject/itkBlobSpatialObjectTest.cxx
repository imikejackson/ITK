/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkBlobSpatialObjectTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

/**
 * This is a test file for the itkBlobSpatialObject class.
 */

#include "itkBlobSpatialObject.h"
#include "itkSpatialObjectPoint.h"

int itkBlobSpatialObjectTest(int, char**)
{
  typedef itk::BlobSpatialObject<3>    BlobType;
  typedef BlobType::Pointer            BlobPointer;
  typedef itk::SpatialObjectPoint<3>   BlobPointType;

  std::cout<<"=================================="<<std::endl;
  std::cout<<"Testing BlobSpatialObject:"<<std::endl<<std::endl;

  BlobType::PointListPointer list  = new BlobType::PointListType();

  for( unsigned int i=0; i<10; i++)
  {
    BlobPointType::Pointer p = BlobPointType::New();
    p->SetPosition(i,i+1,i+2);
    list->push_back(p);
  }

  // Create a Blob Spatial Object
  BlobPointer blob = BlobType::New();
  blob->GetProperty()->SetName("Blob 1");
  blob->SetId(1);
  blob->SetPoints(list);
  blob->ComputeBounds();

  // Number of points
  std::cout << "Testing Consistency: " << std::endl;
  std::cout << "Number of Points: ";

  if(blob->GetPoints()->size() != 10)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  else
  { 
    std::cout<<"[PASSED]"<<std::endl;
  }

  // Point consistency
  std::cout << "Point consistency: ";

  BlobType::PointListType::const_iterator it = blob->GetPoints()->begin();

  unsigned int i=0;
  while(it != blob->GetPoints()->end())
  {
    for(unsigned int d=0;d<3;d++)
    {
      if((*it)->GetPosition()[d]!=i+d)
      {
        std::cout<<"[FAILED]"<<std::endl;
        return EXIT_FAILURE;
      }
    }
    it++;
    i++;
  }

  std::cout<<"[PASSED]"<<std::endl;

  // Point consistency
  std::cout << "Is Inside: ";
  itk::Point<double,3> in;
  in[0]=1;in[1]=2;in[2]=3;
  itk::Point<double,3> out;
  out[0]=0;out[1]=0;out[2]=0;

  if(!blob->IsInside(in))
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }

  if(blob->IsInside(out))
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }

  std::cout<<"[PASSED]"<<std::endl;
  return EXIT_SUCCESS;

}

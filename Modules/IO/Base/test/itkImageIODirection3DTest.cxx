/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"

#define SPECIFIC_IMAGEIO_MODULE_TEST

int itkImageIODirection3DTest( int ac, char * av[] )
{

  if( ac < 11 )
    {
    std::cerr << "Usage: " << av[0]
    << " InputImage  (9 direction cosines terms) "
    << "[outputImage]"
    << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 3;
  typedef unsigned char PixelType;

  typedef itk::Image<PixelType, Dimension>    ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( av[1] );

  try
    {
    reader->Update();
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  ImageType::ConstPointer image = reader->GetOutput();

  ImageType::DirectionType directionCosines = image->GetDirection();

  std::cout << directionCosines << std::endl;

  unsigned int element = 2;
  const double tolerance = 1e-5;

  for( unsigned int row=0; row < Dimension; ++row )
    {
    for( unsigned int col = 0; col < Dimension; ++col )
      {
      const double expectedValue = atof( av[ element++ ] );
      const double currentValue = directionCosines[row][col];
      const double difference = currentValue - expectedValue;
      if( vnl_math_abs( difference ) > tolerance )
        {
        std::cerr << "Error: " << std::endl;
        std::cerr << "Expected " << expectedValue << std::endl;
        std::cerr << "Read     " << currentValue << std::endl;
        return EXIT_FAILURE;
        }
      }
    }


  if( ac > 11 )
    {
    typedef itk::ImageFileWriter< ImageType >   WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( av[11] );
    writer->SetInput( reader->GetOutput() );

    try
      {
      writer->Update();
      }
    catch (itk::ExceptionObject & e)
      {
      std::cerr << e << std::endl;
      return EXIT_FAILURE;
      }
    }


  return EXIT_SUCCESS;
}

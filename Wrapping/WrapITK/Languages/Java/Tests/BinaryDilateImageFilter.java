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

/**
 *  Example on the use of the BinaryDilateImageFilter
 *
 */

import org.itk.base.*;
import org.itk.io.*;
import org.itk.binarymorphology.*;
import org.itk.simplefilters.*;

public class BinaryDilateImageFilter
{
  public static void main( String argv[] )
  {
    System.out.println("BinaryDilateImageFilter Example");

    itkImageFileReaderIUC2 reader = new itkImageFileReaderIUC2();
    itkImageFileWriterIUC2 writer = new itkImageFileWriterIUC2();

    itkBinaryDilateImageFilterIUC2IUC2SE2 filter = new itkBinaryDilateImageFilterIUC2IUC2SE2();

    filter.SetInput( reader.GetOutput() );
    writer.SetInput( filter.GetOutput() );

    reader.SetFileName( argv[0] );
    writer.SetFileName( argv[1] );

    itkSize2 radius = new itkSize2();
    radius.Fill( 5 );
    itkFlatStructuringElement2 element = itkFlatStructuringElement2.Ball( radius );

    filter.SetKernel( element );

    short value = 200;

    filter.SetDilateValue( value );

    writer.Update();
  }

}

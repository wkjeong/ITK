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
#ifndef __itkComplexToImaginaryImageFilter_h
#define __itkComplexToImaginaryImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "vnl/vnl_math.h"

namespace itk
{
/** \class ComplexToImaginaryImageFilter
 * \brief Computes pixel-wise the imaginary part of a complex image.
 *
 * \ingroup IntensityImageFilters  Multithreaded
 * \ingroup ITK-ImageIntensity
 */
namespace Functor
{
template< class TInput, class TOutput >
class ComplexToImaginary
{
public:
  ComplexToImaginary() {}
  ~ComplexToImaginary() {}
  bool operator!=(const ComplexToImaginary &) const
  {
    return false;
  }

  bool operator==(const ComplexToImaginary & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput & A) const
  {
    return (TOutput)( A.imag() );
  }
};
}

template< class TInputImage, class TOutputImage >
class ITK_EXPORT ComplexToImaginaryImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage, TOutputImage,
                           Functor::ComplexToImaginary<
                             typename TInputImage::PixelType,
                             typename TOutputImage::PixelType >   >
{
public:
  /** Standard class typedefs. */
  typedef ComplexToImaginaryImageFilter Self;
  typedef UnaryFunctorImageFilter<
    TInputImage, TOutputImage,
    Functor::ComplexToImaginary< typename TInputImage::PixelType,
                                 typename TOutputImage::PixelType > > Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(ComplexToImaginaryImageFilter,
               UnaryFunctorImageFilter);

  typedef typename TInputImage::PixelType                     InputPixelType;
  typedef typename TOutputImage::PixelType                    OutputPixelType;
  typedef typename NumericTraits< InputPixelType >::ValueType InputPixelValueType;

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro( InputConvertibleToOutputCheck,
                   ( Concept::Convertible< InputPixelValueType, OutputPixelType > ) );
  /** End concept checking */
#endif
protected:
  ComplexToImaginaryImageFilter() {}
  virtual ~ComplexToImaginaryImageFilter() {}
private:
  ComplexToImaginaryImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                //purposely not implemented
};
} // end namespace itk

#endif

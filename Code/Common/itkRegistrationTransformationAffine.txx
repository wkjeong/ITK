/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkRegistrationTransformationAffine.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/

#include <itkExceptionObject.h>

namespace itk
{

/**
 * Constructor
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>
::RegistrationTransformationAffine()
{
  m_Parameters->Reserve( NDimensions * ( NDimensions + 1 ) );
}


/**
 * Constructor
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>
::RegistrationTransformationAffine( const Self & other )
{
  m_AffineTransform = other.m_AffineTransform;
}


/**
 * Assignment Operator
 */
template <unsigned int NDimensions>
const RegistrationTransformationAffine<NDimensions> &
RegistrationTransformationAffine<NDimensions>
::operator=( const Self & other )
{
  m_AffineTransform = other.m_AffineTransform;
  return *this;
}


/**
 * Transform a Point
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>::PointType
RegistrationTransformationAffine<NDimensions>
::Transform(const PointType & point )
{
  return m_AffineTransform.Transform( point );
}




/**
 * Transform a Vector
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>::VectorType
RegistrationTransformationAffine<NDimensions>
::Transform(const VectorType & vector )
{
  return m_AffineTransform.Transform( vector );
}


/**
 * Inverse Transform a Point
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>::PointType
RegistrationTransformationAffine<NDimensions>
::InverseTransform(const PointType & point )
{
  return m_AffineTransform.BackTransform( point );
}



/**
 * Inverse Transform a Vector
 */
template <unsigned int NDimensions>
RegistrationTransformationAffine<NDimensions>::VectorType
RegistrationTransformationAffine<NDimensions>
::InverseTransform(const VectorType & vector )
{
  return m_AffineTransform.BackTransform( vector );
}




/**
 * Set the transformation parameters
 */
template <unsigned int NDimensions>
void
RegistrationTransformationAffine<NDimensions>
::SetParameters(const ParametersType * parameters )
{

  if( parameters->Size() != m_Parameters->Size() )
  {
    throw ExceptionObject();
  }
  

  // Copy Parameters Vector
  ParametersType::ConstIterator it = parameters->Begin();
  ParametersType::Iterator      ot = m_Parameters->Begin();
  while( it != parameters->End() )
  {
    ot.Value() = it.Value();
    ++it;
    ++ot;
  }

  
  typename AffineTransformationType::MatrixType linear;
  typename AffineTransformationType::VectorType constant;
  
  ParametersType::ConstIterator pit = m_Parameters->Begin();

  // Transfer the linear part
  for(unsigned int row=0; row<NDimensions; row++) 
  {
    for(unsigned int col=0; col<NDimensions; col++) 
    {
      linear(row,col) = pit.Value();
      ++pit;
    }
  }

  // Transfer the constant part
  for(unsigned int i=0; i<NDimensions; i++) 
  {
    constant[i] = pit.Value();
    ++pit;
  }

  m_AffineTransform.SetLinearPart( linear);
  m_AffineTransform.SetConstantPart( constant );

}





} // end namespace itk

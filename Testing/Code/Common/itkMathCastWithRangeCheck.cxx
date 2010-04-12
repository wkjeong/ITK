/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMathCastWithRangeCheck.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkMath.h"
#include <iostream>
#include <cstdlib>

#include "itkNumericTraits.h"
#include "itkConceptChecking.h"
#include <iostream>
#include <cstdlib>


namespace 
{


// we validate the results against just converting the numbers to
// doubles. This will work for all integers less then 32-bit but is
// not always exact with larger integers.
template < typename T1, typename T2 >
bool DoCastWithRangeCheckTestVerify( const T2 value, const T1 = 0 )
{
  T1 ret;
  // tying to convert T2 to T1
  try 
    {
    ret = itk::Math::CastWithRangeCheck<T1>( value );
    // value should match
    if ( double(ret) != double(value) )
      {
      std::cout << "casting error with input value: " << static_cast<typename itk::NumericTraits<T2>::PrintType>(value) << " output value: " << static_cast<typename itk::NumericTraits<T1>::PrintType>(ret) << std::endl;
      return false;
      }
    }
  catch(...) 
    {
    // conversion should result in some overflow problem
    T1 retCheck =  static_cast<T1>( value );
    if ( double(retCheck) == double(value) )
      {
      std::cout << "unexpected exception with value: " << value << std::endl;
      return false;
      }
    
    }
  
  
  return true;
}


template < typename T1, typename T2 >
bool DoCastWithRangeCheckTestExulstive( const T1* = 0, const T2* = 0 )
{
  // test convert T2 to T1
  bool pass = true;
  for ( T2 i = itk::NumericTraits<T2>::NonpositiveMin();  i !=  itk::NumericTraits<T2>::max(); ++i )
    {
    pass &= DoCastWithRangeCheckTestVerify<T1, T2>( i );
    }

  return pass;
}

template < typename T1, typename T2 >
bool DoCastWithRangeCheckTest( const T1* = 0, const T2* = 0 )
{
  // test convert T2 to T1
  bool pass = true;
  pass &= DoCastWithRangeCheckTestVerify<T1, T2>( itk::NumericTraits<T2>::NonpositiveMin() );
  pass &= DoCastWithRangeCheckTestVerify<T1, T2>( itk::NumericTraits<T2>::max() );
  pass &= DoCastWithRangeCheckTestVerify<T1, T2>( itk::NumericTraits<T2>::Zero );
  pass &= DoCastWithRangeCheckTestVerify<T1, T2>( itk::NumericTraits<T2>::One );
  pass &= DoCastWithRangeCheckTestVerify<T1, T2>( static_cast<T2>(itk::NumericTraits<T2>::One*-1) );

  return pass;
}

template < typename T1 >
bool DoCastWithRangeCheckTestForTypes( const T1* = 0 )
{
  // call method for all type to be converted to type T1
  bool pass = true;

  pass &= DoCastWithRangeCheckTest<T1, unsigned char>();
  pass &= DoCastWithRangeCheckTest<T1, signed char>();
  pass &= DoCastWithRangeCheckTest<T1, unsigned short>();
  pass &= DoCastWithRangeCheckTest<T1, signed short>();
  pass &= DoCastWithRangeCheckTest<T1, unsigned int>();
  pass &= DoCastWithRangeCheckTest<T1, signed int>();
  pass &= DoCastWithRangeCheckTest<T1, unsigned long>(); 
  pass &= DoCastWithRangeCheckTest<T1, signed long>();
#ifdef ITK_USE_LONG_LONG
  pass &= DoCastWithRangeCheckTest<T1, unsigned long long>();
  pass &= DoCastWithRangeCheckTest<T1, signed long long>();
#endif
  return pass;
}
 
} // end namespace

int itkMathCastWithRangeCheckTest( int, char *[] )
{
  bool pass = true;
  
   try 
    {
    itk::Math::CastWithRangeCheck<short, int>( int(itk::NumericTraits<short>::max())+10 );
    pass = false;
    std::cout << "failed to through exception with " <<  int(itk::NumericTraits<short>::max())+10 << " to int ";
    }
   catch( ... )
     {
     std::cout << "caught exception as expected" << std::endl;
     }

  
  DoCastWithRangeCheckTestExulstive<signed char, unsigned char>();
  DoCastWithRangeCheckTestExulstive<unsigned char, signed char>();
  DoCastWithRangeCheckTestExulstive<unsigned char, signed short>();
  DoCastWithRangeCheckTestExulstive<signed char, signed short>();

  DoCastWithRangeCheckTestExulstive<unsigned int, signed char>();
  

  pass &= DoCastWithRangeCheckTestForTypes<unsigned char>();
  pass &= DoCastWithRangeCheckTestForTypes<signed char>();
  pass &= DoCastWithRangeCheckTestForTypes<unsigned short>();
  pass &= DoCastWithRangeCheckTestForTypes<signed short>();
  pass &= DoCastWithRangeCheckTestForTypes<unsigned int>();
  pass &= DoCastWithRangeCheckTestForTypes<signed int>();
  pass &= DoCastWithRangeCheckTestForTypes<unsigned long>();
  pass &= DoCastWithRangeCheckTestForTypes<signed long>();
#ifdef ITK_USE_LONG_LONG
  pass &= DoCastWithRangeCheckTestForTypes<unsigned long long>();
  pass &= DoCastWithRangeCheckTestForTypes<signed long long>();
#endif

  if (pass)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
  
}
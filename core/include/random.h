#ifndef CORE_RANDOM_H
#define CORE_RANDOM_H

#include "../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

class IRandom
{
  ////////////////////////////////////////////////////////////////
  // Class Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~IRandom() {}

  ////////////////////////////////////////////////////////////////
  // Class functions
  ////////////////////////////////////////////////////////////////
  private:
    /// Get the next pseudo-random number
    /// @return a value in the range [1, uimax]
    virtual const uint64_t getNext() = 0;

    /// Maximum number returned by the generator
    virtual const uint64_t getMax() const = 0;

  public:
    /// Get the next number according to uniform distribution
    /// @return a number in the range [0, uiMax-1]
    const uint64_t getUniform();

    /// Get the next number according to uniform distribution
    /// @return a number in the range [iLow, iHigh]
    const int64_t getUniform(int64_t iLow, int64_t iHigh);

    /// Get the next number as double
    /// @param bClosed defines the right bracket: ) for false, ] for true
    /// @return a number in the range [0, 1) or [0, 1]
    const double getUniformDouble(bool bClosed = false);

    /// Get the next two numbers as gaussians of center 0 and sigma^2 = 1
    ///
    /// The first number is returned by the function, the second one as parameter
    const double getGaussians(double& secondValue);

    /// Get the next number as gaussian of given center and sigma^2
    ///
    /// @param center the value where the gaussian should be centered to
    /// @param sigma the width of the curve (~95% inside 2 sigma)
    /// NOTE: TWO VALUES ARE GENERATED BUT ONLY ONE RETURNED !
    const double getGaussian(const double center = 0., const double sigma = 1.);

  ////////////////////////////////////////////////////////////////
  // Static members
  ////////////////////////////////////////////////////////////////
  private:
    static const uint64_t maskDouble;
};

////////////////////////////////////////////////////////////////

}

#endif

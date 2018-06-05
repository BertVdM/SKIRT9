/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "LogWavelengthDistribution.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

void LogWavelengthDistribution::setupSelfBefore()
{
    RangeWavelengthDistribution::setupSelfBefore();

    _logMin = log(range().min());
    _logWidth = log(range().max()) - log(range().min());
}

//////////////////////////////////////////////////////////////////////

double LogWavelengthDistribution::probability(double wavelength) const
{
    return 1. / (_logWidth * wavelength);
}

//////////////////////////////////////////////////////////////////////

double LogWavelengthDistribution::generateWavelength() const
{
    return exp(_logMin + _logWidth*random()->uniform());
}

//////////////////////////////////////////////////////////////////////

/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "DiskWindVectorField.hpp"

//////////////////////////////////////////////////////////////////////

void DiskWindVectorField::setupSelfBefore()
{
    // calculate and store the sine and cosine of the fixed polar angle
    _sintheta = sin(_theta);
    _costheta = cos(_theta);
}

//////////////////////////////////////////////////////////////////////

int DiskWindVectorField::dimension() const
{
    return 3;
}

//////////////////////////////////////////////////////////////////////

Vec DiskWindVectorField::vector(Position bfr) const
{
    // get the cylindrical coordinates of the position vector, except
    // if R or z are zero, then immediately return a null vector
    if (bfr.z() == 0 || (bfr.x() == 0 && bfr.y() == 0)) return Vec();
    double z = bfr.z();
    double R = sqrt(bfr.x() * bfr.x() + bfr.y() * bfr.y());

    // get the unit vector in the vector field direction
    double absz = fabs(z);
    Vec u(_sintheta * bfr.x() / R, _sintheta * bfr.y() / R, z / absz * _costheta);

    // set the magnitude to a default value of unity, and update if needed
    double v = 1.;
    if (scalelengthR() > 0.)
    {
        if ((exponentR() > 0. && R < scalelengthR()) || (exponentR() < 0. && R > scalelengthR()))
            v *= pow(R / scalelengthR(), exponentR());
    }
    if (scalelengthZ() > 0.)
    {
        if ((exponentZ() > 0. && absz < scalelengthZ()) || (exponentZ() < 0. && absz > scalelengthZ()))
            v *= pow(absz / scalelengthZ(), exponentZ());
    }

    // return the field vector with proper magnitude and direction
    return v * u;
}

//////////////////////////////////////////////////////////////////////

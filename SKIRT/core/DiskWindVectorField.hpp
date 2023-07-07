/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef DISKWINDVECTORFIELD_HPP
#define DISKWINDVECTORFIELD_HPP

#include "VectorField.hpp"

//////////////////////////////////////////////////////////////////////

/** DiskWindVectorField represents an axisymmetric vector field modelling a disk wind outflow,
    which is further symmetrical about the xy-plane. Field vectors lay in the meridional plane, and
    are making a fixed angle \f$\theta_\text{W}\f$ with the positive z-axis (for \f$z>0\f$), or the
    negative z-axis (for \f$z<0\f$).

    The magnitude of the vectors varies independently with radial distance \f$R\f$ from the z-axis,
    and the distance \f$|z|\f$ from the disk: \f$v(R, z) = v(R) v(z) = v(R) v(|z|)\f$. The class
    has five configuration properties: the fixed polar angle \f$\theta_\text{W}\f$ of the vector
    field, the power-law exponent \f$\alpha_R\f$ and the scale length \f$R_0\f$ governing the
    radial dependence of the vector magnitude, and the power-law exponent \f$\alpha_z\f$ and the
    scale length \f$z_0\f$ governing the z-dependence of the vector magnitude.

    The radial part of the vector magnitude \f$v(R)\f$ is given by

    \f[ R_0=0 \lor \alpha_R=0 \qquad v(R) = \begin{cases} 0 & \mathrm{for}\;R=0 \\ 1 &
    \mathrm{for}\;R>0 \end{cases} \f]

    \f[ R_0>0 \land \alpha_R>0 \qquad v(R) = \begin{cases} 0 & \mathrm{for}\;R=0 \\
    (R/R_0)^{\alpha_R} & \mathrm{for}\;0<R<R_0 \\ 1 & \mathrm{for}\;R\ge R_0 \end{cases} \f]

    \f[ R_0>0 \land \alpha_R<0 \qquad v(R) = \begin{cases} 0 & \mathrm{for}\;R=0 \\ 1 &
    \mathrm{for}\;0<R<R_0 \\ (R/R_0)^{\alpha_R} & \mathrm{for}\;R \ge R_0 \end{cases} \f]

    The z-part of the vector magnitude \f$v(z)\f$ is given by

    \f[ z_0=0 \lor \alpha_z=0 \qquad v(z) = \begin{cases} 0 & \mathrm{for}\;|z|=0 \\ 1 &
    \mathrm{for}\;|z|>0 \end{cases} \f]

    \f[ z_0>0 \land \alpha_z>0 \qquad v(z) = \begin{cases} 0 & \mathrm{for}\;|z|=0 \\
    (|z|/z_0)^{\alpha_z} & \mathrm{for}\;0<|z|<z_0 \\ 1 & \mathrm{for}\;|z|\ge z_0 \end{cases} \f]

    \f[ z_0>0 \land \alpha_z<0 \qquad v(z) = \begin{cases} 0 & \mathrm{for}\;|z|=0 \\ 1 &
    \mathrm{for}\;0<|z|<z_0 \\ (|z|/z_0)^{\alpha_z} & \mathrm{for}\;|z| \ge z_0 \end{cases} \f] */
class DiskWindVectorField : public VectorField
{
    ITEM_CONCRETE(DiskWindVectorField, VectorField, "a disk wind vector field with a fixed polar angle")
        ATTRIBUTE_TYPE_INSERT(DiskWindVectorField, "Dimension3")

        PROPERTY_DOUBLE(theta, "the fixed polar angle of the vector field")
        ATTRIBUTE_QUANTITY(theta, "posangle")
        ATTRIBUTE_MIN_VALUE(theta, "0 deg")
        ATTRIBUTE_MAX_VALUE(theta, "90 deg")
        ATTRIBUTE_DEFAULT_VALUE(theta, "30 deg")

        PROPERTY_DOUBLE(exponentR, "the power-law exponent governing the radial dependence of the vector magnitude")
        ATTRIBUTE_DEFAULT_VALUE(exponentR, "1")

        PROPERTY_DOUBLE(scalelengthR, "the scale length governing the radial dependence of the vector magnitude")
        ATTRIBUTE_QUANTITY(scalelengthR, "length")
        ATTRIBUTE_MIN_VALUE(scalelengthR, "0")
        ATTRIBUTE_DEFAULT_VALUE(scalelengthR, "1")

        PROPERTY_DOUBLE(exponentZ, "the power-law exponent governing the z-dependence of the vector magnitude")
        ATTRIBUTE_DEFAULT_VALUE(exponentZ, "1")

        PROPERTY_DOUBLE(scalelengthZ, "the scale length governing the z-dependence of the vector magnitude")
        ATTRIBUTE_QUANTITY(scalelengthZ, "length")
        ATTRIBUTE_MIN_VALUE(scalelengthZ, "0")
        ATTRIBUTE_DEFAULT_VALUE(scalelengthZ, "1")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function stores the sine and cosine of the field's fixed polar angle for later use. */
    void setupSelfBefore() override;

    //======================== Other Functions =======================

public:
    /** This function returns the dimension of the vector field, which is 3 for this
        class,indicating no symmetries (the vectors point in a different direction at each
        position). */
    int dimension() const override;

    /** This function returns a field vector with a fixed polar angle \f$\theta_\text{W}\f$ (or
        \f$180^\circ - \theta_\text{W}\f$ for \f$z<0\f$), the same azimuth angle as the given
        position \f$\bf{r}\f$, and a magnitude according to the definitions given in the class
        header. */
    Vec vector(Position bfr) const override;

    //======================== Data Members ========================

private:
    double _sintheta, _costheta;
};

////////////////////////////////////////////////////////////////////

#endif

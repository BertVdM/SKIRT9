/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef TIMEFRAMEINSTRUMENT_HPP
#define TIMEFRAMEINSTRUMENT_HPP

#include "DistantInstrument.hpp"
#include "TimeGrid.hpp"

////////////////////////////////////////////////////////////////////

/** A TimeFrameInstrument object represents a distant instrument that records the surface
    brightness in every pixel of a given frame for each time lag interval in a user-configured
    time grid, and outputs the result as a data cube in a FITS file. It is identical to a
    FrameInstrument (see that class for the pixel geometry and projection details), except that
    the frames making up the data cube are sliced along a time lag axis rather than along a
    wavelength axis.

    As for the aperture-based timing instruments (see TimeInstrument), the wavelength grid
    inherited from the base instrument classes is still required to determine the spectral
    response of the instrument, i.e. to select or weigh the range of photon packet wavelengths
    that contribute to the recorded frames, even though the resulting frames are not spectrally
    resolved. */
class TimeFrameInstrument : public DistantInstrument
{
    ITEM_CONCRETE(TimeFrameInstrument, DistantInstrument,
                  "a distant instrument that outputs the surface brightness in every pixel as a data cube with a time lag axis")
        ATTRIBUTE_TYPE_ALLOWED_IF(TimeFrameInstrument, "ExtinctionOnly")
        ATTRIBUTE_TYPE_DISPLAYED_IF(TimeFrameInstrument, "Level2")

        PROPERTY_DOUBLE(fieldOfViewX, "the total field of view in the horizontal direction")
        ATTRIBUTE_QUANTITY(fieldOfViewX, "length")
        ATTRIBUTE_MIN_VALUE(fieldOfViewX, "]0")

        PROPERTY_INT(numPixelsX, "the number of pixels in the horizontal direction")
        ATTRIBUTE_MIN_VALUE(numPixelsX, "1")
        ATTRIBUTE_MAX_VALUE(numPixelsX, "10000")
        ATTRIBUTE_DEFAULT_VALUE(numPixelsX, "250")

        PROPERTY_DOUBLE(centerX, "the center of the frame in the horizontal direction")
        ATTRIBUTE_QUANTITY(centerX, "length")
        ATTRIBUTE_DEFAULT_VALUE(centerX, "0")
        ATTRIBUTE_DISPLAYED_IF(centerX, "Level2")

        PROPERTY_DOUBLE(fieldOfViewY, "the total field of view in the vertical direction")
        ATTRIBUTE_QUANTITY(fieldOfViewY, "length")
        ATTRIBUTE_MIN_VALUE(fieldOfViewY, "]0")

        PROPERTY_INT(numPixelsY, "the number of pixels in the vertical direction")
        ATTRIBUTE_MIN_VALUE(numPixelsY, "1")
        ATTRIBUTE_MAX_VALUE(numPixelsY, "10000")
        ATTRIBUTE_DEFAULT_VALUE(numPixelsY, "250")

        PROPERTY_DOUBLE(centerY, "the center of the frame in the vertical direction")
        ATTRIBUTE_QUANTITY(centerY, "length")
        ATTRIBUTE_DEFAULT_VALUE(centerY, "0")
        ATTRIBUTE_DISPLAYED_IF(centerY, "Level2")

        PROPERTY_ITEM(timeGrid, TimeGrid, "the time grid for this instrument")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function configures the FluxRecorder instance associated with this instrument. */
    void setupSelfBefore() override;

    //======================== Other Functions =======================

public:
    /** This function simulates the detection of a photon packet by the instrument. It determines
        the projected position of the photon packet's last interaction site on the instrument frame
        and then calls the detect() function of the FluxRecorder instance associated with this
        instrument. */
    void detect(PhotonPacket* pp) override;

private:
    /** This private helper function returns the index of the spatial pixel on the detector that
        will be hit by a photon packet, or -1 if the photon packet does not hit the detector. See
        FrameInstrument::pixelOnDetector() for the full derivation; the geometry is identical
        here. */
    int pixelOnDetector(const PhotonPacket* pp) const;

    //======================== Data Members ========================

private:
    // data members derived from the discoverable properties during setup, used in pixelOnDetector()
    double _costheta{0};
    double _sintheta{0};
    double _cosphi{0};
    double _sinphi{0};
    double _cosomega{0};
    double _sinomega{0};
    int _Nxp{0};
    int _Nyp{0};
    double _xpmin{0};
    double _xpsiz{0};
    double _ypmin{0};
    double _ypsiz{0};
};

////////////////////////////////////////////////////////////////////

#endif

#include "erfam.h"

void eraC2tpe(double tta, double ttb, double uta, double utb,
              double dpsi, double deps, double xp, double yp,
              double rc2t[3][3])
/*
**  - - - - - - - - -
**   e r a C 2 t p e
**  - - - - - - - - -
**
**  Form the celestial to terrestrial matrix given the date, the UT1,
**  the nutation and the polar motion.  IAU 2000.
**
**  Given:
**     tta,ttb    double        TT as a 2-part Julian Date (Note 1)
**     uta,utb    double        UT1 as a 2-part Julian Date (Note 1)
**     dpsi,deps  double        nutation (Note 2)
**     xp,yp      double        coordinates of the pole (radians, Note 3)
**
**  Returned:
**     rc2t       double[3][3]  celestial-to-terrestrial matrix (Note 4)
**
**  Notes:
**
**  1) The TT and UT1 dates tta+ttb and uta+utb are Julian Dates,
**     apportioned in any convenient way between the arguments uta and
**     utb.  For example, JD(UT1)=2450123.7 could be expressed in any of
**     these ways, among others:
**
**             uta            utb
**
**         2450123.7           0.0       (JD method)
**         2451545.0       -1421.3       (J2000 method)
**         2400000.5       50123.2       (MJD method)
**         2450123.5           0.2       (date & time method)
**
**     The JD method is the most natural and convenient to use in
**     cases where the loss of several decimal digits of resolution is
**     acceptable.  The J2000 and MJD methods are good compromises
**     between resolution and convenience.  In the case of uta,utb, the
**     date & time method is best matched to the Earth rotation angle
**     algorithm used:  maximum precision is delivered when the uta
**     argument is for 0hrs UT1 on the day in question and the utb
**     argument lies in the range 0 to 1, or vice versa.
**
**  2) The caller is responsible for providing the nutation components;
**     they are in longitude and obliquity, in radians and are with
**     respect to the equinox and ecliptic of date.  For high-accuracy
**     applications, free core nutation should be included as well as
**     any other relevant corrections to the position of the CIP.
**
**  3) The arguments xp and yp are the coordinates (in radians) of the
**     Celestial Intermediate Pole with respect to the International
**     Terrestrial Reference System (see IERS Conventions 2003),
**     measured along the meridians to 0 and 90 deg west respectively.
**
**  4) The matrix rc2t transforms from celestial to terrestrial
**     coordinates:
**
**        [TRS] = RPOM * R_3(GST) * RBPN * [CRS]
**
**              = rc2t * [CRS]
**
**     where [CRS] is a vector in the Geocentric Celestial Reference
**     System and [TRS] is a vector in the International Terrestrial
**     Reference System (see IERS Conventions 2003), RBPN is the
**     bias-precession-nutation matrix, GST is the Greenwich (apparent)
**     Sidereal Time and RPOM is the polar motion matrix.
**
**  5) Although its name does not include "00", This function is in fact
**     specific to the IAU 2000 models.
**
**  Called:
**     eraPn00      bias/precession/nutation results, IAU 2000
**     eraGmst00    Greenwich mean sidereal time, IAU 2000
**     eraSp00      the TIO locator s', IERS 2000
**     eraEe00      equation of the equinoxes, IAU 2000
**     eraPom00     polar motion matrix
**     eraC2teqx    form equinox-based celestial-to-terrestrial matrix
**
**  Reference:
**
**     McCarthy, D. D., Petit, G. (eds.), IERS Conventions (2003),
**     IERS Technical Note No. 32, BKG (2004)
**
**  Copyright (C) 2013, NumFOCUS Foundation.
**  Copyright (C) 2012 IAU SOFA Board.
**  Derived, with permission, from the SOFA library.  See notes at end of file.
*/
{
   double epsa, rb[3][3], rp[3][3], rbp[3][3], rn[3][3],
          rbpn[3][3], gmst, ee, sp, rpom[3][3];


/* Form the celestial-to-true matrix for this TT. */
   eraPn00(tta, ttb, dpsi, deps, &epsa, rb, rp, rbp, rn, rbpn);

/* Predict the Greenwich Mean Sidereal Time for this UT1 and TT. */
   gmst = eraGmst00(uta, utb, tta, ttb);

/* Predict the equation of the equinoxes given TT and nutation. */
   ee = eraEe00(tta, ttb, epsa, dpsi);

/* Estimate s'. */
   sp = eraSp00(tta, ttb);

/* Form the polar motion matrix. */
   eraPom00(xp, yp, sp, rpom);

/* Combine to form the celestial-to-terrestrial matrix. */
   eraC2teqx(rbpn, gmst + ee, rpom, rc2t);

   return;

}
/*----------------------------------------------------------------------
**  
**  
**  Copyright (C) 2013, NumFOCUS Foundation.
**  Copyright (C) 2012, Standards Of Fundamental Astronomy Board
**    of the International Astronomical Union.
**  All rights reserved.
**  
**  This library is derived, with permission, from the International
**  Astronomical Union's "Standards of Fundamental Astronomy" library,
**  available from http://www.iausofa.org.
**  
**  The ERFA version is intended to retain identical functionality to
**  the SOFA library, but with different routine and file names. Although
**  the intent is to replicate the SOFA API (other than replacement of
**  prefix names) and results (with the exception of bugs; any that are
**  discovered will be fixed), SOFA is not responsible for any errors found
**  in this version of the library.
**  If you wish to acknowledge the SOFA heritage, please acknowledge that
**  you are using a library derived from SOFA, rather than SOFA itself.
**  
**  TERMS AND CONDITIONS
**  
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**  
**  1 Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**  
**  2 Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**  
**  3 Neither the name of the Standards Of Fundamental Astronomy Board, the
**     International Astronomical Union nor the names of its contributors
**     may be used to endorse or promote products derived from this software
**     without specific prior written permission.
**  
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
**  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
**  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
**  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
**  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
**  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
**  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
**  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
**  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**  
*/

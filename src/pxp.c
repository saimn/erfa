#include "erfam.h"

void eraPxp(double a[3], double b[3], double axb[3])
/*
**  - - - - - - -
**   e r a P x p
**  - - - - - - -
**
**  p-vector outer (=vector=cross) product.
**
**  Given:
**     a        double[3]      first p-vector
**     b        double[3]      second p-vector
**
**  Returned:
**     axb      double[3]      a x b
**
**  Note:
**     It is permissible to re-use the same array for any of the
**     arguments.
**
**  Copyright (C) 2013, NumFOCUS Foundation.
**  Copyright (C) 2012 IAU SOFA Board.
**  Derived, with permission, from the SOFA library.  See notes at end of file.
*/
{
   double xa, ya, za, xb, yb, zb;


   xa = a[0];
   ya = a[1];
   za = a[2];
   xb = b[0];
   yb = b[1];
   zb = b[2];
   axb[0] = ya*zb - za*yb;
   axb[1] = za*xb - xa*zb;
   axb[2] = xa*yb - ya*xb;

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

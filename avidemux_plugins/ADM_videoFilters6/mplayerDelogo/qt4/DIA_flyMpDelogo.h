/***************************************************************************
    copyright            : (C) 2011 by mean
    email                : fixounet@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef FLY_MPDELOGO_H
#define FLY_MPDELOGO_H
/**
    \class flyASharp
*/
#include "delogo.h"
/**
    \class flyMpDelogo
*/
class flyMpDelogo : public ADM_flyDialogQt4
{
  
  public:
   delogo      param;
   bool        preview;
  public:
   uint8_t     processYuv(ADMImage* in, ADMImage *out);
   uint8_t     download(void);
   uint8_t     upload(void);
               flyMpDelogo (uint32_t width,uint32_t height,ADM_coreVideoFilter *in,
                                    ADM_QCanvas *canvas, QSlider *slider) : 
                ADM_flyDialogQt4(width, height,in,canvas, slider,true,RESIZE_AUTO) 
                {};
   virtual     ~flyMpDelogo() {};
   bool         setXy(int x,int y);
   bool         setPreview(bool onoff)
                {
                    preview=onoff;
                    return true;
                }
};
// EOF


#endif
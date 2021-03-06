/***************************************************************************
                          Q_eq2.cpp  -  description

                flyDialog for MPlayer EQ2 filter
    copyright            : (C) 2002/2007 by mean Fixounet@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Q_eq2.h"
#include "ADM_toolkitQt.h"

//
//	Video is in YV12 Colorspace
//
//
  Ui_eq2Window::Ui_eq2Window(QWidget *parent, eq2 *param,ADM_coreVideoFilter *in) : QDialog(parent)
  {
    uint32_t width,height;
        ui.setupUi(this);
        lock=0;
        // Allocate space for green-ised video
        width=in->getInfo()->width;
        height=in->getInfo()->height;

        canvas=new ADM_QCanvas(ui.graphicsView,width,height);
        
        myCrop=new flyEq2(this, width, height,in,canvas,ui.horizontalSlider);
        memcpy(&(myCrop->param),param,sizeof(eq2));
        myCrop->_cookie=&ui;
        myCrop->addControl(ui.toolboxLayout);
        myCrop->upload();
        myCrop->sliderChanged();
        myCrop->update();


        connect( ui.horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderUpdate(int)));
#define SPINNER(x) connect( ui.horizontalSlider##x,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int))); 
        SPINNER(Red);
        SPINNER(Blue);
        SPINNER(Green);
         
        SPINNER(Contrast);
        SPINNER(Brightness);
        SPINNER(Saturation);

        SPINNER(Initial);
        SPINNER(Weight);
  }
  void Ui_eq2Window::sliderUpdate(int foo)
  {
    myCrop->sliderChanged();
  }
  void Ui_eq2Window::gather(eq2 *param)
  {
    
        myCrop->download();
        memcpy(param,&(myCrop->param),sizeof(eq2));
  }
Ui_eq2Window::~Ui_eq2Window()
{
  if(myCrop) delete myCrop;
  myCrop=NULL; 
  if(canvas) delete canvas;
  canvas=NULL;
}
void Ui_eq2Window::valueChanged( int f )
{
  if(lock) return;
  lock++;
  myCrop->download();
  myCrop->sameImage();
  lock--;
}

#define sliderSet(x,y) w->horizontalSlider##x->setValue((int)(param.y*100));
#define sliderGet(x,y) param.y=w->horizontalSlider##x->value()/100.;
//************************
uint8_t flyEq2::upload(void)
{
Ui_eq2Dialog *w=(Ui_eq2Dialog *)_cookie;


        sliderSet(Contrast,contrast);
        sliderSet(Brightness,brightness);
        sliderSet(Saturation,saturation);

        sliderSet(Red,rgamma);
        sliderSet(Green,ggamma);
        sliderSet(Blue,bgamma);

        sliderSet(Initial,gamma);
        sliderSet(Weight,gamma_weight);
        
       return 1;
}
uint8_t flyEq2::download(void)
{
	Ui_eq2Dialog *w=(Ui_eq2Dialog *)_cookie;

        sliderGet(Contrast,contrast);
        sliderGet(Brightness,brightness);
        sliderGet(Saturation,saturation);

        sliderGet(Red,rgamma);
        sliderGet(Green,ggamma);
        sliderGet(Blue,bgamma);

        sliderGet(Initial,gamma);
        sliderGet(Weight,gamma_weight);

return 1;
}
/**
      \fn     DIA_getEQ2Param
      \brief  Handle MPlayer EQ2 flyDialog
*/
uint8_t DIA_getEQ2Param(eq2 *param, ADM_coreVideoFilter *in)
{
        uint8_t ret=0;
        Ui_eq2Window dialog(qtLastRegisteredDialog(), param,in);

		qtRegisterDialog(&dialog);

        if(dialog.exec()==QDialog::Accepted)
        {
            dialog.gather(param); 
            ret=1;
        }

		qtUnregisterDialog(&dialog);

        return ret;
}
//____________________________________
// EOF



#ifndef UserInterface_h
#define UserInterface_h

// ====================  头文件  ====================
#include <errno.h>
#include<stdlib.h>
#include<algorithm>
#include<cmath>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Scroll.H>
#include <FL/x.H>
#include<Fl_Menu_Button.H>
#include <FL/Fl_Sys_Menu_Bar.H>

#include<vtkPointData.h>
#include <vtkImageData.h>
//#include <vtkSmartPointer.h>
#include "vtkActor.h"
//#include "vtkImageActor.h"
#include "vtkActor2D.h"
//#include"vtkImageLuminance.h"
#include"vtkImageViewer.h"
#include <vtkImageViewer2.h>
//#include <vtkJPEGReader.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkRenderer.h>
#include "vtkInteractorStyle.h"

#include <vtkSmartPointer.h>
#include "vtkInteractorStyleTrackballCamera.h"
#include <vtkImageMapper3D.h>
//#include <vtkImageCanvasSource2D.h>
#include <vtkImageLuminance.h>
#include<vtkImageMagnitude.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include<vtkXYPlotActor.h>
#include<vtkImageExtractComponents.h>
#include<vtkImageAccumulate.h>
#include<vtkFloatArray.h>
#include<vtkTextMapper.h>
#include<vtkTextProperty.h>
#include<vtkCursor3D.h>
#include<vtkPolyDataMapper2D.h>
#include<vtkProperty2D.h>
#include<vtkCoordinate.h>
#include <vtkCallbackCommand.h>
#include "vtkPointPicker.h"
#include <vtkImageCast.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>

#include<Fl_Output.H>
//===========================================

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/fl_message.H>
#include <FL/Fl_Multiline_Output.H>
//#include <stdlib.h>
//#include "../src/flstring.h"
#include <FL/fl_draw.H>
//#include "Fl_Native_File_Chooser.h"







//============================================







// ====================  常量  ====================
//#define IDI_ICON                        101		//{{NO_DEPENDENCIES}}
												// Microsoft Developer Studio generated include file.
												// Used by icons.rc
												//

/*
// Next default values for new objects 
#ifdef APSTUDIO_INVOKED							
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        105
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
*/
// ====================  类  ====================
class UserInterfaceGUI {
public:
	Fl_Double_Window *MainWin;	
	Fl_Menu_Bar *Menu;
	Fl_Tabs *MenuTab;
	Fl_Group *RightPaneGrp;
	Fl_Group *ImageGrp;	
	Fl_Group *FilterGrp;
	Fl_Group *MorphoGrp;
	Fl_Group *TransGrp;
	Fl_Group *GrayGrp;
	Fl_Group *MGrayGrp;

	
	//Fl_Group *LocatorGrp;	
	//Fl_Group *SettingGrp;	
	//Fl_Group *HelpGrp;	
	Fl_Group *SlicePanelGrp[4];	
	
  //  Fl_Input* inp[25];
    
public:
	UserInterfaceGUI();
	~UserInterfaceGUI();
	void Show();
	virtual void Quit();
	virtual void Redraw();
	//void m_roberts(Fl_Widget*, void*);
}; // UserInterfaceGUI

#endif
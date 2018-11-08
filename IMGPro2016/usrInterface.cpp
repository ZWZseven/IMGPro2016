//#include"cstringex.h"
#include"usrInterface.h"
#include "vtkFlRenderWindowInteractor.h"



#define _CRT_SECURE_NO_WARNINGS


using namespace std;
Fl_Input* wsize;

Fl_Multiline_Output* text;
Fl_Input* inp0;Fl_Input* inp1;Fl_Input* inp2;Fl_Input* inp3;Fl_Input* inp4;
Fl_Input* inp5;Fl_Input* inp6;Fl_Input* inp7;Fl_Input* inp8;Fl_Input* inp9;
Fl_Input* inp10;Fl_Input* inp11;Fl_Input* inp12;Fl_Input* inp13;Fl_Input* inp14;
Fl_Input* inp15;Fl_Input* inp16;Fl_Input* inp17;Fl_Input* inp18;Fl_Input* inp19;
Fl_Input* inp20;Fl_Input* inp21;Fl_Input* inp22;Fl_Input* inp23;Fl_Input* inp24;
//=============================================
Fl_Input* inpm0;Fl_Input* inpm1;Fl_Input* inpm2;Fl_Input* inpm3;Fl_Input* inpm4;
Fl_Input* inpm5;Fl_Input* inpm6;Fl_Input* inpm7;Fl_Input* inpm8;
Fl_Input* xi;Fl_Input* yi;
int mt[][3] = {
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 } };
int *imagematrix=NULL;
Fl_Input* msize;
//=========================================================================
Fl_Input* inpg0;Fl_Input* inpg1;Fl_Input* inpg2;Fl_Input* inpg3;Fl_Input* inpg4;
Fl_Input* inpg5;Fl_Input* inpg6;Fl_Input* inpg7;Fl_Input* inpg8;
Fl_Input* gxi;Fl_Input* gyi;
int gt[][3] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 } };
int *gimagematrix=NULL;
Fl_Input* gsize;
//==========================================================================
 vtkJPEGReader* jpegReader=NULL;
vtkImageData*imagedata=NULL;
vtkImageData*grayimage=NULL;
vtkImageData*binaryimage=NULL;
vtkImageMapper *map=NULL;
vtkImageMapper *binmap=NULL;
 vtkActor2D*act=NULL;
 vtkActor2D*binact=NULL;
 vtkFloatArray*bin=NULL;
 vtkImageExtractComponents* extract=NULL;
 //vtkActor2D*magnitudeActor;
 vtkImageActor* luminanceActor=NULL;
 vtkImageActor* magnitudeActor=NULL;
 vtkImageLuminance* luminanceFilter=NULL;
 vtkImageMagnitude* magnitudeFilter=NULL;
 vtkXYPlotActor*plot=NULL;
 vtkActor2D*HairCrossAct=NULL;
 vtkTextMapper* slidertxt=NULL;
 vtkCursor3D*cursor=NULL;
 vtkPolyDataMapper2D*cursormapper=NULL;
 vtkActor2D *sliderTxtAct=NULL;
 vtkImageAccumulate*histogram=NULL;
 vtkPNGReader* pngreader=NULL;
 vtkJPEGWriter* jpegwriter=NULL;
//Fl_Output*ivalue=NULL;
 int* dims=NULL;

Fl_Box *b;
Fl_Double_Window *w;
Fl_Shared_Image *img=NULL;
static char name[1024];
//extern imagepro* jpgpro; 
void binimage(unsigned char threshold1);
unsigned char threshold=100;

Fl_Window *Win;	
//Fl_JPEG_Image* jpg;
Fl_Scroll* scroll;
// 
Fl_Scrollbar *SliceSlider;	// 

//float** imagemat;

void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
//void MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
vtkRenderer *SliceRenderer[4];	
vtkRenderWindow *SliceRenderWin[4];	
vtkFlRenderWindowInteractor *SliceWin[4];
vtkPointPicker *picker;
vtkInteractorStyleTrackballCamera *style;
vtkCallbackCommand * cmd1;
vtkCallbackCommand * cmd;
Fl_Output* pickx;
Fl_Output* picky;
Fl_Input* WindowImageFileName;
void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	int selPt[2];
	SliceWin[3]->GetEventPosition (selPt);
	char* S0=new char [1];
	_itoa(selPt[0],S0,10);
	const char*cs0=S0;

	char* S1=new char [1];
	_itoa(selPt[1],S1,10);
	const char*cs1=S1;
		
	printf("X: %d, Y: %d\n",selPt[0],selPt[1]);
	pickx->value(cs0);
	picky->value(cs1);

	float temp=binaryimage->GetScalarComponentAsFloat(selPt[0],selPt[1],0,0);
	printf("像素为:  %f\n",temp);

	//style->OnLeftButtonDown();
}

//void MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
//{
//	double selPt[3];
//	picker->GetSelectionPoint(selPt);
//	printf("X:  %f, Y:  %f\n",selPt[0],selPt[1]);
//
//	float temp=binaryimage->GetScalarComponentAsFloat(selPt[0],selPt[1],0,0);
//	printf("像素为:  %d\f",temp);
//	/*
//	double globalCoordinate[3]; 
//	picker->GetPickPosition(globalCoordinate);
//	printf("X:  %f, Y:  %f, Z:  %f\n",
//	globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);
//	*/
//	style->OnLeftButtonDown();
//}
//=================================================================
void vtkFlRenderWindowInteractor::SaveAsJPG(const char *filename,unsigned int window)
{

	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(SliceWin[window]->GetRenderWindow());

	vtkImageCast *imagecast = vtkImageCast::New();
	imagecast->SetInput(filter->GetOutput());
	imagecast->SetOutputScalarTypeToUnsignedChar();

	//vtkPNGWriter *writer = vtkPNGWriter::New();
	vtkJPEGWriter *writer = vtkJPEGWriter::New();
	writer->SetInput(imagecast->GetOutput());
	writer->SetFileName(filename);
	writer->Write();
	//	writer->Update();
} // SaveAsPNG

void ImageSave(unsigned int window)
{
	string SaveFileName;
	SaveFileName = WindowImageFileName->value();
	//SaveFileName += ".png";
	SaveFileName += ".jpg";

	if (window<4)
		SliceWin[window]->SaveAsJPG(SaveFileName.c_str(), window);
} // SliceImageSave
void m_SaveOKButton(Fl_Button*, void*)
{
	ImageSave(3);
	Win->hide();
}

void m_CancelButton(Fl_Button*, void*)
{
	
	Win->hide();
}
int ScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);	// Screen width
int ScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);	// Screen height
void save_cb(Fl_Widget*, void*) 
{	Win = new Fl_Window((ScreenWidth-400)/2, (ScreenHeight-190)/2, 400, 190,"Save");

		{	Fl_Output *WindowImageName = new Fl_Output(25, 40, 100, 25);
			WindowImageName->box(FL_FLAT_BOX);
			WindowImageName->color((Fl_Color)FL_BACKGROUND_COLOR);
			WindowImageName->textsize(14);
			WindowImageName->align(FL_ALIGN_CENTER);
			WindowImageName->value("filename");
		} // Fl_Output *WindowImageName

		{	WindowImageFileName = new Fl_Input(25, 70, 340, 25);
		} // Fl_Input *WindowImageFileName

		{	Fl_Button *OKButton = new Fl_Button(210, 130, 70, 25,"OK");
			OKButton->labelsize(14);
			OKButton->align(FL_ALIGN_CLIP|FL_ALIGN_CENTER);
			OKButton->box(FL_PLASTIC_UP_BOX);
			OKButton->down_box(FL_PLASTIC_DOWN_BOX);
			OKButton->color(FL_WHITE);
			OKButton->callback((Fl_Callback*)m_SaveOKButton);
		} // Fl_Button *OKButton

		{	Fl_Button *CancelButton = new Fl_Button(290, 130, 70, 25,"Cancel");	
			CancelButton->labelsize(14);
			CancelButton->align(FL_ALIGN_CLIP|FL_ALIGN_CENTER);
			CancelButton->box(FL_PLASTIC_UP_BOX);
			CancelButton->down_box(FL_PLASTIC_DOWN_BOX);
			CancelButton->color(FL_WHITE);
			CancelButton->callback((Fl_Callback*)m_CancelButton);
		} // Fl_Button *CancelButton

		Win->set_modal();
		Win->end();
		Win->show();
} // Fl_Window *Win

//=========================================================================


void load_file(const char *n) {
  if (img) {
    img->release();
    img = 0L;
  }
  if (fl_filename_isdir(n)) {
  
    return;
  }
  img = Fl_Shared_Image::get(n);
  if (!img) {
	
    return;
  }
  
}

void file_cb(const char *n) {
  if (!strcmp(name,n)) return;
  load_file(n);
  strcpy(name,n);
  w->label(name);
   
}

void open_cb(Fl_Widget *,void *) {
  fl_file_chooser_callback(file_cb);
  const char *fname = fl_file_chooser("Image file?","*.{bm,bmp,gif,jpg,pbm,pgm,png,ppm,xbm,xpm}", name);
  puts(fname ? fname : "(null)"); fflush(stdout);
  fl_file_chooser_callback(0);
  if(!fl_filename_isdir(name))
					  {
					
					//===============0-read-image================================
					  if(!jpegReader)jpegReader =vtkJPEGReader::New();
					  jpegReader->SetFileName( name );
					  jpegReader->SetDataByteOrderToLittleEndian();
					  jpegReader->SetDataScalarTypeToUnsignedChar();
					  jpegReader->SetFileDimensionality(3);
					  jpegReader->SetDataOrigin(0.0,0.0,0.0);
					  imagedata=jpegReader->GetOutput();

					//================1-display-raw-image==============================
					  if(!map)map= vtkImageMapper::New();
					  map->SetInput(imagedata);
  
					  map->SetColorLevel(128);
					  map->SetColorWindow(256);
					 //map->Update();
					  act=vtkActor2D::New ();
					  act->SetMapper(map);
					//======================2-grayscale===========================
					  if(!luminanceFilter)luminanceFilter = vtkImageLuminance::New();
  
					  luminanceFilter->SetInput(imagedata);
						luminanceFilter->Update();
						luminanceActor =vtkImageActor::New();
						luminanceActor->GetMapper()->SetInputConnection(luminanceFilter->GetOutputPort());
						grayimage=luminanceFilter->GetOutput();
 
						if(!plot)plot =  vtkXYPlotActor::New();
					  plot->ExchangeAxesOff();
					  plot->SetLabelFormat( "%g" );
					  plot->SetXTitle( "Level" );
					  plot->SetYTitle( "Frequency" );
					  plot->SetXValuesToValue();
 
					  double xmax = 0.;
					  double ymax = 0.;
 
					  double colors[3][3] = {
						{ 1, 0, 0 },
						{ 0, 1, 0 },
						{ 0, 0, 1 } };
 
					  const char* labels[3] = {
						"Red", "Green", "Blue" };
 
   
					   if(!extract)extract = vtkImageExtractComponents::New();
    
					   extract->SetInput(grayimage);
    
						extract->SetComponents( 0 );
					   extract->Update();
 
						double range[2];
						extract->GetOutput()->GetScalarRange( range );
 
						if(!histogram)histogram =vtkImageAccumulate::New();
						histogram->SetInputConnection( extract->GetOutputPort() );
						histogram->SetComponentExtent(
						  0,
						  static_cast<int>(range[1])-static_cast<int>(range[0])-1,0,0,0,0 );
						histogram->SetComponentOrigin( range[0],0,0 );
						histogram->SetComponentSpacing( 1,0,0 );
    
						histogram->Update();
	
						 xmax=255;
						if( histogram->GetOutput()->GetScalarRange()[1] > ymax ) 
						  {
						  ymax = histogram->GetOutput()->GetScalarRange()[1];
						  }
 
					#if VTK_MAJOR_VERSION <= 5
						plot->AddInput( histogram->GetOutput() );
					#else
						plot->AddDataSetInputConnection( histogram->GetOutputPort() );
					#endif
   
 
					  plot->SetXRange( 0, xmax );
					  plot->SetYRange( 0, ymax );
					  plot->SetWidth(0.695);
					//======================4-binary-image========================================
					  //unsigned char threshold=100;
 
					  #if VTK_MAJOR_VERSION <= 5
					  grayimage->SetNumberOfScalarComponents(1);
 
					  grayimage->AllocateScalars();
					#else
					  imageData->AllocateScalars(VTK_DOUBLE,1);
					#endif 
					  dims = grayimage->GetDimensions();
  

					 if(!binaryimage)binaryimage= vtkImageData::New();
					 binaryimage->SetNumberOfScalarComponents(1);
					 binaryimage->AllocateScalars();
					  binaryimage->SetScalarTypeToUnsignedChar();
					  binaryimage->SetDimensions(dims);
					  binaryimage->SetOrigin(0,0,0);
					  double sp=1/256;
					  binaryimage->SetSpacing(sp,sp,1);
					  if(!bin) bin=vtkFloatArray::New();
					 for (int x = 0; x < dims[0]; x++){
						 for(int y=0;y<dims[1];y++)
						{
					   // double* pixel = static_cast<double*>(grayimage->GetScalarPointer(x,y,0));
							unsigned char* pixel = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
    
						if(pixel[0]>threshold)bin->InsertTuple1(x+y*dims[0],255);
						else bin->InsertTuple1(x+y*dims[0],0);
	
						}
					 } 

					 binaryimage->GetPointData()->SetScalars(bin);
  
					  if(!binmap)binmap= vtkImageMapper::New();
					  binmap->SetInput(binaryimage);
  
					  binmap->SetColorLevel(128);
					  binmap->SetColorWindow(256);
					  if(!binact)binact=vtkActor2D::New ();
					  binact->SetMapper(binmap);
  
 
					//==============================================================
					   char str1[10];
						_itoa_s(threshold, str1, 10, 10);
	
						const char*s=str1;
						if(!slidertxt)slidertxt=vtkTextMapper::New();
						slidertxt->SetInput(s); 
						slidertxt->GetTextProperty()->SetFontSize(18);
						sliderTxtAct=vtkActor2D::New();
						sliderTxtAct->SetMapper(slidertxt);
						sliderTxtAct->SetPosition(540,SliceWin[1]->h()-40);
						SliceRenderer[1]->AddActor2D(sliderTxtAct);
	
						if(!cursor)cursor=vtkCursor3D::New();
						cursor->SetFocalPoint(0,0,0);
						cursor->SetModelBounds(0,0,-130,+130,0,0);
						cursor->AxesOn();
						cursor->OutlineOff();
						cursor->XShadowsOff();
						cursor->YShadowsOff();
						cursor->ZShadowsOff();
						if(!cursormapper)cursormapper=vtkPolyDataMapper2D::New();
						cursormapper->SetInput(cursor->GetOutput());
						if(!HairCrossAct)HairCrossAct=vtkActor2D::New();
						HairCrossAct->SetMapper(cursormapper);	//红线
						HairCrossAct->GetProperty()->SetColor(1,0,0);
						HairCrossAct->SetPosition(273+plot->GetPosition()[0]+threshold,plot->GetPosition()[1]+200);
						SliceRenderer[1]->AddActor2D(HairCrossAct);	

			//============================================================

			imagematrix=new int[dims[0]*dims[1]];
			gimagematrix=new int[dims[0]*dims[1]];
	
				cout<<"dims[0]="<<dims[0]<<"  "<<"dims[1]="<<dims[1]<<endl;
				int i=0;
				ofstream biimagpro2016("C:\\biimagpro2016.TXT",ios_base::trunc );
				//for (int x = 0; x < dims[0]; x++)
			 //{
				// for(int y=0;y<dims[1];y++)
			 //   {
			 //   unsigned char* pixel = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
			 //   //pixel[0] = x*10;
				//if(pixel[0]>threshold1)bin->InsertTuple1(x+y*dims[0],255);
				//else bin->InsertTuple1(x+y*dims[0],0);
				//
			 //   }
				// //cout<<endl<<int(threshold1);
			 //} 
			 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					//unsigned char* I = static_cast<unsigned char*>(bin->getgetGetScalarPointer(x,y,0));
					unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));

					gimagematrix[i]=I[0];

				  // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
					if(I[0]>threshold){imagematrix[i]=1;}
					else
					{
						imagematrix[i]=0;//cout<<I[0];
					}
				   i++;
				   biimagpro2016<<I[0]<<" ";
    
				}
				 biimagpro2016<<endl;
				 //cout<<endl<<int(threshold1);
			 } 
			 biimagpro2016.close();
			 //=====================================================================




			//==================================================================
					  SliceWin[0]->activate();
					  SliceWin[1]->activate();
					  SliceWin[2]->activate();
					  SliceWin[3]->activate();
 
						SliceSlider->activate();
						SliceSlider->value(threshold);
	

					  SliceRenderer[0]->AddActor2D(act);
					  SliceRenderer[0]->DisplayToView();
  
					  SliceRenderer[2]->AddActor2D(luminanceActor);
					  SliceRenderer[2]->ResetCamera();
					  SliceRenderer[1]->AddActor2D(plot);
					  SliceRenderer[3]->AddActor2D(binact);
 
					  SliceRenderWin[0]->Render();
					  SliceRenderWin[1]->Render();
					  SliceRenderWin[2]->Render();
					  SliceRenderWin[3]->Render();

        

					  Fl::run();
					  //iren->Start();

  
					  };
}//open_cb


void quit_cb(Fl_Widget*, void*) {exit(0);}

void binimage(unsigned char threshold1)
 {   
	 threshold=threshold1;
	 bin->Initialize();
  //vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
 for (int x = 0; x < dims[0]; x++)
 {
	 for(int y=0;y<dims[1];y++)
    {
    unsigned char* pixel = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
    //pixel[0] = x*10;
	if(pixel[0]>threshold1)bin->InsertTuple1(x+y*dims[0],255);
	else bin->InsertTuple1(x+y*dims[0],0);
	
    }
	 //cout<<endl<<int(threshold1);
 } 

 binaryimage->GetPointData()->SetScalars(bin);
 //bi->
  
 
 //binmap->Update();
  
    
 HairCrossAct->SetPosition(273+plot->GetPosition()[0]+threshold1,plot->GetPosition()[1]+200);


 char str11[10];
	_itoa_s(threshold1, str11, 10, 10);
	
	const char*s1=str11;
	 slidertxt->SetInput(s1);
   SliceSlider->value(threshold1);
  SliceWin[1]->Render();
  SliceWin[3]->Render();



  //=========================================================================
	int i=0;
				ofstream biimagpro2016("C:\\biimagpro2016.TXT",ios_base::trunc );
				
			 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					//unsigned char* I = static_cast<unsigned char*>(bin->getgetGetScalarPointer(x,y,0));
					unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
				  // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
					if(I[0]>threshold){imagematrix[i]=255;}
					else
					{
						imagematrix[i]=0;//cout<<I[0];
					}
				   i++;
				   biimagpro2016<<I[0]<<" ";
    
				}
				 biimagpro2016<<endl;
				 //cout<<endl<<int(threshold1);
			 } 
			 biimagpro2016.close();


//=========================================================================
 }
void m_SliceSlider(Fl_Widget*, void*)
{
		threshold=SliceSlider->value();
		binimage(threshold);
		
}

Fl_Menu_Item menutable[] = 
		    {
               {"&File",0,0,0,FL_SUBMENU},
               {"&Open",	FL_ALT+'o', open_cb, 0, FL_MENU_DIVIDER},
			   {"&Save",	FL_ALT+'s', save_cb, 0, FL_MENU_DIVIDER},
			   {"&Quit",	FL_ALT+'q', quit_cb, 0},
			   {0}
		
		     };
//Fl_Menu_Bar* menus[1];

void otsu_cb(Fl_Widget*, void*)
{
	if(!jpegReader)return;

	 float histo[256] ;//= {0};  
  for(int i=0;i<256;i++) histo[i]=0;

	 for(int i=0;i<histogram->GetOutput()->GetDimensions()[0];i++)   
 {  
	 int* H=static_cast<int*>(histogram->GetOutput()->GetScalarPointer(i,0,0));
     histo[i]=H[0];
	 }
 //int totalpixel = grayimage->GetDimensions()[0] *grayimage->GetDimensions()[1];  
 // 
 //for(int i=0;i<256;i++)  
 //  { histo[i] =(float) histo[i]/(float)totalpixel;//归一化直方图  
 //cout<<""<<histo[i]<<endl;}

 //float maxavgvalue = 0;  
 // 
 //for(int i=0;i<256;i++)  
 // maxavgvalue = i*histo[i];//总的灰度均值，其实在这里可将其设为0  
 // 
 //float PA = 0;//A类出现概率  
 //float PB = 0;//B类出现概率  
 //float Agrayvalue = 0;//A类灰度均值  
 //float Bgrayvalue = 0;//B类灰度均值  
 //float maxvariance = 0;  
 //float variance ;  
 //int thre;  
 // 
 //for(int i=0;i<256;i++)  
 //  {  
 //       PA += histo[i];  
 //     PB = 1-PA;  
 //   Agrayvalue += i*histo[i];//A类灰度均值  
 //   Bgrayvalue += maxavgvalue - Agrayvalue;//B类灰度均值  
 //  
 //       variance = PA*(Agrayvalue-maxavgvalue)*(Agrayvalue-maxavgvalue)+PB*(Bgrayvalue-maxavgvalue)*(Bgrayvalue-maxavgvalue);//计算类间方差  
 // 
 // 
 //    if(variance>maxvariance)  
 //      {  
 //   maxvariance = variance;  
 //   thre = i;//求得最大类间方差时的像素值，即为最佳阈值  
 //       }  
 //  }  
 
    int thresholdValue=1; // 阈值
    //int ihist[256]; // 图像直方图，256个点
    int  k; // various counters
    int n, n1, n2, gmin, gmax;
    double m1, m2, sum, csum, fmax, sb;
     
    gmin=255; gmax=0;
 // set up everything
    sum = csum = 0.0;
    n = 0;
    for (k = 0; k <= 255; k++)
    {
        sum += (double) k * (double) histo[k]; // x*f(x) 质量矩
        n += histo[k]; //f(x) 质量
    }
    if (!n)
    {
        // if n has no value, there is problems
        fprintf (stderr, "NOT NORMAL thresholdValue = 160\n");
        thresholdValue=(160);
    }
    // do the otsu global thresholding method
    fmax = -1.0;
    n1 = 0;
    for (k = 0; k < 255; k++)
    {
        n1 += histo[k];
        if (!n1) { continue; }
        n2 = n - n1;
        if (n2 == 0) { break; }
        csum += (double) k *histo[k];
        m1 = csum / n1;
        m2 = (sum - csum) / n2;
        sb = (double) n1 *(double) n2 *(m1 - m2) * (m1 - m2);
        /**//* bbg: note: can be optimized. */
        if (sb > fmax) {
            fmax = sb;
            thresholdValue = k;
        }
    }
    // at this point we have our thresholding value，debug code to display thresholding values
    
   
  binimage(thresholdValue);
}


// 计算当前位置的能量熵

typedef enum {back,object} entropy_state;
double caculateCurrentEntropy(float * Histogram1, int cur_threshold, entropy_state state)
{
int start,end;
if(state == back) 
{
  start = 0;
  end = cur_threshold; 
}
else
{
  start = cur_threshold;
  end = 256;
}
int  total = 0;
for(int i = start; i < end; i++) 
{
  total += (int)Histogram1[i];
}
double cur_entropy = 0.0;
for(int i = start; i < end; i++)
{
  //if((int)Histogram1[i]==0) continue;
	if((int)Histogram1[i]!=0) {
  double percentage=Histogram1[i]/total;
  cur_entropy+=-percentage * logf(percentage); // 能量的定义公式
 // cout<<cur_entropy;
	}
}
return cur_entropy;
}
void maxent_cb(Fl_Widget*, void*)
{
	if(!jpegReader)return;

	 float histo[256] ;//= {0};  
  for(int i=0;i<256;i++) histo[i]=0;

	 for(int i=0;i<histogram->GetOutput()->GetDimensions()[0];i++)   
 {  
	 int*H=static_cast<int*>(histogram->GetOutput()->GetScalarPointer(i,0,0));
     histo[i]=H[0];
	// cout<<"H[0]"<<H[0]<<endl;
 }  
  
 int totalpixel = grayimage->GetDimensions()[0] *grayimage->GetDimensions()[1];  


// 寻找最大熵阈值并分割

//CvHistogram * hist  = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY, HistogramRange);
//    cvCalcHist(&src, hist);
double maxentropy = -1.0;
int max_index ;
// 循环测试每个分割点，寻找到最大的阈值分割点
for(int i = 0; i < 256; i++)
{
  double cur_entropy = caculateCurrentEntropy(histo, i, object) + caculateCurrentEntropy(histo, i, back);
  if(cur_entropy > maxentropy)
  {
   maxentropy = cur_entropy;
   max_index = i;
  }
}

binimage(max_index);
}

//===================================================================================================================
double RobertsOperator1[4]={1,0,
	                       0,-1};
double RobertsOperator2[4]={0,1,
	                       -1,0};
double PrewittOperatory[9]={-1,-1,-1,
	                        0,0,0,
                            1,1,1};
double PrewittOperatorx[9]={-1,0,1,
	                        -1,0,1,
                            -1,0,1};
double Sobely[9]={-1,-2,-1,
	               0,0,0,
                   1,2,1};
double Sobelx[9]={-1,0,1,
	              -2,0,2,
                  -1,0,1};
double GaussianF[25]={1/273,4/273,7/273,4/273,1/273,
	                  4/273,16/273,26/273,16/273,4/273,
					  7/273,26/273,41/273,26/273,7/273,
					  4/273,16/273,26/273,16/273,4/273,
					  1/273,4/273,7/273,4/273,1/273};

void convolve(int* input,int*output,double*filter,int n,int h,int w)
{
	int edgex=n/2;int edgey=n/2;//n represents the width of the filter window;
	for(int i=edgey;i<h-edgey;i++)
	{
		for(int j=edgex;j<w-edgex;j++)
		{
			for(int y=0;y<n;y++)
			{
				for(int x=0;x<n;x++)
				{
					output[j*h+i]+=input[(j+x-edgex)*h+(i+y-edgey)]*filter[x*n+y];
				}
			}
		}
	}
}

void medianf(int* input,int*output,int n,int h,int w)
{
	int edge=n/2;
	for(int i=edge;i<h-edge;i++)
	{
		for(int j=edge;j<w-edge;j++)
		{   
			int* f=new int[n*n];
		    int k=0;
			for(int y=0;y<n;y++)
			{
				for(int x=0;x<n;x++)
				{
					f[k]=input[(j+x-edge)*h+(i+y-edge)];
					k++;
					//output[j-1+(i-1)*(h-2)]+=input[j+x+(i+y)*h]*filter[x+1+(y+1)*3];
				}
			}
			sort(f,f+n*n);
			output[j*h+i]=f[(n*n)/2];
			delete [] f;
		}
	}
	
}

void m_roberts(Fl_Widget*, void*)
{
	wsize->value("2");
	inp0->value("1");inp1->value("0");
    inp5->value("0");inp6->value("-1");
};
void m_prewitt(Fl_Widget*, void*)
{
	wsize->value("3");
	inp0->value("-1");inp1->value("-1");inp2->value("-1");
	inp5->value("0");inp6->value("0");inp7->value("0");
	inp10->value("1");inp11->value("1");inp12->value("1");
}
void m_sobel(Fl_Widget*, void*)
{
	wsize->value("3");
	inp0->value("-1");inp1->value("-2");inp2->value("-1");
	inp5->value("0");inp6->value("0");inp7->value("0");
	inp10->value("1");inp11->value("2");inp12->value("1");
}
void m_gaussian(Fl_Widget*, void*)
{
	wsize->value("5");
	inp0->value("0.00366");inp1->value("0.01465");inp2->value("0.02564");inp3->value("0.01465");inp4->value("0.00366");
	inp5->value("0.01465");inp6->value("0.05861");inp7->value("0.09524");inp8->value("0.05861");inp9->value("0.01465");
	inp10->value("0.02564");inp11->value("0.09524");inp12->value("0.15018");inp13->value("0.09524");inp14->value("0.02564");
	inp15->value("0.01465");inp16->value("0.05861");inp17->value("0.09524");inp18->value("0.05861");inp19->value("0.01465");
	inp20->value("0.00366");inp21->value("0.01465");inp22->value("0.02564");inp23->value("0.01465");inp24->value("0.00366");
}
void m_median(Fl_Widget*, void*)
{
	if(!jpegReader)return;
	wsize->value("M3");
	int n=3;
	//vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
	bin->Initialize();
	int *imagematrix=new int[dims[0]*dims[1]];
	int i=0;
    for (int x=0; x <dims[0]; x++)
    {
	      for(int y=0;y<dims[1];y++)
          {
		       unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
               imagematrix[i]=I[0];
	           i++;
          }
	} 

	int *output=new int[dims[0]*dims[1]];
	for(int i=0;i<dims[0]*dims[1];i++)
	{
		output[i]=0;
	};

	medianf(imagematrix,output,3,dims[1],dims[0]);

       int j=0;
       for (int x=0; x <dims[0]; x++)
       {
	       for(int y=0;y<dims[1];y++)
           {
               bin->InsertTuple1(x+y*dims[0],output[j]);
	           j++;
               
	       }
	           //cout<<endl<<int(threshold1);
       } 
	 
	   binaryimage->GetPointData()->SetScalars(bin);
       //binmap->Update();
	   delete [] output;
	   delete [] imagematrix;
	   SliceWin[3]->Render();
}

void m_Do(Fl_Widget*, void*)
{
	if(!jpegReader)return;
	//vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
	bin->Initialize();
	int *imagematrix=new int[dims[0]*dims[1]];
	
	cout<<"dims[0]="<<dims[0]<<"  "<<"dims[1]="<<dims[1]<<endl;
	int i=0;
 for (int x=0; x <dims[0]; x++)
 {
	 for(int y=0;y<dims[1];y++)
    {
		unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
      // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
	   imagematrix[i]=I[0];
	   i++;
    
	}
	 //cout<<endl<<int(threshold1);
 } 
 //cout<<imagematrix[1]<<" ";
 // binmap->Update();
 int n=0;

 if(atof(wsize->value())==2)n=2;
 if(atof(wsize->value())==3)n=3;
 if(atof(wsize->value())==5)n=5;

	int e=n/2;
	//int *output=new int[(dims[0]-2*e)*(dims[1]-2*e)];
	int *output=new int[dims[0]*dims[1]];
	for(int i=0;i<dims[0]*dims[1];i++)
	{
		output[i]=0;
	};
	double* w=new double[n*n];
	//cout<<wsize->value()<<"  ";
	if(n==2)
		{
		   w[0]=atof(inp0->value());
		   w[1]=atof(inp1->value());
		   w[2]=atof(inp5->value());
		   w[3]=atof(inp6->value());
		   convolve(imagematrix,output,w,n,dims[1],dims[0]);
	    }
	else if(n==3)
		{ 
			w[0]=atof(inp0->value());
		    w[1]=atof(inp1->value());
			w[2]=atof(inp2->value());
		    w[3]=atof(inp5->value());
		    w[4]=atof(inp6->value());
		    w[5]=atof(inp7->value());
			w[6]=atof(inp10->value());
		    w[7]=atof(inp11->value());
		    w[8]=atof(inp12->value());
		  convolve(imagematrix,output,w,n,dims[1],dims[0]);
		}
	else if(n==5)
		{
			w[0]=atof(inp0->value());
		    w[1]=atof(inp1->value());
			w[2]=atof(inp2->value());
			w[3]=atof(inp3->value());
		    w[4]=atof(inp4->value());
			w[5]=atof(inp5->value());
			w[6]=atof(inp6->value());
		    w[7]=atof(inp7->value());
			w[8]=atof(inp8->value());
			w[9]=atof(inp9->value());
		    w[10]=atof(inp10->value());
			w[11]=atof(inp11->value());
		    w[12]=atof(inp12->value());
			w[13]=atof(inp13->value());
			w[14]=atof(inp14->value());
		    w[15]=atof(inp15->value());
			w[16]=atof(inp16->value());
		    w[17]=atof(inp17->value());
			w[18]=atof(inp18->value());
			w[19]=atof(inp19->value());
		    w[20]=atof(inp20->value());
			w[21]=atof(inp21->value());
		    w[22]=atof(inp22->value());
			w[23]=atof(inp23->value());
			w[24]=atof(inp24->value());
		    convolve(imagematrix,output,w,n,dims[1],dims[0]);
		}
	else
		{
			text->value("The filter width\n should be 2,\n 3,or 5.");
			return;
		}
	
	 // cout<<output[3]<<"  ";
		int j=0;
       for (int x=0; x <dims[0]; x++)
       {
	       for(int y=0;y<dims[1];y++)
           {
               bin->InsertTuple1(x+y*dims[0],output[j]);
	           j++;
               
	       }
	           //cout<<endl<<int(threshold1);
       } 
	 
	   binaryimage->GetPointData()->SetScalars(bin);
     // binmap->Update();
	   delete [] w;
	   delete [] output;
	   delete [] imagematrix;
	   SliceWin[3]->Render();
};
void do_dilate(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	if(size==2)
	{
		int* in=new int [(dims[0]+1*2)*(dims[1]+1*2)];
				
		for(int i=0;i<dims[0]+1*2;i++)
		{
			for(int j=0;j<dims[1]+1*2;j++)
			{
				in[i*(dims[1]+1*2)+j]=0;
			}
		}

		for(int i=1;i<dims[0]+1;i++)
		{
			for(int j=1;j<dims[1]+1;j++)
			{
				in[i*(dims[1]+1*2)+j]=input[(i-1)*(dims[1])+j-1];
			}
		}

		
		for(int i=1;i<dims[0]+1;i++)
		{

					for(int j=1;j<dims[1]+1;j++)
					{
						if(in[i*(dims[1]+1*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+1*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=1;
						}
					}

		}
		cout<<endl<<"dil  done";
		//delete [] a00;delete [] a01;delete [] a10;delete [] a11;
		
		
		
		//delete [] output;
		delete [] in;
		return;
	}
	else
	{
		int* in=new int [(dims[0]+2*2)*(dims[1]+2*2)];
				
		for(int i=0;i<dims[0]+2*2;i++)
		{
			for(int j=0;j<dims[1]+2*2;j++)
			{
				in[i*(dims[1]+2*2)+j]=0;
			}
		}

		for(int i=2;i<dims[0]+2;i++)
		{
			for(int j=2;j<dims[1]+2;j++)
			{
				in[i*(dims[1]+2*2)+j]=input[(i-2)*(dims[1])+j-2];
			}
		}

		
		for(int i=2;i<dims[0]+2;i++)
		{

					for(int j=2;j<dims[1]+2;j++)
					{
						if(in[i*(dims[1]+2*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+2*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=1;
						}
					}

		}
		cout<<endl<<"dil  done";
		return;

		delete [] in;

	}
}
//====================================================================================
void m_dilation(Fl_Widget*, void*)
{
	if(!jpegReader)return;
	//vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
	//binimage(threshold);
	

 //for (int x=0; x <dims[0]; x++)
 //{
	// for(int y=0;y<dims[1];y++)
 //   {
	//	unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
 //     // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
	//   imagematrix[i]=I[0];
	//   i++;
 //   
	//}
	// //cout<<endl<<int(threshold1);
 //} 

	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_dilate(imagematrix,ot,mt,xx,yy,ks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+y*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//=====================================================================================================================


void do_erode(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	if(size==2)
	{
		int* in=new int [(dims[0]+1*2)*(dims[1]+1*2)];
				
		for(int i=0;i<dims[0]+1*2;i++)
		{
			for(int j=0;j<dims[1]+1*2;j++)
			{
				in[i*(dims[1]+1*2)+j]=0;
			}
		}

		for(int i=1;i<dims[0]+1;i++)
		{
			for(int j=1;j<dims[1]+1;j++)
			{
				in[i*(dims[1]+1*2)+j]=input[(i-1)*(dims[1])+j-1];
			}
		}

		
		for(int i=1;i<dims[0]+1;i++)
		{

					for(int j=1;j<dims[1]+1;j++)
					{
						
						if(in[i*(dims[1]+1*2)+j]!=0)
						{
							int b=1;
							if(mt[0][0]){if(in[(i+0-ox)*(dims[1]+1*2)+j+0-oy]==0)b=0;}
						    if(mt[0][1]){if(in[(i+0-ox)*(dims[1]+1*2)+j+1-oy]==0)b=0;}
							if(mt[1][0]){if(in[(i+1-ox)*(dims[1]+1*2)+j+0-oy]==0)b=0;}
							if(mt[1][1]){if(in[(i+1-ox)*(dims[1]+1*2)+j+1-oy]==0)b=0;}
							output[i*(dims[1]+1*2)+j]=b;
						}

					}

		}
		cout<<endl<<"ero  done";
		//delete [] a00;delete [] a01;delete [] a10;delete [] a11;
		
		
		
		//delete [] output;
		delete [] in;
		return;
	}
	else
	{
		int* in=new int [(dims[0]+2*2)*(dims[1]+2*2)];
				
		for(int i=0;i<dims[0]+2*2;i++)
		{
			for(int j=0;j<dims[1]+2*2;j++)
			{
				in[i*(dims[1]+2*2)+j]=0;
			}
		}

		for(int i=2;i<dims[0]+2;i++)
		{
			for(int j=2;j<dims[1]+2;j++)
			{
				in[i*(dims[1]+2*2)+j]=input[(i-2)*(dims[1])+j-2];
			}
		}

		
		for(int i=2;i<dims[0]+2;i++)
		{

					for(int j=2;j<dims[1]+2;j++)
					{
							
						if(in[i*(dims[1]+2*2)+j]!=0)
						{
							int b=1;
							if(mt[0][0]){if(in[(i+0-ox)*(dims[1]+2*2)+j+0-oy]==0)b=0;}
							if(mt[0][1]){if(in[(i+0-ox)*(dims[1]+2*2)+j+1-oy]==0)b=0;}
							if(mt[0][2]){if(in[(i+0-ox)*(dims[1]+2*2)+j+2-oy]==0)b=0;}
							if(mt[1][0]){if(in[(i+1-ox)*(dims[1]+2*2)+j+0-oy]==0)b=0;}
							if(mt[1][1]){if(in[(i+1-ox)*(dims[1]+2*2)+j+1-oy]==0)b=0;}
							if(mt[1][2]){if(in[(i+1-ox)*(dims[1]+2*2)+j+2-oy]==0)b=0;}
							if(mt[2][0]){if(in[(i+2-ox)*(dims[1]+2*2)+j+0-oy]==0)b=0;}
							if(mt[2][1]){if(in[(i+2-ox)*(dims[1]+2*2)+j+1-oy]==0)b=0;}
							if(mt[2][2]){if(in[(i+2-ox)*(dims[1]+2*2)+j+2-oy]==0)b=0;}
							output[i*(dims[1]+2*2)+j]=b;
						}
						
					}

		}
		delete [] in;
		return;

		

	}

}
void m_erosion(Fl_Widget*, void*)
{
		if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_erode(imagematrix,ot,mt,xx,yy,ks);
	cout<<"done";
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+y*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
	}
//=====================================================================================================================
void do_closing(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1]+2*c)+j]=0;
						
					}

		}

	do_dilate(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0])*(dims[1])];
	/*for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						
						if(ot1[i*(dims[1]+2*c)+j])ot1[i*(dims[1]+2*c)+j]=255;
						
					}

		}*/
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						ot1[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 
	do_erode(ot1,output,mt,ox,oy, size);

	delete [] ot;
	delete [] ot1;
}
void m_closing(Fl_Widget*, void*)
{
	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_closing(imagematrix,ot,mt,xx,yy,ks);

	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				        i++;
				   
    
				}
				 
			 } 

for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	   {
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+y*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//=====================================================================================================================

void do_opening(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}

	do_erode(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0])*(dims[1])];
	/*for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						
						if(ot1[i*(dims[1]+2*c)+j])ot1[i*(dims[1]+2*c)+j]=255;
						
					}

		}*/
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						ot1[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 
	do_dilate(ot1,output,mt,ox,oy, size);
	delete [] ot;
	delete [] ot1;
}

void m_opening(Fl_Widget*, void*)
{

	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_opening(imagematrix,ot,mt,xx,yy,ks);

	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[i]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

        for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	   {
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+y*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//========================================================================================================================
void do_distance(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int ones=0;
	for(int i=0;i<dims[0];i++)
		{
					for(int j=0;j<dims[1];j++)
					{
						if(input[i*(dims[1])+j])ones=ones+1;
					}
		}

	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	int n=0;
	int m=0;
	while(n<ones)
	{
		m=m+1;
			for(int i=0;i<dims[0]+2*c;i++)
				{
							for(int j=0;j<dims[1]+2*c;j++)
							{
								ot[i*(dims[1]+2*c)+j]=0;
							}
				}

			do_erode(input,ot,mt,ox,oy, size);
			int i=0;
			 for (int x=c; x <dims[0]+c; x++)
					 {
						 for(int y=c;y<dims[1]+c;y++)
						{
					
								if(input[(x-c)*(dims[1])+y-c]-ot[x*(dims[1]+2*c)+y])
								{
									output[x*(dims[1]+2*c)+y]=m;//cout<<I[0];
									n=n+1;
								}
					   
						   i++;
				   
    
						}
				 
					 } 

			  i=0;
	         for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						input[(x-c)*(dims[1])+y-c]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 
	
	}
	delete [] ot;
}

void m_distance(Fl_Widget*, void*)
{

	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	
	int c=ceil(ks/2.0);
	int * output =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						output[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<output<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	
	do_distance(imagematrix,output,mt,xx,yy,ks);

	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[(x-c)*(dims[1])+y-c]=output[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	   {
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x-c+(y-c)*(dims[0]),output[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] output;
   
  
 
  SliceWin[3]->Render();
}
//=======================================================================================================================
void do_skeletonex(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	
	for (int x=1; x <dims[0]-1; x++)
	{
		for(int y=1;y<dims[1]-1;y++)
		{
					

			if(!((input[x*(dims[1])+y]<input[x*(dims[1])+y-1])||(input[x*(dims[1])+y]<input[x*(dims[1])+y+1])
				||(input[x*(dims[1])+y]<input[(x-1)*(dims[1])+y-1])||(input[(x)*(dims[1])+y]<input[(x-1)*(dims[1])+y+1])
				||(input[x*(dims[1])+y]<input[(x+1)*(dims[1])+y-1])||(input[(x)*(dims[1])+y]<input[(x+1)*(dims[1])+y+1])
				||(input[x*(dims[1])+y]<input[(x+1)*(dims[1])+y])||(input[(x)*(dims[1])+y]<input[(x+1)*(dims[1])+y])))
				output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
			//if((input[x*(dims[1])+y]>input[x*(dims[1])+y-1])&&(input[x*(dims[1])+y]>=input[x*(dims[1])+y+1]))output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
			//if((input[x*(dims[1])+y]<=input[(x-1)*(dims[1])+y-1])&&(input[x*(dims[1])+y]<input[x*(dims[1])+y+1]))output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
			//if((input[x*(dims[1])+y]<input[x*(dims[1])+y-1])&&(input[x*(dims[1])+y]<=input[x*(dims[1])+y+1]))output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
			//if((input[x*(dims[1])+y]>input[(x-1)*(dims[1])+y])&&(input[x*(dims[1])+y]>input[(x+1)*(dims[1])+y]))output[x*(dims[1]+2*c)+y]=1;
		
		}
				 
	} 
	//for (int y=c; y <dims[1]+c; y++)
	//{
	//	for(int x=c;x<dims[0]+c;x++)
	//	{
	//				
	//		if((input[y*(dims[0])+x]>=input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]>input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		if((input[y*(dims[0])+x]>input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]>=input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		if((input[y*(dims[0])+x]<=input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]<input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		if((input[y*(dims[0])+x]<input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]<=input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		//if((input[x*(dims[1])+y]>input[(x-1)*(dims[1])+y])&&(input[x*(dims[1])+y]>input[(x+1)*(dims[1])+y]))output[x*(dims[1]+2*c)+y]=1;
	//	
	//	}
	//			 
	//} 
}



void m_skeletonex(Fl_Widget*, void*)
{

	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	
	int c=ceil(ks/2.0);
	int * output =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						output[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<output<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	
	do_skeletonex(imagematrix,output,mt,xx,yy,ks);

	cout<<"done";
	
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
					imagematrix[(x-c)*(dims[1])+y-c]=output[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

//for(int i=0;i<dims[0]+2*c;i++)
//		{
//
//					for(int j=0;j<dims[1]+2*c;j++)
//					{
//						//cout<<ot[i*(dims[1]+2*c)+j];
//						if(output[i*(dims[1]+2*c)+j])output[i*(dims[1]+2*c)+j]=255;
//						
//					}
//
//		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	   {
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x-c+(y-c)*(dims[0]),output[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] output;
   
  
 
  SliceWin[3]->Render();
}
//=======================================================================================================================
void do_skeletonre(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	//int c=ceil(size/2.0);
	//
	//for (int x=c; x <dims[0]+c; x++)
	//{
	//	for(int y=c;y<dims[1]+c;y++)
	//	{
	//				
	//		if((input[x*(dims[1])+y]>=input[x*(dims[1])+y-1])&&(input[x*(dims[1])+y]>input[x*(dims[1])+y+1]))output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
	//		if((input[x*(dims[1])+y]>input[x*(dims[1])+y-1])&&(input[x*(dims[1])+y]>=input[x*(dims[1])+y+1]))output[x*(dims[1]+2*c)+y]=input[x*(dims[1])+y];//cout<<I[0];
	//		//if((input[x*(dims[1])+y]>input[(x-1)*(dims[1])+y])&&(input[x*(dims[1])+y]>input[(x+1)*(dims[1])+y]))output[x*(dims[1]+2*c)+y]=1;
	//	
	//	}
	//			 
	//} 
	//for (int y=c; y <dims[1]+c; y++)
	//{
	//	for(int x=c;x<dims[0]+c;x++)
	//	{
	//				
	//		if((input[y*(dims[0])+x]>=input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]>input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		if((input[y*(dims[0])+x]>input[y*(dims[0])+x-1])&&(input[y*(dims[0])+x]>=input[y*(dims[0])+x+1]))output[y*(dims[0]+2*c)+x]=input[x*(dims[1])+y];//cout<<I[0];
	//		//if((input[x*(dims[1])+y]>input[(x-1)*(dims[1])+y])&&(input[x*(dims[1])+y]>input[(x+1)*(dims[1])+y]))output[x*(dims[1]+2*c)+y]=1;
	//	
	//	}
	//			 
	//} 
	int maxi=1;
	for(int i=0;i<dims[0];i++)
		{
					for(int j=0;j<dims[1];j++)
					{
						if(input[i*(dims[1])+j]>maxi)maxi=input[i*(dims[1])+j];
					}
		}

        int c=ceil(size/2.0);

	    int i=0;
	    for (int x=c; x <dims[0]+c; x++)
		{
			for(int y=c;y<dims[1]+c;y++)
			{
					if(input[(x-c)*(dims[1])+y-c]==1)
					{

									
						output[x*(dims[1]+2*c)+y]=1;
							//cout<<I[0];
									
						input[(x-c)*(dims[1])+y-c]=0;
					}
					   
				i++;
				   
    
			}
				 
		}

	
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	int n=2;
	//int m=0;
	while(n<=maxi)
	{
		//m=m+1;
			
		for(int m=0;m<n-1;m++)
		{
			    for(int i=0;i<dims[0]+2*c;i++)
				{
							for(int j=0;j<dims[1]+2*c;j++)
							{
								ot[i*(dims[1]+2*c)+j]=0;
							}
				}
			   do_dilate(input,ot,mt,ox,oy, size);
			   //if(m<n-2)
			  // {
					   i=0;
					 for (int x=c; x <dims[0]+c; x++)
					 {
						 for(int y=c;y<dims[1]+c;y++)
						{
					
							input[(x-c)*(dims[1])+y-c]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
						   i++;
				   
    
						}
				 
					 } 
			   //}

		}

			i=0;
	    for (int x=c; x <dims[0]+c; x++)
		{
			for(int y=c;y<dims[1]+c;y++)
			{
					if((input[i]>=1)&&(input[i]<=n))
					{

									
						output[x*(dims[1]+2*c)+y]=input[(x-c)*(dims[1])+y-c];
							//cout<<I[0];
									
						input[(x-c)*(dims[1])+y-c]=0;
					}
					   
				i++;
				   
    
			}
				 
		}

		n=n+1;
	        
	
	}
	delete [] ot;
}

void m_skeletonre(Fl_Widget*, void*)
{
	
	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	
	int c=ceil(ks/2.0);
	int * output =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						output[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<output<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	
	do_skeletonre(imagematrix,output,mt,xx,yy,ks);

	cout<<"done";
	
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
					imagematrix[(x-c)*(dims[1])+y-c]=output[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						if(output[i*(dims[1]+2*c)+j])output[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	   {
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x-c+(y-c)*(dims[0]),output[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] output;
   
  
 
  SliceWin[3]->Render();

}

void do_gdilate(int* input,int* output,int gt[][3],int ox,int oy,int size)
{
	int a=0; int b1=0;int c1=0;
	int d1=0;int e1=0;int f1=0;
	int g1=0;int h1=0;int i1=0;
	if(size==2)
	{
		int* in=new int [(dims[0])*(dims[1])];
				
		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=0;
			}
		}

		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=input[(i)*(dims[1])+j];
			}
		}
		
		
		for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						 /*a=gt[0][0]+in[(i+0-ox)*(dims[1]+1*2)+j+0-oy];
						 b1=gt[0][1]+in[(i+0-ox)*(dims[1]+1*2)+j+1-oy];
						 c1=gt[1][0]+in[(i+1-ox)*(dims[1]+1*2)+j+0-oy];
						 d1=gt[1][1]+in[(i+1-ox)*(dims[1]+1*2)+j+1-oy];*/
						//if()break;
						


						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 a=gt[0][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            a=gt[0][0]+in[(i+0-ox)*(dims[1])+j+0-oy];
						}
						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 b1= gt[0][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            b1=gt[0][1]+in[(i+0-ox)*(dims[1])+j+1-oy];
						}
						  if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 c1= gt[1][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            c1=gt[1][0]+in[(i+1-ox)*(dims[1])+j+0-oy];
						}
						  if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 d1=gt[1][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            d1=gt[1][1]+in[(i+1-ox)*(dims[1])+j+1-oy];
						}
					//	if(!((a==gt[0][0])&& (b1== gt[0][1])&&(c1== gt[1][0])&&(d1==gt[1][1])))
					//	{
							 if(a<b1)a=b1;
							 if(a<c1)a=c1;
							 if(a<d1)a=d1;
							 if(a>255)a=255;
							//output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=a;
							 output[(i+0)*(dims[1])+j+0]=a;
					//	}
						/*if(in[i*(dims[1]+1*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+1*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=1;
						}*/
					}

		}
		cout<<endl<<"dil  done";
		//delete [] a00;delete [] a01;delete [] a10;delete [] a11;
		
		
		
		//delete [] output;
		delete [] in;
		return;
	}
	else
	{
		int* in=new int [(dims[0])*(dims[1])];
				
		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=0;
			}
		}

		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=input[(i)*(dims[1])+j];
			}
		}

		
		for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						 /*a= gt[0][0]+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						 b1=gt[0][1]+in[(i+0-ox)*(dims[1]+2*2)+j+1-oy];
						 c1=gt[0][2]+in[(i+0-ox)*(dims[1]+2*2)+j+2-oy];
						 d1=gt[1][0]+in[(i+1-ox)*(dims[1]+2*2)+j+0-oy];
						 e1=gt[1][1]+in[(i+1-ox)*(dims[1]+2*2)+j+1-oy];
						 f1=gt[1][2]+in[(i+1-ox)*(dims[1]+2*2)+j+2-oy];
						 g1=gt[2][0]+in[(i+2-ox)*(dims[1]+2*2)+j+0-oy];
						 h1=gt[2][1]+in[(i+2-ox)*(dims[1]+2*2)+j+1-oy];
						 i1=gt[2][2]+in[(i+2-ox)*(dims[1]+2*2)+j+2-oy];*/
						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 a=gt[0][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                             a= gt[0][0]+in[(i+0-ox)*(dims[1])+j+0-oy];
						}
						// for(int j=0;j<dims[1]+2*2;j++)
					
						if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 b1=gt[0][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                             b1=gt[0][1]+in[(i+0-ox)*(dims[1])+j+1-oy];
						}
						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 c1= gt[0][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            c1=gt[0][2]+in[(i+0-ox)*(dims[1])+j+2-oy];
						}
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 d1=gt[1][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            d1=gt[1][0]+in[(i+1-ox)*(dims[1])+j+0-oy];
						}
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 e1=gt[1][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            e1=gt[1][1]+in[(i+1-ox)*(dims[1])+j+1-oy];
						}
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 f1= gt[1][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            f1=gt[1][2]+in[(i+1-ox)*(dims[1])+j+2-oy];
						}
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 g1=gt[2][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            g1=gt[2][0]+in[(i+2-ox)*(dims[1])+j+0-oy];
						}
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 h1=gt[2][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            h1=gt[2][1]+in[(i+2-ox)*(dims[1])+j+1-oy];
						}
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 i1= gt[2][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            i1=gt[2][2]+in[(i+2-ox)*(dims[1])+j+2-oy];
						}
						 if(!((a==gt[0][0])&& (b1== gt[0][1])&&(c1== gt[0][2])&&(d1==gt[1][0])&&(e1==gt[1][1])&& (f1== gt[1][2])&&(g1== gt[2][0])&&(h1==gt[2][1])&&(i1==gt[2][2])))
						 {
							 if(a<b1)a=b1;
							 if(a<c1)a=c1;
							 if(a<d1)a=d1;
							 if(a<e1)a=e1;
							 if(a<f1)a=f1;
							 if(a<g1)a=g1;
							 if(a<h1)a=h1;
							 if(a<i1)a=i1;
							  if(a>255)a=255;
							//output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=a;
							 output[(i+0)*(dims[1])+j+0]=a;
						 }
						/*if(in[i*(dims[1]+2*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+2*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=1;
						}*/
					}

		}
		cout<<endl<<"dil  done";
		return;

		delete [] in;

	}
}
void g_dilation(Fl_Widget*, void*)
{
	
	if(!jpegReader)return;
	//vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
	//binimage(threshold);
	

 //for (int x=0; x <dims[0]; x++)
 //{
	// for(int y=0;y<dims[1];y++)
 //   {
	//	unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
 //     // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
	//   imagematrix[i]=I[0];
	//   i++;
 //   
	//}
	// //cout<<endl<<int(threshold1);
 //} 

	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(gt[0][2]||gt[1][2]||gt[2][2]||gt[2][0]||gt[2][1])
	{
		gks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<gxx<<gyy<<gks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_gdilate(gimagematrix,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();

	delete [] ot;
 
  SliceWin[3]->Render();

}

//=============================================================
void g_reset(Fl_Widget*, void*)
{
	if(!jpegReader)return;
	int i=0;
	         for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
					unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));

					gimagematrix[i]=I[0];

				
					
				   i++;
				   
    
				}
				
			 } 
}
//=======================================================================================



void do_gerode(int* input,int* output,int gt[][3],int ox,int oy,int size)
{
	int a=0; int b1=0;int c1=0;
	int d1=0;int e1=0;int f1=0;
	int g1=0;int h1=0;int i1=0;
	if(size==2)
	{
		int* in=new int [(dims[0])*(dims[1])];
				
		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=0;
			}
		}

		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=input[(i)*(dims[1])+j];
			}
		}
		
		
		for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 a=-gt[0][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            a=-gt[0][0]+in[(i+0-ox)*(dims[1])+j+0-oy];
						}
						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 b1= -gt[0][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            b1=-gt[0][1]+in[(i+0-ox)*(dims[1])+j+1-oy];
						}
						  if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 c1=-gt[1][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            c1=-gt[1][0]+in[(i+1-ox)*(dims[1])+j+0-oy];
						}
						  if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 d1=-gt[1][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            d1=-gt[1][1]+in[(i+1-ox)*(dims[1])+j+1-oy];
						}
						if(!((a==-gt[0][0])&& (b1== -gt[0][1])&&(c1== -gt[1][0])&&(d1==-gt[1][1])) )
						{
							 if(a>b1)a=b1;
							 if(a>c1)a=c1;
							 if(a>d1)a=d1;
							  if(a<0)a=0;
							//output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=a;
							 output[(i+0)*(dims[1])+j+0]=a;
						}

						/*if(in[i*(dims[1]+1*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=in[i*(dims[1]+1*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=in[i*(dims[1]+1*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+1*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+1*2)+j+1-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+1*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+1*2)+j+1-oy]=1;
						}*/
					}

		}
		cout<<endl<<"dil  done";
		//delete [] a00;delete [] a01;delete [] a10;delete [] a11;
		
		
		
		//delete [] output;
		delete [] in;
		return;
	}
	else
	{
		int* in=new int [(dims[0])*(dims[1])];
				
		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=0;
			}
		}

		for(int i=0;i<dims[0];i++)
		{
			for(int j=0;j<dims[1];j++)
			{
				in[i*(dims[1])+j]=input[(i)*(dims[1])+j];
			}
		}

		
		for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						
						if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 a= -gt[0][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                             a= -gt[0][0]+in[(i+0-ox)*(dims[1])+j+0-oy];
						};
						 
					
						if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 b1= -gt[0][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                             b1=-gt[0][1]+in[(i+0-ox)*(dims[1])+j+1-oy];
						};
						 if(((i+0-ox)<0)||((i+0-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 c1= -gt[0][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            c1=-gt[0][2]+in[(i+0-ox)*(dims[1])+j+2-oy];
						};
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 d1= -gt[1][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            d1=-gt[1][0]+in[(i+1-ox)*(dims[1])+j+0-oy];
						};
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 e1=-gt[1][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            e1=-gt[1][1]+in[(i+1-ox)*(dims[1])+j+1-oy];
						};
						 if(((i+1-ox)<0)||((i+1-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 f1=-gt[1][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            f1=-gt[1][2]+in[(i+1-ox)*(dims[1])+j+2-oy];
						};
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+0-oy)<0)||((j+0-oy)>=(dims[1])))
						{
							 g1= -gt[2][0];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            g1=-gt[2][0]+in[(i+2-ox)*(dims[1])+j+0-oy];
						};
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+1-oy)<0)||((j+1-oy)>=(dims[1])))
						{
							 h1= -gt[2][1];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            h1=-gt[2][1]+in[(i+2-ox)*(dims[1])+j+1-oy];
						};
						 if(((i+2-ox)<0)||((i+2-ox)>=(dims[0]))||((j+2-oy)<0)||((j+2-oy)>=(dims[1])))
						{
							 i1=-gt[2][2];//-gt[0][0];//+in[(i+0-ox)*(dims[1]+2*2)+j+0-oy];
						}else
						{
                            i1=-gt[2][2]+in[(i+2-ox)*(dims[1])+j+2-oy];
						};
						if(!((a==-gt[0][0])&& (b1== -gt[0][1])&&(c1== -gt[0][2])&&(d1==-gt[1][0])&&(e1==-gt[1][1])&& (f1== -gt[1][2])&&(g1== -gt[2][0])&&(h1==-gt[2][1])&&(i1==-gt[2][2])))
						 { 
							 if(a>b1)a=b1;
							 if(a>c1)a=c1;
							 if(a>d1)a=d1;
							 if(a>e1)a=e1;
							 if(a>f1)a=f1;
							 if(a>g1)a=g1;
							 if(a>h1)a=h1;
							 if(a>i1)a=i1;
							  if(a<0)a=0;
							//output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=a;
							 output[(i+0)*(dims[1])+j+0]=a;
						}
						/*if(in[i*(dims[1]+2*2)+j]>1)
						{
								if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=in[i*(dims[1]+2*2)+j]-1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=in[i*(dims[1]+2*2)+j]-1;
								
						}
						else if(in[i*(dims[1]+2*2)+j]==1)
						{
							    if(mt[0][0])output[(i+0-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[0][1])output[(i+0-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[0][2])output[(i+0-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[1][0])output[(i+1-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[1][1])output[(i+1-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[1][2])output[(i+1-ox)*(dims[1]+2*2)+j+2-oy]=1;
								if(mt[2][0])output[(i+2-ox)*(dims[1]+2*2)+j+0-oy]=1;
								if(mt[2][1])output[(i+2-ox)*(dims[1]+2*2)+j+1-oy]=1;
								if(mt[2][2])output[(i+2-ox)*(dims[1]+2*2)+j+2-oy]=1;
						}*/
					}

		}
		cout<<endl<<"erosion  done";
		return;

		delete [] in;

	};
};
void g_erosion(Fl_Widget*, void*)
{
	
	if(!jpegReader)return;
	//vtkSmartPointer<vtkFloatArray> bi=vtkFloatArray::New();
	//binimage(threshold);
	

 //for (int x=0; x <dims[0]; x++)
 //{
	// for(int y=0;y<dims[1];y++)
 //   {
	//	unsigned char* I = static_cast<unsigned char*>(grayimage->GetScalarPointer(x,y,0));
 //     // int*I=static_cast<int*>(grayimage->GetScalarPointer(x,y,0));
	//   imagematrix[i]=I[0];
	//   i++;
 //   
	//}
	// //cout<<endl<<int(threshold1);
 //} 

	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(gt[0][2]||gt[1][2]||gt[2][2]||gt[2][0]||gt[2][1])
	{
		gks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<gxx<<gyy<<gks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_gerode(gimagematrix,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}

//==========================================================================================

void do_gclosing(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1])+j]=0;
						
					}

		}

	do_gdilate(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0])*(dims[1])];
	/*for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						
						if(ot1[i*(dims[1]+2*c)+j])ot1[i*(dims[1]+2*c)+j]=255;
						
					}

		}*/
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						ot1[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

	do_gerode(ot1,output,mt,ox,oy, size);

	delete [] ot;
	delete [] ot1;
}
void g_closing(Fl_Widget*, void*)
{
	if(!jpegReader)return;

	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(gt[0][2]||gt[1][2]||gt[2][2]||gt[2][0]||gt[2][1])
	{
		gks=3;
		
	}

	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<gimagematrix<<":"<<ot<<":"<<mt<<":"<<gxx<<gyy<<gks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_gclosing(gimagematrix,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x<dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//======================================================================================

void do_gopening(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1])+j]=0;
						
					}

		}

	do_gerode(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0])*(dims[1])];
	/*for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						
						if(ot1[i*(dims[1]+2*c)+j])ot1[i*(dims[1]+2*c)+j]=255;
						
					}

		}*/
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						ot1[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

	do_gdilate(ot1,output,mt,ox,oy, size);

	delete [] ot;
	delete [] ot1;
}



void g_opening(Fl_Widget*, void*)
{
	if(!jpegReader)return;


	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(gt[0][2]||gt[1][2]||gt[2][2]||gt[2][0]||gt[2][1])
	{
		gks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<gxx<<gyy<<gks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_gopening(gimagematrix,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//============================================================================================

void do_edgedetect(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1]+2*c)+j]=0;
						
					}

		}

	do_dilate(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot1[i*(dims[1]+2*c)+j]=0;
						
					}

		}

	do_erode(input,ot1,mt,ox,oy, size);

	int i=0;
	 for (int x=0; x <dims[0]+2*c; x++)
			 {
				 for(int y=0;y<dims[1]+2*c;y++)
				{
					
						output[i]=ot[x*(dims[1]+2*c)+y]-ot1[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

	delete [] ot;
	delete [] ot1;
}



void m_edgedetection(Fl_Widget*, void*)
{
	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}
	//{
	//	int * output=new int[(dims[0]+2)*(dims[1]+2)];
	//}
	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_edgedetect(imagematrix,ot,mt,xx,yy,ks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[(x-c)*(dims[1])+y-c]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
	{
		
				////unsigned char* pixel = static_cast<unsigned char*>(binaryimage->GetScalarPointer(x,y,0));
				//pixel[0] = x*10;
				////if(pixel[0]>threshold1)bi->InsertTuple1(x+y*dims[0],255);
				//bin->InsertTuple1(x+y*(dims[0]+c),ot[j]);
		        bin->InsertTuple1(x-c+(y-c)*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();

}

//========================================================================================




void do_morphogradient(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot[i*(dims[1])+j]=0;
						
					}

		}

	do_gdilate(input,ot,mt,ox,oy, size);
	int * ot1 =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						//cout<<ot[i*(dims[1]+2*c)+j];
						//if(ot[i*(dims[1]+2*c)+j])ot[i*(dims[1]+2*c)+j]=255;
						ot1[i*(dims[1])+j]=0;
						
					}

		}

	do_gerode(input,ot1,mt,ox,oy, size);

	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						output[i]=0.5*ot[x*(dims[1])+y]-0.5*ot1[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

	delete [] ot;
	delete [] ot1;
}

void m_morphogradient(Fl_Widget*, void*)
{
	if(!jpegReader)return;

	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		gks=3;
		
	}

	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<gimagematrix<<":"<<ot<<":"<<gt<<":"<<gxx<<gyy<<gks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_morphogradient(gimagematrix,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
		{

		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			    j++;
		}

	
	}
		//cout<<endl<<int(threshold1);
	//int d33[3]={dims[0]+c,dims[1]+c,dims[2]};
	//binaryimage->SetDimensions(d33);
	binaryimage->GetPointData()->SetScalars(bin);
  
 
	//binmap->Update();
  
    
 

	delete [] ot;
   
  
 
  SliceWin[3]->Render();

}
//============================================================================================


void do_conditionaldilation(int* input,int* output,int mt[][3],int ox,int oy,int size)
{
	int px=atoi(pickx->value());int py=atoi(picky->value());

	int* in=new int [(dims[0])*(dims[1])];
	//int ones=0;
	for(int i=0;i<dims[0];i++)
		{
					for(int j=0;j<dims[1];j++)
					{
						in[i*(dims[1])+j]=0;
					}
		}
	in[px*(dims[1])+py]=1;
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	
	//int m=0;
	int total0=10;int total1=0;
	while(total0!=total1)//!((total0==total1)||(total0==total1+1)||(total0==total1-1)))
	{
		total1=total0;
		//m=m+1;
			for(int i=0;i<dims[0]+2*c;i++)
				{
							for(int j=0;j<dims[1]+2*c;j++)
							{
								ot[i*(dims[1]+2*c)+j]=0;
							}
				}

			do_dilate(in,ot,mt,ox,oy, size);
			int i=0;
			int n=0;
			 for (int x=c; x <dims[0]+c; x++)
					 {
						 for(int y=c;y<dims[1]+c;y++)
						{
					
								if(input[(x-c)*(dims[1])+y-c]*ot[x*(dims[1]+2*c)+y])
								{
									//output[x*(dims[1]+2*c)+y]=m;//cout<<I[0];
									n=n+1;
								}
					   
						   i++;
				   
    
						}
				 
					 } 
			 total0=n;

			  i=0;
	         for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						if(input[(x-c)*(dims[1])+y-c]*ot[x*(dims[1]+2*c)+y])
								{
									//output[x*(dims[1]+2*c)+y]=1;//ot[x*(dims[1]+2*c)+y];//cout<<I[0];
									in[(x-c)*(dims[1])+y-c]=1;
								}
					
				   i++;
				   
    
				}
				 
			 } 
	
	}
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
					 {
						 for(int y=c;y<dims[1]+c;y++)
						{
					            
								if(input[(x-c)*(dims[1])+y-c]*ot[x*(dims[1]+2*c)+y])
								{
									output[x*(dims[1]+2*c)+y]=2;//ot[x*(dims[1]+2*c)+y];//cout<<I[0];
									//in[(x-c)*(dims[1])+y-c]=1;
								}
								else
								{
									output[x*(dims[1]+2*c)+y]=0;
								}
					   
						   i++;
				   
    
						}
				 
					 } 
	for(int i=c;i<dims[0]+c;i++)
				{
							for(int j=c;j<dims[1]+c;j++)
							{
								if((input[(i-c)*(dims[1])+j-c]==1)&&(ot[i*(dims[1]+2*c)+j]!=2))
								output[i*(dims[1]+2*c)+j]=1;//ot[i*(dims[1]+2*c)+j]+input[(i-c)*(dims[1])+j-c];
							}
				}
	delete [] ot;
}

void m_conditionaldilation(Fl_Widget*, void*)
{
	if(!jpegReader)return;


	mt[0][0]=atof(inpm0->value());
	mt[0][1]=atof(inpm1->value());
	mt[0][2]=atof(inpm2->value());
	mt[1][0]=atof(inpm3->value());
	mt[1][1]=atof(inpm4->value());
	mt[1][2]=atof(inpm5->value());
	mt[2][0]=atof(inpm6->value());
	mt[2][1]=atof(inpm7->value());
	mt[2][2]=atof(inpm8->value());
	int xx=atof(xi->value());
	int yy=atof(yi->value());
	int ks=2;
	if(mt[0][2]||mt[1][2]||mt[2][2]||mt[2][0]||mt[2][1])
	{
		ks=3;
		
	}

	int c=ceil(ks/2.0);
	int * ot =new int[(dims[0]+2*c)*(dims[1]+2*c)];
	for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						ot[i*(dims[1]+2*c)+j]=0;
					}

		}
	cout<<"to do"<<imagematrix<<":"<<ot<<":"<<mt<<":"<<xx<<yy<<ks<<c;
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
	do_conditionaldilation(imagematrix,ot,mt,xx,yy,ks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=c; x <dims[0]+c; x++)
			 {
				 for(int y=c;y<dims[1]+c;y++)
				{
					
						imagematrix[(x-c)*(dims[1])+y-c]=ot[x*(dims[1]+2*c)+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 

for(int i=0;i<dims[0]+2*c;i++)
		{

					for(int j=0;j<dims[1]+2*c;j++)
					{
						if(ot[i*(dims[1]+2*c)+j]==2)ot[i*(dims[1]+2*c)+j]=121;
						if(ot[i*(dims[1]+2*c)+j]==1)ot[i*(dims[1]+2*c)+j]=0;//255;
					}

		}
//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = c; x < dims[0]+c; x++)
	{
		for(int y=c;y<dims[1]+c;y++)
		{
		        bin->InsertTuple1(x-c+(y-c)*(dims[0]),ot[y+x*(dims[1]+2*c)]);
			j++;
		}

	
	}

	binaryimage->GetPointData()->SetScalars(bin);

	delete [] ot;
 
 
  SliceWin[3]->Render();

}
//===========================================================================================
void do_grayscalerecon(int* input,int* mask,int* output,int gt[][3],int ox,int oy,int size)
{
	int px=atoi(pickx->value());int py=atoi(picky->value());
	
	int* in=new int [(dims[0])*(dims[1])];
	//int ones=0;
	for(int i=0;i<dims[0];i++)
		{
					for(int j=0;j<dims[1];j++)
					{
						in[i*(dims[1])+j]=0;
					}
		}
	in[px*(dims[1])+py]=10;
	int c=ceil(size/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	
	int m=1;
	int total0=0;int total1=255;
	while(total0!=total1)//!((total0==total1)||(total0==total1+1)||(total0==total1-1)))
	{
		total1=total0;
		//m=m+1;
			for(int i=0;i<dims[0];i++)
				{
							for(int j=0;j<dims[1];j++)
							{
								ot[i*(dims[1])+j]=0;
							}
				}

			do_gdilate(in,ot,mt,ox,oy, size);
			int i=0;
			int n=0;
			 for (int x=0; x <dims[0]; x++)
					 {
						 for(int y=0;y<dims[1];y++)
						{
							 if(mask[(x)*(dims[1])+y])
							 {
									if((ot[x*(dims[1])+y]>=mask[(x)*(dims[1])+y]))
									{
										//output[x*(dims[1]+2*c)+y]=m;//cout<<I[0];
										n=n+mask[(x)*(dims[1])+y];
										//m=0;
									
									}
									else
									{
										n=n+ot[x*(dims[1])+y];
									}
							 }
					   
						   i++;
				   
    
						 }
				 
					 } 
			total0=n;

			  i=0;
	         for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					if(mask[(x)*(dims[1])+y])
					{
						if((mask[(x)*(dims[1])+y]<=ot[x*(dims[1])+y]))
						{
							//output[x*(dims[1]+2*c)+y]=1;//ot[x*(dims[1]+2*c)+y];//cout<<I[0];
							in[(x)*(dims[1])+y]=mask[(x)*(dims[1])+y];
						}
						else //if()
						{
							in[(x)*(dims[1])+y]=ot[(x)*(dims[1])+y];
						}
					}
				   i++;
				   
    
				}
				 
			 } 
	
	}
	int i=0;
	 for (int x=0; x <dims[0]; x++)
					 {
						 for(int y=0;y<dims[1];y++)
						{

							output[x*(dims[1])+y]=ot[x*(dims[1])+y];

					   
						   i++;
				   
    
						}
				 
					 } 

	delete [] ot;

}



void m_grayscalerecon(Fl_Widget*, void*)
{
	if(!jpegReader)return;


	gt[0][0]=atof(inpg0->value());
	gt[0][1]=atof(inpg1->value());
	gt[0][2]=atof(inpg2->value());
	gt[1][0]=atof(inpg3->value());
	gt[1][1]=atof(inpg4->value());
	gt[1][2]=atof(inpg5->value());
	gt[2][0]=atof(inpg6->value());
	gt[2][1]=atof(inpg7->value());
	gt[2][2]=atof(inpg8->value());
	int gxx=atof(gxi->value());
	int gyy=atof(gyi->value());
	int gks=2;
	if(gt[0][2]||gt[1][2]||gt[2][2]||gt[2][0]||gt[2][1])
	{
		gks=3;
		
	}

	int c=ceil(gks/2.0);
	int * ot =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						ot[i*(dims[1])+j]=0;
					}

		}
	cout<<"to do"<<gimagematrix<<":"<<ot<<":"<<gt<<":"<<gxx<<gyy<<gks<<c;
	int * otm =new int[(dims[0])*(dims[1])];
	for(int i=0;i<dims[0];i++)
		{

					for(int j=0;j<dims[1];j++)
					{
						otm[i*(dims[1])+j]=0;
					}

		}
//=========================================================================
	//do_dilate(int* input,int* output,int*kernel,int ox,int oy,int size)
    do_gerode(gimagematrix,otm,gt,gxx,gyy,gks);
	do_grayscalerecon(gimagematrix,otm,ot,gt,gxx,gyy,gks);
	cout<<"done";
	
//=========================================================================
	int i=0;
	 for (int x=0; x <dims[0]; x++)
			 {
				 for(int y=0;y<dims[1];y++)
				{
					
						gimagematrix[(x)*(dims[1])+y]=ot[x*(dims[1])+y];//cout<<I[0];
					
				   i++;
				   
    
				}
				 
			 } 


//=========================================================================
    int j=0;
	bin->Initialize();
	//bi=vtkFloatArray::New();
	for (int x = 0; x < dims[0]; x++)
	{
		for(int y=0;y<dims[1];y++)
		{

		        bin->InsertTuple1(x+(y)*(dims[0]),ot[y+x*(dims[1])]);
			j++;
		}

	
	}

	binaryimage->GetPointData()->SetScalars(bin);

	delete [] ot;
   
  
 
  SliceWin[3]->Render();
}
//=======================================================================================================================
UserInterfaceGUI::UserInterfaceGUI()
{
	
	{	MainWin = new Fl_Double_Window(930, 830,"ByWenzhao");::w=MainWin;	

		{	
			Menu = new Fl_Menu_Bar(0, 0, 930, 30);	
			Menu->menu(menutable);
		    {

		    }
		
		}
		{	
			MenuTab = new Fl_Tabs(0, 30, 130, 780);	
			{	ImageGrp = new Fl_Group(0, 55, 130, 755,"P1");
		        ImageGrp->align(FL_ALIGN_LEFT);
		        {	 Fl_Button *otsu = new Fl_Button(15, 95, 100, 25,"Otsu");

						otsu->callback((Fl_Callback*)otsu_cb);
			    } 
		        {	 Fl_Button *maxent = new Fl_Button(15, 125, 100, 25,"MaxEntropy");

						maxent->callback((Fl_Callback*)maxent_cb);
			    } 
				

		       ImageGrp->end();
		    }
			{
				FilterGrp= new Fl_Group(0, 55, 130, 755,"P2");
				FilterGrp->align(FL_ALIGN_LEFT);
				FilterGrp->hide();
				{
					Fl_Button *Roberts = new Fl_Button(15, 95, 100, 25,"Roberts");
					Roberts->callback(m_roberts);
				}
				{
					 Fl_Button *Prewitt = new Fl_Button(15, 125, 100, 25,"Prewitt");
					 Prewitt->callback(m_prewitt);
				}
				{
					 Fl_Button *Sobel = new Fl_Button(15, 155, 100, 25,"Sobel");
					 Sobel->callback(m_sobel);
				}
				{
					 Fl_Button *Gaussian = new Fl_Button(15, 185, 100, 25,"Gaussian");
					 Gaussian->callback(m_gaussian);
				}
				{
					 Fl_Button *Median = new Fl_Button(15, 215, 100, 25,"Median");
					 Median->callback(m_median);
				}
//======================================
				{
					wsize=new Fl_Input(80,250,40,30,"FilterWidth=");
				}
//======================================
				{
					inp0=new Fl_Input(10,300,20,30);

				}
				{
					inp1=new Fl_Input(30,300,20,30);

				}
				{
					inp2=new Fl_Input(50,300,20,30);

				}
				{
					inp3=new Fl_Input(70,300,20,30);

				}
				{
					inp4=new Fl_Input(90,300,20,30);

				}
//=====================================
				{
					inp5=new Fl_Input(10,340,20,30);

				}
				{
					inp6=new Fl_Input(30,340,20,30);

				}
				{
					inp7=new Fl_Input(50,340,20,30);

				}
				{
					inp8=new Fl_Input(70,340,20,30);

				}
				{
					inp9=new Fl_Input(90,340,20,30);

				}
//================================
				{
					inp10=new Fl_Input(10,380,20,30);

				}
				{
					inp11=new Fl_Input(30,380,20,30);

				}
				{
					inp12=new Fl_Input(50,380,20,30);

				}
				{
					inp13=new Fl_Input(70,380,20,30);

				}
				{
					inp14=new Fl_Input(90,380,20,30);

				}
//==============================
				{
					inp15=new Fl_Input(10,420,20,30);

				}
				{
					inp16=new Fl_Input(30,420,20,30);

				}
				{
					inp17=new Fl_Input(50,420,20,30);

				}
				{
					inp18=new Fl_Input(70,420,20,30);

				}
				{
					inp19=new Fl_Input(90,420,20,30);

				}
//=====================================
				{
					inp20=new Fl_Input(10,460,20,30);

				}
				{
					inp21=new Fl_Input(30,460,20,30);

				}
				{
					inp22=new Fl_Input(50,460,20,30);

				}
				{
					inp23=new Fl_Input(70,460,20,30);

				}
				{
					inp24=new Fl_Input(90,460,20,30);

				}
//===========================
				{
					Fl_Button * doconvolve=new Fl_Button(40,510,50,30,"Do");
					doconvolve->callback(m_Do);
				}
				{
					text=new Fl_Multiline_Output(15,600,100,200);
					text->textcolor(FL_RED);
					text->color((Fl_Color)FL_BACKGROUND_COLOR);
					text->align(FL_ALIGN_CENTER);
				}
				FilterGrp->end();
			}
			{
				MorphoGrp= new Fl_Group(0, 55, 130, 755,"P3");
				MorphoGrp->align(FL_ALIGN_LEFT);
				MorphoGrp->hide();
				{
					Fl_Button *dilation = new Fl_Button(15, 95, 100, 25,"Dilation");
					dilation->callback(m_dilation);
				}
				{
					Fl_Button *erosion = new Fl_Button(15, 125, 100, 25,"Erosion");
					erosion->callback(m_erosion);
				}
				{
					Fl_Button *closing = new Fl_Button(15, 155, 100, 25,"Closing");
					closing->callback(m_closing);
				}
				{
					Fl_Button *opening = new Fl_Button(15, 185, 100, 25,"Opening");
					opening->callback(m_opening);
				}
				{
					msize=new Fl_Input(80,250,40,30,"Size=");
					msize->value("3");
				}
				{
					inpm0=new Fl_Input(10,300,30,30);
					inpm0->value("1");

				}
				{
					inpm1=new Fl_Input(40,300,30,30);
					inpm1->value("1");

				}
				{
					inpm2=new Fl_Input(70,300,30,30);
					inpm2->value("1");

				}
				{
					inpm3=new Fl_Input(10,340,30,30);
					inpm3->value("1");

				}
				{
					inpm4=new Fl_Input(40,340,30,30);
					inpm4->value("1");

				}
				{
					inpm5=new Fl_Input(70,340,30,30);
					inpm5->value("1");

				}
				{
					inpm6=new Fl_Input(10,380,30,30);
					inpm6->value("1");

				}
				{
					inpm7=new Fl_Input(40,380,30,30);
					inpm7->value("1");

				}
				{
					inpm8=new Fl_Input(70,380,30,30);
					inpm8->value("1");

				}
				{
					xi=new Fl_Input(30,420,30,30,"X");
					xi->value("1");

				}
				{
					yi=new Fl_Input(90,420,30,30,"Y");
					yi->value("1");

				}
				MorphoGrp->end();
			}
			{
				TransGrp= new Fl_Group(0, 55, 130, 755,"P4");
				TransGrp->align(FL_ALIGN_LEFT);
				TransGrp->hide();
				{
					Fl_Button *distance = new Fl_Button(15, 95, 100, 25,"Distance");
					distance->callback(m_distance);
				}
				{
					Fl_Button *skeletonex = new Fl_Button(15, 125, 100, 25,"SkeletonEx");
					skeletonex->callback(m_skeletonex);
				}
				{
					Fl_Button *skeletonre = new Fl_Button(15, 155, 100, 25,"SkeletonRe");
					skeletonre->callback(m_skeletonre);
				}
				TransGrp->end();
			}
			{
				GrayGrp= new Fl_Group(0, 55, 130, 755,"P5");
				GrayGrp->align(FL_ALIGN_LEFT);
				GrayGrp->hide();
				{
					Fl_Button *gdilation = new Fl_Button(15, 95, 100, 25,"GDilation");
					gdilation->callback(g_dilation);
				}
				{
					Fl_Button *gerosion = new Fl_Button(15, 125, 100, 25,"GErosion");
					gerosion->callback(g_erosion);
				}
				{
					Fl_Button *gclosing = new Fl_Button(15, 155, 100, 25,"GClosing");
					gclosing->callback(g_closing);
				}
				{
					Fl_Button *gopening = new Fl_Button(15, 185, 100, 25,"GOpening");
					gopening->callback(g_opening);
				}
				{
					gsize=new Fl_Input(80,250,40,30,"Size=");
					gsize->value("3");
				}
				{
					inpg0=new Fl_Input(10,300,30,30);
					inpg0->value("1");

				}
				{
					inpg1=new Fl_Input(40,300,30,30);
					inpg1->value("2");

				}
				{
					inpg2=new Fl_Input(70,300,30,30);
					inpg2->value("3");

				}
				{
					inpg3=new Fl_Input(10,340,30,30);
					inpg3->value("4");

				}
				{
					inpg4=new Fl_Input(40,340,30,30);
					inpg4->value("5");

				}
				{
					inpg5=new Fl_Input(70,340,30,30);
					inpg5->value("6");

				}
				{
					inpg6=new Fl_Input(10,380,30,30);
					inpg6->value("7");

				}
				{
					inpg7=new Fl_Input(40,380,30,30);
					inpg7->value("8");

				}
				{
					inpg8=new Fl_Input(70,380,30,30);
					inpg8->value("9");

				}
				{
					gxi=new Fl_Input(30,420,30,30,"X");
					gxi->value("1");

				}
				{
					gyi=new Fl_Input(90,420,30,30,"Y");
					gyi->value("1");

				}
				{
					Fl_Button *reset = new Fl_Button(15, 500, 100, 25,"reset");
					reset->callback(g_reset);
				}
				GrayGrp->end();
			}

			{
				MGrayGrp= new Fl_Group(0, 55, 130, 755,"P6");
				MGrayGrp->align(FL_ALIGN_LEFT);
				MGrayGrp->hide();
				{
					Fl_Button *EdgeDetection = new Fl_Button(5, 95, 120, 25,"EdgeDetection");
					EdgeDetection->callback(m_edgedetection);
				}
				{
					Fl_Button *ConditionalDilation = new Fl_Button(5, 125, 120, 25,"ConditionalDilation");
					ConditionalDilation->callback(m_conditionaldilation);
				}
				{
					Fl_Button *GrayscaleRecon = new Fl_Button(5, 155, 120, 25,"GrayscaleRecon");
					GrayscaleRecon->callback(m_grayscalerecon);
				}
				{
					Fl_Button *MorphoGradient = new Fl_Button(5, 185, 120, 25,"MorphoGradient");
					MorphoGradient->callback(m_morphogradient);
				}
				{
					pickx=new Fl_Output(30,420,30,30,"X");
					//gxi->value("1");

				}
				{
					picky=new Fl_Output(90,420,30,30,"Y");
					//gyi->value("1");

				}
				{
					Fl_Button *reset = new Fl_Button(15, 500, 100, 25,"reset");
					reset->callback(g_reset);
				}
				MGrayGrp->end();
			}
		    MenuTab->end();
		}
		
		{	RightPaneGrp = new Fl_Group(130,30, 800,800);	
		    RightPaneGrp->box(FL_FLAT_BOX);
			RightPaneGrp->color((Fl_Color)166);
		   {	SlicePanelGrp[0] = new Fl_Group(130, 30, 400, 400,"");	//左上窗口（Axial）
				SlicePanelGrp[0]->box(FL_UP_BOX);

				{	Fl_Group *Grp = new Fl_Group(135, 35, 371, 365);
				
					{	SliceWin[0] = new vtkFlRenderWindowInteractor(135, 35, 371, 365,"");
						SliceWin[0]->box(FL_PLASTIC_DOWN_BOX);
						SliceWin[0]->color((Fl_Color)55);
						SliceWin[0]->selection_color((Fl_Color)FL_BACKGROUND_COLOR);
						SliceWin[0]->labeltype(FL_NORMAL_LABEL);
						SliceWin[0]->labelfont(0);
						SliceWin[0]->labelsize(14);
						SliceWin[0]->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
						SliceWin[0]->align(FL_ALIGN_CENTER);
					} // vtkFlRenderWindowInteractor *SliceWin[0]	
					
					Grp->end();
					Fl_Group::current()->resizable(SliceWin[0]);
				} // Fl_Group *Grp

				
				SlicePanelGrp[0]->end();
			} // Fl_Group *SlicePanelGrp[0]

			{	SlicePanelGrp[1] = new Fl_Group(530, 30, 400, 400,"");	//右上窗口（Sagittal）
				SlicePanelGrp[1]->box(FL_UP_BOX);

				{	Fl_Group *Grp = new Fl_Group(535, 35, 371, 365);

					{	SliceWin[1] = new vtkFlRenderWindowInteractor(535, 35, 371, 365,"");
						SliceWin[1]->box(FL_PLASTIC_DOWN_BOX);
						SliceWin[1]->color((Fl_Color)55);
						SliceWin[1]->selection_color((Fl_Color)FL_BACKGROUND_COLOR);
						SliceWin[1]->labeltype(FL_NORMAL_LABEL);
						SliceWin[1]->labelfont(0);
						SliceWin[1]->labelsize(14);
						SliceWin[1]->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
						SliceWin[1]->align(FL_ALIGN_CENTER);
					} // vtkFlRenderWindowInteractor *SliceWin[1]	

					

					Grp->end();
					Fl_Group::current()->resizable(SliceWin[1]);
				} // Fl_Group *Grp

			
			

				{	Fl_Group *Grp = new Fl_Group(530,410, 399,20 );

					{	SliceSlider = new Fl_Scrollbar(531, 410, 390, 18);
						SliceSlider->box( FL_THIN_DOWN_BOX);
						SliceSlider->minimum(0);
						SliceSlider->maximum(255);
						SliceSlider->linesize(1);
						SliceSlider->type(Fl_Scroll::HORIZONTAL);
						SliceSlider->align(FL_ALIGN_LEFT+FL_ALIGN_BOTTOM);
						SliceSlider->callback((Fl_Callback*)m_SliceSlider);
						Fl_Group::current()->resizable(SliceSlider);
					} // Fl_Scrollbar *SliceSlider[1]

					Grp->end();
				} // Fl_Group *Grp

				SlicePanelGrp[1]->end();
			} // Fl_Group *SlicePanelGrp[1]
			
			{	SlicePanelGrp[2] = new Fl_Group(130, 430, 400, 400,"");	//左下窗口（Coronal）
				SlicePanelGrp[2]->box(FL_UP_BOX);

				{	Fl_Group *Grp = new Fl_Group(135, 435, 371, 365);

					{	SliceWin[2] = new vtkFlRenderWindowInteractor(135, 435, 371, 365,"");
						SliceWin[2]->box(FL_PLASTIC_DOWN_BOX);
						SliceWin[2]->color((Fl_Color)55);
						SliceWin[2]->selection_color((Fl_Color)FL_BACKGROUND_COLOR);
						SliceWin[2]->labeltype(FL_NORMAL_LABEL);
						SliceWin[2]->labelfont(0);
						SliceWin[2]->labelsize(14);
						SliceWin[2]->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
						SliceWin[2]->align(FL_ALIGN_CENTER);
					} // vtkFlRenderWindowInteractor *SliceWin[2]	

					Grp->end();
					Fl_Group::current()->resizable(SliceWin[2]);
				} // Fl_Group *Grp

				

				SlicePanelGrp[2]->end();
			} // Fl_Group *SlicePanelGrp[2]			

			{	SlicePanelGrp[3] = new Fl_Group(530, 430, 400, 400,"");	//右下窗口（Volume）
				SlicePanelGrp[3]->box(FL_UP_BOX);

				{	Fl_Group *Grp = new Fl_Group(535, 435, 371, 365);
					
					{	SliceWin[3] = new vtkFlRenderWindowInteractor(535, 435, 371, 365,"");
						SliceWin[3]->box(FL_PLASTIC_DOWN_BOX);
						SliceWin[3]->color((Fl_Color)55);
						SliceWin[3]->selection_color((Fl_Color)FL_BACKGROUND_COLOR);
						SliceWin[3]->labeltype(FL_NORMAL_LABEL);
						SliceWin[3]->labelfont(0);
						SliceWin[3]->labelsize(14);
						SliceWin[3]->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
						SliceWin[3]->align(FL_ALIGN_CENTER);
						SliceWin[3]->when(FL_WHEN_RELEASE);
					} // vtkFlRenderWindowInteractor *SliceWin[3]

					Grp->end();
					Fl_Group::current()->resizable(SliceWin[3]);
				} // Fl_Group *Grp
				
				SlicePanelGrp[3]->end();
			} // Fl_Group *SlicePanelGrp[3]
			
			RightPaneGrp->end();
			Fl_Group::current()->resizable(RightPaneGrp);
		} // Fl_Group *RightPanelGrp

		SliceRenderer[0] = vtkRenderer::New();	
		SliceRenderWin[0] = vtkRenderWindow::New();
		SliceWin[0]->SetRenderWindow(SliceRenderWin[0]);
		SliceRenderWin[0]->AddRenderer(SliceRenderer[0]);

		SliceRenderer[1] = vtkRenderer::New();	
		SliceRenderWin[1] = vtkRenderWindow::New();
		SliceWin[1]->SetRenderWindow(SliceRenderWin[1]);
		SliceRenderWin[1]->AddRenderer(SliceRenderer[1]);

		SliceRenderer[2] = vtkRenderer::New();	 
		SliceRenderWin[2] = vtkRenderWindow::New();
		SliceWin[2]->SetRenderWindow(SliceRenderWin[2]);
		SliceRenderWin[2]->AddRenderer(SliceRenderer[2]);

		SliceRenderer[3] = vtkRenderer::New();	
		SliceRenderWin[3] = vtkRenderWindow::New();
		SliceWin[3]->SetRenderWindow(SliceRenderWin[3]);
		SliceRenderWin[3]->AddRenderer(SliceRenderer[3]);
		SliceRenderWin[3]->SetInteractor(SliceWin[3]);

		/*cmd1 = vtkCallbackCommand::New();
		cmd1->SetCallback(MyExecute);
		picker->AddObserver(vtkCommand::LeftButtonPressEvent, cmd1);
		SliceWin[3]->SetPicker(picker);*/

		 cmd = vtkCallbackCommand::New();
         cmd->SetCallback(left);
         vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=
         vtkInteractorStyleTrackballCamera::New();
		SliceWin[3]-> SetInteractorStyle(style);
		style-> AddObserver (vtkCommand::LeftButtonPressEvent,cmd);

		

		
		MainWin->end();
	}

}

UserInterfaceGUI::~UserInterfaceGUI()
{
	for(int i=0;i<4;i++)
	{
		
		//if(reslice[i])reslice[i]->Delete();

		if(SliceRenderer[i]) SliceRenderer[i]->Delete();

		//if(User2D[i]) User2D[i]->Delete();		
		if(SliceWin[i]) SliceWin[i]->Delete();
		if(SliceRenderWin[i]) SliceRenderWin[i]->Delete();
	} /* for */

} // UserInterfaceGUI::~UserInterfaceGUI


void UserInterfaceGUI::Show()
{
	 SliceWin[0]->show();
	 SliceWin[2]->show();
	//pViewHandling->Init();
	 vtkSmartPointer<vtkInteractorStyleImage> style0 =
    vtkSmartPointer<vtkInteractorStyleImage>::New(); 
  SliceWin[0]->SetInteractorStyle(style0);
  vtkSmartPointer<vtkInteractorStyleImage> style1 =
    vtkSmartPointer<vtkInteractorStyleImage>::New(); 
  SliceWin[1]->SetInteractorStyle(style1);
vtkSmartPointer<vtkInteractorStyleImage> style2 =
    vtkSmartPointer<vtkInteractorStyleImage>::New(); 
  SliceWin[2]->SetInteractorStyle(style2);
  //vtkSmartPointer<vtkInteractorStyleImage> style3 =
  //  vtkSmartPointer<vtkInteractorStyleImage>::New(); 
 // SliceWin[3]->SetInteractorStyle(style3);

 

	SliceWin[0]->Initialize();
	SliceWin[1]->Initialize();
	SliceWin[2]->Initialize();
	SliceWin[3]->Initialize();

	SliceWin[0]->deactivate();
	SliceWin[1]->deactivate();
	SliceWin[2]->deactivate();
	SliceWin[3]->deactivate();

	//SliceSlider[0]->deactivate();
	SliceSlider->deactivate();
	//SliceSlider[2]->deactivate();

	
	//ivalue->deactivate();

	MainWin->show();

} // UserInterfaceGUI::show


void UserInterfaceGUI::Quit()
{
	 if(!imagematrix)delete [] imagematrix;
	MainWin->hide();
} // UserInterfaceGUI::Quit


void UserInterfaceGUI::Redraw()
{
	HWND hwnd;
	hwnd = GetActiveWindow();

	ShowWindow(hwnd,SW_MAXIMIZE);

} // UserInterfaceGUI::Redraw
// ====================================================

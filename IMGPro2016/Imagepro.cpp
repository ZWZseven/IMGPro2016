#include"Imagepro.h"
#include"vtkRenderer.h"
using namespace std;
extern vtkRenderer *SliceRenderer[4];	
extern vtkRenderWindow *SliceRenderWin[4];	
extern vtkFlRenderWindowInteractor *SliceWin[4];	
int SliceLeftLow[2]={0,0};
imagepro::imagepro()
{
};
imagepro::~imagepro()
{
	for(int i=0;i<3;i++){
	if(jpg_viewer[i])jpg_viewer[i]->Delete();
	}
}
imagepro* jpgpro=new imagepro;

void imagepro::init()
{
	reader=vtkJPEGReader::New();
	for(int i=0;i<3;i++){
	jpg_viewer[i] =vtkImageViewer::New();
	}
}
void imagepro::present(char*n)
{
	 
     reader->SetFileName ( n );
	 
}

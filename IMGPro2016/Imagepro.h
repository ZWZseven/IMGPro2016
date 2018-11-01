#include"usrInterface.h"
#include"vtkImageViewer.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkDecimatePro.h"     //消减率控制加速
#include "vtkImageReslice.h"
#include "vtkImageFlip.h"
#include "vtkPropPicker.h"
//#include "vtkSimulateInteractor.h" 
#include "vtkInteractorStyleUser2D.h"
#include "cstringex.h"
//#include "IntPoint3D.h"

#include <vector>
#include <list>
#include <Windows.h>

// ====================  命名空间  ====================
using namespace std;

// ====================  结构体  ====================
struct DOUBLE_POINT_3D
{
	double x;
	double y;
	double z;
};

// ====================  类  ====================
class vtkImageData;
class vtkImageDICOMReader;
class vtkImageReader;
class vtkImageSource; // >>> vtkImageReader
class vtkImageReslice;
class vtkImageViewer;
class vtkTextMapper;
class vtkCursor3D;
class vtkPolyDataMapper2D;
class vtkCylinderSource;
class vtkPlaneSource;
class vtkExtractVOI;
class vtkOutlineFilter;
class vtkVectorText;
class vtkFollower;
class vtkStripper;
class vtkTriangleFilter;
class vtkPolyDataNormals;
class vtkFollower;
class vtkAxes;
class vtkInteractorStyleUser2D;

class vtkImageViewer;
class imagepro
{
public:
	imagepro();
	~imagepro();
public:
	void init();
	void rgb2gray();
	void onhistogram();//create a histogram and a binary picture;
	void onsliceslider();
	vtkJPEGReader* reader ;
    vtkImageViewer* jpg_viewer[4];
    void present(char*n);
	vtkInteractorStyle *User2D[3];
}

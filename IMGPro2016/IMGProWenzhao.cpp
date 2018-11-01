#include"usrInterface.h"

//extern Fl_Box *b;
int dvisual = 0;
void load_file(const char *n) ;
int arg(int, char **argv, int &i) {
  if (argv[i][1] == '8') {dvisual = 1; i++; return 1;}
  return 0;
}
int main(int argc, char **argv)
{
	int i = 1;

  fl_register_images();

  Fl::args(argc,argv,i,arg);
   
	UserInterfaceGUI *gui = new UserInterfaceGUI;	
	
	if (!dvisual) Fl::visual(FL_RGB);
    if (argv[1]) load_file(argv[1]);

	gui->Show();	// 显示用户界面								
	gui->Redraw();	// 最大化用户界面
	Fl::run();

	delete gui;
	return 0;
} // main
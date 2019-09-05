#pragma once
#include<windows.h>
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkBoxWidget.h"
#include "vtkTransform.h"

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);

class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New()
	{
		return new vtkMyCallback;
	}
	void Execute(vtkObject *caller, unsigned long, void*) override
	{
		vtkTransform *t = vtkTransform::New();
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		widget->GetTransform(t);
		widget->GetProp3D()->SetUserTransform(t);
		t->Delete();
	}
};

class VTKCone
{
private:
	vtkConeSource *cone;
	vtkPolyDataMapper *coneMapper;
	vtkActor *coneActor;
	vtkRenderer *ren1;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
	vtkInteractorStyleTrackballCamera *style;
	vtkBoxWidget *boxWidget;
	vtkMyCallback *callback;
public:
	VTKCone(HWND hwnd);
	~VTKCone();
private:
};
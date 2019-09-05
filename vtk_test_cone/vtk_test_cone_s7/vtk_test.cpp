#include"vtk_test.h"
VTKCone::VTKCone(HWND hwnd)
{
	cone = vtkConeSource::New();
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(10);

	coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection(cone->GetOutputPort());

	coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper);

	ren1 = vtkRenderer::New();
	ren1->AddActor(coneActor);
	ren1->SetBackground(0.1, 0.2, 0.4);

	renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	renWin->SetSize(400, 400);
	
	// ---------------- import --------------
	renWin->SetParentId(hwnd);

	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	style = vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

	boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(1.25);
	boxWidget->SetProp3D(coneActor);
	boxWidget->PlaceWidget();
	callback = vtkMyCallback::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
	boxWidget->On();
	renWin->Render();
}
VTKCone::~VTKCone()
{
	if(cone)
		cone->Delete();
	if(coneMapper)
		coneMapper->Delete();
	if (coneActor)
		coneActor->Delete();
	if (callback)
		callback->Delete();
	if (boxWidget)
		boxWidget->Delete();
	if (ren1)
		ren1->Delete();
	if (renWin)
		renWin->Delete();
	if (iren)
		iren->Delete();
	if (style)
		style->Delete();
}

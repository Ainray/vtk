#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
//necessary, althogh these four lines does not appear in offical tutorial
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkInteractionStyle)
// Callback for the interaction
class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New()
	{
		return new vtkMyCallback;
	}
	void Execute(vtkObject *caller, unsigned long, void*) override
	{
		vtkRenderer *renderer = reinterpret_cast<vtkRenderer*>(caller);
		cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
			<< renderer->GetActiveCamera()->GetPosition()[1] << " "
			<< renderer->GetActiveCamera()->GetPosition()[2] << "\n";
	}
};

int main()
{
	//
	// Next we create an instance of vtkConeSource and set some of its
	// properties. The instance of vtkConeSource "cone" is part of a
	// visualization pipeline (it is a source process object); it produces data
	// (output type is vtkPolyData) which other filters may process.
	//
	vtkConeSource *cone = vtkConeSource::New();
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(10);

	//
	// In this example we terminate the pipeline with a mapper process object.
	// (Intermediate filters such as vtkShrinkPolyData could be inserted in
	// between the source and the mapper.)  We create an instance of
	// vtkPolyDataMapper to map the polygonal data into graphics primitives. We
	// connect the output of the cone source to the input of this mapper.
	//
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection(cone->GetOutputPort());

	//
	// Create an actor to represent the cone. The actor orchestrates rendering
	// of the mapper's graphics primitives. An actor also refers to properties
	// via a vtkProperty instance, and includes an internal transformation
	// matrix. We set this actor's mapper to be coneMapper which we created
	// above.
	//
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper);

	//
	// Create the Renderer and assign actors to it. A renderer is like a
	// viewport. It is part or all of a window on the screen and it is
	// responsible for drawing the actors it has.  We also set the background
	// color here.
	//
	vtkRenderer *ren1 = vtkRenderer::New();
	ren1->AddActor(coneActor);
	ren1->SetBackground(0.1, 0.2, 0.4);
	ren1->SetViewport(0.0, 0.0, 0.5, 1.0);
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Azimuth(180);

	vtkRenderer *ren2 = vtkRenderer::New();
	ren2->AddActor(coneActor);
	ren2->SetBackground(0.2, 0.3, 0.5);
	ren2->SetViewport(0.5, 0.0, 1.0, 1.0);

	//
	// Finally we create the render window which will show up on the screen.
	// We put our renderer into the render window using AddRenderer. We also
	// set the size to be 300 pixels by 300.
	//
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	renWin->AddRenderer(ren2);
	renWin->SetSize(600, 300);

	//
	// Now we loop over 360 degrees and render the cone each time.
	//
	int i;
	for (i = 0; i < 360; ++i)
	{
		// render the image
		renWin->Render();
		// rotate the active camera by one degree
		ren1->GetActiveCamera()->Azimuth(1);
		ren2->GetActiveCamera()->Azimuth(1);
	}

	//
	// Free up any objects we created. All instances in VTK are deleted by
	// using the Delete() method.
	//
	cone->Delete();
	coneMapper->Delete();
	coneActor->Delete();
	ren1->Delete();
	ren2->Delete();
	renWin->Delete();

	return 0;
}


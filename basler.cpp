#include <iostream>
#include <pylon/PylonIncludes.h>
#include <TH/TH.h>

using namespace Pylon;
using namespace std;

// Number of images to be grabbed.
// static const uint32_t c_countOfImagesToGrab = 100;

extern "C" 
{
void init_basler(void* handle[1]);
bool IsGrabbing(void* handle[1]);	
void RetrieveResult(void* handle[1], THByteTensor* frame);
void terminate();
}


void init_basler(void* handle[1])	   
{
	// Before using any pylon methods, the pylon runtime must be initialized. 
    PylonInitialize();

    // Create an instant camera object with the camera device found first.
    CInstantCamera* camera = new CInstantCamera(CTlFactory::GetInstance().CreateFirstDevice());

    // Print the model name of the camera.
    cout << "Using device " << camera->GetDeviceInfo().GetModelName() << endl;

    // The parameter MaxNumBuffer can be used to control the count of buffers
    // allocated for grabbing. The default value of this parameter is 10.
    camera->MaxNumBuffer = 5;

    // Start the grabbing of c_countOfImagesToGrab images.
    // The camera device is parameterized with a default configuration which
    // sets up free-running continuous acquisition.
    // camera.StartGrabbing(c_countOfImagesToGrab);
    camera->StartGrabbing();

	handle[1] = camera;
}

bool IsGrabbing(void* handle[1])
{
	CInstantCamera* camera = (CInstantCamera*)(handle[1]);
	return camera->IsGrabbing();
}

void RetrieveResult(void* handle[1], THByteTensor* frame)
{
	CInstantCamera* camera = (CInstantCamera*)(handle[1]);

    // This smart pointer will receive the grab result data.
    CGrabResultPtr ptrGrabResult;

	// Wait for an image and then retrieve it. A timeout of 5000 ms is used.
    camera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

	 // Image grabbed successfully?
    if (ptrGrabResult->GrabSucceeded())
    {
		CImageFormatConverter fc;
		fc.OutputPixelFormat = PixelType_RGB8packed;
		CPylonImage image;
		fc.Convert(image, ptrGrabResult);
        // Access the image data.
        // cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
        // cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
	    // uint8_t *pt = (uint8_t*)ptrGrabResult->GetBuffer();
		
		memcpy(THByteTensor_data(frame), image.GetBuffer(), 3*1200*1920);
		// cout << "Tensor size: " << frame->size[1] << endl;
    }
    else
    {
        cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
    }

}

void terminate()	   
{
	// Releases all pylon resources. 
    PylonTerminate();  
}


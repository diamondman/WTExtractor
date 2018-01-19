#include "WT.hpp"
#include "basetypes.hpp"
#include "InternalCallbackWrapper.hpp"

#include "WTActor.hpp"
#include "WTAudioClip.hpp"
#include "WTAudioClip3D.hpp"
#include "WTBitmap.hpp"
#include "WTCamera.hpp"
#include "WTContainer.hpp"
#include "WTEvent.hpp"
#include "WTFile.hpp"
#include "WTFont.hpp"
#include "WTGroup.hpp"
#include "WTJoystick.hpp"
#include "WTKeyboardPollInfo.hpp"
#include "WTLight.hpp"
#include "WTModel.hpp"
#include "WTMousePollInfo.hpp"
#include "WTPortal.hpp"
#include "WTShadow.hpp"
#include "WTSpout.hpp"
#include "WTStage.hpp"
#include "WTString3D.hpp"
#include "WTSurfaceShader.hpp"
#include "WTSysInfo.hpp"
#include "WTVisualizer.hpp"
#include "WTObject.hpp"

#include <iostream>
#include <unistd.h>

WT::WT(){}

///Creates a box model.
WTModel* WT::createBox(float Width,
                   float Height,
                   float Depth,
                   int Number_Of_Tiles_Per_Edge){
  APILOG;
  return new WTModel();
}

///Create the main stage for the scene.
WTStage* WT::createStage(){
  APILOG;
  return new WTStage();
}

///Create a model using data loaded from the specified .wt file.
WTModel* WT::createModel(char* File_Name,
                         int WTCache_Type){
  APILOG;
  return new WTModel(File_Name, WTCache_Type);
}

///Creates a container for a model or bitmap.
WTContainer* WT::createContainer(){
  APILOG;
  return new WTContainer();
}

///Creates a light.
WTLight* WT::createLight(int Type){
  APILOG;
  return new WTLight(Type);
}

///Creates a group to use for placement of child objects.
WTGroup* WT::createGroup(){
  APILOG;
  return new WTGroup();
}

///Creates an empty WTBitmap object.
WTBitmap* WT::createBlankBitmap(int Width,
                                int Height){
  APILOG;
  return new WTBitmap(Width, Height);
}

///Creates a WTBitmap object from a media file.
WTBitmap* WT::createBitmap(char* File_Name,
                           int WTCache_Type){
  APILOG;
  std::cout << "  (\"" << File_Name << "\", " << WTCache_Type << ")" << std::endl;
  return new WTBitmap(File_Name, WTCache_Type);
}

///Creates a WTAudioClip object from a media file.
WTAudioClip* WT::createAudioClip(char* File_Name,
                                 int WTCache_Type){
  APILOG;
  return new WTAudioClip(File_Name, WTCache_Type);
}

///Creates a WTVisualizer object.
WTVisualizer* WT::createAudioVisualizer(char* Visualizer_Type,
                                        char* Get_Audio_From,
                                        int Number_Of_Data_Bins,
                                        int Reserved){
  APILOG;
  return new WTVisualizer(Visualizer_Type,
                          Get_Audio_From,
                          Number_Of_Data_Bins);
}

///Sets the state of the mouse (arrow) cursor to on or off.
void WT::setMouseCursorState(int Mouse_Cursor_Type){
  APILOG;
}

///Sets the position of the mouse pointer.
void WT::setMousePosition(int WT_X,
                          int WT_Y){
  APILOG;
}

///Starts the scene rendering.
void WT::start(){
  APILOG;
  this->wtThreadRun = true;
  this->wtThreadActive = true;
  wtMainThread = std::thread(thread_bootstrap, this);
}

///Stops all events from firing and stops rendering the scene.
void WT::stop(){
  APILOG;
  this->wtThreadRun = false;
  this->wtMainThread.join();
  this->wtThreadActive = false;
}

///Creates a line model.
WTModel* WT::createLine(float X1,
                        float Y1,
                        float Z1,
                        float X2,
                        float Y2,
                        float Z2,
                        float Radius,
                        int Number_Of_Sides,
                        int Cap_Type,
                        int Line_Type){
  APILOG;
  return new WTModel();
}

///Creates a cone model.
WTModel* WT::createCone(float Height,
                        float Radius,
                        int Number_Of_Sides,
                        int Cap_Type){
  APILOG;
  return new WTModel();
}

///Creates a cylinder model.
WTModel* WT::createCylinder(float Height,
                            float Radius,
                            int Number_Of_Sides,
                            int Cap_Type){
  APILOG;
  return new WTModel();
}

///Creates a plane model.
WTModel* WT::createPlane(float Width,
                         float Height,
                         bool Make_Plane_With_Two_Sides,
                         float X_Center,
                         float Y_Center,
                         int Number_Of_Tiles_Per_Edge){
  APILOG;
  return new WTModel();
}

///Creates a patch model.
WTModel* WT::createPatch(int Number_Of_S_Points,
                         int Number_Of_T_Points,
                         float Size_Of_Each_S_Tile,
                         float Size_Of_Each_T_Tile,
                         float x,
                         float Z,
                         bool Make_Patch_With_Two_Sides){
  APILOG;
  return new WTModel();
}

//[id(0x00000017), hidden]
void WT::setHWND(int hWnd){
  APILOG;
}

//[id(0x00000018), hidden]
void WT::setClientRect(int x,
                       int y,
                       int w,
                       int h){
  APILOG;
}

//[id(0x00000019), hidden]
void WT::setClipRect(int x,
                     int y,
                     int w,
                     int h){
  APILOG;
}

///Gets the last event that occured.
WTEvent* WT::getEvent(){
  APILOG;
  return 0;
}

//[id(0x0000001c), hidden]
WTEvent* WT::getRenderEvent(){
  APILOG;
  return 0;
}

///Overrides the default behaviour for WT exceptions.
void WT::overrideExceptionEvent(int Exception_Type_To_Change,
                                bool New_Value){
  APILOG;
}

///Gets status driver initializations.
bool WT::getInitStatus(int Status_To_Get){
  APILOG;
  switch(Status_To_Get){
  case 0: //DirectX version out of date?
    return false;
  case 1: //Unsupported Color Depth?
    return false;
  case 2: //No hardware acceleration found?
    return false;
  case 3: //No ADPCM (sound) support?
    return false;
  case 7: //24 bit color?
    return false;
  case 8: //32 bit color?
    return true;
  default:
    return false;
  }
}

///Controls the use of hardware rendering capability.
void WT::setUseHAL(bool Use_Hardware_If_Possible){
  APILOG;
}

//[id(0x00000028), hidden]
bool WT::getIsUsable(){
  APILOG;
  return 0;
}

///Gets the currently installed version of the Web Driver.
char* WT::getVersion(){
  APILOG;
  return 0;
}

//Compares Web Driver versions.
int WT::checkVersion(char* Version,
                     char* Check_Against){
  APILOG;
  return 0;
}

///Sets the current working directory (not for web pages).
void WT::setFilesPath(char* Default_File_Path){
  APILOG;
}

///Gets the current working directory.
char* WT::getFilesPath(){
  APILOG;
  return (char*)"/";
}

///Forces a single render.
void WT::exec(){
  APILOG;
}

///Switches to a full screen display mode.
bool WT::setResolution(int Screen_Width,
                       int Screen_Height,
                       int Bits_Per_Pixel){
  APILOG;
  return 0;
}

///Restore the display to windowed mode.
void WT::restoreResolution(){
  APILOG;
}

///Sets the maximum number of files to download at once.
void WT::setMaxDownloads(int Max_Simultaneous_Downloads){
  APILOG;
}

///Gets the maximum number of files that will be downloaded simultaneously.
int WT::getMaxDownloads(){
  APILOG;
  return 0;
}

///Opens a remote or local file for reading.
WTFile* WT::readFile(char* File_Name,
                     int WTCache_Type,
                     int endian){
  APILOG;
  std::cout << "  (\"" << File_Name << "\", " << WTCache_Type << ", " << endian << ")" << std::endl;
  return new WTFile();
}

///Opens a debug window.
void WT::debugWindow(bool Display_the_Window){
  APILOG;
}

///Writes a string to the debug window.
void WT::outDebugString(char* String_To_Display){
  APILOG;
  std::cout << "WTDebug: " << String_To_Display << std::endl;
}

//[id(0x00000038), hidden]
void WT::setLeftHanded(bool newVal){
  APILOG;
}

///Returns the height of the driver window.
int WT::getHeight(){
  APILOG;
  return 0;
}

///Gets the width of the driver window.
int WT::getWidth(){
  APILOG;
  return 0;
}

///Returns system performance information.
WTSysInfo* WT::getPerformanceInfo(){
  APILOG;
  return 0;
}

///Suspends browser execution for a specified period.
void WT::sleep(int Number_Of_Milliseconds){
  APILOG;
}

///Creates a sphere model.
WTModel* WT::createSphere(float Radius,
                          int Number_Of_Points_Around){
  APILOG;
  return new WTModel();
}

//[id(0x0000003d), hidden]
void WT::freeDev(){
  APILOG;
}

///Creates a joystick access object.
WTJoystick* WT::createJoystick(){
  APILOG;
  return new WTJoystick();
}

///Creates group from a WTStudio level file.
WTGroup* WT::createGroupFromFile(char* File_Name,
                                 int WTCache_Type,
                                 int Load_Order_Offset,
                                 int Reserved){
  APILOG;
  return new WTGroup(File_Name,
                     WTCache_Type,
                     Load_Order_Offset);
}

///Create a WTActor from .wsad file.
WTActor* WT::createActor(char* File_Name,
                         int WTCache_Type){
  APILOG;
  return new WTActor(File_Name,
                     WTCache_Type);
}

//[id(0x00000041), hidden]
void WT::NSActivate(int hWnd){
  APILOG;
}

///Allows you to modify how the scene is rendered.
void WT::setRenderOption(int Option_To_Set,
                         int Option_Value){
  APILOG;
}

///Gets a render option value.
int WT::getRenderOption(int Option_To_Get){
  APILOG;
  return 0;
}

///Specifies the desired feature set.
int WT::designedForVersion(char* Version,
                           char* Flavor,
                           int Reserved){
  APILOG;
  return 0;
}

///Give your code the ability to control the mouse cursor.
int WT::requestMouseControl(){
  APILOG;
  return 0;
}

///Gets a snapshot of the keyboard state.
WTKeyboardPollInfo* WT::pollKeyboard(){
  APILOG;
  return 0;
}

///Gets a snapshot of the mouse state.
WTMousePollInfo* WT::pollMouse(){
  APILOG;
  return 0;
}

///Creates a WTSurfaceShader object.
WTSurfaceShader* WT::createSurfaceShader(){
  APILOG;
  return new WTSurfaceShader();
}

///This method creates a WTFont object.
WTFont* WT::createFont(int Reserved){
  APILOG;
  return new WTFont();
}

///Gets the value of a WT option.
VARIANT WT::getOption(int Option_Number){
  APILOG;
  return 0;
}

///Sets a WT option.
void WT::setOption(int Option_Number,
                   VARIANT New_Value){
  APILOG;
}

///Gets the information associated with the WT object.
double WT::getInfo(int Info_Type,
                   int Reserved){
  APILOG;
  return 0;
}

///This method creates a 3D Audio Clip object.
WTAudioClip3D* WT::createAudioClip3D(char* File_Name,
                                     int WTCache_Type){
  APILOG;
  return new WTAudioClip3D(File_Name,
                           WTCache_Type);
}

///Returns the current master volume setting for all audio in the program.
int WT::getMasterVolume(){
  APILOG;
  return 0;
}

///Sets the master volume level for all audio in the program.
void WT::setMasterVolume(int vol){
  APILOG;
}

///Allows the user to read from the registry relative to the
///[HKEY_CURRENT_USER]\Software\WildTangent\UserRegStrings\ key.
char* WT::getRegistryStringValue(char* Sub_Key,
                                 char* Value_Name){
  APILOG;
  return 0;
}

///This method creates a WTSpout object.
WTSpout* WT::createSpout(){
  APILOG;
  return new WTSpout();
}

///Creates a WTPortal object.
WTPortal* WT::createPortal(float Width,
                           float Height,
                           WTCamera* pCam,
                           int mappingOption,
                           bool doubleSided,
                           bool renderOnlyChildren){
  APILOG;
  return new WTPortal(Width,
                      Height,
                      pCam,
                      mappingOption,
                      doubleSided,
                      renderOnlyChildren);
}

///Gets download information.
int WT::getDownloadInfo(int WhichCounter,
                        int Param){
  APILOG;
  return 0;
}

///Resets all of the download and time counters.
void WT::resetDownloadInfo(){
  APILOG;
}

///Create a new Generic Mesh WTModel.
WTModel* WT::createMesh(
  float Vertex_Array[],
  int Face_Array[],
  float Normal_Array[],
  float UV_Array[],
  uint8_t Color_Array[],
  int Vertex_Array_Size,
  int Face_Array_Size,
  int Vertex_Lower_Bound,
  int Face_Lower_Bound,
  int Normal_Lower_Bound,
  int UV_Lower_Bound,
  int Color_Lower_Bound
){
  APILOG;
  return new WTModel();
}

///Creates a blank Generic Mesh WTModel.
WTModel* WT::createBlankMesh(){
  APILOG;
  return new WTModel();
}

//[id(0x00000058), propget]
bool WT::RenderMode(){
  APILOG;
  return 0;
}

//[id(0x00000058), propput]
void WT::RenderMode(bool pValue){
  APILOG;
}

int WT::getRenderMode(){
  APILOG;
  return 0;
}

void WT::setRenderMode(int mode){
  APILOG;
}

///Creates a new WTString3D object.
WTString3D* WT::createString3D(){
  APILOG;
  return new WTString3D();
}

///This method creates a WTShadow object.
WTShadow* WT::createShadow(int Type,
                           int Width,
                           int Height){
  APILOG;
  return new WTShadow(Type,
                      Width,
                      Height);
}

//[id(0x0000005b), hidden]
void WT::setOptionString(char* GUID,
                         char* key,
                         char* Data,
                         int Parameter){
  APILOG;
}

void WT::thread_bootstrap(void* This){
  ((WT*)This)->wtMainThreadFunc();
}

void WT::wtMainThreadFunc(){
  while(this->wtThreadRun){
    std::cout << std::endl << "HELLO FROM WT THREAD" << std::endl;
    if(this->RenderCallback != 0){
      WTEvent *event = new WTEvent();
      event->_Type = 8;
      this->RenderCallback->run(event);
    }
    usleep(0.01 * 1000 * 1000);
  }
}

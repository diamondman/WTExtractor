#include "WT.hpp"
#include "basetypes.hpp"

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

///Creates a box model.
WTModel* createBox(float Width,
                   float Height,
                   float Depth,
                   int Number_Of_Tiles_Per_Edge){
  return 0;
}

///Create the main stage for the scene.
WTStage* WT::createStage(){
  return 0;
}

///Create a model using data loaded from the specified .wt file.
WTModel* WT::createModel(char* File_Name,
                     int WTCache_Type){
  return 0;
}

///Creates a container for a model or bitmap.
WTContainer* WT::createContainer(){
  return 0;
}

///Creates a light.
WTLight* WT::createLight(int Type){
  return 0;
}

///Creates a group to use for placement of child objects.
WTGroup* WT::createGroup(){
  return 0;
}

///Creates an empty WTBitmap object.
WTBitmap* WT::createBlankBitmap(int Width,
                            int Height){
  return 0;
}

///Creates a WTBitmap object from a media file.
WTBitmap* WT::createBitmap(char* File_Name,
                       int WTCache_Type){
  return 0;
}

///Creates a WTAudioClip object from a media file.
WTAudioClip* WT::createAudioClip(char* File_Name,
                             int WTCache_Type){
  return 0;
}

///Creates a WTVisualizer object.
WTVisualizer* WT::createAudioVisualizer(char* Visualizer_Type,
                                    char* Get_Audio_From,
                                    int Number_Of_Data_Bins,
                                    int Reserved){
  return 0;
}

///Sets the state of the mouse (arrow) cursor to on or off.
void WT::setMouseCursorState(int Mouse_Cursor_Type){}

///Sets the position of the mouse pointer.
void WT::setMousePosition(int WT_X,
                      int WT_Y){}

///Starts the scene rendering.
void WT::start(){}

///Stops all events from firing and stops rendering the scene.
void WT::stop(){}

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
  return 0;
}

///Creates a cone model.
WTModel* WT::createCone(float Height,
                    float Radius,
                    int Number_Of_Sides,
                    int Cap_Type){
  return 0;
}

///Creates a cylinder model.
WTModel* WT::createCylinder(float Height,
                        float Radius,
                        int Number_Of_Sides,
                        int Cap_Type){
  return 0;
}

///Creates a plane model.
WTModel* WT::createPlane(float Width,
                     float Height,
                     bool Make_Plane_With_Two_Sides,
                     float X_Center,
                     float Y_Center,
                     int Number_Of_Tiles_Per_Edge){
  return 0;
}

///Creates a patch model.
WTModel* WT::createPatch(int Number_Of_S_Points,
                     int Number_Of_T_Points,
                     float Size_Of_Each_S_Tile,
                     float Size_Of_Each_T_Tile,
                     float x,
                     float Z,
                     bool Make_Patch_With_Two_Sides){
  return 0;
}

//[id(0x00000017), hidden]
void WT::setHWND(int hWnd){}

//[id(0x00000018), hidden]
void WT::setClientRect(int x,
                   int y,
                   int w,
                   int h){}

//[id(0x00000019), hidden]
void WT::setClipRect(int x,
                 int y,
                 int w,
                 int h){}

///Gets the last event that occured.
WTEvent* WT::getEvent(){
  return 0;
}

//[id(0x0000001c), hidden]
WTEvent* WT::getRenderEvent(){
  return 0;
}

///Asks the WT object to start or stop sending WTEvents to a RenderEvent handler.
void WT::setNotifyRenderEvent(bool Turn_Render_Events_On){}

///Returns a value indicating whether render events are turned on or off.
bool WT::getNotifyRenderEvent(){
  return 0;
}

///Sets the detail level of mouse events that the WT Object will send.
void WT::setNotifyMouseEvent(int Level_Of_Detail){}

///Returns a value indicating what detail level of mouse events are
///being sent to a mouse event handler.
int WT::getNotifyMouseEvent(){
  return 0;
}

///Starts or stops sending keyboard events to an event handler.
void WT::setNotifyKeyboardEvent(bool Turn_Keyboard_Events_On){}

///Returns a value indicating whther keyboard events are turned on or off.
bool WT::getNotifyKeyboardEvent(){
  return 0;
}

///Starts or stops sending exception events to an event handler.
void WT::setNotifyExceptionEvent(bool Turn_Exception_Events_On){}

///Returns a value indicating whether exception events are turned on or off.
bool WT::getNotifyExceptionEvent(){
  return 0;
}

///Overrides the default behaviour for WT exceptions.
void WT::overrideExceptionEvent(int Exception_Type_To_Change,
                            bool New_Value){}

///Gets status driver initializations.
bool WT::getInitStatus(int Status_To_Get){
  return 0;
}

///Controls the use of hardware rendering capability.
void WT::setUseHAL(bool Use_Hardware_If_Possible){}

//[id(0x00000028), hidden]
bool WT::getIsUsable(){
  return 0;
}

///Gets the current framerate cap.
int WT::getMaxFramesPerSecond(){
  return 0;
}

///Sets a speed limiter on the number of frames per second.
void WT::setMaxFramesPerSecond(int Frame_Rate_Cap){}

///Gets the currently installed version of the Web Driver.
char* WT::getVersion(){
  return 0;
}

//Compares Web Driver versions.
int WT::checkVersion(char* Version,
                 char* Check_Against){
  return 0;
}

///Sets the current working directory (not for web pages).
void WT::setFilesPath(char* Default_File_Path){}

///Gets the current working directory.
char* WT::getFilesPath(){
  return 0;
}

///Forces a single render.
void WT::exec(){}

///Sets the severity of error handling for the WT object.
void WT::setErrorHandling(int How_To_Handle_Errors){}

///Gets an integer value indicating the current severity of error handling.
int WT::getErrorHandling(){
  return 0;
}

///Switches to a full screen display mode.
bool WT::setResolution(int Screen_Width,
                   int Screen_Height,
                   int Bits_Per_Pixel){
  return 0;
}

///Restore the display to windowed mode.
void WT::restoreResolution(){}

///Sets the maximum number of files to download at once.
void WT::setMaxDownloads(int Max_Simultaneous_Downloads){}

///Gets the maximum number of files that will be downloaded simultaneously.
int WT::getMaxDownloads(){
  return 0;
}

///Opens a remote or local file for reading.
WTFile* WT::readFile(char* File_Name,
                 int WTCache_Type,
                 int endian){
  return 0;
}

///Opens a debug window.
void WT::debugWindow(bool Display_the_Window){}

///Writes a string to the debug window.
void WT::outDebugString(char* String_To_Display){}

//[id(0x00000038), hidden]
void WT::setLeftHanded(bool newVal){}

///Returns the height of the driver window.
int WT::getHeight(){
  return 0;
}

///Gets the width of the driver window.
int WT::getWidth(){
  return 0;
}

///Returns system performance information.
WTSysInfo* WT::getPerformanceInfo(){
  return 0;
}

///Suspends browser execution for a specified period.
void WT::sleep(int Number_Of_Milliseconds){}

///Creates a sphere model.
WTModel* WT::createSphere(float Radius,
                      int Number_Of_Points_Around){
  return 0;
}

//[id(0x0000003d), hidden]
void WT::freeDev(){}

///Creates a joystick access object.
WTJoystick* WT::createJoystick(){
  return 0;
}

///Creates group from a WTStudio level file.
WTGroup* WT::createGroupFromFile(char* File_Name,
                             int WTCache_Type,
                             int Load_Order_Offset,
                             int Reserved){
  return 0;
}

///Create a WTActor from .wsad file.
WTActor* WT::createActor(char* File_Name,
                     int WTCache_Type){
  return 0;
}

//[id(0x00000041), hidden]
void WT::NSActivate(int hWnd){}

///Allows you to modify how the scene is rendered.
void WT::setRenderOption(int Option_To_Set,
                     int Option_Value){}

///Gets a render option value.
int WT::getRenderOption(int Option_To_Get){
  return 0;
}

///Specifies the desired feature set.
int WT::designedForVersion(char* Version,
                       char* Flavor,
                       int Reserved){
  return 0;
}

///Give your code the ability to control the mouse cursor.
int WT::requestMouseControl(){
  return 0;
}

///Gets a snapshot of the keyboard state.
WTKeyboardPollInfo* WT::pollKeyboard(){
  return 0;
}

///Gets a snapshot of the mouse state.
WTMousePollInfo* WT::pollMouse(){
  return 0;
}

///Creates a WTSurfaceShader object.
WTSurfaceShader* WT::createSurfaceShader(){
  return 0;
}

///This method creates a WTFont object.
WTFont* WT::createFont(int Reserved){
  return 0;
}

///Gets the value of a WT option.
VARIANT WT::getOption(int Option_Number){
  return 0;
}

///Sets a WT option.
void WT::setOption(int Option_Number,
               VARIANT New_Value){}

///Gets the information associated with the WT object.
double WT::getInfo(int Info_Type,
               int Reserved){
  return 0;
}

///This method creates a 3D Audio Clip object.
WTAudioClip3D* WT::createAudioClip3D(char* File_Name,
                                 int WTCache_Type){
  return 0;
}

///Returns the current master volume setting for all audio in the program.
int WT::getMasterVolume(){
  return 0;
}

///Sets the master volume level for all audio in the program.
void WT::setMasterVolume(int vol){}

///Allows the user to read from the registry relative to the
///[HKEY_CURRENT_USER]\Software\WildTangent\UserRegStrings\ key.
char* WT::getRegistryStringValue(char* Sub_Key,
                             char* Value_Name){
  return 0;
}

///This method creates a WTSpout object.
WTSpout* WT::createSpout(){
  return 0;
}

///Creates a WTPortal object.
WTPortal* WT::createPortal(float Width,
                       float Height,
                       WTCamera* pCam,
                       int mappingOption,
                       bool doubleSided,
                       bool renderOnlyChildren){
  return 0;
}

///Gets download information.
int WT::getDownloadInfo(int WhichCounter,
                    int Param){
  return 0;
}

///Resets all of the download and time counters.
void WT::resetDownloadInfo(){}

/*///Create a new Generic Mesh WTModel.
  WTModel* WT::createMesh([in, optional] VARIANT Vertex_Array,
  [in, optional] VARIANT Face_Array,
  [in, optional] VARIANT Normal_Array,
  [in, optional] VARIANT UV_Array,
  [in, optional] VARIANT Color_Array,
  int Vertex_Array_Size,
  int Face_Array_Size,
  int Vertex_Lower_Bound,
  int Face_Lower_Bound,
  int Normal_Lower_Bound,
  int UV_Lower_Bound,
  int Color_Lower_Bound){
  return 0;
}*/

///Creates a blank Generic Mesh WTModel.
WTModel* WT::createBlankMesh(){
  return 0;
}

//[id(0x00000058), propget]
bool WT::RenderMode(){
  return 0;
}

//[id(0x00000058), propput]
void WT::RenderMode(bool pValue){}

///Creates a new WTString3D object.
WTString3D* WT::createString3D(){
  return 0;
}

///This method creates a WTShadow object.
WTShadow* WT::createShadow(int Type,
                       int Width,
                       int Height){
  return 0;
}

//[id(0x0000005b), hidden]
void WT::setOptionString(char* GUID,
                     char* key,
                     char* Data,
                     int Parameter){}

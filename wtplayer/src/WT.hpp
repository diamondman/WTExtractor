#pragma once

#include "basetypes.hpp"
#include "InternalCallbackWrapper.hpp"

#include <thread>

class WTExceptionEvent;

class WTActor;
class WTAudioClip;
class WTAudioClip3D;
class WTBitmap;
class WTCamera;
class WTContainer;
class WTEvent;
class WTFile;
class WTFont;
class WTGroup;
class WTJoystick;
class WTKeyboardPollInfo;
class WTLight;
class WTModel;
class WTMousePollInfo;
class WTPortal;
class WTShadow;
class WTSpout;
class WTStage;
class WTString3D;
class WTSurfaceShader;
class WTSysInfo;
class WTVisualizer;
class WTObject;

class WT {

  //private:
  //InternalCallbackWrapper *callbackTest;

public:

  WT();

  /*void setCallbackTest(InternalCallbackWrapper *callback) {
    this->callbackTest = callback;
  }

  void callCallbackTest() {
    if(this->callbackTest != 0){
      this->callbackTest->run();
    }
    }*/

  ///Creates a box model.
  WTModel* createBox(float Width,
                     float Height,
                     float Depth,
                     int Number_Of_Tiles_Per_Edge = 3);

  ///Create the main stage for the scene.
  WTStage* createStage();

  ///Create a model using data loaded from the specified .wt file.
  WTModel* createModel(char* File_Name,
                       int WTCache_Type = 0);

  //Creates a container for a model or bitmap.
  WTContainer* createContainer();

  ///Creates a light.
  WTLight* createLight(int Type);

  ///Creates a group to use for placement of child objects.
  WTGroup* createGroup();

  ///Creates an empty WTBitmap object.
  WTBitmap* createBlankBitmap(int Width,
                              int Height);

  ///Creates a WTBitmap object from a media file.
  WTBitmap* createBitmap(char* File_Name,
                         int WTCache_Type = 0);

  ///Creates a WTAudioClip object from a media file.
  WTAudioClip* createAudioClip(char* File_Name,
                               int WTCache_Type = 0);

  ///Creates a WTVisualizer object.
  WTVisualizer* createAudioVisualizer(char* Visualizer_Type,
                                      char* Get_Audio_From,
                                      int Number_Of_Data_Bins,
                                      int Reserved);

  ///Sets the state of the mouse (arrow) cursor to on or off.
  void setMouseCursorState(int Mouse_Cursor_Type);

  ///Sets the position of the mouse pointer.
  void setMousePosition(int WT_X,
                        int WT_Y);

  ///Starts the scene rendering.
  void start();

  ///Stops all events from firing and stops rendering the scene.
  void stop();

  ///Creates a line model.
  WTModel* createLine(float X1,
                      float Y1,
                      float Z1,
                      float X2,
                      float Y2,
                      float Z2,
                      float Radius,
                      int Number_Of_Sides,
                      int Cap_Type,
                      int Line_Type);

  ///Creates a cone model.
  WTModel* createCone(float Height,
                      float Radius,
                      int Number_Of_Sides,
                      int Cap_Type);

  ///Creates a cylinder model.
  WTModel* createCylinder(float Height,
                          float Radius,
                          int Number_Of_Sides,
                          int Cap_Type);

  ///Creates a plane model.
  WTModel* createPlane(float Width,
                       float Height,
                       bool Make_Plane_With_Two_Sides = false,
                       float X_Center = 0,
                       float Y_Center = 0,
                       int Number_Of_Tiles_Per_Edge = 0);

  ///Creates a patch model.
  WTModel* createPatch(int Number_Of_S_Points,
                       int Number_Of_T_Points,
                       float Size_Of_Each_S_Tile,
                       float Size_Of_Each_T_Tile,
                       float x,
                       float Z,
                       bool Make_Patch_With_Two_Sides = false);

  //[id(0x00000017), hidden]
  void setHWND(int hWnd);

  //[id(0x00000018), hidden]
  void setClientRect(int x,
                     int y,
                     int w,
                     int h);

  //[id(0x00000019), hidden]
  void setClipRect(int x,
                   int y,
                   int w,
                   int h);

  ///Gets the last event that occured.
  WTEvent* getEvent();

  //[id(0x0000001c), hidden]
  WTEvent* getRenderEvent();

  ///Asks the WT object to start or stop sending WTEvents to a RenderEvent handler.
  void setNotifyRenderEvent(bool Turn_Render_Events_On){
      APILOG;
      this->NotifyRenderEvent = Turn_Render_Events_On;
  }

  ///Returns a value indicating whether render events are turned on or off.
  bool getNotifyRenderEvent(){
    APILOG;
    return this->NotifyRenderEvent;
  }

  ///Sets the detail level of mouse events that the WT Object will send.
  void setNotifyMouseEvent(bool Turn_Mouse_Events_On){
    APILOG;
    this->NotifyMouseEvent = Turn_Mouse_Events_On;
  }
  void setNotifyMouseEvent(int Turn_Mouse_Events_On) {
    setNotifyMouseEvent((bool)Turn_Mouse_Events_On);
  }

  ///Returns a value indicating what detail level of mouse events are
  ///being sent to a mouse event handler.
  int getNotifyMouseEvent(){
    APILOG;
    return this->NotifyMouseEvent;
  }

  ///Starts or stops sending keyboard events to an event handler.
  void setNotifyKeyboardEvent(bool Turn_Keyboard_Events_On){
    APILOG;
    this->NotifyKeyboardEvent = Turn_Keyboard_Events_On;
  }

  ///Returns a value indicating whther keyboard events are turned on or off.
  bool getNotifyKeyboardEvent(){
    APILOG;
    return this->NotifyKeyboardEvent;
  }

  ///Starts or stops sending exception events to an event handler.
  void setNotifyExceptionEvent(bool Turn_Exception_Events_On){
    APILOG;
    this->NotifyExceptionEvent = Turn_Exception_Events_On;
  }

  ///Returns a value indicating whether exception events are turned on or off.
  bool getNotifyExceptionEvent(){
    APILOG;
    return this->NotifyExceptionEvent;
  }

  void setOnExceptionEvent(InternalCallbackWrapper *callback){
    APILOG;
    this->ExceptionCallback = callback;
  }

  void setOnKeyboardEvent(InternalCallbackWrapper *callback){
    APILOG;
    this->KeyboardCallback = callback;
  }

  void setOnMouseEvent(InternalCallbackWrapper *callback){
    APILOG;
    this->MouseCallback = callback;
  }

  void setOnRenderEvent(InternalCallbackWrapper *callback){
    APILOG;
    this->RenderCallback = callback;
  }

  ///Overrides the default behaviour for WT exceptions.
  void overrideExceptionEvent(int Exception_Type_To_Change,
                              bool New_Value);

  ///Gets status driver initializations.
  bool getInitStatus(int Status_To_Get);

  ///Controls the use of hardware rendering capability.
  void setUseHAL(bool Use_Hardware_If_Possible);

  //[id(0x00000028), hidden]
  bool getIsUsable();

  ///Gets the current framerate cap.
  int getMaxFramesPerSecond(){
    APILOG;
    return this->MaxFramesPerSecond;
  }

  ///Sets a speed limiter on the number of frames per second.
  void setMaxFramesPerSecond(int Frame_Rate_Cap){
    APILOG;
    this->MaxFramesPerSecond = Frame_Rate_Cap;
  }

  ///Gets the currently installed version of the Web Driver.
  char* getVersion();

  //Compares Web Driver versions.
  int checkVersion(char* Version,
                   char* Check_Against = 0);

  ///Sets the current working directory (not for web pages).
  void setFilesPath(char* Default_File_Path);

  ///Gets the current working directory.
  char* getFilesPath();

  ///Forces a single render.
  void exec();

  /**Sets the severity of error handling for the WT object.
    WTHANDLEERROR_QUIET  = 0; Indicates silent errors - no error messages.
    WTHANDLEERROR_MSGBOX = 1; Indicates that dialog boxes mark errors.
  **/
  void setErrorHandling(int How_To_Handle_Errors){
    APILOG;
    this->ErrorHandling = How_To_Handle_Errors;
  }

  ///Gets an integer value indicating the current severity of error handling.
  int getErrorHandling(){
    APILOG;
    return this->ErrorHandling;
  }

  ///Switches to a full screen display mode.
  bool setResolution(int Screen_Width,
                     int Screen_Height,
                     int Bits_Per_Pixel = 0);

  ///Restore the display to windowed mode.
  void restoreResolution();

  ///Sets the maximum number of files to download at once.
  void setMaxDownloads(int Max_Simultaneous_Downloads);

  ///Gets the maximum number of files that will be downloaded simultaneously.
  int getMaxDownloads();

  ///Opens a remote or local file for reading.
  WTFile* readFile(char* File_Name,
                   int WTCache_Type = 0,
                   int endian = 2);

  ///Opens a debug window.
  void debugWindow(bool Display_the_Window);

  ///Writes a string to the debug window.
  void outDebugString(char* String_To_Display);

  //[id(0x00000038), hidden]
  void setLeftHanded(bool newVal);

  ///Returns the height of the driver window.
  int getHeight();

  ///Gets the width of the driver window.
  int getWidth();

  ///Returns system performance information.
  WTSysInfo* getPerformanceInfo();

  ///Suspends browser execution for a specified period.
  void sleep(int Number_Of_Milliseconds);

  ///Creates a sphere model.
  WTModel* createSphere(float Radius,
                        int Number_Of_Points_Around = 8);

  //[id(0x0000003d), hidden]
  void freeDev();

  ///Creates a joystick access object.
  WTJoystick* createJoystick();

  ///Creates group from a WTStudio level file.
  WTGroup* createGroupFromFile(char* File_Name,
                               int WTCache_Type = 0,
                               int Load_Order_Offset = 0,
                               int Reserved = 0);

  ///Create a WTActor from .wsad file.
  WTActor* createActor(char* File_Name,
                       int WTCache_Type = 0);

  //[id(0x00000041), hidden]
  void NSActivate(int hWnd);

  ///Allows you to modify how the scene is rendered.
  void setRenderOption(int Option_To_Set,
                       int Option_Value);

  ///Gets a render option value.
  int getRenderOption(int Option_To_Get);

  ///Specifies the desired feature set.
  int designedForVersion(char* Version,
                         char* Flavor = (char*)"FULL",
                         int Reserved = 1);

  ///Give your code the ability to control the mouse cursor.
  int requestMouseControl();

  ///Gets a snapshot of the keyboard state.
  WTKeyboardPollInfo* pollKeyboard();

  ///Gets a snapshot of the mouse state.
  WTMousePollInfo* pollMouse();

  ///Creates a WTSurfaceShader object.
  WTSurfaceShader* createSurfaceShader();

  ///This method creates a WTFont object.
  WTFont* createFont(int Reserved = 0);

  ///Gets the value of a WT option.
  VARIANT getOption(int Option_Number);

  ///Sets a WT option.
  void setOption(int Option_Number,
                 VARIANT New_Value);

  ///Gets the information associated with the WT object.
  double getInfo(int Info_Type,
                 int Reserved = 0);

  ///This method creates a 3D Audio Clip object.
  WTAudioClip3D* createAudioClip3D(char* File_Name,
                                   int WTCache_Type = 0);

  ///Returns the current master volume setting for all audio in the program.
  int getMasterVolume();

  ///Sets the master volume level for all audio in the program.
  void setMasterVolume(int vol);

  ///Allows the user to read from the registry relative to the
  ///[HKEY_CURRENT_USER]\Software\WildTangent\UserRegStrings\ key.
  char* getRegistryStringValue(char* Sub_Key,
                               char* Value_Name);

  ///This method creates a WTSpout object.
  WTSpout* createSpout();

  ///Creates a WTPortal object.
  WTPortal* createPortal(float Width,
                         float Height,
                         WTCamera* pCam,
                         int mappingOption,
                         bool doubleSided,
                         bool renderOnlyChildren);

  ///Gets download information.
  int getDownloadInfo(int WhichCounter,
                      int Param = 0);

  ///Resets all of the download and time counters.
  void resetDownloadInfo();

  ///Create a new Generic Mesh WTModel.
  WTModel* createMesh(float Vertex_Array[] = 0,
                      int Face_Array[] = 0,
                      float Normal_Array[] = 0,
                      float UV_Array[] = 0,
                      uint8_t Color_Array[] = 0,
                      int Vertex_Array_Size = -1,
                      int Face_Array_Size = -1,
                      int Vertex_Lower_Bound = 0,
                      int Face_Lower_Bound = 0,
                      int Normal_Lower_Bound = 0,
                      int UV_Lower_Bound = 0,
                      int Color_Lower_Bound = 0);

  ///Creates a blank Generic Mesh WTModel.
  WTModel* createBlankMesh();

  //[id(0x00000058), propget]
  bool RenderMode();

  //[id(0x00000058), propput]
  void RenderMode(bool pValue);

  int getRenderMode();

  void setRenderMode(int mode);

  ///Creates a new WTString3D object.
  WTString3D* createString3D();

  ///This method creates a WTShadow object.
  WTShadow* createShadow(int Type = 0,
                         int Width = 128,
                         int Height = 128);

  //[id(0x0000005b), hidden]
  void setOptionString(char* GUID,
                       char* key,
                       char* Data,
                       int Parameter = 0);

private:
  static void thread_bootstrap(void*);
  void wtMainThreadFunc();

  std::thread wtMainThread;
  bool wtThreadRun = true;
  bool wtThreadActive = false;

  bool NotifyRenderEvent = false;
  bool NotifyMouseEvent = false;
  bool NotifyKeyboardEvent = false;
  bool NotifyExceptionEvent = false;

  InternalCallbackWrapper *ExceptionCallback = 0;
  InternalCallbackWrapper *KeyboardCallback = 0;
  InternalCallbackWrapper *MouseCallback = 0;
  InternalCallbackWrapper *RenderCallback = 0;

  int ErrorHandling = 1;
  int MaxFramesPerSecond = 25;
};

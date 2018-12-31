#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <stdexcept>
#include <SDL.h>
#include <cairo.h>
#include <chrono>

#include "basetypes.hpp"
#include "InternalCallbackWrapper.hpp"

#include "WT.hpp"
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

WT::WT(char* localver_path,
       int width,
       int height){
  this->width = std::max(1, width);
  this->height = std::max(1, height);

  if(localver_path)
    this->working_directory = std::string(localver_path);
  else
    this->working_directory = "";

  std::cout << "Working directory: " << this->working_directory << std::endl;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    throw std::runtime_error("SDL coult not initialize.");
  }

  this->window = SDL_CreateWindow( "WTPlayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   width, height, SDL_WINDOW_SHOWN ); //
  if(this->window == NULL) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    throw std::runtime_error("Could not create SDL Window.");
  }

  this->sdlsurf = SDL_GetWindowSurface(window);

  this->cairosurf = cairo_image_surface_create_for_data
    (
     (unsigned char*)this->sdlsurf->pixels,
     CAIRO_FORMAT_RGB24,
     this->sdlsurf->w,
     this->sdlsurf->h,
     this->sdlsurf->pitch
    );
  if(this->cairosurf == NULL) {
    printf( "Cairo Surface could not be created!\n" );
    throw std::runtime_error("Could not create Cairo Surface.");
  }

  this->cr = cairo_create(this->cairosurf);
  if(this->cr == NULL) {
    printf( "Cairo Context could not be created!\n" );
    throw std::runtime_error("Could not create Cairo Context.");
  }
}

WT::~WT(){
  if(this->cr)
    cairo_destroy(this->cr);

  if(this->cairosurf)
    cairo_surface_destroy(this->cairosurf);

  if(this->stage)
    this->stage->Release();

  //SDL_FreeSurface( gHelloWorld );

  if(this->window)
    SDL_DestroyWindow(this->window);

  SDL_Quit();
}

///Creates a box model.
WTModel* WT::createBox(float Width,
                       float Height,
                       float Depth,
                       int Number_Of_Tiles_Per_Edge){
  APILOG;
  return new WTModel(this);
}

///Create the main stage for the scene.
WTStage* WT::createStage(){
  APILOG;
  if(this->stage)
    return this->stage;
  this->stage = new WTStage(this);
  this->stage->AddRef();
  return this->stage;
}

///Create a model using data loaded from the specified .wt file.
WTModel* WT::createModel(char* File_Name,
                         int WTCache_Type){
  APILOG;
  return new WTModel(this,
                     File_Name,
                     WTCache_Type);
}

///Creates a container for a model or bitmap.
WTContainer* WT::createContainer(){
  APILOG;
  return new WTContainer(this);
}

///Creates a light.
WTLight* WT::createLight(int Type){
  APILOG;
  return new WTLight(this,
                     Type);
}

///Creates a group to use for placement of child objects.
WTGroup* WT::createGroup(){
  APILOG;
  return new WTGroup(this);
}

///Creates an empty WTBitmap object.
WTBitmap* WT::createBlankBitmap(int Width,
                                int Height){
  APILOG;
  return new WTBitmap(this, Width, Height);
}

///Creates a WTBitmap object from a media file.
WTBitmap* WT::createBitmap(char* File_Name,
                           int WTCache_Type){
  APILOG;
  std::cout << "  (\"" << File_Name << "\", " << WTCache_Type << ")" << std::endl;
  return new WTBitmap(this, File_Name, WTCache_Type);
}

///Creates a WTAudioClip object from a media file.
WTAudioClip* WT::createAudioClip(char* File_Name,
                                 int WTCache_Type){
  APILOG;
  return new WTAudioClip(this,
                         File_Name,
                         WTCache_Type);
}

///Creates a WTVisualizer object.
WTVisualizer* WT::createAudioVisualizer(char* Visualizer_Type,
                                        char* Get_Audio_From,
                                        int Number_Of_Data_Bins,
                                        int Reserved){
  APILOG;
  return new WTVisualizer(this,
                          Visualizer_Type,
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
  return new WTModel(this);
}

///Creates a cone model.
WTModel* WT::createCone(float Height,
                        float Radius,
                        int Number_Of_Sides,
                        int Cap_Type){
  APILOG;
  return new WTModel(this);
}

///Creates a cylinder model.
WTModel* WT::createCylinder(float Height,
                            float Radius,
                            int Number_Of_Sides,
                            int Cap_Type){
  APILOG;
  return new WTModel(this);
}

///Creates a plane model.
WTModel* WT::createPlane(float Width,
                         float Height,
                         bool Make_Plane_With_Two_Sides,
                         float X_Center,
                         float Y_Center,
                         int Number_Of_Tiles_Per_Edge){
  APILOG;
  return new WTModel(this);
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
  return new WTModel(this);
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
  return new WTFile(this, File_Name, WTCache_Type, endian);
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
  return new WTModel(this);
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
  return new WTGroup(this,
                     File_Name,
                     WTCache_Type,
                     Load_Order_Offset);
}

///Create a WTActor from .wsad file.
WTActor* WT::createActor(char* File_Name,
                         int WTCache_Type){
  APILOG;
  return new WTActor(this,
                     File_Name,
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
  return new WTSurfaceShader(this);
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
  return new WTAudioClip3D(this,
                           File_Name,
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
  return new WTSpout(this);
}

///Creates a WTPortal object.
WTPortal* WT::createPortal(float Width,
                           float Height,
                           WTCamera* pCam,
                           int mappingOption,
                           bool doubleSided,
                           bool renderOnlyChildren){
  APILOG;
  return new WTPortal(this,
                      Width,
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
  return new WTModel(this);
}

///Creates a blank Generic Mesh WTModel.
WTModel* WT::createBlankMesh(){
  APILOG;
  return new WTModel(this);
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
  return new WTString3D(this);
}

///This method creates a WTShadow object.
WTShadow* WT::createShadow(int Type,
                           int Width,
                           int Height){
  APILOG;
  return new WTShadow(this,
                      Type,
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

static int SDLKeyToWTKey(SDL_Keycode code) {
  switch(code){
  case SDLK_LEFT:
    return 37;
  case SDLK_UP:
    return 38;
  case SDLK_RIGHT:
    return 39;
  case SDLK_DOWN:
    return 40;
  case SDLK_RETURN:
    return 13;//return
  case SDLK_SPACE:
    return 32;//space
  case SDLK_SEMICOLON:
    return 186;//semicolon
  case SDLK_EQUALS:
    return 187;//"equals
  case SDLK_COMMA:
    return 188;//"comma
  case SDLK_MINUS:
    return 189;//"dash
  case SDLK_PERIOD:
    return 190;//"period
  case SDLK_SLASH:
    return 191;//"fslash
  //case SDL_:
  //  return 192;//"~
  case SDLK_BACKSLASH:
    return 220;//"backslash
  case SDLK_QUOTE:
    return 222;//"quote
  case SDLK_KP_MULTIPLY:
    return 106;//"kp_star
  case SDLK_KP_PLUS:
    return 107;//"kp_plus
  case SDLK_KP_MINUS:
    return 109;//"kp_minus
  case SDLK_KP_BACKSPACE: // Correct?
    return 110;//"kp_del
  case SDLK_KP_DIVIDE:
    return 111;//"kp_slash
  case SDLK_KP_0:
    return 96;//"kp_0
  case SDLK_KP_1:
    return 97;//"kp_1
  case SDLK_KP_2:
    return 98;//"kp_2
  case SDLK_KP_3:
    return 99;//"kp_3
  case SDLK_KP_4:
    return 100;//"kp_4
  case SDLK_KP_5:
    return 101;//"kp_5
  case SDLK_KP_6:
    return 102;//"kp_6
  case SDLK_KP_7:
    return 103;//"kp_7
  case SDLK_KP_8:
    return 104;//"kp_8
  case SDLK_KP_9:
    return 105;//"kp_9
  case SDLK_0:
    return '0';
  case SDLK_1:
    return '1';
  case SDLK_2:
    return '2';
  case SDLK_3:
    return '3';
  case SDLK_4:
    return '4';
  case SDLK_5:
    return '5';
  case SDLK_6:
    return '6';
  case SDLK_7:
    return '7';
  case SDLK_8:
    return '8';
  case SDLK_9:
    return '9';
  case SDLK_a:
    return 'A';
  case SDLK_b:
    return 'B';
  case SDLK_c:
    return 'C';
  case SDLK_d:
    return 'D';
  case SDLK_e:
    return 'E';
  case SDLK_f:
    return 'F';
  case SDLK_g:
    return 'G';
  case SDLK_h:
    return 'H';
  case SDLK_i:
    return 'I';
  case SDLK_j:
    return 'J';
  case SDLK_k:
    return 'K';
  case SDLK_l:
    return 'L';
  case SDLK_m:
    return 'M';
  case SDLK_n:
    return 'N';
  case SDLK_o:
    return 'O';
  case SDLK_p:
    return 'P';
  case SDLK_q:
    return 'Q';
  case SDLK_r:
    return 'R';
  case SDLK_s:
    return 'S';
  case SDLK_t:
    return 'T';
  case SDLK_u:
    return 'U';
  case SDLK_v:
    return 'V';
  case SDLK_w:
    return 'W';
  case SDLK_x:
    return 'X';
  case SDLK_y:
    return 'Y';
  case SDLK_z:
    return 'Z';
  default:
    return 0;
  }
}

void WT::wtMainThreadFunc(){
  SDL_Event e;

  using namespace std::chrono;
  int last_render = (int)(duration_cast< milliseconds >
                          (system_clock::now().time_since_epoch()).count());

  while(this->wtThreadRun){
    std::cout << std::endl << "HELLO FROM WT THREAD " <<
      std::hex << static_cast<void*>(this->RenderCallback) << " Refcnt " <<
      std::endl;
    while( SDL_PollEvent(&e) ) {
      switch( e.type) {
      case SDL_QUIT:
        this->wtThreadRun = false;
        break;

      case SDL_MOUSEMOTION:{
        std::cout << "MOUSE MOTION EVENT ("<<e.motion.x<<", "<<e.motion.y<<")"
                  << std::endl;
        if(this->MouseCallback != 0){
            WTEvent *event = new WTEvent(WTEVENT_MOUSEMOVEEVENT);
            event->_WTX = e.motion.x;
            event->_WTY = e.motion.y;
            event->_X = e.motion.x;
            event->_Y = e.motion.y;
            //event->_ButtonState = 0; // TODO
            this->MouseCallback->run(event);
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
        if(this->MouseCallback != 0){
          int type_;
          int doubleType_;
          bool typeValid = true;
          switch(e.button.button){
          case SDL_BUTTON_LEFT:
            std::cout << "MOUSE LBTN DOWN EVENT";
            type_ = WTEVENT_MOUSELEFTBUTTONDOWN;
            doubleType_ = WTEVENT_MOUSELEFTDBLCLICKEVENT;
            break;
          case SDL_BUTTON_RIGHT:
            std::cout << "MOUSE RBTN DOWN EVENT";
            type_ = WTEVENT_MOUSERIGHTBUTTONDOWN;
            doubleType_ = WTEVENT_MOUSERIGHTDBLCLICKEVENT;
            break;
          case SDL_BUTTON_MIDDLE:
            std::cout << "MOUSE MBTN DOWN EVENT";
            type_ = WTEVENT_MOUSEMIDDLEBUTTONDOWN;
            doubleType_ = WTEVENT_MOUSEMIDDLEDBLCLICKEVENT;
            break;
          default:
            typeValid = false;
          }
          if(!typeValid) break;
          std::cout << " ("<<e.button.x<<", "<<e.button.y<<")" << std::endl;

          WTEvent *event = new WTEvent(type_);
          event->_WTX = e.button.x;
          event->_WTY = e.button.y;
          event->_X = e.button.x;
          event->_Y = e.button.y;
          //event->_ButtonState = 0; // TODO
          this->MouseCallback->run(event);

          if(e.button.clicks == 2){
            std::cout << "MOUSE DOUBLE CLICK ALSO SENT" << std::endl;
            event = new WTEvent(doubleType_);
            event->_WTX = e.button.x;
            event->_WTY = e.button.y;
            event->_X = e.button.x;
            event->_Y = e.button.y;
            //event->_ButtonState = 0; // TODO
            this->MouseCallback->run(event);
          }
        }
        break;

      case SDL_MOUSEBUTTONUP:
        if(this->MouseCallback != 0){
          int type_;
          bool typeValid = true;
          switch(e.button.button){
          case SDL_BUTTON_LEFT:
            std::cout << "MOUSE LBTN UP EVENT";
            type_ = WTEVENT_MOUSELEFTBUTTONUP;
            break;
          case SDL_BUTTON_RIGHT:
            std::cout << "MOUSE RBTN UP EVENT";
            type_ = WTEVENT_MOUSERIGHTBUTTONUP;
            break;
          case SDL_BUTTON_MIDDLE:
            std::cout << "MOUSE MBTN UP EVENT";
            type_ = WTEVENT_MOUSEMIDDLEBUTTONUP;
            break;
          default:
            typeValid = false;
          }
          if(!typeValid) break;
          std::cout << " ("<<e.button.x<<", "<<e.button.y<<")" << std::endl;

          WTEvent *event = new WTEvent(type_);
          event->_WTX = e.button.x;
          event->_WTY = e.button.y;
          event->_X = e.button.x;
          event->_Y = e.button.y;
          //event->_ButtonState = 0; // TODO
          this->MouseCallback->run(event);

          //usleep(2 * 1000 * 1000);
        }
        break;
      case SDL_KEYDOWN:
        std::cout << "KEY DOWN EVENT ("<<e.key.keysym.sym<<")" << std::endl;
        if(this->KeyboardCallback != 0){
          WTEvent *event = new WTEvent(WTEVENT_KEYBOARDEVENT);
          event->_Key = SDLKeyToWTKey(e.key.keysym.sym);
          event->_KeyState = KEY_PRESS;
          this->KeyboardCallback->run(event);
        }
        break;
      case SDL_KEYUP:
        std::cout << "KEY UP EVENT ("<<e.key.keysym.sym<<")" << std::endl;
        if(this->KeyboardCallback != 0){
          WTEvent *event = new WTEvent(WTEVENT_KEYBOARDEVENT);
          event->_Key = SDLKeyToWTKey(e.key.keysym.sym);
          event->_KeyState = KEY_RELEASE;
          this->KeyboardCallback->run(event);
        }
        break;
      }
    }

    int curr_time = (int)(duration_cast<milliseconds>
                          (system_clock::now().time_since_epoch()).count());
    if(this->RenderCallback != 0){
      WTEvent *event = new WTEvent(WTEVENT_RENDEREVENT,
                                   curr_time - last_render);
      this->RenderCallback->run(event);
    }
    last_render = curr_time;

    SDL_FillRect(this->sdlsurf, NULL, 0x000000);

    if(this->stage)
      this->stage->_render(this->cr);

    SDL_UpdateWindowSurface(this->window);

    usleep(0.3 * 1000 * 1000);
  }
}

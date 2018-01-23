#include "basetypes.hpp"
#include "WTBitmap.hpp"
#include "WT.hpp"

WTBitmap::WTBitmap(WT* wt,
                   int width,
                   int height) :
  _wt(wt){
  std::cout << "New WTBitmap(width=" << width << ", height=" << height << ");" << std::endl;

  sdlsurf = SDL_CreateRGBSurface
    (0, width, height, 32,
     0x00FF0000,
     0x0000FF00,
     0x000000FF,
     0xFF000000);

  cairosurf = cairo_image_surface_create_for_data
    ((unsigned char*)sdlsurf->pixels,
     CAIRO_FORMAT_RGB24,
     this->sdlsurf->w,
     this->sdlsurf->h,
     this->sdlsurf->pitch);

  cr = cairo_create(cairosurf);
}


WTBitmap::WTBitmap(WT* wt,
                   char* File_Name,
                   int WTCache_Type) :
  _wt(wt){
  sdlsurf = SDL_CreateRGBSurface
    (0, 640, 480, 32,
     0x00FF0000,
     0x0000FF00,
     0x000000FF,
     0xFF000000);

  cairosurf = cairo_image_surface_create_for_data
    ((unsigned char*)sdlsurf->pixels,
     CAIRO_FORMAT_RGB24,
     this->sdlsurf->w,
     this->sdlsurf->h,
     this->sdlsurf->pitch);

  cr = cairo_create(cairosurf);
}

WTBitmap::~WTBitmap(){
  cairo_destroy(this->cr);
  cairo_surface_destroy(this->cairosurf);
  SDL_FreeSurface(this->sdlsurf);
}

void WTBitmap::setColorKey(unsigned char Red,
                           unsigned char Green,
                           unsigned char Blue){
  APILOG;
}

void WTBitmap::unsetColorKey(){
  APILOG;
}

int WTBitmap::getWidth(){
  APILOG;
  return this->sdlsurf->w;
}

int WTBitmap::getHeight(){
  APILOG;
  return this->sdlsurf->h;
}

void WTBitmap::drawText(int x,
                        int y,
                        char* Text_To_Draw){
  APILOG;
  std::cout << "  (X: " << x << "; Y: " << y << "; STR: " << Text_To_Draw << ")" << std::endl;
  cairo_move_to(this->cr, x, y);
  cairo_show_text(this->cr, Text_To_Draw);
}

void WTBitmap::setTextBold(int Draw_Text_In_Bold){
  APILOG;
}

void WTBitmap::setTextHeight(int Text_Height_In_Points){
  APILOG;
  cairo_set_font_size(this->cr, Text_Height_In_Points);
}

void WTBitmap::setTextItalic(int Draw_Text_In_Italic){
  APILOG;
}

void WTBitmap::setTextProperties(int Amount_Of_Bold,
                                 int Draw_Text_In_Italic,
                                 int Draw_Text_Underline,
                                 int Draw_Text_Strikeout,
                                 int Text_CharacterSet,
                                 int Text_Quality){
  APILOG;
}

//[id(0x00002332), hidden]
void WTBitmap::setTextFamily(int nPitch,
                             int nFamily){
  APILOG;
}

void WTBitmap::setTextFace(char* Font_Name_List){
  APILOG;
}

void WTBitmap::setTextColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){
  APILOG;
  cairo_set_source_rgb(this->cr, Red, Green, Blue);
}

void WTBitmap::setTextBkColor(unsigned char Red,
                              unsigned char Green,
                              unsigned char Blue){
  APILOG;
}

void WTBitmap::setColor(unsigned char Red,
                        unsigned char Green,
                        unsigned char Blue){
  APILOG;
}

void WTBitmap::drawLine(int X1,
                        int Y1,
                        int X2,
                        int Y2){
  APILOG;
}

void WTBitmap::setDrawColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){
  APILOG;
}

void WTBitmap::drawPixel(int x,
                         int y){
  APILOG;
}

void WTBitmap::destroy(){
  APILOG;
}

void WTBitmap::drawFillRect(int x,
                            int y,
                            int Width,
                            int Height){
  APILOG;
}

void WTBitmap::copyRect(WTBitmap* Source_Bitmap_To_Copy_From,
                        int Type,
                        int Source_X,
                        int Source_Y,
                        int Source_Width,
                        int Source_Height,
                        int Destination_X,
                        int Destination_Y,
                        int Destination_Width,
                        int Destination_Height){
  APILOG;
}

//[id(0x0000233f), hidden]
void WTBitmap::drawLineWithString(char* str,
                                  int bPolyline){
  APILOG;
}

//[id(0x00002340), hidden]
void WTBitmap::drawPixelWithString(char* str){
  APILOG;
}

//[id(0x00002341), hidden]
void WTBitmap::drawPolygonWithString(char* str){
  APILOG;
}

void WTBitmap::copyRectFromIntArray(int Source_Array[],
                                    int Blit_Type,
                                    int x,
                                    int y,
                                    int Source_Width,
                                    int Source_Height,
                                    int Destination_X,
                                    int Destination_Y,
                                    int Destination_Width,
                                    int Destination_Height,
                                    int Total_Array_Image_Width,
                                    int Total_Array_Image_Height){
  APILOG;
}

void WTBitmap::copyRectFromByteArray(uint8_t Source_Array[],
                                     int Blit_Type,
                                     int x,
                                     int y,
                                     int Source_Width,
                                     int Source_Height,
                                     int Destination_X,
                                     int Destination_Y,
                                     int Destination_Width,
                                     int Destination_Height,
                                     int Total_Array_Image_Width,
                                     int Total_Array_Image_Height){
  APILOG;
}

void WTBitmap::setTextureOpacityMask(WTBitmap* Bitmap_To_Be_Used_As_Alpha_Mask,
                                     int Channel){
  APILOG;
}

void WTBitmap::enableTextureTranslucency(bool Enable_Texture_Translucency){
  APILOG;
}

void WTBitmap::mapColorToBitmap(WTBitmap* Source_Bitmap,
                                int Red,
                                int Green,
                                int Blue){
  APILOG;
}

void WTBitmap::setTextUnderline(int Draw_Text_In_Underline){
  APILOG;
}

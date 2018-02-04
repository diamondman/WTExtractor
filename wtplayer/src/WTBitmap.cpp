#include <cairo.h>
#include <SDL.h>
#include <dataaccessors.h>
#include <wld3_extract.h>

#include "basetypes.hpp"

#include "WTBitmap.hpp"
#include "WT.hpp"

WTBitmap::WTBitmap(WT* wt_,
                   int width,
                   int height) :
  WTObject(wt_){
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


WTBitmap::WTBitmap(WT* wt_,
                   char* File_Name,
                   int WTCache_Type) :
  WTObject(wt_){
  std::string full_fname = std::string(this->wt->getFilesPath()) + "/" + File_Name;
  std::cout << "opening file: \"" << full_fname << "\"" << std::endl;

  DataAccessor* acc = openFileAccessor(full_fname.c_str());
  if(!acc){
    printf("Failed to create accessor for WTBitmap!\n\n");
    throw std::runtime_error("Could not create Accessor for WTBitmap.");
  }
  WLD3* wld3 = wld3_extract(acc);

  if(!wld3) {
    printf( "Cairo Surface could not be created!\n" );
    throw std::runtime_error("Could not create Cairo Surface.");
  }

  wld3_print(wld3);
  wld3_free(wld3);
  //wld3->payload_len
  //wld3->payload_data
  freeFileAccessor(acc);




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

  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, this->text_height);
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
  std::cout << std::hex <<
    "  (0x" << (int)Red <<
    ", 0x" << (int)Green <<
    ", 0x" << (int)Blue << ")" << std::endl;
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
  cairo_move_to(this->cr, x, y + this->text_height);
  cairo_set_source_rgb(cr, this->text_r, this->text_g, this->text_b);
  cairo_show_text(this->cr, Text_To_Draw);
}

void WTBitmap::setTextBold(int Draw_Text_In_Bold){
  APILOG;
}

void WTBitmap::setTextHeight(int Text_Height_In_Points){
  APILOG;
  int pixelheight = round(((float)Text_Height_In_Points * 2)/1.5);
  std::cout << "  (" << Text_Height_In_Points << " [" << pixelheight << "px])" << std::endl;
  this->text_height = pixelheight;
  cairo_set_font_size(this->cr, pixelheight);
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
  std::cout << "  (" << Font_Name_List << ")" << std::endl;
}

void WTBitmap::setTextColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){
  APILOG;
  std::cout << std::hex <<
    "  (0x" << (int)Red <<
    ", 0x" << (int)Green <<
    ", 0x" << (int)Blue << ")" << std::endl;
  this->text_r = ((float)Red)/255;
  this->text_g = ((float)Green)/255;
  this->text_b = ((float)Blue)/255;
}

void WTBitmap::setTextBkColor(unsigned char Red,
                              unsigned char Green,
                              unsigned char Blue){
  APILOG;
  std::cout << std::hex <<
    "  (0x" << (int)Red <<
    ", 0x" << (int)Green <<
    ", 0x" << (int)Blue << ")" << std::endl;
}

void WTBitmap::setColor(unsigned char Red,
                        unsigned char Green,
                        unsigned char Blue){
  APILOG;
  std::cout << std::hex <<
    "  (0x" << (int)Red <<
    ", 0x" << (int)Green <<
    ", 0x" << (int)Blue << ")" << std::endl;
  //std::cout << std::dec <<
  //  "  (" << (((float)Red)/255) <<
  //  ", " << (((float)Green)/255) <<
  //  ", " << (((float)Blue)/255) << ")" << std::endl;
  cairo_set_source_rgb(cr, ((float)Red)/255, ((float)Green)/255, ((float)Blue)/255);
  cairo_new_path (cr);  /* current path is not
                         consumed by cairo_clip() */
  cairo_rectangle (cr, 0, 0, this->sdlsurf->w, this->sdlsurf->h);
  cairo_fill (cr);

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
  std::cout << std::hex <<
    "  (0x" << (int)Red <<
    ", 0x" << (int)Green <<
    ", 0x" << (int)Blue << ")" << std::endl;
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

#include <algorithm>
#include <cairo.h>
#include <SDL.h>
#include <png.h>
#include <dataaccessors.h>
#include <wld3_extract.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <streambuf>

#include "basetypes.hpp"

#include "WTBitmap.hpp"
#include "WT.hpp"

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};

void ReadDataFromWLD3Buf(png_structp png_ptr,
                         png_bytep outBytes,
                         png_size_t byteCountToRead) {

   png_voidp io_ptr = png_get_io_ptr(png_ptr);
   if(io_ptr == NULL)
      return;   // add custom error handling here

   std::istream& inputStream = *(std::istream*)io_ptr;
   inputStream.read(
      (char*)outBytes,
      (size_t)byteCountToRead);

   if((png_size_t)inputStream.gcount() != byteCountToRead)
      return;   // add custom error handling here
}



WTBitmap::WTBitmap(WT* wt_,
                   int width,
                   int height) :
  WTObject(wt_),
  width(width), height(height){
  std::cout << "New WTBitmap(width=" << width << ", height=" << height << ");" << std::endl;

  int stride = cairo_format_stride_for_width (CAIRO_FORMAT_RGB24, width);
  data = (unsigned char*)malloc (stride * this->height);
  memset(data, 0, stride * this->height);

  for(int i = 0; i < this->width * this->height; i++){
    ((unsigned int*)this->data)[i] = 0x00FF0000;
  }

  cairosurf = cairo_image_surface_create_for_data
    ((unsigned char*)this->data,
     CAIRO_FORMAT_RGB24,
     this->width,
     this->height,
     stride);

  cr = cairo_create(cairosurf);
}


WTBitmap::WTBitmap(WT* wt_,
                   char* File_Name,
                   int WTCache_Type) :
  WTObject(wt_),
  width(100), height(100){

  std::string full_fname = std::string(this->wt->getFilesPath()) + "/" + File_Name;
  std::cout << "opening file: \"" << full_fname << "\"" << std::endl;

  std::shared_ptr<DataAccessor> acc = std::shared_ptr<DataAccessor>
    (openFileAccessor(full_fname.c_str()),
     freeFileAccessor);
  if(acc == nullptr){
    printf("Failed to create accessor for WTBitmap (%s)!\n\n", full_fname.c_str());
    throw std::runtime_error("Could not create Accessor for WTBitmap.");
  }
  printf("Acc made\n");

  std::shared_ptr<WLD3> wld3 = std::shared_ptr<WLD3>(wld3_extract(acc.get()),
                                                     wld3_free);
  if(wld3 == nullptr) {
    printf( "Cairo Surface could not be created!\n" );
    throw std::runtime_error("Could not create Cairo Surface.");
  }
  wld3->print();

  membuf sbuf((char*)wld3->payload_data,
              (char*)wld3->payload_data + wld3->payload_len);
  std::istream wld3buf(&sbuf);

  std::string outext = std::string((char*)wld3->outext);
  printf("Image type is %s\n\n", outext.c_str());

  if(outext == "jpg"){
    printf("IT IS A JPG! SKIP DOING THINGS\n\n");
    int stride = cairo_format_stride_for_width (CAIRO_FORMAT_RGB24, width);
    data = (unsigned char*)malloc (stride * this->height);
    memset(data, 0, stride * this->height);
    cairosurf = cairo_image_surface_create_for_data
      (this->data,//(unsigned char*)sdlsurf->pixels,
       CAIRO_FORMAT_RGB24,
       this->width,
       this->height,
       stride);//this->sdlsurf->pitch);

    for(int i = 0; i < this->width * this->height; i++){
      ((unsigned int*)this->data)[i] = 0x00FFFF00;
    }
  }else if(outext == "png"){
    if(png_sig_cmp(wld3->payload_data, 0, std::min((size_t)8, wld3->payload_len)) != 0){
      printf("WTBitmap: Png has incorrect signature!\n\n");
      throw std::runtime_error("WTBitmap: Png has incorrect signature.");
    }

    png_structp png_ptr = NULL;
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(png_ptr == NULL){
      printf("WTBitmap: libpng failed to create png_struct.\n\n");
      throw std::runtime_error("WTBitmap: libpng failed to create png_struct.");
    }


    png_infop info_ptr = png_create_info_struct(png_ptr);

    if(info_ptr == NULL){
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      printf("WTBitmap: libpng failed to create png_info.\n\n");
      throw std::runtime_error("WTBitmap: libpng failed to create png_info.");
    }

    png_set_read_fn(png_ptr, &wld3buf, ReadDataFromWLD3Buf);


    png_read_info(png_ptr, info_ptr);

    width          = png_get_image_width(png_ptr, info_ptr);
    height         = png_get_image_height(png_ptr, info_ptr);
    int color_type = png_get_color_type(png_ptr, info_ptr);
    int bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

    if(bit_depth == 16)
      png_set_strip_16(png_ptr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_expand_gray_1_2_4_to_8(png_ptr);

    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png_ptr);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    data = new unsigned char[this->width * this->height * 4];

    char* rowData = new char[png_get_rowbytes(png_ptr, info_ptr)];
    for(int y = 0; y < height; y++) {
      png_read_row(png_ptr, (png_bytep)&data[png_get_rowbytes(png_ptr, info_ptr) * y], NULL);
    }
    delete[] rowData;

    cairosurf = cairo_image_surface_create_for_data
      (this->data,
       CAIRO_FORMAT_RGB24,
       this->width,
       this->height,
       png_get_rowbytes(png_ptr, info_ptr));

  }else{
    printf("WTBitmap: Unknown image type %s!\n\n", outext.c_str());
    throw std::runtime_error("WTBitmap: Unknown image type.");
  }

  cr = cairo_create(cairosurf);

  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, this->text_height);
}

WTBitmap::~WTBitmap(){
  cairo_destroy(this->cr);
  cairo_surface_destroy(this->cairosurf);
  if(this->sdlsurf)
    SDL_FreeSurface(this->sdlsurf);
  if(this->data)
    delete [] this->data;
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
  cairo_rectangle (cr, 0, 0, this->width, this->height);
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

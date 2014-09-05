#include <stdio.h>
#include <ruby.h>

int red(unsigned long color) {
    return (color & 0xff000000) >> 24;
}

int green(unsigned long color) {
    return (color & 0x00ff0000) >> 16;
}

int blue(unsigned long color) {
    return (color & 0x0000ff00) >> 8;
}

int alpha(unsigned long color) {
    return color & 0x000000ff;
}

VALUE bitmap_data(VALUE vself, VALUE vpixels) {
    int pixel_size = RARRAY_LEN(vpixels);
    unsigned long color;
    int a; // alpha for swf bitmap data
    float a_dash;
    unsigned char r, g, b; // red, green, blue for swf bitmap data
    unsigned char data[pixel_size * 4]; // argb for swf bitmap data
    int i;
    int data_index = 0;
    for (i=0; i<pixel_size; ++i) {
        color = NUM2ULONG((RARRAY_PTR(vpixels)[i]));
        a = alpha(color);
        a_dash = a / 255.0;
        r = (unsigned char)(red(color) * a_dash);
        g = (unsigned char)(green(color) * a_dash);
        b = (unsigned char)(blue(color) * a_dash);
        data[data_index] = a; ++data_index;
        data[data_index] = r; ++data_index;
        data[data_index] = g; ++data_index;
        data[data_index] = b; ++data_index;
    }
    VALUE vdata;
    vdata = rb_str_new(0,0); // 戻り値用にrubyの空文字を作成 vdata = '' と同じ
    rb_str_cat(vdata, data, (pixel_size * 4)); // rubyの文字列としてバイナリデータを連結
    return vdata;
}

void Init_oily_png2swf() {
    VALUE Png2swf = rb_define_module("OilyPng2swf");

    VALUE DefineBitsLossless2 = rb_define_module_under(Png2swf, "DefineBitsLossless2");
    rb_define_method(DefineBitsLossless2, "bitmap_data", bitmap_data, 1);
}

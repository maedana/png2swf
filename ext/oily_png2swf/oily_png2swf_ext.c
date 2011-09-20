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
    int pixel_size = RARRAY(vpixels)->len;
    unsigned long color;
    int a; // alpha for swf bitmap data
    unsigned char r, g, b; // red, green, blue for swf bitmap data
    unsigned char data[pixel_size * 4]; // argb for swf bitmap data
    int i;
    int data_index = 0;
    for (i=0; i<pixel_size; i++) {
        color = NUM2ULONG((RARRAY(vpixels)->ptr[i]));
        a = alpha(color);
        r = (unsigned char)((red(color) * a) / 255.0);
        g = (unsigned char)((green(color) * a) / 255.0);
        b = (unsigned char)((blue(color)) * a / 255.0);
        data[data_index] = a;
        data[data_index+1] = r;
        data[data_index+2] = g;
        data[data_index+3] = b;
        data_index+=4;
    }
    VALUE vdata = rb_str_new(0,0); // 戻り値用にrubyの空文字を作成 vdata = '' と同じ
    rb_str_cat(vdata, data, (pixel_size * 4)); // rubyの文字列としてバイナリデータを連結
    return vdata;
}

Init_oily_png2swf() {
    VALUE Png2swf = rb_define_module("OilyPng2swf");

    VALUE DefineBitsLossless2 = rb_define_module_under(Png2swf, "DefineBitsLossless2");
    rb_define_method(DefineBitsLossless2, "bitmap_data", bitmap_data, 1);
}

require 'base64'
require 'chunky_png'
require 'png2swf/oily_png2swf'

module Png2swf
  class DefineBitsLossless2
    extend OilyPng2swf::DefineBitsLossless2

    def self.image2data_from_file filepath
      image2data(ChunkyPNG::Image.from_file(filepath))
    end

    def self.image2data_from_blob blob
      image2data(ChunkyPNG::Image.from_blob(blob))
    end

    def self.image2data image
      zlib_bitmap_data = Zlib::Deflate.deflate(bitmap_data(image.pixels))
      ::Base64.encode64(zlib_bitmap_data).split.join
    end
  end
end

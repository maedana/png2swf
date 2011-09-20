# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "png2swf/version"

Gem::Specification.new do |s|
  s.name        = "png2swf"
  s.rubyforge_project = "png2swf"
  s.version     = Png2swf::VERSION
  s.authors     = ["Naoki Maeda"]
  s.email       = ["maeda.na@gmail.com"]
  s.homepage    = "http://wiki.github.com/maedana/png2swf"
  s.summary     = %q{Encode png for swfmill bitmap formats.}
  s.description = %q{Encode png for swfmill bitmap formats.}


  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }

  s.extensions = ["ext/png2swf/extconf.rb"]
  s.require_paths = ["lib", "ext"]
end

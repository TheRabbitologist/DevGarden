#!/usr/bin/ruby

require 'rbconfig'
require 'pathname'
include RbConfig

_path = Pathname.new(ARGV[0])
_buildpath = _path.dirname.to_s+"/../"+(_path.dirname.basename.to_s)+"-build";

if !Dir.exist? _buildpath
	Dir.mkdir _buildpath
end

Dir.chdir _buildpath
system "qmake", "-r", _path.to_s
system "make"

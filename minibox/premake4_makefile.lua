if not _PREMAKE_VERSION then
   os.execute('premake4 --file=premake4_makefile.lua clean')
   os.execute('premake4 --file=premake4_makefile.lua gmake')
   return
end

solution "minibox"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "minibox"
      kind "ConsoleApp"
      language "C"
      location ( "build" )
      targetdir ( "bin" )
      libdirs { "/usr/lib" }
      links { "rt", "pthread", "gstreamer-0.10" }
      includedirs { "../lib/include", "usr/include", "/usr/include/gstreamer-0.10", "/usr/include/libxml2", "usr/include/gtk-3.0" }

      buildoptions { "`pkg-config --cflags gtk+-3.0`" }
      linkoptions { "`pkg-config --libs gtk+-3.0`" }

      files { "../lib/src/**.c", "src/**.h", "src/**.c" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }     

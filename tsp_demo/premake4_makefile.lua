if not _PREMAKE_VERSION then
   os.execute('premake4 --file=premake4_makefile.lua clean')
   os.execute('premake4 --file=premake4_makefile.lua gmake')
   return
end

solution "tsp_demo"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "tsp_demo"
      kind "ConsoleApp"
      language "C"
      location ( "build" )
      targetdir ( "bin" )
      libdirs { "/usr/lib" }
      links { }
      includedirs { "../lib/include", "usr/include", "usr/include/gtk-3.0" }

      buildoptions { "`pkg-config --cflags gtk+-3.0`" }
      linkoptions { "`pkg-config --libs gtk+-3.0`" }

      files { "src/**.h", "src/**.c" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }     

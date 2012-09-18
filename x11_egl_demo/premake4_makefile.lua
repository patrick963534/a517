if not _PREMAKE_VERSION then
   os.execute('premake4 --file=premake4_makefile.lua clean')
   os.execute('premake4 --file=premake4_makefile.lua gmake')
   return
end

solution "x11_egl_demo"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "x11_egl_demo"
      kind "ConsoleApp"
      language "C"
      location ( "build" )
      targetdir ( "bin" )
      libdirs { "/usr/lib" }
      links { "rt", "pthread", "gstreamer-0.10", "EGL", "X11", "GLESv2" }
      includedirs { "usr/include" }

      buildoptions { }
      linkoptions { }

      files { "src/**.h", "src/**.c" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }     

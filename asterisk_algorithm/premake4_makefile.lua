if not _PREMAKE_VERSION then
   os.execute('premake4 --file=premake4_makefile.lua clean')
   os.execute('premake4 --file=premake4_makefile.lua gmake')
   return
end

solution "asterisk_algorithm"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "asterisk_algorithm"
      kind "ConsoleApp"
      language "C"
      location ( "build" )
      targetdir ( "bin" )
      libdirs { "/usr/lib" }
      links { }
      includedirs { "usr/include", }

      buildoptions { }
      linkoptions { }

      files { "src/**.h", "src/**.c" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }     

if not _PREMAKE_VERSION then
   os.execute('premake4 --file=premake4_makefile.lua clean')
   os.execute('premake4 --file=premake4_makefile.lua gmake')
   return
end


solution "yard_chat_client"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "yard_chat_client"
      kind "ConsoleApp"
      language "C"
      location ( "build" )
      targetdir ( "bin" )
      libdirs { "/usr/lib" }
      links { "rt", "pthread" }
      includedirs { "../../lib/include", "../net_package/include", "usr/include" }
      files { "../../lib/**.c", "src/**.h", "src/**.c" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }     

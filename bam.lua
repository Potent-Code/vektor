-- input paths
sourcePath = "src/"
includePath = sourcePath .. "include/"
implPath = sourcePath .. "impl/"

-- output paths
outputPath = "build/"
objectPath = outputPath .. "obj/"
outputLibPath = outputPath .. "usr/local/lib/"
outputBinPath = outputPath .. "usr/local/bin/"
outputIncludePath = outputPath .. "usr/local/include/"
outputSharePath = outputPath .. "usr/local/share/vektor/"

-- common settings for all Vektor outputs
function NewVektorSettings()
	local vektor_settings = NewSettings()

	-- use clang (TODO: bootstrap this properly with compiler detection)
	vektor_settings.cc.exe_c = "clang"
	vektor_settings.cc.exe_cxx = "clang++"
	vektor_settings.link.exe = "clang"
	vektor_settings.dll.exe = "clang"
	
	-- full warning level, treat warnings as errors
	vektor_settings.cc.flags:Add("-Wall -Wextra -Werror")
	-- use fPIC for making a shared object
	vektor_settings.cc.flags:Add("-fPIC")
	
	-- set optimization level
	if (vektor_settings.debug > 0) then
		vektor_settings.cc.flags:Add("-O0")
	else
		vektor_settings.cc.flags:Add("-O3")
	end
	
	-- set up include path
	vektor_settings.cc.includes:Add(includePath, "/usr/local/include", "/usr/local/include/libxml2")
	
	-- version define (TODO: improve via gitflow/semver)
	vektor_settings.cc.defines:Add("PACKAGE_VERSION=\\\"0.0.1\\\"")
	
	-- output objects to obj directory
	vektor_settings.cc.Output = function(vektor_settings, input)
		return objectPath .. PathFilename(PathBase(input))
	end

	-- add libpath
	vektor_settings.dll.libpath:Add("/usr/local/lib")
	vektor_settings.link.libpath:Add("/usr/local/lib")

	-- linker flags
	return vektor_settings
end

-- extract a static library with `ar -x libX.a`
function ExtractStaticLibrary(pathToLib)
	local objectOutputPath = objectPath .. "external/" .. PathFilename(pathToLib) .. "/"

	print("Unpacking archive " .. pathToLib .. " to " .. objectOutputPath)
	--ExecuteSilent("rm -fR " .. objectOutputPath)
	ExecuteSilent("mkdir -p " .. objectOutputPath)
	ExecuteSilent("cd " .. objectOutputPath .. " && ar -x " .. pathToLib)

	return Collect(objectOutputPath .. "*.o")
end

-- collect sources and compile
settings = NewVektorSettings()
core_objects = Compile(settings, Collect(implPath .. "core/*.c"))
ui_objects = Compile(settings, Collect(implPath .. "ui/*.c"))

-- set up dependencies
settings.dll.libs:Add("SDL", "GL", "xml2", "png", "delta")
settings.link.libs:Add("GL")
libsdl_objects = ExtractStaticLibrary("/usr/local/lib/libSDL.a")
libpng_objects = ExtractStaticLibrary("/usr/local/lib/libpng.a")
libm_objects = ExtractStaticLibrary("/usr/lib/libm.a")
libz_objects = ExtractStaticLibrary("/usr/lib/libz.a")
libdelta_objects = ExtractStaticLibrary("/usr/local/lib/libdelta.a")
libxml2_objects = ExtractStaticLibrary("/usr/local/lib/libxml2.a")
liblzma_objects = ExtractStaticLibrary("/usr/lib/liblzma.a")

-- set up output directories
ExecuteSilent("mkdir -p " .. outputIncludePath)
ExecuteSilent("mkdir -p " .. outputLibPath)
ExecuteSilent("mkdir -p " .. outputBinPath)
ExecuteSilent("mkdir -p " .. outputSharePath)

-- make shared library libvektor.so
libvektor = SharedLibrary(settings, outputLibPath .. "libvektor", core_objects, ui_objects)
-- make static library libvektor.a
libvektor_static = StaticLibrary(settings, outputLibPath .. "vektor", core_objects, ui_objects, libsdl_objects, libxml2_objects, liblzma_objects, libpng_objects, libm_objects, libz_objects, libdelta_objects)

-- make library header
print("Compiling vektor.h...")
Execute(settings.cc.exe_c .. " -E -I" .. includePath .. " " .. includePath .. "core/vektor_in.h " ..
	"| sed '/^\#/d' > " .. includePath .. "core/vektor_out_2.h " ..
	"&& cat " .. includePath .. "core/vektor_out_1.h " .. includePath .. "core/vektor_out_2.h " .. includePath .. "core/vektor_out_3.h " ..
	"| indent -st -ut -sob -bl -bbb -nce > " .. outputIncludePath .. "vektor.h" ..
	"&& rm -f " .. includePath .. "core/vektor_out_2.h")

-- make tools
settings = NewVektorSettings()
vektor_maketexture = Link(settings, outputBinPath .. "vektor_maketexture", Compile(settings, implPath .. "tools/maketexture.c"), libvektor_static)
vektor_makemodel = Link(settings, outputBinPath .. "vektor_makemodel", Compile(settings, implPath .. "tools/makemodel.c"), libvektor_static)

-- make assets
ExecuteSilent("rm -fR " .. outputSharePath .. "*")
ExecuteSilent("mkdir -p " .. outputSharePath .. "fonts")
ExecuteSilent("mkdir -p " .. outputSharePath .. "ui")
Execute("cp -af src/glsl " .. outputSharePath)
Execute(outputBinPath .. "vektor_maketexture share/png/logo.png " .. outputSharePath .. "logo.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/fonts/default.png " .. outputSharePath .. "fonts/default.font")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/chat_button.png " .. outputSharePath .. "ui/chat_button.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/console_button.png " .. outputSharePath .. "ui/console_button.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/log_button.png " .. outputSharePath .. "ui/log_button.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/scroll_bar.png " .. outputSharePath .. "ui/scroll_bar.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/ui_content.png " .. outputSharePath .. "ui/ui_content.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/ui_input_bar.png " .. outputSharePath .. "ui/ui_input_bar.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/ui_menu_bg.png " .. outputSharePath .. "ui/ui_menu_bg.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/ui_scrollbar.png " .. outputSharePath .. "ui/ui_scrollbar.texture")
Execute(outputBinPath .. "vektor_maketexture share/png/ui/ui_window.png " .. outputSharePath .. "ui/ui_window.texture")

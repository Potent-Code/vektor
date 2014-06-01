-- important paths
sourcePath = "src/"
implPath = sourcePath .. "impl/"
objectPath = "obj/"

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
	
	-- set up include path
	vektor_settings.cc.includes:Add(sourcePath .. "include", "/usr/local/include", "/usr/local/include/libxml2")
	
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

-- collect sources and compile
settings = NewVektorSettings()
core_objects = Compile(settings, Collect(implPath .. "core/*.c"))
ui_objects = Compile(settings, Collect(implPath .. "ui/*.c"))

settings.dll.libs:Add("SDL", "GL", "xml2", "png", "delta")
settings.link.libs:Add("SDL", "GL", "xml2", "png", "delta")

-- make shared library libvektor.so
libvektor = SharedLibrary(settings, "libvektor", core_objects, ui_objects)
-- make static library libvektor.a
libvektor_static = StaticLibrary(settings, "vektor", core_objects, ui_objects)


-- make tools
settings = NewVektorSettings()
settings.link.libpath:Add(".")
settings.link.libs:Add("vektor")
vektor_maketexture = Link(settings, "vektor_maketexture", Compile(settings, implPath .. "tools/maketexture.c"))
vektor_makemodel = Link(settings, "vektor_makemodel", Compile(settings, implPath .. "tools/makemodel.c"))

-- important paths
sourcePath = "src/"
implPath = sourcePath .. "impl/"
objectPath = "obj/"

-- set up compiler settings
settings = NewSettings()

-- use clang (TODO: bootstrap this properly with compiler detection)
settings.cc.exe_c = "clang"
settings.cc.exe_cxx = "clang++"
settings.link.exe = "clang"
settings.dll.exe = "clang"

-- full warning level, treat warnings as errors
settings.cc.flags:Add("-Wall -Wextra -Werror")
-- use fPIC for making a shared object
settings.cc.flags:Add("-fPIC")

-- set up include path
settings.cc.includes:Add(sourcePath .. "include", "/usr/local/include", "/usr/local/include/libxml2")

-- version define (TODO: improve via gitflow/semver)
settings.cc.defines:Add("PACKAGE_VERSION=\\\"0.0.1\\\"")

-- output objects to obj directory
settings.cc.Output = function(settings, input)
	return objectPath .. PathFilename(PathBase(input))
end

-- collect sources and compile
core_objects = Compile(settings, Collect(implPath .. "core/*.c"))
ui_objects = Compile(settings, Collect(implPath .. "ui/*.c"))

-- make shared objects
libvektor = SharedLibrary(settings, "libvektor", core_objects, ui_objects)

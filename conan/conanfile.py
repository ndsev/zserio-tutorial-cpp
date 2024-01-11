from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain

class ZserioTutorialCppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("zserio/2.13.0")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.15]")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False # disable CMakeUserPresets.json generation
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

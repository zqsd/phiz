FIND_PATH(GLM_INCLUDE_DIR glm/glm.hpp
    $ENV{GLM_DIR}/include
    $ENV{GLM_DIR}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/csw/include
    /opt/include
    /usr/freeware/include
)

INCLUDE("FindPackageHandleStandardArgs")
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM REQUIRED_VARS GLM_INCLUDE_DIR)

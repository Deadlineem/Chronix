include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        2b003bb063d66f016cc1aef7d63951350ce60f35
    GIT_PROGRESS TRUE
)
message("MinHook")
FetchContent_MakeAvailable(minhook)
set_property(TARGET minhook PROPERTY CXX_STANDARD 23)
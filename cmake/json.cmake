include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
option(JSON_MultipleHeaders "Disable nlohmann JSON multi header default." OFF)
FetchContent_MakeAvailable(json)
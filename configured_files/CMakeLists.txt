

set(SOUNDCLOUD_CLIENT_ID )
set(SOUNDCLOUD_CLIENT_SECRET )

set(VK_MOBILE_CLIENT_ID 2274003)
set(VK_MOBILE_CLIENT_SECRET hHbZxrka2uZ6jB1inYsH)

set(YOUTUBE_API_KEY "AIzaSyDGAm9bAPQGDZOBCiBdombfVrG-_1_dd_Y")

# A very simple example of a configured file that might need to be
# converted to one that is publicly installed in the case that
# you are developing a library
configure_file("config.hpp.in" "${CMAKE_BINARY_DIR}/configured_files/include/internal_use_only/config.hpp" ESCAPE_QUOTES)



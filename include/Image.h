#include <curl/curl.h>
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>

class Image
{
    GLuint avatarTexture = 0;
public:
    struct LoadedImage {
        unsigned char* data = nullptr;
        int width = 0;
        int height = 0;
        int channels = 0;
    };

    static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp);

    std::string downloadImage(const std::string& url);
    LoadedImage decodeImage(const std::string& buffer);
    GLuint createTexture(const LoadedImage& img);
    void loadAvatar(const std::string& url);
    GLuint getTexture() const { return avatarTexture; }
       

};
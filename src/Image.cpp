#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <curl/curl.h>
#include <iostream>
#include <GLFW/glfw3.h>


size_t Image::WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Image::downloadImage(const std::string& url)
{
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Image::WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "Curl failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}




Image::LoadedImage Image::decodeImage(const std::string& buffer)
{
    LoadedImage img;
    img.data = stbi_load_from_memory(
        (const unsigned char*)buffer.data(),
        buffer.size(),
        &img.width,
        &img.height,
        &img.channels,
        4
    );
    return img;
}

GLuint Image::createTexture(const LoadedImage& img) {
    if (!img.data) return 0;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        img.width, img.height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

    glBindTexture(GL_TEXTURE_2D, 0);
    return tex;
}

void Image::loadAvatar(const std::string& url)
{
    std::string imgData = downloadImage(url);
    LoadedImage img = decodeImage(imgData);
    avatarTexture = createTexture(img);
    stbi_image_free(img.data);
}

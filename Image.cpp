//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"




bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users
    try {
        if (ifs.fail()) {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
    }

    return true;
}
bool Image::loadRaw(string filename)
{
    return false;
}
bool Image::savePPM(string filename)
{
    if (this->w == 0 || this->h == 0) { fprintf(stderr, "Can't save an empty image\n"); }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << this->w << " " << this->h << "\n255\n";
        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; ++i) {
            r = static_cast<unsigned char>((this->pixels[i].r));
            g = static_cast<unsigned char>((this->pixels[i].g));
            b = static_cast<unsigned char>((this->pixels[i].b));
            ofs << r << g << b;
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return true;
}


void Image::filterRed()
{

    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{

    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{

    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}
void Image::greyScale()
{
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = pixels[i].r * 0.299 + pixels[i].g * 0.587 + pixels[i].b * 0.114;
        this->pixels[i].g = pixels[i].r * 0.299 + pixels[i].g * 0.587 + pixels[i].b * 0.114;
        this->pixels[i].b = pixels[i].r * 0.299 + pixels[i].g * 0.587 + pixels[i].b * 0.114;
    }
}
void Image::flipHorizontal()
{
    int pixels[3];
    unsigned int temp;
    unsigned int temp1;
    for(int j= 0; j < h; ++j)
    {
        for(int i =0; i <w/2; ++i)
        {
            temp = i + j * w;
            temp1 = (w - 1 - i) + j * w;

            pixels[0] = this->pixels[temp].r;
            pixels[1] = this->pixels[temp].g;
            pixels[2] = this->pixels[temp].b;

            this->pixels[temp] = this->pixels[temp1];

            this->pixels[temp1].r = pixels[0];
            this->pixels[temp1].g = pixels[1];
            this->pixels[temp1].b = pixels[2];
        }
    }
}
void Image::flipVertically()
{

    int pixels[3];
    unsigned int temp,temp1;

    for(int i= 0; i < w; ++i)
    {
        for(int j =0; j <h/2; ++j)
        {
            temp = i + j * w;
            temp1 = i + (h - 1 - j) * w;

            pixels[0] = this->pixels[temp].r;
            pixels[1] = this->pixels[temp].g;
            pixels[2] = this->pixels[temp].b;

            this->pixels[temp] = this->pixels[temp1];

            this->pixels[temp1].r = pixels[0];
            this->pixels[temp1].g = pixels[1];
            this->pixels[temp1].b = pixels[2];
        }
    }

}
void Image::AdditionalFunction2()
{
        //invert colors
        for (int i = 0; i < w * h; ++i) {
            pixels[i].r = 255 - pixels[i].r;
            pixels[i].g = 255 - pixels[i].g;
            pixels[i].b = 255 - pixels[i].b;
        }
}
void Image::AdditionalFunction3()
{
    int pixels[3];
    unsigned int x;
    for(int i = 0; i < (h*w / 2); ++i)
    {
        x = h*w - i;
        pixels[0] = this->pixels[i].r;
        pixels[1] = this->pixels[i].g;
        pixels[2] = this->pixels[i].b;
        this->pixels[i] = this->pixels[x];
        this->pixels[x].r = pixels[0];
        this->pixels[x].g = pixels[1];
        this->pixels[x].b = pixels[2];
    }
}
void Image::AdditionalFunction1()
{

        //half blue half red
        for(int j = 0; j < w * (h/2); ++j) {
            this->pixels[j].r = 0;
            this->pixels[j].g = 0;
        }

        for(int j = w * (h/2); j < w *h; ++j){
            this->pixels[j].g = 0;
            this->pixels[j].b = 0;
        }




}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}
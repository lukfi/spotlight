#include "export/systeminfo.h"
#include <stdio.h>
#include <string>
#include <cstdarg> // va_list, va_start(), va_end()
#include <sstream>

void sformata(std::string& s, const std::string fmt, ...)
{
    std::string ss;
    int n;
    int size = 100;
    bool b = false;
    va_list marker;

    while (!b)
    {
        ss.resize(size);
        va_start(marker, fmt);
        n = vsnprintf((char*)ss.c_str(), size, fmt.c_str(), marker);
        va_end(marker);
        if ((n > 0) && ((b = (n < size)) == true)) {
            ss.resize(n);
        }
        else {
            size *= 2;
        }
    }
    s += ss;
}

std::string indexPartTemplate = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, height=device-height, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no, viewport-fit=cover, shrink-to-fit=no">
    <meta name="robots" content="index, follow">
    <title>Finster.pro Gallery</title>
    <script src="dist/spotlight.bundle.js"></script>
    <!--<script src="dist/js/spotlight.min.js"></script>-->
    <!--<link rel="stylesheet" href="dist/css/spotlight.min.css">-->
    <!-- Custom Control: -->
    <style>
        /*
         * Custom Control:
         * ---------------
         */
        /* custom classes are always prefixed by "spl-" automatically */
        .spl-like{
            background-image: url(demo/gallery/heart-outline.svg);
            background-size: 23px;
        }
        /* optionally, additional state to toggle the button: */
        .spl-like.on{
            background-image: url(demo/gallery/heart.svg);
        }
        /*
         * Custom Animation:
         * -----------------
         */
        /* custom scene transition (slide effect) */
        .only-this-gallery.show .spl-scene{
            transition: transform 0.2s ease;
        }
        /* custom animation "visible state" (css context by custom classname "only-this-gallery" to apply these animation just on a specific gallery) */
        .only-this-gallery.show .spl-pane > *{
            clip-path: circle(100%% at center);
            transition: transform 0.35s ease,
                        opacity 0.65s ease,
                        clip-path 0.8s ease;
        }
        /* custom animation "hidden state" ("custom" is the name of the animation you pass as gallery option) */
        .only-this-gallery .spl-pane .custom {
            clip-path: circle(0px at center) ;
            transition: transform 0.65s ease,
                        opacity 0.65s ease;
        }
        /* animation state when gallery is hidden */
        #spotlight.only-this-gallery{
            clip-path: circle(0px at center);
        }
        /* animation state when gallery will open */
        #spotlight.only-this-gallery.show{
            clip-path: circle(100%% at center);
            transition: clip-path 0.65s ease 0.15s;
        }
    </style>

    <link rel="stylesheet" href="demo/style.css">
    <meta name="format-detection" content="telephone=no">
    <meta name="description" content="Web's most easy to integrate lightbox gallery library. Super-lightweight, outstanding performance, no dependencies.">
    <meta name="keywords" content="gallery, lightbox, photo-gallery, javascript-library, image-viewer, lightbox-gallery-plugin, gallery-plugin, gallery-extension, gallery-widget, lightbox-gallery, gallery-template, gallery-viewer, gallery-simple, lightbox-plugin">
    <meta name="thumbnail" content="favicon.ico">
    <meta property="og:url" content="https://nextapps-de.github.io/spotlight/">
    <meta property="og:site_name" content="Spotlight.js - Modern HTML5 Image Gallery">
    <meta property="og:image" content="https://nextapps-de.github.io/spotlight/demo/og-image.png">
    <meta property="og:title" content="Spotlight.js - Modern HTML5 Image Gallery">
    <meta property="og:description" content="WinBox is the web's most easy to integrate lightbox gallery library. Super-lightweight, outstanding performance, no dependencies.">
    <meta property="og:type" content="Software">
    <meta property="og:url" content="https://nextapps-de.github.io/spotlight/">
    <link rel="icon" sizes="16x16 32x32 48x48 64x64" type="image/png" href="favicon.ico">
    <link rel="icon" sizes="512x512 1024x1024" type="image/png" href="https://nextapps-de.github.io/spotlight/demo/og-image.png">
</head>
<body>

<script>
Spotlight.theme("dark");
</script>

%s

</body>
</html>
)";

std::string imagePartTemplate = R"(
    <a class="spotlight" href="%s" data-control="page,fullscreen,theme,prev,next,close">
        <img src="%s">
    </a>

)";

extern "C"
{

DLL_EXPORT char* GenerateIndex(const char* images[], int count)
{
    std::string imagePart;
    for (int i = 0; i < count; ++i)
    {
        sformata(imagePart, imagePartTemplate, images[i], images[i]);
    }

    std::string indexString;
    sformata(indexString, indexPartTemplate, imagePart.c_str());

    int len = indexString.size() + 1;
    char* ret = new char[indexString.size() + 1];
    if (ret)
    {
        memcpy_s(ret, len, indexString.data(), indexString.size());
        ret[indexString.size()] = 0;
    }

    return ret;
}

}
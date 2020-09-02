//
// fonts-lister.cpp
//
// Reference: https://www.lemoda.net/pango/list-fonts/index.html
//
// Build on Linux:
//   g++ -g -Wall -o fonts-lister `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../fonts-lister.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4` && ./fonts-lister
//
// Build on Linux:
//   g++ -g -Wall -std=c++17 -o fonts-lister `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../fonts-lister.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4` && ./fonts-lister
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <glibmm.h>
#include <cairomm/cairomm.h>

#include <pangomm.h>
#include <pangomm/fontdescription.h>
#include <pangomm/fontface.h>
#include <pangomm/init.h>
#include <pangomm/item.h>
#include <pangomm/glyphstring.h>

void list_fonts()
{
    Pango::init();
    Cairo::RefPtr<Cairo::PdfSurface> surface = Cairo::PdfSurface::create("fonts", 0, 0);
    Cairo::RefPtr<Cairo::Context> cairoContext = Cairo::Context::create(surface);
    auto layout = Pango::Layout::create(cairoContext);
    auto pangoContext = layout->get_context();

    std::vector<Glib::RefPtr<Pango::FontFamily> > fontFamilies = pangoContext->list_families();
    std::sort(fontFamilies.begin(), fontFamilies.end(), [](const Glib::RefPtr<Pango::FontFamily>& fontFamily1, const Glib::RefPtr<Pango::FontFamily>& fontFamily2) {
        return fontFamily1->get_name() < fontFamily2->get_name();
    });
    std::cout << "There are " << fontFamilies.size() << " families\n";
    for (size_t i = 0; i < fontFamilies.size(); i++)
    {
        const auto fontFamily = fontFamilies[i];
        std::cout <<"Family " << i << ": " << fontFamily->get_name() << std::endl;

        std::vector<Glib::RefPtr<Pango::FontFace> > fontFaces = fontFamily->list_faces();
        for (size_t j = 0; j < fontFaces.size(); j++)
        {
            const auto fontFace = fontFaces[j];
            std::cout << fontFamily->get_name() << " " << fontFace->get_name() << std::endl;
        }

        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    list_fonts ();
    return 0;
}

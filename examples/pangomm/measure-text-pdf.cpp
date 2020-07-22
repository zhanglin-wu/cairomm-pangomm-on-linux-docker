
// measure-text-pdf.cpp
//
// To build on Linux:
//   cd /path/to/folder-of-this-file
//   mkdir build
//   cd build
//
//   g++ -g -Wall -o measure-text-pdf `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../measure-text-pdf.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4` && ./measure-text-pdf "../measure-text-pdf-test-data.txt" "Noto Sans Mono CJK TC"
//
// To build on Mac:
//   g++ -g -Wall -std=c++17 -o measure-text-pdf `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../measure-text-pdf.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4`

#include <sstream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <tuple>

#include <glibmm.h>
#include <string>
#include <pangomm.h>
#include <pangomm/fontdescription.h>
#include <pangomm/item.h>
#include <pangomm/glyphstring.h>

#include <cairomm/cairomm.h>
#include <pangomm.h>
#include <pangomm/init.h>

static const double fontSize = 10000;

std::tuple<int, int> GetTextSize(std::string utf8Text, std::string fontName);
std::string ReadTextFromFile(std::string filePath);
std::vector<std::string> ReadLinesFromFile(std::string filePath);
void DrawShapes(const Cairo::RefPtr<Cairo::Context>& context, const Cairo::RefPtr<Cairo::Surface>& surface);

int main(int argc, char** argv)
{
    std::cout << "argc: " << argc << std::endl;
    for (int argIndex = 0; argIndex < argc; argIndex++)
    {
        std::cout << "argv[" << argIndex << "]: " << argv[argIndex] << std::endl;
    }

    Pango::init();

    std::string filename = "measure-text.pdf";
    int width = 600;
    int height = 800;

    Cairo::RefPtr<Cairo::PdfSurface> surface = Cairo::PdfSurface::create(filename, width, height);
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(surface);

    context->move_to(0.0, 0.0);
    auto layout = Pango::Layout::create(context);

    std::string fontName = "DejaVu Sans";
    if (argc > 2)
    {
        fontName = argv[2];
    }

    auto font = Glib::ustring(fontName);
    Pango::FontDescription desc(font);
    desc.set_size(fontSize);
    std::cout << std::endl << desc.get_family() << std::endl;
    layout->set_font_description(desc);

    if (argc > 1)
    {
        std::string filePath = argv[1];
        std::string utf8Text = ReadTextFromFile(filePath);
        std::cout << "Test data: \"" << utf8Text << "\"" << std::endl;

        auto text = Glib::ustring(utf8Text);
        layout->set_text(text);
        layout->update_from_cairo_context(context);
        layout->show_in_cairo_context(context);

        std::stringstream sizeInfo;
        sizeInfo << "The width and height of each line in pixel:" << std::endl;
        auto lines = ReadLinesFromFile(filePath);
        for (const std::string& line : lines)
        {
            int text_width = 0;
            int text_height = 0;
            std::tie(text_width, text_height) = GetTextSize(line, fontName);

            sizeInfo << "(" << text_width << ", " << text_height << "), ";
        }

        context->move_to(0, 140);
        layout->set_text(sizeInfo.str());
        layout->update_from_cairo_context(context);
        layout->show_in_cairo_context(context);

        std::cout << sizeInfo.str() << std::endl;
    }

    DrawShapes(context, surface);

    // context->restore();
    context->show_page();
    std::cout << "Wrote PDF file \"" << filename << "\"" << std::endl;

    return 0;
}

std::tuple<int, int> GetTextSize(std::string utf8Text, std::string fontName)
{
    int width = 600;
    int height = 800;

    Pango::init();

    Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(surface);

    context->move_to(0.0, 0.0);
    auto layout = Pango::Layout::create(context);

    auto font = Glib::ustring(fontName);
    Pango::FontDescription desc(font);
    desc.set_size(fontSize);
    layout->set_font_description(desc);

    auto text = Glib::ustring(utf8Text);
    layout->set_text(text);

    // Measure the text
    int text_width;
    int text_height;
    layout->get_pixel_size(text_width, text_height);

    return std::make_tuple(text_width, text_height);
}

void DrawShapes(const Cairo::RefPtr<Cairo::Context>& context, const Cairo::RefPtr<Cairo::Surface>& surface)
{
    int width = 600;
    int height = 800;

    // draw a border around the image
    context->set_source_rgba(0.0, 0.8, 0.0, 0.7);
    context->set_line_width(2.0);
    context->rectangle(20.0, 180.0, width - 40, height - 260.0);
    context->stroke();

    // draw a circle in the center of the image
    context->arc(width / 2.0, height / 2.0, height / 4.0, 0.0, 2.0 * M_PI);
    context->stroke();

    // draw a diagonal line
    context->move_to(width / 4.0, height / 4.0);
    context->line_to(width * 3.0 / 4.0, height * 3.0 / 4.0);
    context->stroke();

    // draw a curve
    context->set_source_rgba(1.0, 0.8, 0.0, 0.7);
    context->set_line_width(4.0);
    context->move_to(width / 2.0 - 4, height / 2.0);
    context->curve_to(50, 120, 75, 340, 200, 400);
    context->rel_curve_to(50, -60, 75, 85, 100, -50);
    context->stroke();

    context->save();
    const double scale = width / 10.0;
    context->set_source_rgba(0.0, 0.8, 0.7, 0.7);
    context->translate(width / 2.0, height / 2.0);
    context->scale(scale, scale * 2);
    context->set_line_width(1.0 / scale);
    context->arc(0, 0, 1.0, 0.0, 2.0 * M_PI);
    context->stroke();
    context->restore();
}

std::string ReadTextFromFile(std::string filePath)
{
    std::fstream filestream(filePath);

    std::vector<char> buffer;
    std::copy(std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>(), std::back_inserter(buffer));

    buffer.push_back(0);
    return std::string(buffer.begin(), buffer.end());
}

std::vector<std::string> ReadLinesFromFile(std::string filePath)
{
    std::fstream filestream(filePath);

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(filestream, line))
    {
        lines.push_back(line);
    }

    return lines;
}
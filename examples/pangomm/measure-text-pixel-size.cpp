
// apt-get install libpangomm-1.4-dev -y
// g++ -g -Wall -o measure-text-pixel-size `pkg-config --cflags cairomm-1.0 pangomm-1.4` measure-text-pixel-size.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4`


#include <sstream>
#include <iostream>

#include <glibmm.h>
#include <string>
#include <pangomm.h>
#include <pangomm/fontdescription.h>
#include <pangomm/item.h>
#include <pangomm/glyphstring.h>

#include <cairomm/cairomm.h>
#include <pangomm.h>
#include <pangomm/init.h>

int main() {
  Pango::init();

  auto surf = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, 600, 800);
  auto cr = Cairo::Context::create(surf);
  cr->set_source_rgb(0.5, 0.7, 0.5);
  cr->paint();
  cr->move_to(0.0, 0.0);
  cr->set_source_rgb(1.0, 1.0, 1.0);
  auto layout = Pango::Layout::create(cr);

  // auto font = Glib::ustring("OpenSansEmoji");
  // Pango::FontDescription desc(font);
  // std::cout << std::endl << desc.get_family() << std::endl;
  // layout->set_font_description(desc);

  // Glib::ustring text = Glib::locale_to_utf8("好人");
  // auto text = Glib::ustring("Hello World!\n\xE4\xB8\xAD\xE5\x9B\xBD\xE2\x9A\xA1\xF0\x9F\x99\x82");
  // auto text = Glib::ustring("Hello World!");
  auto text = Glib::ustring("\xE4\xB8\xAD\xE5\x9B\xBD\xE2\x9A\xA1\xF0\x9F\x99\x82");
  // auto text = Glib::ustring("\xE4\xB8\xAD\xE5\x9B\xBD\xE2\x9A\xA1\xF0\x9F\x99\x82\n\n\xE2\x9A\xA1\xF0\x9F\x99\x82\xE2\x9A\xA1\xF0\x9F\x99\x82");
  // auto text = Glib::ustring("\xE4\xB8\xAD");
  // text = Glib::ustring("\xE5\x9B\xBD");
  // text = Glib::ustring("\xE2\x9A\xA1");
  // text = Glib::ustring("\xF0\x9F\x99\x82");
  
  layout->set_text(text);
  layout->update_from_cairo_context(cr);
  layout->show_in_cairo_context(cr);
  
  // Measure the text
  int text_width;
  int text_height;
  layout->get_pixel_size(text_width, text_height);
	
  std::stringstream ss;
  ss << "\n(" << text_width << ", " << text_height << ")\n";
  cr->move_to(10, 50);
  layout->set_text(ss.str());
  layout->update_from_cairo_context(cr);
  layout->show_in_cairo_context(cr);

  surf->write_to_png("measure-text-pixel-size.png");

  return 0;
}

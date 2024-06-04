#include <string>
#include "SFML_output.h"
#include "Drawing.h"

static const unsigned int WINDOW_WIDTH(1000);
static const unsigned int WINDOW_HEIGHT(700);

SFML_output::SFML_output()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Outil visualisation")
{
    // To use less CPU, we limit framerate to 30 fps
    // We could have preferred to use window.setVerticalSyncEnabled(true) as mentionned in
    // https://www.sfml-dev.org/tutorials/2.5/window-window-fr.php#contrcler-le-framerate
    // But, on Linux used by Michel Simatic, there is the error message "Setting vertical sync not supported"
    // displayed by SFML: This message signifies that window.setVerticalSyncEnabled(true) instruction
    // cannot be considered on this Linux.
    window.setFramerateLimit(30);

}

void SFML_output::draw_circle(double absolute_x, double absolute_y, double r, std::string const& color)
{
	sf::CircleShape shape(static_cast<float>(r));
	shape.setFillColor(string2color(color));
    // In the following setPosition(), we use window.getSize().x instead of WINDOW_WIDTH
    // and window.getSize().y instead of WINDOW_HEIGHT, so that if window is resized by
    // user, drawing remains the same.
    // Actually, it does not work properly as SFML seems to keep an internal scale linked
    // to initial size of the window (e.g.     // a circle becomes an ellipse when you
    // resize horizontally the window).
	shape.setPosition(static_cast<float>(absolute_x + window.getSize().x / 2. - r), static_cast<float>(window.getSize().y / 2. - (absolute_y + r)));
	window.draw(shape);
}

void SFML_output::display(Drawing const& d)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
            if (event.type == sf::Event::Resized)
            {
                // Update the view to the new size of the window, so that contents is not distorted by resizing
                // See https://www.sfml-dev.org/tutorials/2.6/graphics-view.php#showing-more-when-the-window-is-resized
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        window.clear(sf::Color::White);
        d.draw(this);
        window.display();
	}
}

sf::Color SFML_output::string2color(std::string const &s)
{
    std::map<std::string_view, sf::Color, std::less<>> msc = {
            {"Black",  sf::Color::Black},
            {"White",  sf::Color::White},
            {"Red",    sf::Color::Red},
            {"Green",  sf::Color::Green},
            {"Blue",   sf::Color::Blue},
            {"Yellow", sf::Color::Yellow},
            {"Magenta",sf::Color::Magenta},
            {"Cyan",   sf::Color::Cyan}
    };

	return msc[s]; // Notice that we return the equivalent of sf::Color:Black if s was not found in msc
}

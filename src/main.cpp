#include <System.hpp>
#include <System/CallTimer.hpp>

#include <User.hpp>
#include <Renderer.hpp>


int main(int argc, char* argv[]) {
  System::init();
  sf::RenderWindow* window = Renderer::window;

  while(window->isOpen()) {
    while(std::optional<Event> eventOpt = window->pollEvent()) {
      if(!window->hasFocus()) continue;

      const auto& event = *eventOpt;

      User::handle(event);

           if(event.is<Event::Closed>()) window->close();
      else if(const auto* resized = event.getIf<Event::Resized>())
        window->setView(sf::View(sf::FloatRect(Vec2(), Vec2(resized->size))));
    }

    if(!window->hasFocus()) continue;
    
    System::update();
    
    CallTimer timer;
    Renderer::draw();
    System::drawTime = timer.end();
  }

  delete window;
  return System::end();
}
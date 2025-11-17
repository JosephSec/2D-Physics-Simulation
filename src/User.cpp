#include <User.hpp>

#include <System.hpp>
#include <Renderer.hpp>

#include <Simulation.hpp>

#include <UI.hpp>
#include <UI/UIController.hpp>
#include <UI/UITextEditor.hpp>



ForceState User::cursorForce = ForceState::Off;
float User::cursorMass = 1;

Vec2 User::mousePos;
Vec2 User::mouseDelta;
Vec2 User::WorldMousePos;

bool User::focused  = true;
bool User::controlPressed = false;


static bool fullscreen = false;
static Vec2 lastWindowSize = Vec2zero;
void User::handle(const Event& event) {
       if(event.is<Event::FocusLost>())   focused = false;
  else if(event.is<Event::FocusGained>()) focused = true;

  if(!focused || UI::Manager::handle(event)) return;

  else if(const auto* key = event.getIf<Event::KeyPressed>()) {
    if(UI::TextEditor::selected) return;

         if(key->code == Keyboard::Key::Escape) Renderer::window->close();
    else if(key->code == Keyboard::Key::F11 && focused) {
      if(fullscreen) {
        Renderer::window->create(sf::VideoMode(lastWindowSize), Renderer::windowName, sf::Style::Default);
      } else {
        lastWindowSize = Renderer::window->getSize();
        Renderer::window->create(sf::VideoMode::getDesktopMode(), Renderer::windowName, sf::Style::None);
      }
      Renderer::window->setFramerateLimit(180);
      fullscreen = !fullscreen;
    }

    else if(key->code == Keyboard::Key::R && !(controlPressed && UI::UIController::uiWindow.IsActive))
      Simulation::reset();
    else if(key->code == Keyboard::Key::C) Simulation::clear(true, controlPressed);
    else if(key->code == Keyboard::Key::U)
      Simulation::SpawnBurst(User::WorldMousePos, .1f * cursorMass*(System::ScaleByWorld? Renderer::WorldToScreenScale : 1));

    else if(key->code == Keyboard::Key::P && Simulation::blackHoleActive) Simulation::blackHolePos = WorldMousePos;

    else if(key->code == Keyboard::Key::Space) System::Paused = !System::Paused;
    else if(key->code == Keyboard::Key::Backspace && cursorForce == Off) Simulation::DeleteBody();
    else if(key->code == Keyboard::Key::Enter     && cursorForce == Off) Simulation::CreateBody(WorldMousePos, cursorMass);


    else if(key->code == Keyboard::Key::Subtract) Simulation::DeleteSimulated();
    else if(key->code == Keyboard::Key::Equal)    Simulation::CreateSimulated();
  }

  else if(const auto* mouseWheelScroll = event.getIf<Event::MouseWheelScrolled>()) {
    const float dif = mouseWheelScroll->delta*Renderer::WorldZoom*.1f;
    if(Renderer::WorldZoom + dif < .01f) {
      Renderer::WorldZoom = .01f;
      return;
    }
    Renderer::WorldZoom += dif;
  }

  else if(const auto* mouseButton = event.getIf<Event::MouseButtonPressed>()) {
         if(mouseButton->button == Mouse::Button::Left)  cursorForce = ForceState::Positive;
    else if(mouseButton->button == Mouse::Button::Right) cursorForce = ForceState::Negative;
  }

  else if(const auto* mouseButton = event.getIf<Event::MouseButtonReleased>()) {
    if(cursorForce == Off) return;
    cursorForce = ForceState::Off;
    Simulation::update(true);
  }
}


void User::update() {
  if(!focused || UI::TextEditor::selected) return;

  controlPressed = Keyboard::isKeyPressed(Keyboard::Key::LControl) | Keyboard::isKeyPressed(Keyboard::Key::RControl);

  mouseDelta = Mouse::getPosition(*Renderer::window) - mousePos;
  mousePos += mouseDelta;
  WorldMousePos = Renderer::ScreenToWorld(mousePos);

  Vec2 cameraMoveDir;
  if(Keyboard::isKeyPressed(Keyboard::Key::W) || !controlPressed && Keyboard::isKeyPressed(Keyboard::Key::Up))    cameraMoveDir += Vec2(0,1);
  if(Keyboard::isKeyPressed(Keyboard::Key::S) || !controlPressed && Keyboard::isKeyPressed(Keyboard::Key::Down))  cameraMoveDir -= Vec2(0,1);
  if(Keyboard::isKeyPressed(Keyboard::Key::D) || !controlPressed && Keyboard::isKeyPressed(Keyboard::Key::Right)) cameraMoveDir += Vec2(1,0);
  if(Keyboard::isKeyPressed(Keyboard::Key::A) || !controlPressed && Keyboard::isKeyPressed(Keyboard::Key::Left))  cameraMoveDir -= Vec2(1,0);
  Renderer::cameraPosition += cameraMoveDir / Renderer::WorldZoom/10;
}
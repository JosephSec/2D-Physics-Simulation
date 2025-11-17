#include <Renderer.hpp>

#include <System.hpp>
#include <System/ThreadPool.hpp>

#include <User.hpp>
#include <UI.hpp>
#include <Simulation.hpp>


sf::RenderWindow* Renderer::window;
const string Renderer::windowName = "Physics Simulation";
Vec2 Renderer::windowSize;

float Renderer::WorldToScreenScale = WORLDSCALE;
float Renderer::WorldZoom = 1;

Vec2 Renderer::windowCenter;
Vec2 Renderer::cameraPosition;

sf::VertexArray Renderer::starShape(sf::PrimitiveType::Points);
Color Renderer::StarColor(0, 0, 230);

Color Renderer::SlowColor(0, 255, 0);
Color Renderer::FastColor(255, 0, 0);
float Renderer::VelocitySensitivity = 1;

Color Renderer::SpaceGridColor(120, 120, 0);


void drawCircle(const Vec2& pos, float mass, const Color& color) {
  const float radius = mass*Renderer::WorldToScreenScale/2.0f;
  sf::CircleShape circle(radius, 3+21*(radius/25));
  circle.setOrigin(Vec2one * radius);
  circle.setPosition(pos);
  circle.setFillColor(color);
  Renderer::window->draw(circle);
}

int starCount;
void Renderer::init() {
  sf::Image icon;
  if(!icon.loadFromFile(System::PATH+"/assets/Icon.png"))
    Debug::error("Icon.png is missing or can't be loaded");

  window = new sf::RenderWindow(sf::VideoMode(Vec2(800, 800)), windowName);
  window->setIcon(icon.getSize(), icon.getPixelsPtr());
  window->setFramerateLimit(180);
  window->requestFocus();

  windowSize = Vec2(window->getSize());
  windowCenter = windowSize/2.0f;

  starShape.resize(Simulation::bodyCount);
  ThreadPool::DoJobs([&](unsigned int i)
    {starShape[i].color = StarColor; }, Simulation::bodyCount);
  starCount = Simulation::bodyCount;
}

void Renderer::update() {
  windowSize = Vec2(window->getSize());
  windowCenter = windowSize/2.0f;

  if(starCount == Simulation::bodyCount) return;
  
  starShape.resize(Simulation::bodyCount);
  for(unsigned int i = starCount; i < Simulation::bodyCount; i++)
    starShape[i].color = StarColor;
  starCount = Simulation::bodyCount;
}
void Renderer::draw() {
  window->clear(Color(0,2,7));

  if(WorldZoom <= 0) WorldZoom = 1;
  WorldToScreenScale = WorldZoom*WORLDSCALE;

  const Color colorDif(
    FastColor.r-SlowColor.r,
    FastColor.g-SlowColor.g,
    FastColor.b-SlowColor.b);
  
  const Vec2* position = Simulation::posAddr;
  const Vec2* velocity = Simulation::velAddr;

  const unsigned int pointC = Simulation::bodyCount;
  for(int i = 0; i < pointC; i++) {
    starShape[i].position = WorldToScreen(position[i]);

    if(System::VisualizeVelocity) {
      const float max = 255.0f/VelocitySensitivity;
      const float t = std::min(velocity[i].magnitude()*50, max)/max;
      starShape[i].color = Color(
        SlowColor.r + t * colorDif.r,
        SlowColor.g + t * colorDif.g,
        SlowColor.b + t * colorDif.b);
    } else starShape[i].color = StarColor;
  }
  window->draw(starShape);

  if(Simulation::blackHoleActive || User::focused && Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
    const Vec2 pos = Simulation::blackHoleActive? Simulation::blackHolePos : User::WorldMousePos;
    drawCircle(WorldToScreen(pos), Simulation::blackHoleMass*BLACKHOLE_RADIUS, Color::Black);
  }

  int planetCount = Simulation::bodies.size();
  for(const Body& planet : Simulation::bodies) {
    const Vec2 screen = WorldToScreen(planet.position);
    if(Renderer::InWindow(screen)) drawCircle(screen, planet.mass, Color::Green);
  }

  if(User::cursorForce != ForceState::Off || User::focused && Keyboard::isKeyPressed(Keyboard::Key::LControl))
    drawCircle(Vec2(User::mousePos), User::cursorMass, Color::Red);  

  if(SpaceVisualizer::IsActive) window->draw(SpaceVisualizer::gridShape);

  UI::Manager::draw();
  window->display();
}
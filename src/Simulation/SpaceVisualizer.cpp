#include <Simulation/SpaceVisualizer.hpp>

#include <Simulation.hpp>
#include <Renderer.hpp>
#include <User.hpp>


bool SpaceVisualizer::IsActive;

Vec2 SpaceVisualizer::sampleGrid;
int SpaceVisualizer::resolution = 1;
float SpaceVisualizer::sensitivity = 1;

sf::VertexArray SpaceVisualizer::gridShape(sf::PrimitiveType::Lines);


void SpaceVisualizer::update(bool values) {
  const Vec2 newGrid = Renderer::windowSize/(WORLDSCALE/resolution);
  if(sampleGrid != newGrid) resize(newGrid.x,newGrid.y);  

  if(values) {
    int index = 1;
    for(int x = 0; x < sampleGrid.x; x++) {
      for(int y = 0; y < sampleGrid.y; y++) {
        gridShape[index] = sf::Vertex{Renderer::WorldToScreen(SampleSpace(GetSamplePoint(x,y))), Renderer::SpaceGridColor};
        index += 2;
      }
    }
  }
}

// @brief resizes the %sampleGrid vector to a grid size
// @param x sample grid width
// @param y sample grid height
// @warning updating after is recommended to avoid error values
// @warning the parameter values are double to mirror negatively
void SpaceVisualizer::resize(int xPos, int yPos) {
  xPos += 2; yPos += 2;
  sampleGrid = Vec2(xPos,yPos);
  gridShape.resize(sampleGrid.x*sampleGrid.y*2);

  int index = 0;
  for(int x = 0; x < sampleGrid.x; x++) {
    for(int y = 0; y < sampleGrid.y; y++) {
      gridShape[index] = sf::Vertex{Renderer::WorldToScreen(GetSamplePoint(x,y)), Renderer::SpaceGridColor};
      index += 2;
    }
  }
}


bool SpaceVisualizer::DoUpdate() {
   return IsActive && 
    (User::cursorForce != Off || Simulation::blackHoleActive || Simulation::bodies.size() != 0);
    // || Simulation::bodyCount != 0 && !System::IsolatedSimulation);
}



const Vec2 SpaceVisualizer::GetSamplePoint(int x, int y) {
  return Renderer::cameraPosition + Vec2(x+1-sampleGrid.x/2,y+1-sampleGrid.y/2)/Renderer::WorldZoom/resolution;
}

static inline const float getdist(const Vec2& v) {
  return std::sqrt(v.x*v.x+v.y*v.y);
}
static inline const float getforce(float mass, float dist) {
  return std::max(.1f, std::min(dist, (Simulation::Gravity/(mass*dist))*SpaceVisualizer::sensitivity));
}
const Vec2 SpaceVisualizer::SampleSpace(Vec2 world) {
  Vec2 dir;

  for(const Body& planet : Simulation::bodies) {
    dir = planet.position-world;
    world += dir.normalize()*getforce(planet.mass, dir.magnitude());
  }

  if(User::cursorForce != ForceState::Off || User::controlPressed) {
    dir = User::WorldMousePos-world;
    const int cursorDir = User::cursorForce == ForceState::Off? 1 : User::cursorForce;
    const float scale = System::ScaleByWorld? Renderer::WorldZoom : 1;
    world += dir.normalize()*getforce(User::cursorMass / (scale/2), dir.magnitude())*cursorDir;
  }

  if(Simulation::blackHoleActive) {
    dir = Simulation::blackHolePos-world;
    world += dir.normalize()*getforce(Simulation::blackHoleMass, dir.magnitude());
  }

  return world;
}
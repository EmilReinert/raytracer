//needed for testing
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

//other stuff needed
#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>

//include classes for testing
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "color.hpp"
#include "scene.hpp"
#include "sdfloader.hpp"
#include "light.hpp"
#include "camera.hpp"


// ----------------------------------
// SHAPE TESTS
// ----------------------------------


TEST_CASE("getter shape","[shape]")
{
	Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
	REQUIRE(s.get_name() == "name");

	Material c{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f};
	REQUIRE(s.get_material() == c); //added operator == in color.hpp
}

TEST_CASE("operator<< and print shape","[shape]")
{
	Sphere es {"empty_sphere"};
	std::cout << es;
	
	
	Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
	std::cout << s;

}

// ----------------------------------
// SPHERE TESTS
// ----------------------------------

TEST_CASE("constructors of sphere","[sphere]")
{
	Sphere s1 {"name"};
	Sphere s2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};

	REQUIRE(s1.get_center() == s2.get_center());
	REQUIRE(s1.get_radius() == s2.get_radius());
}

TEST_CASE("get_center and get_radius","[sphere]")
{
	Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};

	REQUIRE(s.get_radius() == 1.0f);
	REQUIRE(s.get_center() == glm::vec3{0.0f});
}

TEST_CASE("area","[sphere]")
{
	Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};
	REQUIRE(12.566f == Approx(s.area()).epsilon(0.001));
}

TEST_CASE("volume","[sphere]")
{
	Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};
	REQUIRE(4.189 == Approx(s.volume()).epsilon(0.001));
}

TEST_CASE("print sphere","[sphere]")
{
	Sphere es {"empty_sphere"};
	std::cout << es;
	
	
	Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
	std::cout << s;
}

TEST_CASE("sphere-realintersection","[spehrerealintersecction]"){
	Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},
		Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f,0.0f,-4.0f},1.0f};
	Ray r{glm::vec3{0.0f},glm::vec3{0.0f,0.0f,1.0f}};
	float	distance = 5.0f;
	Intersection inter = s.realintersect(r,distance);
	std::cout<<"-----lalalalalala-----"<<inter;
}
// ----------------------------------
// BOX TESTS
// ----------------------------------

TEST_CASE("constructors of box","[box]")
{
	Box b1 {"name"};
	Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(b1.get_min() == b2.get_min());
	REQUIRE(b1.get_max() == b2.get_max());
}

TEST_CASE("get_min and get_max","[box]")
{
	Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(b2.get_min() == glm::vec3{0.0f});
	REQUIRE(b2.get_max() == glm::vec3{1.0f});
}

TEST_CASE("area of box","[box]")
{
	Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};
	REQUIRE(6.0f == Approx(b2.area()).epsilon(0.001));
}

TEST_CASE("volume of box","[box]")
{
	Box b2 {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(1.0f == Approx(b2.volume()).epsilon(0.001));
}

TEST_CASE("print box","[box]")
{
	Box eb {"empty_box"};
	std::cout << eb;
	
	
	Box b {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};
	std::cout << b;
}

// ----------------------------------
// AUFGABE 5.6 TEST
// ----------------------------------

TEST_CASE("intersectRaySphere", "[intersect]")
{
	//Ray
	glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
	//ray direction has to be normalized !
	//you can use:
		//v = glm::normalize(some_vector);
	glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

	//Sphere
	glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
	float sphere_radius{1.0f};

	float distance{0.0f};
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center,
		sphere_radius * sphere_radius,
		distance);

	REQUIRE(distance == Approx(4.0f));

	Sphere s {"some_sphere", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},
		sphere_center, sphere_radius};

	Ray r {ray_origin,ray_direction};

	s.intersect(r,distance);

	REQUIRE(distance == Approx(4.0f));
}

// ----------------------------------
// AUFGABE 5.8 TEST
// ----------------------------------




// ----------------------------------
// MATERIAL Tests
// ----------------------------------

TEST_CASE("material in place of color struct", "Material")
{
	Color c{0.0f,0.0f,0.0f};
	Material mate1 {};
	std::cout << mate1;

	Material mate2 {"some material",c,c,c,0.0f};
	std::cout << mate2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

// ----------------------------------
// SDFLOADER Tests
// ----------------------------------

TEST_CASE("SDFloader test", "[SDFloader]")
{
	SDFloader loader{};
	Scene s2 {};
	std::string bla = "/home/emil/Documents/RAYTRACER/final_program/raytracer/source/material_input.txt";
	s2 = loader.load(bla);
	std::cout<<s2;
}

// ----------------------------------
// INTERSECT Tests
// ----------------------------------

TEST_CASE("intersection tests","Box")
{
	Color c {0.0f,0.0f,0.0f};

	Ray ray1 {glm::vec3(0.5f,0.5f,1.0f), 
			glm::vec3{0.0f,0.0f,-4.0f}};

	Ray ray2 {glm::vec3{0.0f}, //aus koordinatenursprung
			glm::vec3{1.0f,1.0f,-2.0f}}; //schräg in anderem winkel in -z richtung

	Ray ray3 {glm::vec3{1.0f,1.0f,-2.0f}, //von innerhalb der Box aus
			glm::vec3{0.0f,0.0f,-1.0f}}; // gerade in -z Richtung schauend

	Ray ray3b {glm::vec3{1.0f,1.0f,-2.0f}, //von innerhalb der Box aus
			glm::vec3{1.0f,1.0f,-1.0f}}; // schräg in -z Richtung schauend

	Ray ray4 {glm::vec3{0.0f}, //aus koordinatenursprung
			glm::vec3{0.0f,0.0f,-2.0f}}; //entlang -z Achse

	Ray ray4b {glm::vec3{1.0f,1.0f,0.0f}, //from (1|1|0)
			glm::vec3{0.0f,0.0f,-2.0f}}; //parallel -z Achse, gerade

	Box box {"test_box",
		Material{"",c,c,c, 0.0f},
		glm::vec3{0.0f,0.0f,-1.0f},	//min
		glm::vec3{2.0f,2.0f,-3.0f}	//max
	};

	std::cout << box;

	float distance = 4.0f;
	std::cout << "\n\nray -----------MUYIMPORTANTE---------: \n";
	bool hit = box.intersect(ray1,distance);
	std::cout << "\nHit? " << hit << " Distance: " << distance;
	
	distance = 0.0f;
	std::cout << "\n\nray 2: \n";
	hit = box.intersect(ray2,distance);
	std::cout << "\n\nHit? " << hit << " Distance: " << distance;

	distance = 0.0f;
	std::cout << "\n\nray 3: \n";
	hit = box.intersect(ray3,distance);
	std::cout << "\n\nHit? " << hit << " Distance: " << distance <<"\n";
	
	distance = 0.0f;
	std::cout << "\n\nray 3b: \n";
	hit = box.intersect(ray3b,distance);
	std::cout << "\n\nHit? " << hit << " Distance: " << distance <<"\n";

	distance = 0.0f;
	std::cout << "\n\nray 4: \n";
	hit = box.intersect(ray4,distance);
	std::cout << "\n\nHit? " << hit << " Distance: " << distance <<"\n";

	distance = 0.0f;
	std::cout << "\n\nray 4b: \n";
	hit = box.intersect(ray4b,distance);
	std::cout << "\n\nHit? " << hit << " Distance: " << distance <<"\n";
}

TEST_CASE("nother test", "intersect")
{
	//Strahl z-Richtung
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	Ray ray{ray_origin, ray_direction};
	float distance{0.0};

	Box box{"Zu schneidende Box", Material{},
		glm::vec3{-2,-2,1}, glm::vec3{2,6,5}};
	REQUIRE(!box.intersect(ray, distance));
	REQUIRE(distance == 0.0f);
}

TEST_CASE("no intersection", "intersect")
{
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	Ray ray{ray_origin, ray_direction};
	float distance{0.0};

	Box box{"Nicht zu schneidende Box",
		Material{}, glm::vec3{-2,2,1}, glm::vec3{2,6,5}};
	REQUIRE(!box.intersect(ray, distance));
}

TEST_CASE("vektor normalization", "glm::vec3")
{
	glm::vec3 v {0.0f,0.0f,2.0f};
	glm::vec3 norm {0.0f};

	std::cout << "\n" << v.x << ", " << v.y
		<< ", "  << v.z;
	
	norm = glm::normalize(v);

	std::cout << "\n" << norm.x << ", " << norm.y
		<< ", "  << norm.z<<"\n";
}
// - box realintersection
TEST_CASE("realintersectt","[realintersectt]"){
	Ray ray1 {glm::vec3(0.5f,0.5f,2.0f), glm::vec3{0.0f,0.0f,-4.0f}};Color c {0.0f,0.0f,0.0f};
	
	Box box {"test_box",
		Material{"",c,c,c, 0.0f},
		glm::vec3{0.0f,0.0f,-1.0f},	//min
		glm::vec3{2.0f,2.0f,-3.0f}	//max
	};
	
	float dist = 4.0f;
	Intersection inter = box.realintersect(ray1,dist);
	std::cout<<"\n---Box Realintersection---\n"<<"\nBox: "<<box<<"\n"<<inter;
}

// ----------------------------------
// LIGHT Tests
// ----------------------------------


TEST_CASE("light construction", "[lightconstruction]"){
	Light light1 = Light();
	Color clr = Color{1.0f,1.0f,1.0f};
	Light light2 = Light("light2",glm::vec3{0.0f},clr);
	REQUIRE(light2.getName()=="light2");
	REQUIRE(light2.getColor()==clr);
	REQUIRE(light2.getSource()==glm::vec3{0.0f});
	REQUIRE(light1.getName()=="noname_light");
	REQUIRE(light1.getColor()==Color());
	REQUIRE(light1.getSource()==glm::vec3{0.0f});
}

// ----------------------------------
// INTERSECTION Tests
// ----------------------------------


TEST_CASE("intersection constructor","[intersectionconstructor]"){ 
	Intersection inter1 = Intersection();
	Sphere s {"SHAPEE NUMERO UNO", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
	std::shared_ptr<Shape>	f = std::make_shared<Sphere>(s);
	Intersection inter2 = Intersection{glm::vec3{1.0f},glm::vec3{1.0f},1.0f,true,f};//important!
	//REQUIRE(glm::vec3{1.0f}==glm::vec3(1.0f,1.0f,1.0f));
	REQUIRE(inter1.getNormal()==glm::vec3{0.0f});
	REQUIRE(inter2.getNormal()==glm::vec3(1.0f,1.0f,1.0f));
	REQUIRE(inter2.isHit());
	//INTERSECTION print
	std::cout<<"\n--------------------Intersection print---------------------\n"<<inter2;
	
	
}

TEST_CASE("anotherintersectreal","[blub]"){
	Sphere sphere1{"sphere1", Material{"weiß",Color{1.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{0.0f,0.0f,0.0f},50.0f};
	
	Ray rr{glm::vec3(0.0f),glm::vec3{-10.0f,-62.0f,-120.0f}};
	float distance = 120;
	Intersection inter = sphere1.realintersect(rr,distance);
	std::cout<<"\n-------------------intersec hhhh-------------\n"<<sphere1.intersect(rr,distance)<<inter;
}

// ----------------------------------
// RAY Tests
// ----------------------------------


TEST_CASE("ray copy","[raycopy]"){
	//REQUIRE(glm::vec3(1.0f,0.0f,0.0f).length()==1.0f); WRONG!
	
	Ray ray1 {glm::vec3(1.0f,0.0f,0.0f),glm::vec3{1.0f,1.0f,-1.0f}}; 
	Ray ray2(ray1);
	REQUIRE(ray1.m_direction==ray2.m_direction);
	ray1.setDirection(ray2.m_direction);
	Ray newray3 = ray1.newLength(1);
	REQUIRE(newray3.getLength()==Approx(1.0f));
	//winkel
	Ray ray3 {glm::vec3{0.0f},glm::vec3{0.0f,0.0f,-1.0f}}; 
	Ray ray4 {glm::vec3{0.0f},glm::vec3{1.0f,0.0f,0.0f}};
	float winkel= ray3.rayWinkel(ray4.m_direction);
	REQUIRE(winkel==Approx(90));
	
}

TEST_CASE("ray spiegel","[rayspiegel]"){
	Ray ray1 {glm::vec3(0.0f),glm::vec3{1.0f,1.0f,1.0f}}; 
	Ray ray2 {glm::vec3(0.0f),glm::vec3{0.0f,0.0f,1.0f}}; 
	glm::vec3 hi =ray1.BProjectOnA(ray2.m_direction,ray1.m_direction);
	REQUIRE(hi.x==Approx(0.33333));
	REQUIRE(hi.y==Approx(0.33333));
	REQUIRE(hi.z==Approx(0.33333));
	Ray ray3 = ray1.mirror(ray2);
	REQUIRE(ray3.m_direction.x<0);
	REQUIRE(ray3.m_direction.y<0);
	REQUIRE(ray3.m_direction.z>0);
	
	
	
}

TEST_CASE("ray spiegecl","[rayspiegecl]"){
	Ray ray1 {glm::vec3(0.0f),glm::vec3{10.0f,30.0f,10.0f}}; 
	Ray ray2 {glm::vec3(0.0f),glm::vec3{0.0f,0.0f,10.0f}}; 
	glm::vec3 hi =ray1.BProjectOnA(ray1.m_direction,ray2.m_direction);
	Ray holder{glm::vec3{0.0f},hi};
	Ray ray3 = ray1.mirror(ray2);
	std::cout<<"\n----------------PROJEFCTION DOESNT WORK WT---------mirrorRay----------------\n"<<ray1<<ray2<<holder<<ray3;
}	
	
TEST_CASE("ray refraction","[rayfraction]"){
	Ray ray1 {glm::vec3(0.0f),glm::vec3{10.0f,30.0f,10.0f}}; 
	Ray ray2 {glm::vec3(0.0f),glm::vec3{0.0f,0.0f,10.0f}}; 
	Ray ray3 = ray1.refractionRay(ray2);
	std::cout<<"\n----------------REFRACTION----------------\n"<<ray1<<ray2<<ray3;
	
	
}
// ----------------------------------
// CAMERA Tests
// ----------------------------------

TEST_CASE("blablacamera","[yoloo]"){
	Camera cam = Camera();
	float cc= cam.getDirection().z;
	REQUIRE(cc==Approx(-1));
	std::cout <<cam;

}


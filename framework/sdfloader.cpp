#include "sdfloader.hpp"

	//SDFloader::SDFloader() :
	//m_vecMaterials{std::vector<Material> vec_material}
	//	{};
	
	/*
	void SDFloader::addToMaterial(Material const& material)
	{
		vec_material.push_back(material);
	}
	*/

	Scene SDFloader::load(std::string const& inputFile)
	{
		Scene scene{};
		std::fstream input;
		input.open(inputFile);

		if(input.is_open())
		{
			std::string line;
			std::string word;
			
			while(std::getline(input, line))
			{	
				std::stringstream stream;
				stream << line; 
				stream >> word;	
				if(word == "define")
				{
					stream >> word;

					if(word == "material")
					{
						Material in_material;
						
						stream >> in_material.m_name;
						stream >> in_material.m_ka.r;
						stream >> in_material.m_ka.g;
						stream >> in_material.m_ka.b;
						stream >> in_material.m_kd.r;
						stream >> in_material.m_kd.g;
						stream >> in_material.m_kd.b;
						stream >> in_material.m_ks.r;
						stream >> in_material.m_ks.g;
						stream >> in_material.m_ks.b;
						stream >> in_material.m_opacity;

						//addToMaterial(material);
						scene.m_materials[in_material.m_name]=in_material;	
						std::cout<<"\nMaterial Added: "<< in_material.m_name;

					}
					if(word == "shape"){
					
						stream>>word;
						if(word=="sphere"){
							std::string name;
							stream>>name;				
								
							glm::vec3 ctr;
							stream>>ctr.x;
							stream>>ctr.y;
							stream>>ctr.y;
							float r;
							stream>>r;
							std::string material;
							stream>>material;
							Material mat = scene.m_materials[material];
							Sphere sp{name,mat,ctr,r};
							scene.m_shapes.push_back(std::make_shared<Sphere>(sp));
							std::cout<<"\nSphere Added: "<< name;
						}
					if(word == "box"){
							std::string name;
							stream>>name;				
							
							glm::vec3 min;
							glm::vec3 max;
							stream>>min.x;
							stream>>min.y;
							stream>>min.z;
							stream>>max.x;
							stream>>max.y;
							stream>>max.z;
							std::string material;
							stream>>material;
							Material mat = scene.m_materials[material];
							Box box{name,mat,min,max};
							scene.m_shapes.push_back(std::make_shared<Box>(box));
							std::cout<<"\nBox Added: "<< name;
						}
					}
					if(word=="ambient"){
						Color clr;
						stream>>clr.r;
						stream>>clr.g;
						stream>>clr.b;
						scene.m_ambient_light = clr;
					}
					if(word=="light"){
						std::string name;
						stream>>name;
						glm::vec3 position;
						stream>>position.x;
						stream>>position.y;
						stream>>position.z;		
						float radius;
						stream>> radius;
						Color clr;
						stream>>clr.r;
						stream>>clr.g;
						stream>>clr.b;
						float intensity;
						stream>>intensity;
						Light lght{name,position,radius,clr,intensity};
						scene.m_lights.push_back(std::make_shared<Light>(lght));
					}
				}
			}
			return scene;
		}
		else
		{
			std::cout << "Couldn't find file. Empty Scene returned!" << std::endl;
			return scene;
		}
	}
	


#include "Assets.hpp"
#include <iostream>

Assets::Assets()
{
}

Assets::Assets(std::filesystem::path& folderPath)
{
	init(folderPath);
}

void Assets::init(std::filesystem::path& folderPath)
{
	loadTexturesRecursive(folderPath);
	loadFontsRecursive(folderPath);
}

void Assets::addTexture(const std::string& name, const std::string& path) {
	sf::Texture texture;

	if (!texture.loadFromFile(path)) {
		std::cout << "texture from path " << path << " was not loaded\n";
	}

	m_textures[name] = texture;
}

//void Assets::addAnimation(const std::string& name, Animation&& animation)
//{
//	m_animations[name] = std::move(animation);
//}

void Assets::addSound(const std::string& name, const std::string& path)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(path)) {
		std::cout << "sound from path " << path << " was not loaded\n";
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	m_sounds[name] = sound;
}

void Assets::addFont(const std::string& name, const std::string& path)
{
	sf::Font font;

	if (!font.loadFromFile(path)) {
		std::cout << "font from path " << path << " was not loaded\n";
	}

	m_fonts[name] = font;
}

const sf::Texture& Assets::getTexture(const std::string& name) const
{
	return m_textures.at(name);
}

//const Animation& Assets::getAnimation(const std::string& name) const
//{
//	return m_animations.at(name);
//}

const sf::Sound& Assets::getSound(const std::string& name) const
{
	return m_sounds.at(name);
}

const sf::Font& Assets::getFont(const std::string& name) const
{
	return m_fonts.at(name);
}

void Assets::loadTexturesFromPath(std::string& folderPath)
{
	std::cout << "Current working directory: " << folderPath << "\n";

	if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath))
	{
		for (auto& entry : std::filesystem::directory_iterator(folderPath))
		{
			// Get the file path
			auto filePath = entry.path();

			// Access individual components of the path
			auto directory = filePath.parent_path().string();
			auto filename = filePath.filename().string();
			auto stem = filePath.stem().string();
			auto extension = filePath.extension().string();

			// print the components
			std::cout << "directory: " << directory << "\n";
			std::cout << "filename: " << filename << "\n";
			std::cout << "stem: " << stem << "\n";
			std::cout << "extension: " << extension << "\n";

			// Print the file path
			std::cout << "\n";

			sf::Texture texture;
			if (!texture.loadFromFile(filePath.string()))
			{
				// error..
			}
			else
			{
				m_textures[stem] = texture;
			}
		}
	}
	else 
	{
		std::cerr << "Directory not found." << "\n";
	}
}

void Assets::loadTexturesRecursive(const std::filesystem::path& folderPath)
{
	for (auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		auto filePath = entry.path();

		if (std::filesystem::is_directory(filePath))
		{
			// Recursive call for subdirectories
			loadTexturesRecursive(filePath);
		}
		else
		{
			auto extension = filePath.extension().string();

			// Only do .png files (for now)
			if (extension == ".png")
			{
				auto stem = filePath.stem().string();

				sf::Texture texture;
				if (!texture.loadFromFile(filePath.string()))
				{
					// Handle error..
					std::cerr << "Error loading texture from file: " << filePath << "\n";
				}
				else
				{
					m_textures[stem] = texture;
				}
			}
		}
	}
}

void Assets::loadFontsRecursive(const std::filesystem::path& folderPath)
{
	for (auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		auto filePath = entry.path();

		if (std::filesystem::is_directory(filePath))
		{
			// Recursive call for subdirectories
			loadFontsRecursive(filePath);
		}
		else
		{
			auto extension = filePath.extension().string();

			// Only do .ttf files (for now)
			if (extension == ".ttf")
			{
				auto stem = filePath.stem().string();

				sf::Font font;
				if (!font.loadFromFile(filePath.string()))
				{
					// Handle error..
					std::cerr << "Error loading font from file: " << filePath << "\n";
				}
				else
				{
					m_fonts[stem] = font;
				}
			}
		}
	}
}

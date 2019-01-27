#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

struct TileSheet
{
	TileSheet(const std::string& name, int tileSize, int columns);

	sf::IntRect getTileLocation(int tileID) const;

	const int m_tileSize;
	const int m_columns;
	sf::Texture m_texture;
};

class TileLayer
{
public:
	TileLayer(const std::vector<std::vector<int>>& tileLayer, const std::string& tileSheetName, sf::Vector2i mapSize);

	const std::string& getName() const;
	void draw(const TileSheet& tileSheet, sf::RenderWindow& window) const;

private:
	const std::string m_name;
	const std::vector<std::vector<int>> m_tileLayer;
	const sf::Vector2i m_mapSize;
};

struct Level
{
public:
	Level(const std::vector<TileLayer>& tileLayers, const std::unordered_map<std::string, TileSheet>& tileSheets);

	void draw(sf::RenderWindow& window) const;

	const std::vector<TileLayer> m_tileLayers;
	const std::unordered_map<std::string, TileSheet> m_tileSheets;
};